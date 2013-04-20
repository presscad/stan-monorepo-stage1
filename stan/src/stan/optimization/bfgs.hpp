#ifndef __STAN__OPTIMIZATION__BFGS_HPP__
#define __STAN__OPTIMIZATION__BFGS_HPP__

#include <stan/model/prob_grad.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <cstdlib>
#include <cmath>

namespace stan {
  namespace optimization {
    namespace {
      template<typename FunctorType, typename Scalar, typename XType>
      int BTLineSearch(FunctorType &func,
                       Scalar &alpha, 
                       XType &x1, Scalar &f1, XType &gradx1,
                       const XType &p,
                       const XType &x0, const Scalar &f0, const XType &gradx0,
                       const Scalar &rho, const Scalar &c,
                       const Scalar &minAlpha)
      {
        const Scalar cdfdp(c*gradx0.dot(p));
        int ret;
        
        while (1) {
          x1 = x0 + alpha*p;
          ret = func(x1,f1);
          if (ret!=0 && f1 <= f0 + alpha*cdfdp)
            break;
          else
            alpha *= rho;
          
          if (alpha < minAlpha)
            return 1;
        }
        func.df(x1,gradx1);
        return 0;
      }
      
      template<typename FunctorType, typename Scalar, typename XType>
      int WolfLSZoom(Scalar &alpha, XType &newX, Scalar &newF, XType &newDF,
                     FunctorType &func,
                     const XType &x, const Scalar &f, const Scalar &dfp,
                     const Scalar &c1dfp, const Scalar &c2dfp, const XType &p,
                     Scalar alo, Scalar aloF, Scalar aloDFp,
                     Scalar ahi, Scalar ahiF, Scalar ahiDFp,
                     const Scalar &min_range)
      {
        Scalar d1, d2, newDFp;
        int itNum(0);
        
        while (1) {
          itNum++;
          
          if (std::abs(alo-ahi) < min_range)
            return 1;
          
          if (itNum%5 == 0) {
            alpha = 0.5*(alo+ahi);
          }
          else {
            // Perform cubic interpolation to determine next point to try
            d1 = aloDFp + ahiDFp - 3*(aloF-ahiF)/(alo-ahi);
            d2 = std::sqrt(d1*d1 - aloDFp*ahiDFp);
            if (ahi < alo)
              d2 = -d2;
            alpha = ahi - (ahi - alo)*(ahiDFp + d2 - d1)/(ahiDFp - aloDFp + 2*d2);
            if (alpha < std::min(alo,ahi) || alpha > std::max(alo,ahi))
              alpha = 0.5*(alo+ahi);
          }
          
          newX = x + alpha*p;
          while (func(newX,newF,newDF)) {
            alpha = 0.5*(alpha+std::min(alo,ahi));
            if (std::abs(alo-alpha) < min_range)
              return 1;
            newX = x + alpha*p;
          }
          newDFp = newDF.dot(p);
          if (newF > (f + alpha*c1dfp) || newF >= aloF) {
            ahi = alpha;
            ahiF = newF;
            ahiDFp = newDFp;
          }
          else {
            if (std::abs(newDFp) <= -c2dfp)
              break;
            if (newDFp*(ahi-alo) >= 0) {
              ahi = alo;
              ahiF = aloF;
              ahiDFp = aloDFp;
            }
            alo = alpha;
            aloF = newF;
            aloDFp = newDFp;
          }
        }
        return 0;
      }
      
