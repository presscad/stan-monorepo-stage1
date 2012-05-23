#include <stan/mcmc/mcmc_output.hpp>
#include <gtest/gtest.h>

class stanMcmc : public ::testing::Test {
  // R code:
  // R> set.seed(0)
  // R> y <- rnorm(100)
protected:
  virtual void SetUp() {
    std::vector<double> y1(&r_[0], &r_[50]);
    std::vector<double> y2(&r_[50], &r_[100]);
    mcmc_output.add_chain(y1);
    mcmc_output.add_chain(y2);

    factory.addFile("src/test/mcmc/mcmc_output/blocker1.csv");
    factory.addFile("src/test/mcmc/mcmc_output/blocker2.csv");
  }

  stan::mcmc::mcmc_output mcmc_output;
  stan::mcmc::mcmc_output_factory factory;
  static const double r_[100];
};

const double stanMcmc::r_[100] = 
    {1.26295428488079,-0.326233360705649,1.3297992629225,1.2724293214294,0.414641434456408,
     -1.53995004190371,-0.928567034713538,-0.29472044679056,-0.00576717274753696,2.40465338885795,
     0.76359346114046,-0.799009248989368,-1.14765700923635,-0.289461573688223,-0.299215117897316,
     -0.411510832795067,0.252223448156132,-0.891921127284569,0.435683299355719,-1.23753842192996,
     -0.224267885278309,0.377395645981701,0.133336360814841,0.804189509744908,-0.0571067743838088,
     0.503607972233726,1.08576936214569,-0.69095383969683,-1.28459935387219,0.046726172188352,
     -0.235706556439501,-0.542888255010254,-0.433310317456782,-0.649471646796233,0.726750747385451,
     1.1519117540872,0.992160365445798,-0.429513109491881,1.23830410085338,-0.279346281854269,
     1.75790308981071,0.560746090888056,-0.452783972553158,-0.832043296117832,-1.16657054708471,
     -1.0655905803883,-1.563782051071,1.15653699715018,0.83204712857239,-0.227328691424755,
     0.266137361672105,-0.376702718583628,2.44136462889459,-0.795339117255372,-0.0548774737115786,
     0.250141322854153,0.618243293566247,-0.172623502645857,-2.22390027400994,-1.26361438497058,
     0.358728895971352,-0.0110454784656636,-0.940649162618608,-0.115825322156954,-0.814968708869917,
     0.242263480859686,-1.4250983947325,0.36594112304922,0.248412648872596,0.0652881816716207,
     0.0191563916602738,0.257338377155533,-0.649010077708898,-0.119168762418038,0.66413569989411,
     1.10096910219409,0.14377148075807,-0.117753598165951,-0.912068366948338,-1.43758624082998,
     -0.797089525071965,1.25408310644997,0.77214218580453,-0.21951562675344,-0.424810283377287,
     -0.418980099421959,0.996986860909106,-0.275778029088027,1.2560188173061,0.646674390495345,
     1.29931230256343,-0.873262111744435,0.00837095999603331,-0.880871723252545,0.59625901661066,
     0.119717641289537,-0.282173877322451,1.45598840106634,0.229019590694692,0.996543928544126};


TEST_F(stanMcmc, effectiveSize)  {
  double ess = mcmc_output.effectiveSize();
  
  EXPECT_FLOAT_EQ(78.42269, ess);
}

TEST_F(stanMcmc, splitRHat) {
  double splitRHat = mcmc_output.splitRHat();
  
  EXPECT_FLOAT_EQ(0.9892759, splitRHat);
}

TEST_F(stanMcmc, mean) {
  double mean = mcmc_output.mean();
  
  EXPECT_FLOAT_EQ(0.02266845, mean);
}

TEST_F(stanMcmc, variance) {
  double variance = mcmc_output.variance();
  
  EXPECT_FLOAT_EQ(0.7790714, variance);
}

TEST_F(stanMcmc, factory) {
  stan::mcmc::mcmc_output mu1;
  EXPECT_NO_THROW(mu1 = factory.create("mu.1"));
}

TEST_F(stanMcmc, factoryAvailableVariables) {
  std::vector<std::string> vars;
  EXPECT_NO_THROW(vars = factory.availableVariables());
  EXPECT_FLOAT_EQ(49, vars.size());
  EXPECT_EQ("lp__", vars[0]);
  EXPECT_EQ("mu.1", vars[4]);

  EXPECT_NO_THROW(vars = factory.availableVariables(0));
  EXPECT_FLOAT_EQ(49, vars.size());
  EXPECT_EQ("lp__", vars[0]);
  EXPECT_EQ("d", vars[2]);

  EXPECT_NO_THROW(vars = factory.availableVariables(1));
  EXPECT_FLOAT_EQ(49, vars.size());
  EXPECT_EQ("lp__", vars[0]);
  EXPECT_EQ("delta.1", vars[26]);

  EXPECT_THROW(vars = factory.availableVariables(2), std::runtime_error);
}

TEST_F(stanMcmc, mu1) {
  stan::mcmc::mcmc_output mu1 = factory.create("mu.1");
  EXPECT_FLOAT_EQ(13.599755, mu1.effectiveSize());
  EXPECT_FLOAT_EQ(1.187, mu1.splitRHat());
}

TEST_F(stanMcmc, delta22) {
  stan::mcmc::mcmc_output delta22 = factory.create("delta.22");
  EXPECT_FLOAT_EQ(43.58981, delta22.effectiveSize());
  EXPECT_FLOAT_EQ(1.03715, delta22.splitRHat());
}
