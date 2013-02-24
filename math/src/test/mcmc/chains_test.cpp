#include <stan/mcmc/chains.hpp>
#include <stan/io/stan_csv_reader.hpp>
#include <gtest/gtest.h>
#include <boost/random/additive_combine.hpp>
#include <set>
#include <exception>
#include <utility>
#include <fstream>



class McmcChains_New : public testing::Test {
public:
  
  void SetUp() {
    blocker1_stream.open("src/test/mcmc/test_csv_files/blocker.1.csv");
    blocker2_stream.open("src/test/mcmc/test_csv_files/blocker.2.csv");
    epil1_stream.open("src/test/mcmc/test_csv_files/epil.1.csv");
    epil2_stream.open("src/test/mcmc/test_csv_files/epil.2.csv");
  }
  
  void TearDown() {
    blocker1_stream.close();
    blocker2_stream.close();
    epil1_stream.close();
    epil2_stream.close();
  }
  std::ifstream blocker1_stream, blocker2_stream, epil1_stream, epil2_stream;
};

TEST_F(McmcChains_New, constructor) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  // construct with Eigen::Vector
  stan::mcmc::chains_new<> chains1(blocker1.header);
  EXPECT_EQ(0, chains1.num_chains());
  EXPECT_EQ(blocker1.header.size(), chains1.num_params());
  for (int i = 0; i < blocker1.header.size(); i++)
    EXPECT_EQ(blocker1.header(i), chains1.param_name(i));
  
  
  // construct with stan_csv
  stan::mcmc::chains_new<> chains2(blocker1);
  EXPECT_EQ(1, chains2.num_chains());
  EXPECT_EQ(blocker1.header.size(), chains2.num_params());
  for (int i = 0; i < blocker1.header.size(); i++)
    EXPECT_EQ(blocker1.header(i), chains2.param_name(i));
  EXPECT_EQ(0, chains2.warmup(0));
  EXPECT_EQ(1000, chains2.num_samples(0));
}

TEST_F(McmcChains_New, add) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  
  // construct with Eigen::Vector
  stan::mcmc::chains_new<> chains(blocker1.header);
  EXPECT_EQ(0, chains.num_chains());
  EXPECT_EQ(0, chains.num_samples());

  Eigen::RowVectorXd theta = blocker1.samples.row(0);
  EXPECT_NO_THROW(chains.add(1, theta)) 
    << "adding a single sample to a new chain";
  EXPECT_EQ(2, chains.num_chains());
  EXPECT_EQ(0, chains.num_samples(0));
  EXPECT_EQ(1, chains.num_samples(1));
  EXPECT_EQ(1, chains.num_samples());

  theta = blocker1.samples.row(1);
  EXPECT_NO_THROW(chains.add(1, theta)) 
    << "adding a single sample to an existing chain";
  EXPECT_EQ(2, chains.num_chains());
  EXPECT_EQ(0, chains.num_samples(0));
  EXPECT_EQ(2, chains.num_samples(1));
  EXPECT_EQ(2, chains.num_samples());
  
  EXPECT_NO_THROW(chains.add(3, blocker1.samples))
    << "adding multiple samples to a new chain";
  EXPECT_EQ(4, chains.num_chains());
  EXPECT_EQ(0, chains.num_samples(0));
  EXPECT_EQ(2, chains.num_samples(1));
  EXPECT_EQ(0, chains.num_samples(2));
  EXPECT_EQ(1000, chains.num_samples(3));
  EXPECT_EQ(1002, chains.num_samples());

  EXPECT_NO_THROW(chains.add(3, blocker1.samples))
    << "adding multiple samples to an existing chain";
  EXPECT_EQ(4, chains.num_chains());
  EXPECT_EQ(0, chains.num_samples(0));
  EXPECT_EQ(2, chains.num_samples(1));
  EXPECT_EQ(0, chains.num_samples(2));
  EXPECT_EQ(2000, chains.num_samples(3));
  EXPECT_EQ(2002, chains.num_samples());


  EXPECT_NO_THROW(chains.add(blocker1.samples))
    << "adding multiple samples, adds new chain";
  EXPECT_EQ(5, chains.num_chains());
  EXPECT_EQ(0, chains.num_samples(0));
  EXPECT_EQ(2, chains.num_samples(1));
  EXPECT_EQ(0, chains.num_samples(2));
  EXPECT_EQ(2000, chains.num_samples(3));
  EXPECT_EQ(1000, chains.num_samples(4));
  EXPECT_EQ(3002, chains.num_samples());


  stan::io::stan_csv epil1 = stan::io::stan_csv_reader::parse(epil1_stream);
  theta.resize(epil1.samples.cols());
  theta = epil1.samples.row(0);
  EXPECT_THROW(chains.add(1, theta), std::invalid_argument)
    << "adding mismatched sample to an existing chain";
  EXPECT_THROW(chains.add(10, theta), std::invalid_argument)
    << "adding mismatched sample to a new chain";
  EXPECT_THROW(chains.add(3, epil1.samples), std::invalid_argument)
    << "adding mismatched samples to an existing chain";
  EXPECT_THROW(chains.add(10, epil1.samples), std::invalid_argument)
    << "adding mismatched samples to a new chain";
  EXPECT_THROW(chains.add(epil1), std::invalid_argument)
    << "adding mismatched sample";

  EXPECT_EQ(5, chains.num_chains())
    << "validate state is identical to before";
  EXPECT_EQ(0, chains.num_samples(0))
    << "validate state is identical to before";
  EXPECT_EQ(2, chains.num_samples(1))
    << "validate state is identical to before";
  EXPECT_EQ(0, chains.num_samples(2))
    << "validate state is identical to before";
  EXPECT_EQ(2000, chains.num_samples(3))
    << "validate state is identical to before";
  EXPECT_EQ(1000, chains.num_samples(4))
    << "validate state is identical to before";
  EXPECT_EQ(3002, chains.num_samples())
    << "validate state is identical to before";
}

TEST_F(McmcChains_New, blocker1_num_chains) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  
  EXPECT_EQ(1, chains.num_chains());
}
TEST_F(McmcChains_New, blocker1_param_names) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  ASSERT_EQ(blocker1.header.size(), chains.num_params());
  ASSERT_EQ(blocker1.header.size(), chains.param_names().size());
  for (int i = 0; i < blocker1.header.size(); i++) {
    EXPECT_EQ(blocker1.header(i), chains.param_names()(i));
  }
}
TEST_F(McmcChains_New, blocker1_param_name) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  ASSERT_EQ(blocker1.header.size(), chains.num_params());
  for (int i = 0; i < blocker1.header.size(); i++) {
    EXPECT_EQ(blocker1.header(i), chains.param_name(i));
  }
}
TEST_F(McmcChains_New, blocker1_index) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  ASSERT_EQ(blocker1.header.size(), chains.num_params());
  for (int i = 0; i < blocker1.header.size(); i++)
    EXPECT_EQ(i, chains.index(blocker1.header(i)));
}
TEST_F(McmcChains_New, blocker1_warmup) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);

  ASSERT_EQ(1, chains.warmup().size());
  EXPECT_EQ(0, chains.warmup()(0));
  EXPECT_EQ(0, chains.warmup(0));

  chains.set_warmup(10);
  ASSERT_EQ(1, chains.warmup().size());
  EXPECT_EQ(10, chains.warmup()(0));
  EXPECT_EQ(10, chains.warmup(0));


  chains.set_warmup(100);
  ASSERT_EQ(1, chains.warmup().size());
  EXPECT_EQ(100, chains.warmup()(0));
  EXPECT_EQ(100, chains.warmup(0));
 
  chains.add(blocker1);
  ASSERT_EQ(2, chains.warmup().size());
  EXPECT_EQ(100, chains.warmup()(0));
  EXPECT_EQ(100, chains.warmup(0));
  EXPECT_EQ(0, chains.warmup()(1));
  EXPECT_EQ(0, chains.warmup(1));


  chains.set_warmup(1, 20);
  ASSERT_EQ(2, chains.warmup().size());
  EXPECT_EQ(100, chains.warmup()(0));
  EXPECT_EQ(100, chains.warmup(0));
  EXPECT_EQ(20, chains.warmup()(1));
  EXPECT_EQ(20, chains.warmup(1));


  chains.set_warmup(50);
  ASSERT_EQ(2, chains.warmup().size());
  EXPECT_EQ(50, chains.warmup()(0));
  EXPECT_EQ(50, chains.warmup(0));
  EXPECT_EQ(50, chains.warmup()(1));
  EXPECT_EQ(50, chains.warmup(1));
}
TEST_F(McmcChains_New, blocker_mean) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  stan::io::stan_csv blocker2 = stan::io::stan_csv_reader::parse(blocker2_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);

  Eigen::VectorXd means1 = blocker1.samples.colwise().mean();
  for (int j = 0; j < chains.num_params(); j++) {
    ASSERT_FLOAT_EQ(means1(j), chains.mean(0,j))
      << "1: chain, param mean";
    ASSERT_FLOAT_EQ(means1(j), chains.mean(j))
      << "1: param mean";
  }

  ASSERT_NO_THROW(chains.add(blocker2))
    << "adding a second chain";
  Eigen::VectorXd means2 = blocker2.samples.colwise().mean();
  for (int j = 0; j < chains.num_params(); j++) {
    ASSERT_FLOAT_EQ(means2(j), chains.mean(1,j))
      << "2: chain, param mean";
    ASSERT_FLOAT_EQ((means1(j) + means2(j)) * 0.5, chains.mean(j))
      << "2: param mean";
  }


  ASSERT_NO_THROW(chains.set_warmup(500));
  means1 = blocker1.samples.bottomRows(500).colwise().mean();
  means2 = blocker2.samples.bottomRows(500).colwise().mean();
  for (int j = 0; j < chains.num_params(); j++) {
    ASSERT_FLOAT_EQ(means1(j), chains.mean(0,j))
      << "3: chain mean 1 with warmup";
    ASSERT_FLOAT_EQ(means2(j), chains.mean(1,j))
      << "3: chain mean 2 with warmup";
    ASSERT_FLOAT_EQ((means1(j) + means2(j)) * 0.5, chains.mean(j))
      << "3: param mean with warmup";
  }

  for (int j = 0; j < chains.num_params(); j++) {
    std::string param_name = chains.param_name(j);
    ASSERT_FLOAT_EQ(chains.mean(0,j), chains.mean(0,param_name))
      << "4: chain mean 0 called with string name: " << param_name;
    ASSERT_FLOAT_EQ(chains.mean(1,j), chains.mean(1,param_name))
      << "4: chain mean 1 called with string name: " << param_name;
    ASSERT_FLOAT_EQ(chains.mean(j), chains.mean(param_name))
      << "4: mean called with string name: " << param_name;
  }
}