      template<typename FunctorType, typename Scalar, typename XType>
      int WolfeLineSearch(FunctorType &func,
                          Scalar &alpha,
                          XType &x1, Scalar &f1, XType &gradx1,
                          const XType &p,
                          const XType &x0, const Scalar &f0, const XType &gradx0,
                          const Scalar &c1, const Scalar &c2,
                          const Scalar &minAlpha, const Scalar &maxAlpha)
      {
        const Scalar dfp(gradx0.dot(p));
        const Scalar c1dfp(c1*dfp);
        const Scalar c2dfp(c2*dfp);
        
        Scalar alpha0(minAlpha);
        Scalar alpha1(alpha);
        
        Scalar prevF(f0);
        XType prevDF(gradx0);
        Scalar prevDFp(dfp);
        Scalar newDFp;
        
        int retCode = 0, nits = 0, ret;
        
        while (1) {
          x1.noalias() = x0 + alpha1*p;
          ret = func(x1,f1,gradx1);
          if (ret!=0) {
            alpha1 = 0.5*(alpha0+alpha1);
            continue;
          }
          newDFp = gradx1.dot(p);
          if ((f1 > f0 + alpha*c1dfp) || (f1 >= prevF && nits > 0)) {
            retCode = WolfLSZoom(alpha, x1, f1, gradx1,
                                 func,
                                 x0, f0, dfp,
                                 c1dfp, c2dfp, p,
                                 alpha0, prevF, prevDFp,
                                 alpha1, f1, newDFp,
                                 1e-16);
            break;
          }
          if (std::abs(newDFp) <= -c2dfp) {
            alpha = alpha1;
            break;
          }
          if (newDFp >= 0) {
            retCode = WolfLSZoom(alpha, x1, f1, gradx1,
                                 func,
                                 x0, f0, dfp,
                                 c1dfp, c2dfp, p,
                                 alpha1, f1, newDFp,
                                 alpha0, prevF, prevDFp,
                                 1e-16);
            break;
          }
          
          alpha0 = alpha1;
          prevF = f1;
          std::swap(prevDF,gradx1);
          prevDFp = newDFp;
          
          alpha1 = std::min(2.0*alpha0,maxAlpha);
          
          nits++;
        }
        return retCode;
      }

      template<typename FunctorType, typename Scalar = double,
               int DimAtCompile = Eigen::Dynamic,
               int LineSearchMethod = 1>
      class BFGSMinimizer {
      public:
        typedef Eigen::Matrix<Scalar,DimAtCompile,1> VectorT;
        typedef Eigen::Matrix<Scalar,DimAtCompile,DimAtCompile> HessianT;
        
      protected:
        FunctorType &_func;
        VectorT _gk, _gk_1, _xk_1, _xk, _s;
        Scalar _fk, _fk_1, _alpha, _alpha0;
        Eigen::LDLT< HessianT > _ldlt;
        size_t _itNum;
        
      public:
        const Scalar &curr_f() const { return _fk; }
        const VectorT &curr_x() const { return _xk; }
        const VectorT &curr_g() const { return _gk; }
        
        const Scalar &prev_f() const { return _fk_1; }
        const VectorT &prev_x() const { return _xk_1; }
        const VectorT &prev_g() const { return _gk_1; }

        const Scalar &init_step_size() const { return _alpha0; }
        const Scalar &step_size() const { return _alpha; }
        
        struct BFGSOptions {
          BFGSOptions() {
            maxIts = 10000;
            rho = 0.75;
            c1 = 1e-4;
            c2 = 0.9;
            minStep = 1e-16;
            minGradNorm = 1e-6;
            minAlpha = 1e-12;
            maxAlpha = 5.0;
            alpha0 = 1e-3;
          }
          size_t maxIts;
          Scalar rho;
          Scalar c1;
          Scalar c2;
          Scalar minStep;
          Scalar minGradNorm;
          Scalar alpha0;
          Scalar minAlpha;
          Scalar maxAlpha;
        } _opts;
        
        
        BFGSMinimizer(FunctorType &f) : _func(f) { }
        
        void initialize(const VectorT &x0) {
          int ret;
          _xk = x0;
          ret = _func(_xk,_fk,_gk);
          if (ret) {
            throw std::runtime_error("Error evaluating initial BFGS point.");
          }
          
          _itNum = 0;
        }
        
