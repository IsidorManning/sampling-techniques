#include "Sampling_Techniques.cpp"
#include <iostream>

int main() {
  Sampling sampler; 

  double my_uniform_number = sampler.uniform(0, 100);
  std::cout << "My uniform number: " << my_uniform_number << std::endl;

  double my_gaussian_number = sampler.gaussian(50, 10);
  std::cout << "My gaussian number: " << my_gaussian_number << std::endl;

  double my_exponential_number = sampler.exponential(2, 5);
  std::cout << "My exponential number: " << my_exponential_number << std::endl;

  double my_logarithmic_number = sampler.logarithmic(4);
  std::cout << "My logarithmic number: " << my_logarithmic_number << std::endl;

  double my_poisson_number = sampler.poisson(10, 10);
  std::cout << "My poisson number: " << my_poisson_number << std::endl;

  double my_bernoulli_number = sampler.bernoulli(0.5);
  std::cout << "My bernoulli number: " << my_bernoulli_number << std::endl;

  double my_binomial_number = sampler.binomial(10, 0.5);
  std::cout << "My binomial number: " << my_binomial_number << std::endl;

  double my_beta_number = sampler.beta(2, 2);
  std::cout << "My beta number: " << my_beta_number << std::endl;

  double my_gamma_number = sampler.gamma(4, 2.5);
  std::cout << "My gamma number: " << my_gamma_number << std::endl;

  return 0;
} 