double sd(Eigen::VectorXd x) {
  return sqrt((x.array() - x.mean()).square().sum() / (x.rows() - 1));
}

TEST_F(McmcChains_New, blocker_sd) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  stan::io::stan_csv blocker2 = stan::io::stan_csv_reader::parse(blocker2_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  
  using std::sqrt;
  for (int j = 0; j < chains.num_params(); j++) {
    ASSERT_NEAR(sd(blocker1.samples.col(j)), chains.sd(0,j), 1e-8)
      << "1: chain, param sd. index: " << j;
    ASSERT_NEAR(sd(blocker1.samples.col(j)), chains.sd(j), 1e-8)
      << "1: param sd. index: " << j;
  }

  ASSERT_NO_THROW(chains.add(blocker2))
    << "adding a second chain";
  for (int j = 0; j < chains.num_params(); j++) {
    ASSERT_NEAR(sd(blocker2.samples.col(j)), chains.sd(1,j), 1e-8)
      << "2: chain, param sd. index: " << j;
    Eigen::VectorXd x(blocker1.samples.rows() + blocker2.samples.rows());
    x << blocker1.samples.col(j), blocker2.samples.col(j);
    ASSERT_NEAR(sd(x), chains.sd(j), 1e-8)
      << "2: param sd. index: " << j;
  }
  
  ASSERT_NO_THROW(chains.set_warmup(500));
  for (int j = 0; j < chains.num_params(); j++) {
    Eigen::VectorXd x1(500), x2(500), x(1000);
    x1 << blocker1.samples.col(j).bottomRows(500);
    x2 << blocker2.samples.col(j).bottomRows(500);
    x << x1, x2;
    
    ASSERT_NEAR(sd(x1), chains.sd(0,j), 1e-8)
      << "3: chain sd 1 with warmup";
    ASSERT_NEAR(sd(x2), chains.sd(1,j), 1e-8)
      << "3: chain sd 2 with warmup";
    ASSERT_NEAR(sd(x), chains.sd(j), 1e-8)
      << "3: param sd with warmup";
  }

  for (int j = 0; j < chains.num_params(); j++) {
    std::string param_name = chains.param_name(j);
    ASSERT_FLOAT_EQ(chains.sd(0,j), chains.sd(0,param_name))
      << "4: chain sd 0 called with string name: " << param_name;
    ASSERT_FLOAT_EQ(chains.sd(1,j), chains.sd(1,param_name))
      << "4: chain sd 1 called with string name: " << param_name;
    ASSERT_FLOAT_EQ(chains.sd(j), chains.sd(param_name))
      << "4: sd called with string name: " << param_name;
  }

}


double variance(Eigen::VectorXd x) {
  return (x.array() - x.mean()).square().sum() / (x.rows() - 1);
}

TEST_F(McmcChains_New, blocker_variance) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  stan::io::stan_csv blocker2 = stan::io::stan_csv_reader::parse(blocker2_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  
  using std::sqrt;
  for (int j = 0; j < chains.num_params(); j++) {
    ASSERT_NEAR(variance(blocker1.samples.col(j)), chains.variance(0,j), 1e-8)
      << "1: chain, param variance. index: " << j;
    ASSERT_NEAR(variance(blocker1.samples.col(j)), chains.variance(j), 1e-8)
      << "1: param variance. index: " << j;
  }

  ASSERT_NO_THROW(chains.add(blocker2))
    << "adding a second chain";
  for (int j = 0; j < chains.num_params(); j++) {
    ASSERT_NEAR(variance(blocker2.samples.col(j)), chains.variance(1,j), 1e-8)
      << "2: chain, param variance. index: " << j;
    Eigen::VectorXd x(blocker1.samples.rows() + blocker2.samples.rows());
    x << blocker1.samples.col(j), blocker2.samples.col(j);
    ASSERT_NEAR(variance(x), chains.variance(j), 1e-8)
      << "2: param variance. index: " << j;
  }
  
  ASSERT_NO_THROW(chains.set_warmup(500));
  for (int j = 0; j < chains.num_params(); j++) {
    Eigen::VectorXd x1(500), x2(500), x(1000);
    x1 << blocker1.samples.col(j).bottomRows(500);
    x2 << blocker2.samples.col(j).bottomRows(500);
    x << x1, x2;
    
    ASSERT_NEAR(variance(x1), chains.variance(0,j), 1e-8)
      << "3: chain variance 1 with warmup";
    ASSERT_NEAR(variance(x2), chains.variance(1,j), 1e-8)
      << "3: chain variance 2 with warmup";
    ASSERT_NEAR(variance(x), chains.variance(j), 1e-8)
      << "3: param variance with warmup";
  }

  for (int j = 0; j < chains.num_params(); j++) {
    std::string param_name = chains.param_name(j);
    ASSERT_FLOAT_EQ(chains.variance(0,j), chains.variance(0,param_name))
      << "4: chain variance 0 called with string name: " << param_name;
    ASSERT_FLOAT_EQ(chains.variance(1,j), chains.variance(1,param_name))
      << "4: chain variance 1 called with string name: " << param_name;
    ASSERT_FLOAT_EQ(chains.variance(j), chains.variance(param_name))
      << "4: variance called with string name: " << param_name;
  }

}

double covariance(Eigen::VectorXd x, Eigen::VectorXd y) {
  double x_mean = x.mean();
  double y_mean = y.mean();
  return ((x.array() - x_mean) * (y.array() - y_mean)).sum() / (x.rows() - 1);
}

TEST_F(McmcChains_New, blocker_covariance) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  stan::io::stan_csv blocker2 = stan::io::stan_csv_reader::parse(blocker2_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  chains.add(blocker2);
  
  int n = 0;
  for (int i = 0; i < chains.num_params(); i++) {
    for (int j = i; j < chains.num_params(); j++) {
      if (++n % 13 == 0) { // test every 13th value
	Eigen::VectorXd x1(1000), x2(1000), x(2000);
	Eigen::VectorXd y1(1000), y2(1000), y(2000);
	x1 << blocker1.samples.col(i);
	x2 << blocker1.samples.col(j);

	y1 << blocker2.samples.col(i);
	y2 << blocker2.samples.col(j);

	x << x1, y1;
	y << x2, y2;
      
	double cov1 = covariance(x1, x2);
	double cov2 = covariance(y1, y2);
	double cov = covariance(x, y);
      
	ASSERT_NEAR(cov1, chains.covariance(0,i,j), 1e-8);
	ASSERT_NEAR(cov2, chains.covariance(1,i,j), 1e-8);
	ASSERT_NEAR(cov, chains.covariance(i,j), 1e-8);

	ASSERT_NEAR(cov1, chains.covariance(0,j,i), 1e-8);
	ASSERT_NEAR(cov2, chains.covariance(1,j,i), 1e-8);
	ASSERT_NEAR(cov, chains.covariance(j,i), 1e-8);

	std::string name1 = chains.param_name(i);
	std::string name2 = chains.param_name(j);
	ASSERT_FLOAT_EQ(chains.covariance(0,i,j), chains.covariance(0,name1,name2));
	ASSERT_FLOAT_EQ(chains.covariance(1,j,i), chains.covariance(1,name2,name1));
	ASSERT_FLOAT_EQ(chains.covariance(i,j), chains.covariance(name1,name2));
      }
    }
  }
}