        int step() {
          Scalar gradNorm, thetak, skyk, skBksk;
          VectorT sk, yk, Bksk, rk;
          int retCode;
          int resetB(0);
          
          _itNum++;
          
          if (_itNum > 1)
            _alpha0 = _alpha = std::min(1.0, 1.1*(2*(_fk - _fk_1)/_gk_1.dot(_s)));
          else
            _alpha0 = _alpha = 1.0;

          if (_itNum == 1 || !(_ldlt.info() == Eigen::Success && _ldlt.isPositive() && (_ldlt.vectorD().array() > 0).all()))
            resetB = 1;
          else
            resetB = 0;
          
          while (true) {
            if (resetB) {
              Scalar Bscale;
              if (_itNum == 1 || resetB == 2) {
                Bscale = 1.0/_opts.alpha0;
              }
              else {
                std::cerr << "BFGS Hessian reset" << std::endl;
                Bscale = _ldlt.vectorD().maxCoeff();
              }
              // Not needed, as ldlt is never used if resetB == true
  //            _ldlt.compute(Bscale*HessianT::Identity(_xk.size(),_xk.size()));
              _s = -_gk/Bscale;
            }
            else {
              _s = -_ldlt.solve(_gk);
            }
            
            if (LineSearchMethod == 0) {
              retCode = BTLineSearch(_func, _alpha, _xk_1, _fk_1, _gk_1,
                                     _s, _xk, _fk, _gk, _opts.rho, 
                                     _opts.c1, _opts.minAlpha);
            }
            else if (LineSearchMethod == 1) {
              retCode = WolfeLineSearch(_func, _alpha, _xk_1, _fk_1, _gk_1,
                                        _s, _xk, _fk, _gk,
                                        _opts.c1, _opts.c2, 
                                        _opts.minAlpha, _opts.maxAlpha);
            }
            if (retCode) {
              if (resetB) {
                // Line-search failed and nothing left to try
                retCode = -1;
                return retCode;
              }
              else {
                // Line-search failed, try ditching the Hessian approximation
                resetB = 2;
                _alpha0 = _alpha = 1.0;
                continue;
              }
            }
            else {
              break;
            }
          }
          std::swap(_fk,_fk_1);
          _xk.swap(_xk_1);
          _gk.swap(_gk_1);
          
          gradNorm = _gk.squaredNorm();
          sk.noalias() = _xk - _xk_1;
          if (sk.array().abs().maxCoeff() <= _opts.minStep) {
            if (gradNorm <= _opts.minGradNorm) {
              retCode = 1;
            }
            else {
              retCode = 2;
            }
          }
          else {
            retCode = 0;
          }
          
          yk.noalias() = _gk - _gk_1;
          skyk = yk.dot(sk);
          if (resetB) {
            Scalar B0fact = yk.squaredNorm()/skyk;
            _ldlt.compute(B0fact*HessianT::Identity(_xk.size(),_xk.size()));
            Bksk.noalias() = B0fact*sk;
          }
          else {
            Bksk = _ldlt.transpositionsP().transpose()*(_ldlt.matrixL()*(_ldlt.vectorD().asDiagonal()*(_ldlt.matrixU()*(_ldlt.transpositionsP()*sk))));
          }
          skBksk = sk.dot(Bksk);
          if (skyk >= 0.2*skBksk) {
            // Full update
            thetak = 1;
            rk = yk;
          }
          else {
            // Damped update (Procedure 18.2)
            thetak = 0.8*skBksk/(skBksk - skyk);
            rk = thetak*yk + (1.0 - thetak)*Bksk;
            std::cerr << "BFGS Damped Hessian update" << std::endl;
          }
          _ldlt.rankUpdate(rk,1.0/sk.dot(rk));
          _ldlt.rankUpdate(Bksk,-1.0/skBksk);
          
          return retCode;
        }
        
        int minimize(VectorT &x0) {
          int retcode;
          initialize(x0);
          while (!(retcode = step()));
          x0 = _xk;
          return retcode;
        }
      };
    }
    
