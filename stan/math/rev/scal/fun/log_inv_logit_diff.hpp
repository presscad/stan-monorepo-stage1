#ifndef STAN_MATH_REV_SCAL_FUN_LOG_INV_LOGIT_DIFF_HPP
#define STAN_MATH_REV_SCAL_FUN_LOG_INV_LOGIT_DIFF_HPP

#include <stan/math/rev/core.hpp>
#include <stan/math/prim/scal/fun/log_inv_logit_diff.hpp>

namespace stan {
namespace math {
  using std::exp;

namespace {

class log_inv_logit_diff_vv_vari : public op_vv_vari {
 public:
  log_inv_logit_diff_vv_vari(vari* avi, vari* bvi)
      : op_vv_vari(log_inv_logit_diff(avi->val_, bvi->val_), avi, bvi) {}
  void chain() {
    avi_->adj_ += adj_ * (-exp(avi_->val_)/(exp(bvi_->val_) - exp(avi_->val_))
                          - exp(avi_->val_)/(exp(avi_->val_) + 1.0));

    bvi_->adj_ += adj_ * (-exp(bvi_->val_)/(exp(avi_->val_) - exp(bvi_->val_))
                          - exp(bvi_->val_)/(exp(bvi_->val_) + 1.0));
  }
};

class log_inv_logit_diff_vd_vari : public op_vd_vari {
 public:
  log_inv_logit_diff_vd_vari(vari* avi, double b)
      : op_vd_vari(log_inv_logit_diff(avi->val_, b), avi, b) {}
  void chain() {
    avi_->adj_ += adj_ * (-exp(avi_->val_)/(exp(bd_) - exp(avi_->val_))
                          - exp(avi_->val_)/(exp(avi_->val_) + 1.0));
  }
};

class log_inv_logit_diff_dv_vari : public op_dv_vari {
 public:
  log_inv_logit_diff_dv_vari(double a, vari* bvi)
      : op_dv_vari(log_inv_logit_diff(a, bvi->val_), a, bvi) {}
  void chain() {
    bvi_->adj_ += adj_ * (-exp(bvi_->val_)/(exp(ad_) - exp(bvi_->val_))
                          - exp(bvi_->val_)/(exp(bvi_->val_) + 1.0));
  }
};
}  // namespace

inline var log_inv_logit_diff(const var& a, double b) {
  return var(new log_inv_logit_diff_vd_vari(a.vi_, b));
}

inline var log_inv_logit_diff(const var& a, const var& b) {
  return var(new log_inv_logit_diff_vv_vari(a.vi_, b.vi_));
}

inline var log_inv_logit_diff(double a, const var& b) {
  return var(new log_inv_logit_diff_dv_vari(a, b.vi_));
}

}  // namespace math
}  // namespace stan
#endif