TEST_F(McmcChains_New, blocker_correlation) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  stan::io::stan_csv blocker2 = stan::io::stan_csv_reader::parse(blocker2_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  chains.add(blocker2);
  
  int n = 0;
  for (int i = 0; i < chains.num_params(); i++) {
    for (int j = i; j < chains.num_params(); j++) {
      if (++n % 13 == 0) { // test every 13th value
	Eigen::VectorXd x1(1000), x2(1000), x(2000);
	Eigen::VectorXd y1(1000), y2(1000), y(2000);
	x1 << blocker1.samples.col(i);
	x2 << blocker1.samples.col(j);

	y1 << blocker2.samples.col(i);
	y2 << blocker2.samples.col(j);

	x << x1, y1;
	y << x2, y2;
      

	double cov1 = covariance(x1, x2);
	double cov2 = covariance(y1, y2);
	double cov = covariance(x, y);

	double corr1 = 0;
	double corr2 = 0;
	double corr = 0;

	if (std::fabs(cov1) > 1e-8)
	  corr1 = cov1 / sd(x1) / sd(x2);
	if (std::fabs(cov2) > 1e-8)
	  corr2 = cov2 / sd(y1) / sd(y2);
	if (std::fabs(cov) > 1e-8)
	  corr = cov / sd(x) / sd(y);
		
	ASSERT_NEAR(corr1, chains.correlation(0,i,j), 1e-8)
	  << "(" << i << ", " << j << ")";
	ASSERT_NEAR(corr2, chains.correlation(1,i,j), 1e-8)
	  << "(" << i << ", " << j << ")";
	ASSERT_NEAR(corr, chains.correlation(i,j), 1e-8)
	  << "(" << i << ", " << j << ")";

	ASSERT_NEAR(corr1, chains.correlation(0,j,i), 1e-8)
	  << "(" << i << ", " << j << ")";
	ASSERT_NEAR(corr2, chains.correlation(1,j,i), 1e-8)
	  << "(" << i << ", " << j << ")";
	ASSERT_NEAR(corr, chains.correlation(j,i), 1e-8)
	  << "(" << i << ", " << j << ")";
	
	std::string name1 = chains.param_name(i);
	std::string name2 = chains.param_name(j);
	ASSERT_FLOAT_EQ(chains.correlation(0,i,j), chains.correlation(0,name1,name2));
	ASSERT_FLOAT_EQ(chains.correlation(1,j,i), chains.correlation(1,name2,name1));
	ASSERT_FLOAT_EQ(chains.correlation(i,j), chains.correlation(name1,name2));
      }
    }
  }
}

TEST_F(McmcChains_New, blocker_quantile) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  
  int index = 5;
  
  // R's quantile function
  EXPECT_NEAR(-2.93776, chains.quantile(0,index,0.1), 1e-2);
  EXPECT_NEAR(-2.71573, chains.quantile(0,index,0.2), 1e-2);
  EXPECT_NEAR(-2.58469, chains.quantile(0,index,0.3), 1e-2);
  EXPECT_NEAR(-2.57960, chains.quantile(0,index,0.4), 1e-2);
  EXPECT_NEAR(-2.49539, chains.quantile(0,index,0.5), 1e-2);
  EXPECT_NEAR(-2.37983, chains.quantile(0,index,0.6), 1e-2);
  EXPECT_NEAR(-2.22837, chains.quantile(0,index,0.7), 1e-2);
  EXPECT_NEAR(-2.08649, chains.quantile(0,index,0.8), 1e-2);
  EXPECT_NEAR(-1.90839, chains.quantile(0,index,0.9), 1e-2);

  EXPECT_NEAR(-2.93776, chains.quantile(index,0.1), 1e-2);
  EXPECT_NEAR(-2.71573, chains.quantile(index,0.2), 1e-2);
  EXPECT_NEAR(-2.58469, chains.quantile(index,0.3), 1e-2);
  EXPECT_NEAR(-2.57960, chains.quantile(index,0.4), 1e-2);
  EXPECT_NEAR(-2.49539, chains.quantile(index,0.5), 1e-2);
  EXPECT_NEAR(-2.37983, chains.quantile(index,0.6), 1e-2);
  EXPECT_NEAR(-2.22837, chains.quantile(index,0.7), 1e-2);
  EXPECT_NEAR(-2.08649, chains.quantile(index,0.8), 1e-2);
  EXPECT_NEAR(-1.90839, chains.quantile(index,0.9), 1e-2);

  std::string name = chains.param_name(index);
  EXPECT_FLOAT_EQ(chains.quantile(0,index,0.1), chains.quantile(0,name,0.1));
  EXPECT_FLOAT_EQ(chains.quantile(0,index,0.3), chains.quantile(0,name,0.3));  
  EXPECT_FLOAT_EQ(chains.quantile(0,index,0.5), chains.quantile(0,name,0.5));

  EXPECT_FLOAT_EQ(chains.quantile(index,0.2), chains.quantile(name,0.2));
  EXPECT_FLOAT_EQ(chains.quantile(index,0.4), chains.quantile(name,0.4));  
  EXPECT_FLOAT_EQ(chains.quantile(index,0.6), chains.quantile(name,0.6));
}