    class ModelAdaptor {
    private:
      stan::model::prob_grad& _model;
      std::vector<int> _params_i;
      std::ostream* _output_stream;
      std::vector<double> _x, _g;
      size_t _fevals;

    public:
      ModelAdaptor(stan::model::prob_grad& model,
                   const std::vector<int>& params_i,
                   std::ostream* output_stream)
      : _model(model), _params_i(params_i), _output_stream(output_stream), _fevals(0) {}
                  
      size_t fevals() const { return _fevals; }
      int operator()(const Eigen::Matrix<double,Eigen::Dynamic,1> &x, double &f) {
        _x.resize(x.size());
        for (size_t i = 0; i < x.size(); i++)
          _x[i] = x[i];

        try {
          f = -_model.log_prob(_x, _params_i, _output_stream);
        } catch (const std::exception& e) {
          std::cerr << "Error evaluating model log probability:" << std::endl
                    << e.what() << std::endl;
          return 1;
        }

        if (boost::math::isfinite(f))
          return 0;
        else {
          std::cerr << "Error evaluating model log probability:" << std::endl
                    << "Non-finite function evaluation." << std::endl;
          return 2;
        }
      }
      int operator()(const Eigen::Matrix<double,Eigen::Dynamic,1> &x, double &f, Eigen::Matrix<double,Eigen::Dynamic,1> &g) {
        _x.resize(x.size());
        for (size_t i = 0; i < x.size(); i++)
          _x[i] = x[i];
        
        _fevals++;

        try {
          f = -_model.grad_log_prob(_x, _params_i, _g, _output_stream);
        } catch (const std::exception& e) {
          std::cerr << "Error evaluating model log probability:" << std::endl
                    << e.what() << std::endl;
          return 1;
        }

        g.resize(_g.size());
        for (size_t i = 0; i < _g.size(); i++) {
          if (!boost::math::isfinite(_g[i])) {
            std::cerr << "Error evaluating model log probability:" << std::endl
                      << "Non-finite gradient." << std::endl;
            return 3;
          }
          g[i] = -_g[i];
        }

        if (boost::math::isfinite(f))
          return 0;
        else {
          std::cerr << "Error evaluating model log probability:" << std::endl
                    << "Non-finite function evaluation." << std::endl;
          return 2;
        }
      }
      int df(const Eigen::Matrix<double,Eigen::Dynamic,1> &x, Eigen::Matrix<double,Eigen::Dynamic,1> &g) {
        double f;
        return (*this)(x,f,g);
      }
    };
    
    class BFGSLineSearch : public BFGSMinimizer<ModelAdaptor> {
    private:
      ModelAdaptor _adaptor;
      
    public:
      BFGSLineSearch(stan::model::prob_grad& model,
                     const std::vector<double>& params_r,
                     const std::vector<int>& params_i,
                     std::ostream* output_stream = 0)
      : BFGSMinimizer<ModelAdaptor>(_adaptor),
       _adaptor(model,params_i,output_stream)
      {

        Eigen::Matrix<double,Eigen::Dynamic,1> x;
        x.resize(params_r.size());
        for (size_t i = 0; i < params_r.size(); i++)
          x[i] = params_r[i];
        initialize(x);
      }

      size_t grad_evals() { return _adaptor.fevals(); }
      double logp() { return -curr_f(); }
      void grad(std::vector<double>& g) { 
        const BFGSMinimizer<ModelAdaptor>::VectorT &cg(curr_g());
        g.resize(cg.size());
        for (size_t i = 0; i < cg.size(); i++)
          g[i] = -cg[i];
      }
      void params_r(std::vector<double>& x) {
        const BFGSMinimizer<ModelAdaptor>::VectorT &cx(curr_x());
        x.resize(cx.size());
        for (size_t i = 0; i < cx.size(); i++)
          x[i] = cx[i];
      }
    };

  }

}

#endif
