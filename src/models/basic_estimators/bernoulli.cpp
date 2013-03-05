// Code generated by Stan version 1.2

#include <stan/model/model_header.hpp>

namespace bernoulli_model_namespace {

using std::vector;
using std::string;
using std::stringstream;
using stan::agrad::var;
using stan::model::prob_grad_ad;
using stan::math::get_base1;
using stan::math::stan_print;
using stan::io::dump;
using std::istream;
using namespace stan::math;
using namespace stan::prob;
using namespace stan::agrad;

typedef Eigen::Matrix<double,Eigen::Dynamic,1> vector_d;
typedef Eigen::Matrix<double,1,Eigen::Dynamic> row_vector_d;
typedef Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> matrix_d;
typedef Eigen::Matrix<stan::agrad::var,Eigen::Dynamic,1> vector_v;
typedef Eigen::Matrix<stan::agrad::var,1,Eigen::Dynamic> row_vector_v;
typedef Eigen::Matrix<stan::agrad::var,Eigen::Dynamic,Eigen::Dynamic> matrix_v;

class bernoulli_model : public prob_grad_ad {
private:
    int N;
    vector<int> y;
public:
    bernoulli_model(stan::io::var_context& context__,
        std::ostream* pstream__ = 0)
        : prob_grad_ad::prob_grad_ad(0) {
        static const char* function__ = "bernoulli_model_namespace::bernoulli_model(%1%)";
        (void) function__; // dummy call to supress warning
        size_t pos__;
        (void) pos__; // dummy call to supress warning
        std::vector<int> vals_i__;
        std::vector<double> vals_r__;
        context__.validate_dims("data initialization", "N", "int", context__.to_vec());
        N = int(0);
        vals_i__ = context__.vals_i("N");
        pos__ = 0;
        N = vals_i__[pos__++];
        context__.validate_dims("data initialization", "y", "int", context__.to_vec(N));
        stan::math::validate_non_negative_index("y", "N", N);
        y = std::vector<int>(N,int(0));
        vals_i__ = context__.vals_i("y");
        pos__ = 0;
        size_t y_limit_0__ = N;
        for (size_t i_0__ = 0; i_0__ < y_limit_0__; ++i_0__) {
            y[i_0__] = vals_i__[pos__++];
        }
        // validate data
        try { 
            check_greater_or_equal(function__,N,0,"N");
        } catch (std::domain_error& e) { throw std::domain_error(std::string("Invalid value of N: ") + std::string(e.what())); };
        for (int k0__ = 0; k0__ < N; ++k0__) {
            try { 
                check_greater_or_equal(function__,y[k0__],0,"y[k0__]");
                check_less_or_equal(function__,y[k0__],1,"y[k0__]");
            } catch (std::domain_error& e) { throw std::domain_error(std::string("Invalid value of y: ") + std::string(e.what())); };
        }

        // validate transformed data

        set_param_ranges();
    } // dump ctor

    void set_param_ranges() {
        num_params_r__ = 0U;
        param_ranges_i__.clear();
        ++num_params_r__;
    }

    void transform_inits(const stan::io::var_context& context__,
                         std::vector<int>& params_i__,
                         std::vector<double>& params_r__) {
        stan::io::writer<double> writer__(params_r__,params_i__);
        size_t pos__;
        std::vector<double> vals_r__;
        std::vector<int> vals_i__;


        if (!(context__.contains_r("theta")))
            throw std::runtime_error("variable theta missing");
        vals_r__ = context__.vals_r("theta");
        pos__ = 0U;
        context__.validate_dims("initialization", "theta", "double", context__.to_vec());
        double theta(0);
        theta = vals_r__[pos__++];
        writer__.scalar_lub_unconstrain(0,1,theta);
        params_r__ = writer__.data_r();
        params_i__ = writer__.data_i();
    }

    var log_prob(vector<var>& params_r__,
                 vector<int>& params_i__,
                 std::ostream* pstream__ = 0) {

        // Note: this is not a memory leak. Memory will be cleaned up with the arena allocator
        stan::agrad::vari* DUMMY_VARI_PTR__ = new vari(std::numeric_limits<double>::quiet_NaN(),false);
        stan::agrad::var DUMMY_VAR__ = var(DUMMY_VARI_PTR__);
        (void) DUMMY_VAR__;  // suppress unused var warning

        var lp__(0.0);

        // model parameters
        stan::io::reader<var> in__(params_r__,params_i__);

        var theta = in__.scalar_lub_constrain(0,1,lp__);
        (void) theta;  // supress unused variable warning

        // transformed parameters

        // initialized transformed params to avoid seg fault on val access
        

        // validate transformed parameters

        const char* function__ = "validate transformed params %1%";
        (void) function__; // dummy to suppress unused var warning
        // model body
        lp__ += stan::prob::beta_log<true>(theta, 1, 1);
        for (int n = 1; n <= N; ++n) {
            lp__ += stan::prob::bernoulli_log<true>(get_base1(y,n,"y",1), theta);
        }

        return lp__;

    } // log_prob(...var...)


    void get_param_names(std::vector<std::string>& names__) {
        names__.resize(0);
        names__.push_back("theta");
    }


    void get_dims(std::vector<std::vector<size_t> >& dimss__) {
        dimss__.resize(0);
        std::vector<size_t> dims__;
        dims__.resize(0);
        dimss__.push_back(dims__);
    }

    void write_array(std::vector<double>& params_r__,
                     std::vector<int>& params_i__,
                     std::vector<double>& vars__,
                     std::ostream* pstream__ = 0) {
        vars__.resize(0);
        stan::io::reader<double> in__(params_r__,params_i__);
        static const char* function__ = "bernoulli_model_namespace::write_array(%1%)";
        (void) function__; // dummy call to supress warning
        // read-transform, write parameters
        double theta = in__.scalar_lub_constrain(0,1);
        vars__.push_back(theta);

        // declare and define transformed parameters
        double lp__ = 0.0;
        (void) lp__; // dummy call to supress warning


        // validate transformed parameters

        // write transformed parameters

        // declare and define generated quantities


        // validate generated quantities

        // write generated quantities
    }


    void write_csv_header(std::ostream& o__) {
        stan::io::csv_writer writer__(o__);
        writer__.comma();
        o__ << "theta";
        writer__.newline();
    }

    void write_csv(std::vector<double>& params_r__,
                   std::vector<int>& params_i__,
                   std::ostream& o__,
                   std::ostream* pstream__ = 0) {
        stan::io::reader<double> in__(params_r__,params_i__);
        stan::io::csv_writer writer__(o__);
        static const char* function__ = "bernoulli_model_namespace::write_csv(%1%)";
        (void) function__; // dummy call to supress warning
        // read-transform, write parameters
        double theta = in__.scalar_lub_constrain(0,1);
        writer__.write(theta);

        // declare, define and validate transformed parameters
        double lp__ = 0.0;
        (void) lp__; // dummy call to supress warning



        // write transformed parameters

        // declare and define generated quantities


        // validate generated quantities

        // write generated quantities
        writer__.newline();
    }

}; // model

} // namespace

int main(int argc, const char* argv[]) {
    try {
        stan::gm::nuts_command<bernoulli_model_namespace::bernoulli_model>(argc,argv);
    } catch (std::exception& e) {
        std::cerr << std::endl << "Exception: " << e.what() << std::endl;
        std::cerr << "Diagnostic information: " << std::endl << boost::diagnostic_information(e) << std::endl;
        return -1;
    }
}