TEST_F(McmcChains_New, blocker_quantiles) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  
  int index = 5;

  Eigen::VectorXd probs(9);
  probs << 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9;
  
  Eigen::VectorXd quantiles;
  
  quantiles = chains.quantiles(0,index,probs);
  // R's quantile function
  ASSERT_EQ(9, quantiles.size());
  EXPECT_NEAR(-2.93776, quantiles(0), 1e-2);
  EXPECT_NEAR(-2.71573, quantiles(1), 1e-2);
  EXPECT_NEAR(-2.58469, quantiles(2), 1e-2);
  EXPECT_NEAR(-2.57960, quantiles(3), 1e-2);
  EXPECT_NEAR(-2.49539, quantiles(4), 1e-2);
  EXPECT_NEAR(-2.37983, quantiles(5), 1e-2);
  EXPECT_NEAR(-2.22837, quantiles(6), 1e-2);
  EXPECT_NEAR(-2.08649, quantiles(7), 1e-2);
  EXPECT_NEAR(-1.90839, quantiles(8), 1e-2);


  quantiles = chains.quantiles(index,probs);
  // R's quantile function
  ASSERT_EQ(9, quantiles.size());
  EXPECT_NEAR(-2.93776, quantiles(0), 1e-2);
  EXPECT_NEAR(-2.71573, quantiles(1), 1e-2);
  EXPECT_NEAR(-2.58469, quantiles(2), 1e-2);
  EXPECT_NEAR(-2.57960, quantiles(3), 1e-2);
  EXPECT_NEAR(-2.49539, quantiles(4), 1e-2);
  EXPECT_NEAR(-2.37983, quantiles(5), 1e-2);
  EXPECT_NEAR(-2.22837, quantiles(6), 1e-2);
  EXPECT_NEAR(-2.08649, quantiles(7), 1e-2);
  EXPECT_NEAR(-1.90839, quantiles(8), 1e-2);


  std::string name = chains.param_name(index);
  Eigen::VectorXd quantiles_by_name;
  quantiles = chains.quantiles(0,index,probs);
  quantiles_by_name = chains.quantiles(0,name,probs);
  
  ASSERT_EQ(quantiles.size(), quantiles_by_name.size());
  for (int i = 0; i < quantiles.size(); i++) {
    EXPECT_FLOAT_EQ(quantiles(i), quantiles_by_name(i));
  }

  quantiles = chains.quantiles(index,probs);
  quantiles_by_name = chains.quantiles(name,probs);
  
  ASSERT_EQ(quantiles.size(), quantiles_by_name.size());
  for (int i = 0; i < quantiles.size(); i++) {
    EXPECT_FLOAT_EQ(quantiles(i), quantiles_by_name(i));
  }

}
TEST_F(McmcChains_New, blocker_central_interval) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  
  int index = 5;
  
  Eigen::Vector2d interval;

  interval = chains.central_interval(0,index,0.6);
  // R's quantile function
  EXPECT_NEAR(-2.71573, interval(0), 1e-2); // 0.2
  EXPECT_NEAR(-2.08649, interval(1), 1e-2); // 0.8

  interval = chains.central_interval(index,0.6);
  // R's quantile function
  EXPECT_NEAR(-2.71573, interval(0), 1e-2); // 0.2
  EXPECT_NEAR(-2.08649, interval(1), 1e-2); // 0.8

  std::string name = chains.param_name(index);
  Eigen::VectorXd interval_by_name;
  interval = chains.central_interval(0,index,0.6);
  interval_by_name = chains.central_interval(0,name,0.6);
  ASSERT_EQ(2, interval_by_name.size());
  EXPECT_FLOAT_EQ(interval(0), interval_by_name(0));
  EXPECT_FLOAT_EQ(interval(1), interval_by_name(1));

  interval = chains.central_interval(index,0.6);
  interval_by_name = chains.central_interval(name,0.6);
  ASSERT_EQ(2, interval_by_name.size());
  EXPECT_FLOAT_EQ(interval(0), interval_by_name(0));
  EXPECT_FLOAT_EQ(interval(1), interval_by_name(1));
}
TEST_F(McmcChains_New, blocker_autocorrelation) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  Eigen::VectorXd ac;
  EXPECT_NO_THROW(ac = chains.autocorrelation(0,5));

  EXPECT_NEAR(1.0, ac[0], 0.01);  
  EXPECT_NEAR(0.277, ac[1], 0.01);
  EXPECT_NEAR(0.197, ac[2], 0.01);
  EXPECT_NEAR(0.123, ac[3], 0.01);
  EXPECT_NEAR(0.087, ac[4], 0.01);
  EXPECT_NEAR(0.096, ac[5], 0.01);
  EXPECT_NEAR(0.100, ac[6], 0.01);
  EXPECT_NEAR(0.007, ac[7], 0.01);
  EXPECT_NEAR(0.052, ac[8], 0.01);
  EXPECT_NEAR(0.038, ac[9], 0.01);
  EXPECT_NEAR(-0.007, ac[10], 0.01);
  EXPECT_NEAR(0.070, ac[11], 0.01);
  EXPECT_NEAR(0.004, ac[12], 0.01);
  EXPECT_NEAR(0.019, ac[13], 0.01);
  EXPECT_NEAR(0.003, ac[14], 0.01);
  EXPECT_NEAR(-0.035, ac[15], 0.01);
  EXPECT_NEAR(-0.076, ac[16], 0.01);
  EXPECT_NEAR(-0.048, ac[17], 0.01);
  EXPECT_NEAR(-0.097, ac[18], 0.01);
  EXPECT_NEAR(-0.014, ac[19], 0.01);
  EXPECT_NEAR(-0.065, ac[20], 0.01);
  EXPECT_NEAR(-0.069, ac[21], 0.01);
  EXPECT_NEAR(-0.004, ac[22], 0.01);
  EXPECT_NEAR(-0.084, ac[23], 0.01);
  EXPECT_NEAR(-0.005, ac[24], 0.01);
  EXPECT_NEAR(0.031, ac[25], 0.01);
  EXPECT_NEAR(0.002, ac[26], 0.01);
  EXPECT_NEAR(-0.019, ac[27], 0.01);
  EXPECT_NEAR(0.002, ac[28], 0.01);
  EXPECT_NEAR(-0.011, ac[29], 0.01);
  EXPECT_NEAR(-0.016, ac[30], 0.01);

  std::string name = chains.param_name(5);
  Eigen::VectorXd ac_by_name;
  EXPECT_NO_THROW(ac_by_name = chains.autocorrelation(0,name));
  ASSERT_EQ(ac.size(), ac_by_name.size());
  for (int i = 0; i < ac.size(); i++) {
    EXPECT_FLOAT_EQ(ac(i), ac_by_name(i));
  }
}
TEST_F(McmcChains_New, blocker_autocovariance) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  Eigen::VectorXd ac;
  EXPECT_NO_THROW(ac = chains.autocovariance(0,5));

  EXPECT_NEAR( 0.1728635075, ac[0], 0.01);  
  EXPECT_NEAR( 0.0479453913, ac[1], 0.01);
  EXPECT_NEAR( 0.0339712275, ac[2], 0.01);
  EXPECT_NEAR( 0.0213133322, ac[3], 0.01);
  EXPECT_NEAR( 0.0150613410, ac[4], 0.01);
  EXPECT_NEAR( 0.0166353592, ac[5], 0.01);
  EXPECT_NEAR( 0.0173524816, ac[6], 0.01);
  EXPECT_NEAR( 0.0011691359, ac[7], 0.01);
  EXPECT_NEAR( 0.0089205594, ac[8], 0.01);
  EXPECT_NEAR( 0.0065516382, ac[9], 0.01);
  EXPECT_NEAR(-0.0012707460, ac[10], 0.01);
  EXPECT_NEAR( 0.0120453780, ac[11], 0.01);
  EXPECT_NEAR( 0.0007551419, ac[12], 0.01);
  EXPECT_NEAR( 0.0032945508, ac[13], 0.01);
  EXPECT_NEAR( 0.0005656385, ac[14], 0.01);
  EXPECT_NEAR(-0.0060412611, ac[15], 0.01);
  EXPECT_NEAR(-0.0131231022, ac[16], 0.01);
  EXPECT_NEAR(-0.0083577880, ac[17], 0.01);
  EXPECT_NEAR(-0.0168234290, ac[18], 0.01);
  EXPECT_NEAR(-0.0024401327, ac[19], 0.01);
  EXPECT_NEAR(-0.0112285003, ac[20], 0.01);
  EXPECT_NEAR(-0.0120031605, ac[21], 0.01);
  EXPECT_NEAR(-0.0007499154, ac[22], 0.01);
  EXPECT_NEAR(-0.0144821063, ac[23], 0.01);
  EXPECT_NEAR(-0.0008450844, ac[24], 0.01);
  EXPECT_NEAR( 0.0054121234, ac[25], 0.01);
  EXPECT_NEAR( 0.0003861726, ac[26], 0.01);
  EXPECT_NEAR(-0.0032979440, ac[27], 0.01);
  EXPECT_NEAR( 0.0003806655, ac[28], 0.01);
  EXPECT_NEAR(-0.0019447624, ac[29], 0.01);
  EXPECT_NEAR(-0.0028139251, ac[30], 0.01);

  std::string name = chains.param_name(5);
  Eigen::VectorXd ac_by_name;
  EXPECT_NO_THROW(ac_by_name = chains.autocovariance(0,name));
  ASSERT_EQ(ac.size(), ac_by_name.size());
  for (int i = 0; i < ac.size(); i++) {
    EXPECT_FLOAT_EQ(ac(i), ac_by_name(i));
  }
}

TEST_F(McmcChains_New,blocker_effective_sample_size) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  stan::io::stan_csv blocker2 = stan::io::stan_csv_reader::parse(blocker2_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  chains.add(blocker2);

  Eigen::VectorXd n_eff(48);
  n_eff << 
    431,136,450,121,258,
    202,287,615,107,131,
    39,573,608,538,412,
    32,199,106,153,298,
    105,155,340,475,806,
    518,657,277,149,979,
    150,741,923,647,473,
    638,796,62,709,551,
    687,933,798,574,377,
    457,650,44;

  for (int index = 3; index < chains.num_params(); index++) {
    ASSERT_NEAR(n_eff(index - 3), chains.effective_sample_size(index), 1.0)
      << "n_effective for index: " << index << ", parameter: " 
      << chains.param_name(index);
  }

  for (int index = 0; index < chains.num_params(); index++) {
    std::string name = chains.param_name(index);
    ASSERT_EQ(chains.effective_sample_size(index), 
	      chains.effective_sample_size(name));
  }
}

TEST_F(McmcChains_New,blocker_split_potential_scale_reduction) {
  stan::io::stan_csv blocker1 = stan::io::stan_csv_reader::parse(blocker1_stream);
  stan::io::stan_csv blocker2 = stan::io::stan_csv_reader::parse(blocker2_stream);
  
  stan::mcmc::chains_new<> chains(blocker1);
  chains.add(blocker2);

  Eigen::VectorXd rhat(48);
  rhat << 
    1.0044119, 1.0130149, 1.0024355, 1.0123774, 1.0091136,
    1.0046465, 1.0030522, 1.0025938, 1.0016099, 1.0218149, 
    1.0397644, 1.0087594, 1.0017704, 1.0048593, 1.0113208,
    1.0401753, 1.0040739, 1.0151312, 1.0120381, 1.0034498, 
    1.0179943, 1.0160549, 1.0107518, 1.0050004, 0.9997756, 
    1.0014585, 1.0002573, 1.0113728, 1.0368905, 1.0020098,
    1.0058891, 1.0008469, 1.0031100, 1.0071503, 1.0083617,
    1.0062931, 0.9997813, 1.0169052, 0.9998256, 0.9994163,
    1.0029211, 1.0013409, 1.0073875, 1.0023928, 1.0029867,
    1.0002895, 1.0018717, 1.0289164;

  for (int index = 3; index < chains.num_params(); index++) {
    ASSERT_FLOAT_EQ(rhat(index - 3), chains.split_potential_scale_reduction(index))
      << "rhat for index: " << index << ", parameter: " 
      << chains.param_name(index);
  }

  for (int index = 0; index < chains.num_params(); index++) {
    std::string name = chains.param_name(index);
    ASSERT_EQ(chains.split_potential_scale_reduction(index), 
	      chains.split_potential_scale_reduction(name));
  }

}

