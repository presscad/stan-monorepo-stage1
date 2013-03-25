#ifndef __STAN__OPTIMIZATION__NESTEROV__GRADIENT_HPP__
#define __STAN__OPTIMIZATION__NESTEROV__GRADIENT_HPP__

#include <stan/model/prob_grad.hpp>

namespace stan {

  namespace optimization {

    class NesterovGradient {

    private:
      stan::model::prob_grad& model_;
      std::vector<double> x_;
      std::vector<double> y_;
      std::vector<int> z_;
      double logp_;
      std::vector<double> grad_;
      double epsilon_;
      int iteration_;
      std::ostream* output_stream_;

    public:
      void initialize_epsilon() {
        epsilon_ = 1;
        double lastlogp = logp_;
        std::vector<double> lastgrad = grad_;
        std::vector<double> lastx = x_;
        for (size_t i = 0; i < x_.size(); i++)
          x_[i] += epsilon_ * grad_[i];
        logp_ = model_.grad_log_prob(x_, z_, grad_, output_stream_);
        if (logp_ > lastlogp) {
          while (logp_ > lastlogp) {
            lastlogp = logp_;
            lastgrad = grad_;
            lastx = x_;
            epsilon_ *= 2;
            for (size_t i = 0; i < x_.size(); i++)
              x_[i] += epsilon_ * grad_[i];
            logp_ = model_.grad_log_prob(x_, z_, grad_, output_stream_);
          }
          logp_ = lastlogp;
          grad_ = lastgrad;
          x_ = lastx;
          epsilon_ /= 2;
        } else {
          while (!(logp_ > lastlogp)) {
            epsilon_ /= 2;
            for (size_t i = 0; i < x_.size(); i++)
              x_[i] = lastx[i] + epsilon_ * lastgrad[i];
            logp_ = model_.grad_log_prob(x_, z_, grad_, output_stream_);
          }
        }
        y_ = x_;
      }

      NesterovGradient(stan::model::prob_grad& model,
                       const std::vector<double>& params_r,
                       const std::vector<int>& params_i,
                       double epsilon0 = -1,
                       std::ostream* output_stream = 0) :
        model_(model), x_(params_r), y_(params_r), z_(params_i),
        epsilon_(epsilon0), iteration_(0), output_stream_(output_stream) {
        logp_ = model.grad_log_prob(x_, z_, grad_, output_stream_);
        if (epsilon_ == -1)
          initialize_epsilon();
      }

      double logp() { return logp_; }
      void grad(std::vector<double>& g) { g = grad_; }
      void params_r(std::vector<double>& x) { x = y_; }

      double step() {
        iteration_++;
        std::vector<double> lastx = x_;
        double lastlogp = logp_;
        double gradnormsq = 0;
        for (size_t i = 0; i < grad_.size(); i++)
          gradnormsq += grad_[i] * grad_[i];
        epsilon_ *= 2;
        while (!(logp_ > lastlogp + 0.5 * epsilon_ * gradnormsq)) {
          epsilon_ /= 2;
          for (size_t i = 0; i < x_.size(); i++)
            x_[i] = y_[i] + epsilon_ * grad_[i];
          logp_ = model_.log_prob(x_, z_, output_stream_);
        }
        for (size_t i = 0; i < x_.size(); i++)
          y_[i] = x_[i] +
            (iteration_ - 1) / (iteration_ + 2) * (x_[i] - lastx[i]);
        logp_ = model_.grad_log_prob(y_, z_, grad_, output_stream_);
        return logp_;
      }
    };

  }

}

#endif
