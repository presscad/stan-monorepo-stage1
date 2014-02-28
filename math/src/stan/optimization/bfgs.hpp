#ifndef __STAN__OPTIMIZATION__BFGS_HPP__
#define __STAN__OPTIMIZATION__BFGS_HPP__

#include <cmath>
#include <cstdlib>
#include <string>

#include <boost/math/special_functions/fpclassify.hpp>

#include <stan/math/matrix/Eigen.hpp>
#include <stan/model/util.hpp>

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
      
      template<typename Scalar>
      Scalar CubicInterp(const Scalar &df0,
                         const Scalar &x1, const Scalar &f1, const Scalar &df1,
                         const Scalar &loX, const Scalar &hiX)
      {
        const Scalar c3((-12*f1 + 6*x1*(df0 + df1))/(x1*x1*x1));
        const Scalar c2(-(4*df0 + 2*df1)/x1 + 6*f1/(x1*x1));
        const Scalar &c1(df0);
        
        const Scalar t_s = std::sqrt(c2*c2 - 2.0*c1*c3);
        const Scalar s1 = - (c2 + t_s)/c3;
        const Scalar s2 = - (c2 - t_s)/c3;
        
        Scalar tmpF;
        Scalar minF, minX;
        
        // Check value at lower bound
        minF = loX*(loX*(loX*c3/3.0 + c2)/2.0 + c1);
        minX = loX;
        
        // Check value at upper bound
        tmpF = hiX*(hiX*(hiX*c3/3.0 + c2)/2.0 + c1);
        if (tmpF < minF) {
          minF = tmpF;
          minX = hiX;
        }
        
        // Check value of first root
        if (loX < s1 && s1 < hiX) {
          tmpF = s1*(s1*(s1*c3/3.0 + c2)/2.0 + c1);
          if (tmpF < minF) {
            minF = tmpF;
            minX = s1;
          }
        }
        
        // Check value of second root
        if (loX < s2 && s2 < hiX) {
          tmpF = s2*(s2*(s2*c3/3.0 + c2)/2.0 + c1);
          if (tmpF < minF) {
            minF = tmpF;
            minX = s2;
          }
        }
        
        return minX;
      }
      template<typename Scalar>
      Scalar CubicInterp(const Scalar &x0, const Scalar &f0, const Scalar &df0,
                         const Scalar &x1, const Scalar &f1, const Scalar &df1,
                         const Scalar &loX, const Scalar &hiX)
      {
        return x0 + CubicInterp(df0,x1-x0,f1-f0,df1,loX-x0,hiX-x0);
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
          
          if (std::fabs(alo-ahi) < min_range)
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
            if (!boost::math::isfinite(alpha) ||
                alpha < std::min(alo,ahi)+0.01*std::fabs(alo-ahi) ||
                alpha > std::max(alo,ahi)-0.01*std::fabs(alo-ahi))
              alpha = 0.5*(alo+ahi);
          }

          newX = x + alpha*p;
          while (func(newX,newF,newDF)) {
            alpha = 0.5*(alpha+std::min(alo,ahi));
            if (std::fabs(std::min(alo,ahi)-alpha) < min_range)
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
            if (std::fabs(newDFp) <= -c2dfp)
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
                          const Scalar &minAlpha)
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
          if (std::fabs(newDFp) <= -c2dfp) {
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
          
//          alpha1 = std::min(2.0*alpha0,maxAlpha);
          alpha1 *= 10.0;
          
          nits++;
        }
        return retCode;
      }

    }

    template<typename Scalar = double>
    class ConvergenceOptions {
    public:
      ConvergenceOptions() {
        maxIts = 10000;
        tolX = 1e-8;
        tolF = 1e-8;
        tolGrad = 1e-8;
      }
      size_t maxIts;
      Scalar tolX;
      Scalar tolF;
      Scalar tolGrad;
    };

    template<typename Scalar = double>
    class LSOptions {
    public:
      LSOptions() {
        rho = 0.75;
        c1 = 1e-4;
        c2 = 0.9;
        minAlpha = 1e-12;
        alpha0 = 1e-3;
      }
      Scalar rho;
      Scalar c1;
      Scalar c2;
      Scalar alpha0;
      Scalar minAlpha;
    };

    template<typename FunctorType, typename Scalar = double,
             int DimAtCompile = Eigen::Dynamic,
             int LineSearchMethod = 1>
    class BFGSMinimizer {
    public:
      typedef Eigen::Matrix<Scalar,DimAtCompile,1> VectorT;
      typedef Eigen::Matrix<Scalar,DimAtCompile,DimAtCompile> HessianT;
      
    protected:
      FunctorType &_func;
      VectorT _gk, _gk_1, _xk_1, _xk, _pk, _pk_1;
      Scalar _fk, _fk_1, _alphak_1;
      Scalar _alpha, _alpha0;
      HessianT _Hk;
      size_t _itNum;
      std::string _note;
      
    public:
      LSOptions<Scalar> _ls_opts;
      ConvergenceOptions<Scalar> _conv_opts;
      
      const Scalar &curr_f() const { return _fk; }
      const VectorT &curr_x() const { return _xk; }
      const VectorT &curr_g() const { return _gk; }
      const VectorT &curr_p() const { return _pk; }
      
      const Scalar &prev_f() const { return _fk_1; }
      const VectorT &prev_x() const { return _xk_1; }
      const VectorT &prev_g() const { return _gk_1; }
      const VectorT &prev_p() const { return _pk_1; }
      Scalar prev_step_size() const { return _pk_1.norm()*_alphak_1; }

      const Scalar &alpha0() const { return _alpha0; }
      const Scalar &alpha() const { return _alpha; }
      const size_t iter_num() const { return _itNum; }
      
      const std::string &note() const { return _note; }
      
      std::string get_code_string(int retCode) {
        switch(retCode) {
          case 0:
            return std::string("Successful step completed");
          case 1:
            return std::string("Convergence detected: change in objective function was below tolerance");
          case 2:
            return std::string("Convergence detected: gradient norm is below tolerance");
          case 3:
            return std::string("Convergence detected: parameter change was below tolerance");
          case 4:
            return std::string("Maximum number of iterations hit, may not be at an optima");
          case -1:
            return std::string("Line search failed to achieve a sufficient decrease, no more progress can be made");
          default:
            return std::string("Unknown termination code");
        }
      }

      
      BFGSMinimizer(FunctorType &f) : _func(f) { }
      
      void initialize(const VectorT &x0) {
        int ret;
        _xk = x0;
        ret = _func(_xk,_fk,_gk);
        if (ret) {
          throw std::runtime_error("Error evaluating initial BFGS point.");
        }
        
        _itNum = 0;
        _note = "";
      }
      
      int step() {
        Scalar gradNorm, skyk, rhok;
        VectorT sk, yk, Bksk, rk;
        int retCode;
        int resetB(0);
        
        _itNum++;

        if (_itNum == 1) {
          resetB = 1;
          _note = "";
        }
        else {
          resetB = 0;
          _note = "";
        }
        
        while (true) {
          if (resetB) {
            // Reset the Hessian approximation
            _pk = -_gk;
          }
          else {
            _pk = -_Hk*_gk;
          }
          
          if (_itNum > 1 && resetB != 2) {
            _alpha0 = _alpha = std::min(1.0,
                                        1.01*CubicInterp(_gk_1.dot(_pk_1),
                                                         _alphak_1,
                                                         _fk - _fk_1,
                                                         _gk.dot(_pk_1),
                                                         _ls_opts.minAlpha, 1.0));
          }
          else {
            _alpha0 = _alpha = _ls_opts.alpha0;
          }
          
          if (LineSearchMethod == 0) {
            retCode = BTLineSearch(_func, _alpha, _xk_1, _fk_1, _gk_1,
                                   _pk, _xk, _fk, _gk, _ls_opts.rho, 
                                   _ls_opts.c1, _ls_opts.minAlpha);
          }
          else if (LineSearchMethod == 1) {
            retCode = WolfeLineSearch(_func, _alpha, _xk_1, _fk_1, _gk_1,
                                      _pk, _xk, _fk, _gk,
                                      _ls_opts.c1, _ls_opts.c2, 
                                      _ls_opts.minAlpha);
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
              _note += "LS failed, BFGS reset; ";
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
        _pk.swap(_pk_1);
        
        gradNorm = _gk.norm();
        sk.noalias() = _xk - _xk_1;
        // Check for convergence
        if (std::fabs(_fk - _fk_1) < _conv_opts.tolF) {
          retCode = 1; // Objective function improvement wasn't sufficient
        }
        else if (gradNorm < _conv_opts.tolGrad) {
          retCode = 2; // Gradient norm was below threshold
        }
        else if (sk.norm() < _conv_opts.tolX) {
          retCode = 3; // Change in x was too small
        }
        else if (_itNum >= _conv_opts.maxIts) {
          retCode = 4; // Max number of iterations hit
        }
        else {
          retCode = 0; // Step was successful more progress to be made
        }
        
        yk.noalias() = _gk - _gk_1;
        skyk = yk.dot(sk);
        rhok = 1.0/skyk;
        if (resetB) {
          Scalar H0fact = skyk/yk.squaredNorm();
          _Hk.noalias() = H0fact*HessianT::Identity(_xk.size(),_xk.size());
          _pk_1 = -H0fact*_gk_1;
          _alphak_1 = _alpha/H0fact;
        }
        else {
          _alphak_1 = _alpha;
        }

        HessianT Hupd(HessianT::Identity(_xk.size(),_xk.size()) - rhok*sk*yk.transpose());
        _Hk = Hupd*_Hk*Hupd.transpose() + rhok*sk*sk.transpose();

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

                                

    template <typename M>
    double lp_no_jacobian(const M& model,
                          std::vector<double>& params_r,
                          std::vector<int>& params_i,
                          std::ostream* o = 0) {
      // FIXME: is this supposed to return the log probability from the model?
      return 0;
    }

    template <class M>
    class ModelAdaptor {
    private:
      M& _model;
      std::vector<int> _params_i;
      std::ostream* _msgs;
      std::vector<double> _x, _g;
      size_t _fevals;

    public:
      ModelAdaptor(M& model,
                   const std::vector<int>& params_i,
                   std::ostream* msgs)
      : _model(model), _params_i(params_i), _msgs(msgs), _fevals(0) {}
                  
      size_t fevals() const { return _fevals; }
      int operator()(const Eigen::Matrix<double,Eigen::Dynamic,1> &x, 
                     double &f) {
        _x.resize(x.size());
        for (Eigen::Matrix<double,Eigen::Dynamic,1>::size_type i = 0; 
             i < x.size(); i++)
          _x[i] = x[i];

        try {
          f = - _model.template log_prob<false,false>(_x,_params_i,
                                                      _msgs);
        } catch (const std::exception& e) {
          if (_msgs)
            (*_msgs) << e.what() << std::endl;
          return 1;
        }

        if (boost::math::isfinite(f))
          return 0;
        else {
          if (_msgs)
            *_msgs << "Error evaluating model log probability: " 
                      "Non-finite function evaluation." << std::endl;
          return 2;
        }
      }
      int operator()(const Eigen::Matrix<double,Eigen::Dynamic,1> &x, 
                     double &f, Eigen::Matrix<double,Eigen::Dynamic,1> &g) {
        _x.resize(x.size());
        for (Eigen::Matrix<double,Eigen::Dynamic,1>::size_type i = 0; 
             i < x.size(); i++)
          _x[i] = x[i];
        
        _fevals++;

        try {
          f = - stan::model::log_prob_grad<true,false>(_model,
                                                       _x, _params_i,
                                                       _g, _msgs);
        } catch (const std::exception& e) {
          if (_msgs)
            (*_msgs) << e.what() << std::endl;
          return 1;
        }

        g.resize(_g.size());
        for (size_t i = 0; i < _g.size(); i++) {
          if (!boost::math::isfinite(_g[i])) {
            if (_msgs)
              *_msgs << "Error evaluating model log probability: " 
                                 "Non-finite gradient." << std::endl;
            return 3;
          }
          g[i] = -_g[i];
        }

        if (boost::math::isfinite(f))
          return 0;
        else {
          if (_msgs)
            *_msgs << "Error evaluating model log probability: " 
                               "Non-finite function evaluation." 
                   << std::endl;
          return 2;
        }
      }
      int df(const Eigen::Matrix<double,Eigen::Dynamic,1> &x, 
             Eigen::Matrix<double,Eigen::Dynamic,1> &g) {
        double f;
        return (*this)(x,f,g);
      }
    };
    
    template <typename M>
    class BFGSLineSearch : public BFGSMinimizer<ModelAdaptor<M> > {
    private:
      ModelAdaptor<M> _adaptor;
    public:
      typedef typename BFGSMinimizer<ModelAdaptor<M> >::VectorT vector_t;
      typedef typename vector_t::size_type idx_t;
      
      BFGSLineSearch(M& model,
                     const std::vector<double>& params_r,
                     const std::vector<int>& params_i,
                     std::ostream* msgs = 0)
        : BFGSMinimizer<ModelAdaptor<M> >(_adaptor),
          _adaptor(model,params_i,msgs)
      {

        Eigen::Matrix<double,Eigen::Dynamic,1> x;
        x.resize(params_r.size());
        for (size_t i = 0; i < params_r.size(); i++)
          x[i] = params_r[i];
        this->initialize(x);
      }

      size_t grad_evals() { return _adaptor.fevals(); }
      double logp() { return -(this->curr_f()); }
      double grad_norm() { return this->curr_g().norm(); }
      void grad(std::vector<double>& g) { 
        const vector_t &cg(this->curr_g());
        g.resize(cg.size());
        for (idx_t i = 0; i < cg.size(); i++)
          g[i] = -cg[i];
      }
      void params_r(std::vector<double>& x) {
        const vector_t &cx(this->curr_x());
        x.resize(cx.size());
        for (idx_t i = 0; i < cx.size(); i++)
          x[i] = cx[i];
      }
    };

  }

}

#endif