/*
void test_permutation(size_t N) {
  int seed = 187049587;
  boost::random::ecuyer1988 rng(seed);
  std::vector<size_t> pi;
  stan::mcmc::permutation(pi,N,rng);

  EXPECT_EQ(N,pi.size());
  for (size_t i = 0; i < N; ++i)
    EXPECT_TRUE(pi[i] < N);
  size_t match_count = 0;
  for (size_t i = 0; i < N; ++i)
    for (size_t j = 0; j < N; ++j)
      if (pi[j] == i) ++match_count;
  EXPECT_EQ(N,match_count);
  
}

TEST(McmcChains,permutation) {
  test_permutation(0);
  test_permutation(1);
  test_permutation(2);
  test_permutation(3);
  test_permutation(15);
  test_permutation(1024);
  test_permutation(1023);
  test_permutation(1025);
}


void test_permute(size_t N) {
  int seed = 187049587;
  boost::random::ecuyer1988 rng(seed);
  std::vector<size_t> pi;
  stan::mcmc::permutation(pi,N,rng);

  std::vector<double> x(N);
  for (size_t n = 0; n < N; ++n)
    x[n] = 1.0 + n / 2.0;
  std::vector<double> x_pi;
  
  stan::mcmc::permute(pi,x,x_pi);
  EXPECT_EQ(N,x_pi.size());
  if (N < 1) return;

  double sum = 0.0;
  double sum_pi = 0.0;
  for (size_t n = 0; n < N; ++n) {
    sum += x[n];
    sum_pi += x_pi[n];
  }
  EXPECT_GT(sum,0.0);
  EXPECT_EQ(sum,sum_pi);
}

TEST(McmcChains, permute) {
  test_permute(0);
  test_permute(1);  
  test_permute(2);  
  test_permute(3);  
  test_permute(4);  
  test_permute(5);  
  test_permute(2055);
  test_permute(2056);
  test_permute(2057);
}



TEST(McmcChains,ctor_and_immutable_getters) {
  using std::vector;
  using std::string;
  using stan::mcmc::chains;

  size_t K = 4;

  // b(), a(2), d(3,4,5), c(6,7)

  vector<string> names;
  names.push_back("b");
  names.push_back("a");
  names.push_back("d");
  names.push_back("c");

  vector<size_t> b_dims;

  vector<size_t> a_dims;
  a_dims.push_back(2);

  vector<size_t> d_dims;
  d_dims.push_back(3);
  d_dims.push_back(4);
  d_dims.push_back(5);

  vector<size_t> c_dims;
  c_dims.push_back(6);
  c_dims.push_back(7);

  vector<vector<size_t> > dimss;
  dimss.push_back(b_dims);
  dimss.push_back(a_dims);
  dimss.push_back(d_dims);
  dimss.push_back(c_dims);

  chains<> c(K,names,dimss);

  EXPECT_EQ(4U, c.num_chains());

  EXPECT_EQ(size_t(1 + 2 + 3*4*5 + 6*7), c.num_params());

  EXPECT_EQ(4U, c.num_param_names());

  EXPECT_EQ(4U, c.param_names().size());
  EXPECT_EQ("b", c.param_names()[0]);
  EXPECT_EQ("a", c.param_names()[1]);
  EXPECT_EQ("d", c.param_names()[2]);
  EXPECT_EQ("c", c.param_names()[3]);
  EXPECT_EQ("b", c.param_name(0));
  EXPECT_EQ("a", c.param_name(1));
  EXPECT_EQ("d", c.param_name(2));
  EXPECT_EQ("c", c.param_name(3));
  EXPECT_THROW(c.param_name(5), std::out_of_range);

  EXPECT_EQ(0U, c.param_start(0));
  EXPECT_EQ(1U, c.param_start(1));
  EXPECT_EQ(3U, c.param_start(2));
  EXPECT_EQ(63U, c.param_start(3));
  EXPECT_EQ(0U, c.param_starts()[0]);
  EXPECT_EQ(1U, c.param_starts()[1]);
  EXPECT_EQ(3U, c.param_starts()[2]);
  EXPECT_EQ(63U, c.param_starts()[3]);
  EXPECT_THROW(c.param_start(5), std::out_of_range);

  EXPECT_EQ(1U, c.param_size(0));
  EXPECT_EQ(1U, c.param_sizes()[0]);
  EXPECT_EQ(2U, c.param_size(1));
  EXPECT_EQ(2U, c.param_sizes()[1]);
  EXPECT_EQ(60U, c.param_size(2));
  EXPECT_EQ(60U, c.param_sizes()[2]);
  EXPECT_EQ(42U, c.param_size(3));
  EXPECT_EQ(42U, c.param_sizes()[3]);
  EXPECT_EQ(4U, c.param_sizes().size());
  EXPECT_THROW(c.param_size(5), std::out_of_range);

  EXPECT_EQ(0U, c.param_name_to_index("b"));
  EXPECT_EQ(1U, c.param_name_to_index("a"));
  EXPECT_EQ(2U, c.param_name_to_index("d"));
  EXPECT_EQ(3U, c.param_name_to_index("c"));

  EXPECT_EQ(4U, c.param_dimss().size());

  EXPECT_EQ(0U, c.param_dimss()[0].size());
  EXPECT_EQ(0U, c.param_dims(0).size());
  EXPECT_EQ(1U, c.param_dimss()[1].size());
  EXPECT_EQ(1U, c.param_dims(1).size());
  EXPECT_EQ(3U, c.param_dimss()[2].size());
  EXPECT_EQ(3U, c.param_dims(2).size());
  EXPECT_EQ(2U, c.param_dimss()[3].size());
  EXPECT_EQ(2U, c.param_dims(3).size());
  EXPECT_THROW(c.param_dims(5), std::out_of_range);

  EXPECT_EQ(2U, c.param_dimss()[1][0]);
  EXPECT_EQ(2U, c.param_dims(1)[0]);

  EXPECT_EQ(4U, c.param_dimss()[2][1]);
  EXPECT_EQ(4U, c.param_dims(2)[1]);

  EXPECT_THROW(c.param_dims(5), std::out_of_range);


TEST(McmcChains,add) {
  using std::vector;
  using std::string;
  using stan::mcmc::chains;

  size_t K = 4; // num chains

  vector<string> names;
  names.push_back("b");
  names.push_back("a");
  names.push_back("c");

  vector<size_t> b_dims;

  vector<size_t> a_dims;
  a_dims.push_back(2);
  a_dims.push_back(3);

  vector<size_t> c_dims;
  c_dims.push_back(4);

  vector<vector<size_t> > dimss;
  dimss.push_back(b_dims);
  dimss.push_back(a_dims);
  dimss.push_back(c_dims);
  chains<> c(K,names,dimss);

  size_t N = 1 + 2*3 + 4;

  vector<double> theta(N);
  for (size_t n = 0; n < N; ++n)
    theta[n] = n;
  

  EXPECT_EQ(0U,c.num_samples());
  EXPECT_EQ(0U,c.num_samples(0));
  EXPECT_EQ(0U,c.num_samples(1));
  EXPECT_EQ(0U,c.num_samples(2));
  EXPECT_EQ(0U,c.num_samples(3));

  c.add(0,theta);
  
  EXPECT_EQ(1U,c.num_samples());
  EXPECT_EQ(1U,c.num_samples(0));
  EXPECT_EQ(0U,c.num_samples(1));

  for (size_t n = 0; n < N; ++n)
    theta[n] *= 2.0;

  c.add(0,theta);

  EXPECT_EQ(2U,c.num_samples());
  EXPECT_EQ(2U,c.num_samples(0));
  EXPECT_EQ(0U,c.num_samples(1));

  c.add(1,theta);

  EXPECT_EQ(3U,c.num_samples());
  EXPECT_EQ(2U,c.num_samples(0));
  EXPECT_EQ(1U,c.num_samples(1));

  EXPECT_THROW(c.num_samples(5), std::out_of_range);


TEST(McmcChains,get_samples) {
  using std::vector;
  using std::string;
  using stan::mcmc::chains;

  size_t K = 3; // num chains

  vector<string> names; // dims
  names.push_back("b"); // ()
  names.push_back("a"); // (2,3)
  names.push_back("c"); // (4)

  vector<size_t> b_dims;

  vector<size_t> a_dims;
  a_dims.push_back(2);
  a_dims.push_back(3);

  vector<size_t> c_dims;
  c_dims.push_back(4);

  vector<vector<size_t> > dimss;
  dimss.push_back(b_dims);
  dimss.push_back(a_dims);
  dimss.push_back(c_dims);

  chains<> c(K,names,dimss);

  size_t N = 1 + 2*3 + 4;
  vector<double> theta(N);
  for (size_t n = 0; n < N; ++n)
    theta[n] = n;

  c.add(0,theta); // (1,0,0)
  c.add(1,theta); // (1,1,0)
  c.add(2,theta); // (1,1,1)

  for (size_t n = 0; n < N; ++n)
    theta[n] = n * n;
  
  c.add(0,theta); // (2,1,1)
  c.add(1,theta); // (2,2,1)
  c.add(2,theta); // (2,2,2)

  vector<double> rho;
  c.get_samples(0,rho);
  EXPECT_EQ(6U, rho.size());
  EXPECT_THROW(c.get_samples(112,rho), std::out_of_range);

  c.add(1,theta); // (2,3,2)
  c.add(2,theta); // (2,3,3)
  c.add(2,theta); // (2,3,4)
  c.get_samples(0,rho);
  EXPECT_EQ(9U, rho.size());

  for (size_t warmup = 0; warmup < 10; warmup += 2) {
    c.get_samples(0,0,rho);
    EXPECT_EQ(2U,rho.size());
    c.get_samples(1,0,rho);
    EXPECT_EQ(3U,rho.size());
    c.get_samples(2,0,rho);
    EXPECT_EQ(4U,rho.size());
    EXPECT_THROW(c.get_samples(112,0,rho), std::out_of_range);
    EXPECT_THROW(c.get_samples(0,59,rho), std::out_of_range);

    c.get_samples(0,0,rho);
    EXPECT_EQ(2U,rho.size());
    c.get_samples(1,0,rho);
    EXPECT_EQ(3U,rho.size());
    c.get_samples(2,0,rho);
    EXPECT_EQ(4U,rho.size());
    EXPECT_THROW(c.get_samples(112,0,rho), std::out_of_range);
    EXPECT_THROW(c.get_samples(0,59,rho), std::out_of_range);
  }

  c.set_warmup(0);
  for (size_t k = 0; k < K; ++k) {
    for (size_t n = 0; n < N; ++n) { 
      rho.resize(10);
      c.get_warmup_samples(k,n,rho);
      EXPECT_EQ(0U,rho.size());
    }
  }
  EXPECT_THROW(c.get_warmup_samples(40,0,rho), std::out_of_range);
  EXPECT_THROW(c.get_warmup_samples(0,100,rho), std::out_of_range);

  rho.resize(10);
  c.get_warmup_samples(0,rho);
  EXPECT_EQ(0U,rho.size());
  EXPECT_THROW(c.get_warmup_samples(100,rho), std::out_of_range);

  c.set_warmup(1);
  rho.resize(20);
  c.get_warmup_samples(0,rho);
  EXPECT_EQ(3U, rho.size());

  c.set_warmup(2);
  rho.resize(20);
  c.get_warmup_samples(0,rho);
  EXPECT_EQ(6U, rho.size());

  c.set_warmup(100);
  rho.resize(20);
  c.get_warmup_samples(0,rho);
  EXPECT_EQ(9U, rho.size());

  c.set_warmup(3);
  rho.resize(20);
  c.get_warmup_samples(0,0,rho);
  EXPECT_EQ(2U, rho.size());
  c.get_warmup_samples(1,0,rho);
  EXPECT_EQ(3U, rho.size());
  c.get_warmup_samples(2,0,rho);
  EXPECT_EQ(3U, rho.size());
  
  
  c.set_warmup(20);
  for (size_t n = 0; n < N; ++n) {
    for (size_t k = 0; k < K; ++k) {
      rho.resize(27);
      c.get_kept_samples_permuted(n,rho);
      EXPECT_EQ(0U,rho.size());
    }
  }
  EXPECT_THROW(c.get_kept_samples_permuted(92,rho), std::out_of_range);

  c.set_warmup(2);
  rho.resize(15);
  c.get_kept_samples(0,5,rho);
  EXPECT_EQ(0U, rho.size());
  c.get_kept_samples(1,5,rho);
  EXPECT_EQ(1U, rho.size());
  c.get_kept_samples(2,5,rho);
  EXPECT_EQ(2U, rho.size());
  EXPECT_THROW(c.get_kept_samples(27,0,rho), std::out_of_range);
  EXPECT_THROW(c.get_kept_samples(0,1012,rho), std::out_of_range);
}

TEST(McmcChains, get_kept_samples_permuted) {
  using std::vector;
  using std::string;
  using stan::mcmc::chains;

  size_t K = 3; // num chains

  vector<string> names; // dims
  names.push_back("b"); // ()
  names.push_back("a"); // ()

  vector<vector<size_t> > dimss(2,vector<size_t>(0));

  chains<> c(K,names,dimss);

  std::set<double> expected;
  std::set<double> found;

  for (size_t k = 0; k < K; ++k) {
    for (size_t n = 0; n < 20U + k; ++n) {
      double val = (k + 1) * 100 + n; // all distinct
      c.add(k,vector<double>(2,val));
      if (n >= 10U)
        expected.insert(val);
    }
  }
  c.set_warmup(10U);

  vector<double> samples0;
  vector<double> samples1;

  EXPECT_EQ(33U, c.num_kept_samples()); // 3 * 10 + (0 + 1 + 2)
  
  c.get_kept_samples_permuted(0,samples0);
  c.get_kept_samples_permuted(1,samples1);

  
  EXPECT_EQ(samples0.size(), samples1.size());
  for (size_t m = 0; m < samples0.size(); ++m)
    EXPECT_FLOAT_EQ(samples0[m], samples1[m]);

  for (size_t m = 0; m < samples0.size(); ++m)
    found.insert(samples0[m]);
  EXPECT_EQ(expected,found);
}

TEST(McmcChains, quantiles_means) {
  using std::vector;
  using std::string;
  using stan::mcmc::chains;
  unsigned int K = 2;
  chains<> c(K,
             vector<std::string>(1,"a"),
             vector<vector<size_t> >(1, vector<size_t>(0)));
  for (size_t k = 0; k < K; ++k)
    for (size_t i = 0; i < 100; ++i)
      c.add(k,std::vector<double>(1,100000)); 
  c.set_warmup(100); // discard above, keep below
  for (size_t k = 0; k < K; ++k)
    for (size_t i = 0; i <= 1000; ++i)
      c.add(k,std::vector<double>(1,i/1000.0));

  // test low, middle and high branches

  // single quantile, single chain
  EXPECT_FLOAT_EQ(0.1, c.quantile(0,0,0.1));
  EXPECT_FLOAT_EQ(0.5, c.quantile(0,0,0.5));
  EXPECT_FLOAT_EQ(0.9, c.quantile(0,0,0.9));

  EXPECT_FLOAT_EQ(0.1, c.quantile(1,0,0.1));
  EXPECT_FLOAT_EQ(0.5, c.quantile(1,0,0.5));
  EXPECT_FLOAT_EQ(0.9, c.quantile(1,0,0.9));

  EXPECT_THROW(c.quantile(2,0,0.9), std::out_of_range);
  EXPECT_THROW(c.quantile(0,2,0.9), std::out_of_range);


  // single quantile, cross chain
  EXPECT_FLOAT_EQ(0.1, c.quantile(0,0.1));
  EXPECT_FLOAT_EQ(0.5, c.quantile(0,0.5));
  EXPECT_FLOAT_EQ(0.9, c.quantile(0,0.9));
  
  EXPECT_THROW(c.quantile(2,0.9), std::out_of_range);

  // multi quantiles, single chain
  vector<double> qs;
  vector<double> probs(5);
  probs[0] = 0.025;  
  probs[1] = 0.25; 
  probs[2] = 0.5;
  probs[3] = 0.75;
  probs[4] = 0.975;
  c.quantiles(0,0, probs, qs);

  EXPECT_EQ(5U,qs.size());
  EXPECT_FLOAT_EQ(0.025,qs[0]);
  EXPECT_FLOAT_EQ(0.25,qs[1]);
  EXPECT_FLOAT_EQ(0.5,qs[2]);
  EXPECT_FLOAT_EQ(0.75,qs[3]);
  EXPECT_FLOAT_EQ(0.975,qs[4]);
  
  
  EXPECT_THROW(c.quantiles(5,0,probs,qs), std::out_of_range);
  EXPECT_THROW(c.quantiles(0,10,probs,qs), std::out_of_range);


  // multi quantiles, cross chains
  c.quantiles(0, probs, qs);

  EXPECT_EQ(5U,qs.size());
  EXPECT_FLOAT_EQ(0.025,qs[0]);
  EXPECT_FLOAT_EQ(0.25,qs[1]);
  EXPECT_FLOAT_EQ(0.5,qs[2]);
  EXPECT_FLOAT_EQ(0.75,qs[3]);
  EXPECT_FLOAT_EQ(0.975,qs[4]);
  
  
  EXPECT_THROW(c.quantiles(5,probs,qs), std::out_of_range);

  // bad prob test within and across
  probs[1] = 1.2;
  EXPECT_THROW(c.quantiles(0,probs,qs), std::invalid_argument);
  EXPECT_THROW(c.quantiles(0,0,probs,qs), std::invalid_argument);

  // central interval, single chain
  EXPECT_FLOAT_EQ(0.10,c.central_interval(0,0,0.8).first);
  EXPECT_FLOAT_EQ(0.90,c.central_interval(0,0,0.8).second);

  EXPECT_THROW(c.central_interval(2,0,0.8), std::out_of_range);
  EXPECT_THROW(c.central_interval(0,3,0.8), std::out_of_range);
  EXPECT_THROW(c.central_interval(0,0,1.2), std::invalid_argument);

  // central interval, cross chains
  EXPECT_FLOAT_EQ(0.10,c.central_interval(0,0,0.8).first);
  EXPECT_FLOAT_EQ(0.90,c.central_interval(0,0,0.8).second);

  EXPECT_THROW(c.central_interval(2,0.8), std::out_of_range);
  EXPECT_THROW(c.central_interval(0,1.2), std::invalid_argument);

  std::vector<double> samps;
  c.get_kept_samples(0,0,samps);
  EXPECT_FLOAT_EQ(stan::math::mean(samps),
                  c.mean(0,0));
  EXPECT_FLOAT_EQ(stan::math::sd(samps),
                  c.sd(0,0));
  EXPECT_FLOAT_EQ(stan::math::variance(samps),
                  c.variance(0,0));


  c.get_kept_samples_permuted(0,samps);
  EXPECT_FLOAT_EQ(stan::math::mean(samps),
                  c.mean(0));
  EXPECT_FLOAT_EQ(stan::math::sd(samps),
                  c.sd(0));
}
TEST(McmcChains,get_names) {
  std::vector<std::string> tokens;
  tokens.push_back("skip1");
  tokens.push_back("skip2.1");
  tokens.push_back("skip2.2");
  tokens.push_back("skip2.3");
  tokens.push_back("d");
  tokens.push_back("sigmasq_delta");
  tokens.push_back("mu.1");
  tokens.push_back("mu.2");
  tokens.push_back("mu.3");
  tokens.push_back("delta.1.1");
  tokens.push_back("delta.1.2");
  tokens.push_back("delta.1.3");
  tokens.push_back("sigma_delta");

  std::vector<std::string> expected_names;
  expected_names.push_back("d");
  expected_names.push_back("sigmasq_delta");
  expected_names.push_back("mu");
  expected_names.push_back("delta");
  expected_names.push_back("sigma_delta");
  

  std::vector<std::string> names;
  stan::mcmc::get_names(tokens, 2, names);
  ASSERT_EQ(expected_names.size(), names.size());
  for (size_t ii = 0; ii < expected_names.size(); ii++) {
    EXPECT_EQ(expected_names[ii], names[ii]);
  }
}
TEST(McmcChains,get_dimss) {
  std::vector<std::string> tokens;
  tokens.push_back("skip1");
  tokens.push_back("skip2.1");
  tokens.push_back("skip2.2");
  tokens.push_back("skip2.3");
  tokens.push_back("d");
  tokens.push_back("sigmasq_delta");
  tokens.push_back("mu.1");
  tokens.push_back("mu.2");
  tokens.push_back("mu.3");
  tokens.push_back("delta.1.1");
  tokens.push_back("delta.1.2");
  tokens.push_back("delta.1.3");
  tokens.push_back("sigma_delta");

  std::vector<std::vector<size_t> > expected_dimss;
  std::vector<size_t> dims;
  dims.clear(); dims.push_back(1);
  expected_dimss.push_back(dims);
  dims.clear(); dims.push_back(1);
  expected_dimss.push_back(dims);
  dims.clear(); dims.push_back(3);
  expected_dimss.push_back(dims);
  dims.clear(); dims.push_back(1); dims.push_back(3);
  expected_dimss.push_back(dims);
  dims.clear(); dims.push_back(1);
  expected_dimss.push_back(dims);

  std::vector<std::vector <size_t> > dimss;
  stan::mcmc::get_dimss(tokens, 2, dimss);
  ASSERT_EQ(expected_dimss.size(), dimss.size());
  for (size_t ii = 0; ii < expected_dimss.size(); ii++) {
    ASSERT_EQ(expected_dimss[ii].size(), dimss[ii].size());
    for (size_t jj = 0; jj < expected_dimss[ii].size(); jj++) {
      EXPECT_EQ(expected_dimss[ii][jj], dimss[ii][jj]);
    }
  }
}

TEST(McmcChains,read_variables) {
  //"src/test/mcmc/test_csv_files/blocker1.csv"
  //"src/test/mcmc/test_csv_files/blocker1.csv"
  std::vector<std::string> expected_names;
  std::vector<std::vector<size_t> > expected_dimss;
  expected_names.push_back("d");
  expected_names.push_back("sigmasq_delta");
  expected_names.push_back("mu");
  expected_names.push_back("delta");
  expected_names.push_back("sigma_delta");

  std::vector<size_t> dims;
  dims.push_back(1);
  expected_dimss.push_back(dims);
  expected_dimss.push_back(dims);
  dims.clear();
  dims.push_back(22);
  expected_dimss.push_back(dims);
  dims.clear();
  dims.push_back(22);
  expected_dimss.push_back(dims);
  dims.clear();
  dims.push_back(1);
  expected_dimss.push_back(dims);

  std::vector<std::string> names;
  std::vector<std::vector<size_t> > dimss;
  stan::mcmc::read_variables("src/test/mcmc/test_csv_files/blocker1.csv", 2, 
                             names, dimss);  

  // check names
  ASSERT_EQ(expected_names.size(), names.size());
  for (size_t i = 0; i < expected_names.size(); i++) {
    EXPECT_EQ(expected_names[i], names[i]);
  }
  // check dims
  ASSERT_EQ(expected_dimss.size(), dimss.size());
  for (size_t ii = 0; ii < expected_dimss.size(); ii++) {
    ASSERT_EQ(expected_dimss[ii].size(), dimss[ii].size());
    for (size_t jj = 0; jj < expected_dimss[ii].size(); jj++) {
      EXPECT_EQ(expected_dimss[ii][jj], dimss[ii][jj]);
    }
  }
}
TEST(McmcChains,read_values) {
  std::fstream file("src/test/mcmc/test_csv_files/blocker1.csv", 
                    std::fstream::in);
  std::vector<std::vector<double> > thetas;
  stan::mcmc::read_values(file, 3, thetas);
  file.close();
  EXPECT_EQ(1000U, thetas.size());
  EXPECT_EQ(3U, thetas[0].size());
  
  EXPECT_FLOAT_EQ(-0.272311,  thetas[0][0]);
  EXPECT_FLOAT_EQ(-0.0884699, thetas[0][1]);
  EXPECT_FLOAT_EQ(0.183328,   thetas[0][2]);
  
  EXPECT_FLOAT_EQ(-0.0652107,thetas[999][0]);
  EXPECT_FLOAT_EQ(-0.291459, thetas[999][1]);
  EXPECT_FLOAT_EQ(0.123128,  thetas[999][2]);
}
TEST(McmcChains,reorder_values) {
  std::vector<std::vector<double> > thetas;
  std::vector<double> theta;
  theta.clear();
  theta.push_back(0);
  theta.push_back(1);
  theta.push_back(2);
  theta.push_back(3);
  thetas.push_back(theta);
  theta.clear();
  theta.push_back(4);
  theta.push_back(5);
  theta.push_back(6);
  theta.push_back(7);
  thetas.push_back(theta);
  
  std::vector<size_t> from, to;
  from.push_back(0);
  from.push_back(3);
  from.push_back(2);
  to.push_back(3);
  to.push_back(0);
  to.push_back(1);
  
  stan::mcmc::reorder_values(thetas, from, to);
  EXPECT_FLOAT_EQ(3, thetas[0][0]);
  EXPECT_FLOAT_EQ(2, thetas[0][1]);
  EXPECT_FLOAT_EQ(2, thetas[0][2]);
  EXPECT_FLOAT_EQ(0, thetas[0][3]);

  EXPECT_FLOAT_EQ(7, thetas[1][0]);
  EXPECT_FLOAT_EQ(6, thetas[1][1]);
  EXPECT_FLOAT_EQ(6, thetas[1][2]);
  EXPECT_FLOAT_EQ(4, thetas[1][3]);
}
TEST(McmcChains,get_reordering) {
  std::vector<std::vector<size_t> > dimss;
  std::vector<size_t> dims;
  dims.push_back(1);
  dimss.push_back(dims);
  dims.clear();
  dims.push_back(2);
  dims.push_back(3);
  dimss.push_back(dims);
  dims.clear();
  dims.push_back(4);
  dimss.push_back(dims);
  
  std::vector<size_t> from, to;
  stan::mcmc::get_reordering(dimss, from, to);
  ASSERT_EQ(4U, from.size());
  ASSERT_EQ(from.size(), to.size());
   
  EXPECT_EQ(4U, from[0]);
  EXPECT_EQ(2U, from[1]);
  EXPECT_EQ(5U, from[2]);
  EXPECT_EQ(3U, from[3]);

  EXPECT_EQ(2U, to[0]);
  EXPECT_EQ(3U, to[1]);
  EXPECT_EQ(4U, to[2]);
  EXPECT_EQ(5U, to[3]);
}
TEST(McmcChains,add_chain_blocker){
  std::vector<std::string> names;
  std::vector<std::vector<size_t> > dimss;
  stan::mcmc::read_variables("src/test/mcmc/test_csv_files/blocker1.csv", 2,
                             names, dimss);

  stan::mcmc::chains<> c(2, names, dimss);
  add_chain(c, 0, "src/test/mcmc/test_csv_files/blocker1.csv", 2);
  EXPECT_EQ(1000U, c.num_samples(0));
  EXPECT_EQ(0U, c.num_samples(1));
  
  std::vector<double> samples;
  c.get_samples(0, 10, samples); // read mu.9 variable
  
  EXPECT_EQ(1000U, samples.size());
  EXPECT_FLOAT_EQ(-1.83165, samples[0]);
  EXPECT_FLOAT_EQ(-1.74223, samples[1]);
  EXPECT_FLOAT_EQ(-1.82474, samples[2]);
  EXPECT_FLOAT_EQ(-1.73014, samples[3]);
  EXPECT_FLOAT_EQ(-2.00418, samples[4]);
  EXPECT_FLOAT_EQ(-2.02338, samples[5]);
  EXPECT_FLOAT_EQ(-1.97366, samples[6]);
  EXPECT_FLOAT_EQ(-2.01551, samples[7]);
  EXPECT_FLOAT_EQ(-2.18117, samples[8]);
  EXPECT_FLOAT_EQ(-1.70432, samples[9]);
}
TEST(McmcChains,add_chain_epil){
  std::vector<std::string> names;
  std::vector<std::vector<size_t> > dimss;
  stan::mcmc::read_variables("src/test/mcmc/test_csv_files/epil1.csv", 2,
                             names, dimss);
  
  std::vector<size_t> from, to;
  stan::mcmc::get_reordering(dimss, from, to);

  stan::mcmc::chains<> c(2, names, dimss);
  add_chain(c, 1, "src/test/mcmc/test_csv_files/epil1.csv", 2);

  EXPECT_EQ(0U, c.num_samples(0));
  EXPECT_EQ(1000U, c.num_samples(1));

  std::vector<double> samples;
  c.get_samples(1, 6, samples); // b1.1
  EXPECT_FLOAT_EQ(-0.2471360, samples[0]);
  EXPECT_FLOAT_EQ(0.1692730, samples[1]);  
  EXPECT_FLOAT_EQ(0.0416239, samples[2]); 
  EXPECT_FLOAT_EQ(-0.0336843, samples[3]);  
  EXPECT_FLOAT_EQ(0.1142810, samples[4]);

  c.get_samples(1, 65, samples); // b.1.1
  EXPECT_FLOAT_EQ(0.8527490, samples[0]);
  EXPECT_FLOAT_EQ(-0.0965670, samples[1]);  
  EXPECT_FLOAT_EQ(-0.0645587, samples[2]); 
  EXPECT_FLOAT_EQ(0.5508860, samples[3]);  
  EXPECT_FLOAT_EQ(-0.0437883, samples[4]);

  c.get_samples(1, 66, samples); // b.2.1
  EXPECT_FLOAT_EQ(-0.50478600, samples[0]);
  EXPECT_FLOAT_EQ(-0.05057350, samples[1]);  
  EXPECT_FLOAT_EQ(-0.33083700, samples[2]); 
  EXPECT_FLOAT_EQ(0.00132672, samples[3]);  
  EXPECT_FLOAT_EQ(0.01302100, samples[4]);

  c.get_samples(1, 124, samples); // b.1.2
  EXPECT_FLOAT_EQ(0.110787, samples[0]);
  EXPECT_FLOAT_EQ(-0.484066, samples[1]);  
  EXPECT_FLOAT_EQ(0.575406, samples[2]); 
  EXPECT_FLOAT_EQ(-0.115558, samples[3]);  
  EXPECT_FLOAT_EQ(0.346112, samples[4]);
}

TEST(McmcChains,autocorrelation) {
  // duplicating test from stan::prob::autocorrelation
  std::vector<std::string> names;
  std::vector<std::vector<size_t> > dimss;
  std::vector<size_t> dims;

  names.push_back("param");
  dims.push_back(1);
  dimss.push_back(dims);
  stan::mcmc::chains<> c(2, names, dimss);

  std::fstream f("src/test/prob/ar1.csv");
  std::vector<double> y;
  for (size_t i = 0; i < 1000; ++i) {
     double temp;
     f >> temp;
     y.clear();
     y.push_back(temp);
     c.add(0U, y);
   }
  
   std::vector<double> ac;
   c.autocorrelation(0U, 0U, ac);

   EXPECT_EQ(1000U, ac.size());

   EXPECT_NEAR(1.00, ac[0],0.001);
   EXPECT_NEAR(0.80, ac[1], 0.01);
   EXPECT_NEAR(0.64, ac[2], 0.01);
   EXPECT_NEAR(0.51, ac[3], 0.01);
   EXPECT_NEAR(0.41, ac[4], 0.01);
   EXPECT_NEAR(0.33, ac[5], 0.01);
}
TEST(McmcChains,autocovariance) {
  // duplicating test from stan::prob::autocovariance
  std::vector<std::string> names;
  std::vector<std::vector<size_t> > dimss;
  std::vector<size_t> dims;

  names.push_back("param");
  dims.push_back(1);
  dimss.push_back(dims);
  stan::mcmc::chains<> c(2, names, dimss);

  std::fstream f("src/test/prob/ar1.csv");
  std::vector<double> y;
  for (size_t i = 0; i < 1000; ++i) {
     double temp;
     f >> temp;
     y.clear();
     y.push_back(temp);
     c.add(0U, y);
   }
  
   std::vector<double> ac;
   c.autocovariance(0U, 0U, ac);

   EXPECT_EQ(1000U, ac.size());

   EXPECT_NEAR(2.69, ac[0], 0.01);
   EXPECT_NEAR(2.16, ac[1], 0.01);
   EXPECT_NEAR(1.73, ac[2], 0.01);
   EXPECT_NEAR(1.38, ac[3], 0.01);
   EXPECT_NEAR(1.10, ac[4], 0.01);
   EXPECT_NEAR(0.90, ac[5], 0.01);
}

TEST(McmcChains,split_potential_scale_reduction) {
  std::vector<std::string> names;
  std::vector<std::vector<size_t> > dimss;
  stan::mcmc::read_variables("src/test/mcmc/test_csv_files/blocker1.csv", 2,
                             names, dimss);

  stan::mcmc::chains<> c(2, names, dimss);
  add_chain(c, 0, "src/test/mcmc/test_csv_files/blocker1.csv", 2);
  add_chain(c, 1, "src/test/mcmc/test_csv_files/blocker2.csv", 2);

  size_t index;
  std::vector<size_t> idxs;
  idxs.push_back(0);
  index = c.get_total_param_index(c.param_name_to_index("mu"), 
                                  idxs);
  EXPECT_FLOAT_EQ(1.187, c.split_potential_scale_reduction(index)) <<
    "mu.1 split R hat should be around 1.19";

  idxs.clear();
  idxs.push_back(21);
  index = c.get_total_param_index(c.param_name_to_index("delta"), 
                                  idxs);
  EXPECT_FLOAT_EQ(1.03715,  c.split_potential_scale_reduction(index)) <<
    "delta.22 split R hat should be near 1.04";
}
TEST(McmcChains,correlation) {
  std::vector<std::string> names;
  std::vector<std::vector<size_t> > dimss;
  stan::mcmc::read_variables("src/test/mcmc/test_csv_files/blocker1.csv", 2,
                             names, dimss);

  stan::mcmc::chains<> c(2, names, dimss);
  add_chain(c, 0, "src/test/mcmc/test_csv_files/blocker1.csv", 2);
  add_chain(c, 1, "src/test/mcmc/test_csv_files/blocker2.csv", 2);

  size_t index1, index2;
  std::vector<size_t> idxs;
  idxs.push_back(0);
  index1 = c.get_total_param_index(c.param_name_to_index("mu"), 
                                  idxs);
  idxs.clear();
  idxs.push_back(1);
  index2 = c.get_total_param_index(c.param_name_to_index("mu"), 
                                  idxs);
  EXPECT_FLOAT_EQ(0.3615289,   c.correlation(0U, index1, index2)) <<
    "correlation of chain 0";
  EXPECT_FLOAT_EQ(-0.06527095, c.correlation(1U, index1, index2)) <<
    "correlation of chain 1";
  EXPECT_FLOAT_EQ(0.1845687,   c.correlation(index1, index2)) <<
    "correlation";
}

*/
