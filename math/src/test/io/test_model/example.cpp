// Code generated by Stan version 1.3

#include <stan/model/model_header.hpp>

namespace example_model_namespace {

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

class example_model : public prob_grad_ad {
private:
public:
    example_model(stan::io::var_context& context__,
        std::ostream* pstream__ = 0)
        : prob_grad_ad::prob_grad_ad(0) {
        static const char* function__ = "example_model_namespace::example_model(%1%)";
        (void) function__; // dummy call to supress warning
        size_t pos__;
        (void) pos__; // dummy call to supress warning
        std::vector<int> vals_i__;
        std::vector<double> vals_r__;
        // validate data

        // validate transformed data

        set_param_ranges();
    }

    void set_param_ranges() {
        num_params_r__ = 0U;
        param_ranges_i__.clear();
        ++num_params_r__;
        ++num_params_r__;
    }

    void transform_inits(const stan::io::var_context& context__,
                         std::vector<int>& params_i__,
                         std::vector<double>& params_r__) {
        stan::io::writer<double> writer__(params_r__,params_i__);
        size_t pos__;
        std::vector<double> vals_r__;
        std::vector<int> vals_i__;


        if (!(context__.contains_r("mu1")))
            throw std::runtime_error("variable mu1 missing");
        vals_r__ = context__.vals_r("mu1");
        pos__ = 0U;
        context__.validate_dims("initialization", "mu1", "double", context__.to_vec());
        double mu1(0);
        mu1 = vals_r__[pos__++];
        writer__.scalar_unconstrain(mu1);

        if (!(context__.contains_r("mu2")))
            throw std::runtime_error("variable mu2 missing");
        vals_r__ = context__.vals_r("mu2");
        pos__ = 0U;
        context__.validate_dims("initialization", "mu2", "double", context__.to_vec());
        double mu2(0);
        mu2 = vals_r__[pos__++];
        writer__.scalar_unconstrain(mu2);
        params_r__ = writer__.data_r();
        params_i__ = writer__.data_i();
    }

    var log_prob(vector<var>& params_r__,
                 vector<int>& params_i__,
                 std::ostream* pstream__ = 0) {
      return log_prob_poly<true,var>(params_r__,params_i__,pstream__);
    }

    template <bool propto__, typename T__>
    T__ log_prob_poly(vector<T__>& params_r__,
                      vector<int>& params_i__,
                      std::ostream* pstream__ = 0) {

        T__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning

        T__ lp__(0.0);

        // model parameters
        stan::io::reader<T__> in__(params_r__,params_i__);

        T__ mu1 = in__.scalar_constrain(lp__);
        (void) mu1;  // supress unused variable warning
        T__ mu2 = in__.scalar_constrain(lp__);
        (void) mu2;  // supress unused variable warning

        // transformed parameters

        // initialized transformed params to avoid seg fault on val access
        

        // validate transformed parameters

        const char* function__ = "validate transformed params %1%";
        (void) function__; // dummy to suppress unused var warning
        // model body
        lp__ += stan::prob::normal_log<true>(mu1, 0, 10);
        lp__ += stan::prob::normal_log<true>(mu2, 0, 1);

        return lp__;

    } // log_prob_poly(...var...)


    void get_param_names(std::vector<std::string>& names__) {
        names__.resize(0);
        names__.push_back("mu1");
        names__.push_back("mu2");
    }


    void get_dims(std::vector<std::vector<size_t> >& dimss__) {
        dimss__.resize(0);
        std::vector<size_t> dims__;
        dims__.resize(0);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dimss__.push_back(dims__);
    }

    template <typename RNG>
    void write_array(RNG& base_rng__,
                     std::vector<double>& params_r__,
                     std::vector<int>& params_i__,
                     std::vector<double>& vars__,
                     bool include_tparams__ = true,
                     bool include_gqs__ = true,
                     std::ostream* pstream__ = 0) {
        vars__.resize(0);
        stan::io::reader<double> in__(params_r__,params_i__);
        static const char* function__ = "example_model_namespace::write_array(%1%)";
        (void) function__; // dummy call to supress warning
        // read-transform, write parameters
        double mu1 = in__.scalar_constrain();
        double mu2 = in__.scalar_constrain();
        vars__.push_back(mu1);
        vars__.push_back(mu2);

        if (!include_tparams__) return;
        // declare and define transformed parameters
        double lp__ = 0.0;
        (void) lp__; // dummy call to supress warning


        // validate transformed parameters

        // write transformed parameters

        if (!include_gqs__) return;
        // declare and define generated quantities


        // validate generated quantities

        // write generated quantities
    }

    void write_array_params(std::vector<double>& params_r__,
                            std::vector<int>& params_i__,
                            std::vector<double>& vars__,
                            std::ostream* pstream__ = 0) {
        boost::random::minstd_rand base_rng; // dummy
        write_array(base_rng,params_r__,params_i__,vars__,false,false,pstream__);
    }


    void write_csv_header(std::ostream& o__) {
        stan::io::csv_writer writer__(o__);
        writer__.comma();
        o__ << "mu1";
        writer__.comma();
        o__ << "mu2";
        writer__.newline();
    }

    template <typename RNG>
    void write_csv(RNG& base_rng__,
                   std::vector<double>& params_r__,
                   std::vector<int>& params_i__,
                   std::ostream& o__,
                   std::ostream* pstream__ = 0) {
        stan::io::reader<double> in__(params_r__,params_i__);
        stan::io::csv_writer writer__(o__);
        static const char* function__ = "example_model_namespace::write_csv(%1%)";
        (void) function__; // dummy call to supress warning
        // read-transform, write parameters
        double mu1 = in__.scalar_constrain();
        writer__.write(mu1);
        double mu2 = in__.scalar_constrain();
        writer__.write(mu2);

        // declare, define and validate transformed parameters
        double lp__ = 0.0;
        (void) lp__; // dummy call to supress warning



        // write transformed parameters

        // declare and define generated quantities


        // validate generated quantities

        // write generated quantities
        writer__.newline();
    }

    std::string model_name() {
        return "example_model";
    }


    void constrained_param_names(std::vector<std::string>& param_names__,
                                 bool include_tparams__ = true,
                                 bool include_gqs__ = true) {
        std::stringstream param_name_stream__;
        param_name_stream__.str(std::string());
        param_name_stream__ << "mu1";
        param_names__.push_back(param_name_stream__.str());
        param_name_stream__.str(std::string());
        param_name_stream__ << "mu2";
        param_names__.push_back(param_name_stream__.str());

        if (!include_gqs__ && !include_tparams__) return;

        if (!include_gqs__) return;
    }


    void unconstrained_param_names(std::vector<std::string>& param_names__,
                                   bool include_tparams__ = true,
                                   bool include_gqs__ = true) {
        std::stringstream param_name_stream__;
        param_name_stream__.str(std::string());
        param_name_stream__ << "mu1";
        param_names__.push_back(param_name_stream__.str());
        param_name_stream__.str(std::string());
        param_name_stream__ << "mu2";
        param_names__.push_back(param_name_stream__.str());

        if (!include_gqs__ && !include_tparams__) return;

        if (!include_gqs__) return;
    }

}; // model

} // namespace

int main(int argc, const char* argv[]) {
    try {
        stan::gm::command<example_model_namespace::example_model>(argc,argv);
    } catch (std::exception& e) {
        std::cerr << std::endl << "Exception: " << e.what() << std::endl;
        std::cerr << "Diagnostic information: " << std::endl << boost::diagnostic_information(e) << std::endl;
        return -1;
    }
}

