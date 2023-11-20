#include "Sampling_Techniques.h"
#include <math.h>
#include <ctime>
#include <sstream>

Sampling::Sampling() {
  // Altough our constructor is very simple, I want to talk about one interesting
  // problem which I struggled a lot with in the beginning: I wanted to be able to
  // generate many different numbers based on some distribution by calling one
  // of the main methods multiple times. However, the problem I stubbled upon
  // was that if I called the same function (say "gaussian()") multiple times to try
  // to generate multiple different gaussian numbers, then it would just generate
  // the same number for all calls. I knew it had something to do with the
  // initialization of the seed so I tried placing the seed initialization code, on
  // line 26, in the main() function, in the gaussian() function itself and pretty much 
  // everywhere else except in the constructor. when I finally tried to place the line 
  // here, it suddenly worked. I found out that this is due to the fact that when I 
  // called the srand() function in the gaussian() function (the method I was calling 
  // multiple times), it led to initialization of the same seed over and over again,  
  // resulting in the same generation of numbers. By moving the seed initialization  
  // in the constructor we ensure that the seed is set only once when an instance 
  // of the class is created. In this way, it not only fixes the orginal problem  
  // but it also encapsulates the seed initialization logic of the class.
  srand((unsigned) time(nullptr));
}

double Sampling::get_random_prob() {
  // This method generates a pseudo-random number within the range [0, 1) which
  // we will use to represent some random probability.
  double generated_number = int_to_double(rand()) / RAND_MAX;
  return generated_number; 
}

double Sampling::calculate_factorial(double n) {
  // This method simply calculates the factorial of the given number "n".

  // The next if-statement just ensures that the user can't provide us with a 
  // negative number to take the factorial of (since produces an error). We 
  // return 0 if the user inputs an invalid value for the parameter "n".
  if (n < 0) return int_to_double(0);

  double factorial_of_n = 1; // initialization.
  for (int i = 1; i <= n; ++i) factorial_of_n *= i;

  return factorial_of_n;
}

double Sampling::binomial_coefficient(int n, int k) {
  // This function calculates the binomial coefficient ("n choose k"), representing 
  // the number of ways to choose k elements from a set of n distinct elements. 
  // The binomial coefficient is defined by the following relation, computed
  // recursively: 
  //
  // C(n, k) = C(n - 1, k - 1) + C(n - 1, k).

  // when k is 0 or equal to n, there is only one way to choose "n choose 0" or 
  // "n choose n", which is 1, hence, the need for the next line.
  if (k == 0 || k == n) return 1;
  else return binomial_coefficient(n - 1, k - 1) + binomial_coefficient(n - 1, k);
}

int Sampling::gamma_function(int n) {
  // This method is used to calculate the gamma function for a given number ("n")
  // which we assume to be a positive number. Note that it is possible to compute
  // the gamma function for all complex numbers, I simply haven't made the 
  // implementation. If you're interested, look up "Lanczos Approximation".
  //
  // f(n) = (n - 1)!, 
  // where n is a positive integer.

  // we return 0 if the user inputs an invalid value for the parameter "n".
  if (n <= 0) return nan_value;

  return calculate_factorial(n - 1);
}

// With the next couple of method implementations, we want to generate a random 
// number that is based on the specific distribution that the user choose. The
// distributions the user has to choose from are the following:
// 
// - Uniform
// - Gaussian
// - Exponential
// - Logarithmic 
// - Poisson
// - Bernoulli
// - Binomial
// - Beta
// - Gamma

double Sampling::uniform(int min, int max) {
  // This method is designed to generate a pseudo-random floating-point
  // whole number. within a specified range, inclusive of the minimum 
  // value ("min") and exclusive of the maximum value ("max").
  
  // One thing that I found is both very important and interesting to note here
  // is that the modulus operator (%) cannot be directly applied to floating-point 
  // numbers in C++. It can only be applied with integer numbers. I found out about
  // this when I initially tried to define the following line in this way:
  // "double generated_number = int_to_double(rand()) % (max - min + 1) + min".
  // Using this line above instead will produce a compiler error.

  // The next if-statement ensures that min is less than or equal to max.
  if (min > max) return nan_value;

  // Generate a random floating-point whole number between 0 and 1.
  int generated_number = rand() % (max - min + 1) + min;

  return int_to_double(generated_number); 
}

double Sampling::gaussian(double mean, double stddev) {
  // We use the Box-Muller transformation to generate a number following a gaussian
  // distribution and which got the desired mean ("mean") and standard deviation 
  // ("stddev").
  //
  // The transformation states that if we take two random variables with seperate
  //  values ("u_1" & "u_2"), then an independent random variable ("z") with a 
  // gaussian distribution can be written as z = √(-2 * ln(u_1)) * cos(2 * π * u_2).

  double u_1 = int_to_double(rand()) / RAND_MAX;
  double u_2 = int_to_double(rand()) / RAND_MAX; 
  // Use the Box-Muller transform to generate a number with a Gaussian distribution.
  double z_0 = sqrt(-2.0 * log(u_1)) * cos(2.0 * M_PI * u_2);
  // Scale and shift the result to match the desired mean and standard deviation.
  double generated_number = mean + stddev * z_0;

  return generated_number;
}

double Sampling::exponential(double lambda, int max) {
  // This method generates a number between 0 and the provided upper boundary 
  // ("max") that follows an exponential distribution. The hyperparameter 
  // "lambda" is used for scaling (this hyperparameter is also called the 
  // "rate parameter" sometimes).
  //
  // f(λ, "max") = λe^(-λu), 
  // where λ is the rate parameter, and where u is some random number ∈ [0, "max").

  // we return NaN if the user inputs an invalid value for the parameter "lambda".
  if (lambda <= 0) return nan_value;

  // Generate a number with a uniform distribution from 0 to the provided "max".
  double u = uniform(0, max); 
  // Manipulate the random number, "u", so that it follows an exponential 
  // distribution.
  double generated_number = lambda * exp(-lambda * u);

  return generated_number;
}

double Sampling::logarithmic(int rate) {
  // This method generates a number that follows a logarithmic distribution.
  // The hyperparameter "rate" is used to shape the distribution and how
  // quicky or slowly the probability it outputs decreases as the input variable
  // increases (in our case, this would be the generated probability "p").
  //
  // f(k) = [-1 / ln(1 - p)] * [p^k / k], 
  // where k is our parameter "rate", and where p is some random 
  // number ∈ [0, "max").

  // We do not accept "rate" to be under 1 since we want the expression
  // "[p^rate / rate]" to remain well-defined and stable so that we won't 
  // have division by zero or by negative numbers. We return NaN if the user 
  // inputs an invalid value for the parameter "rate".
  if (rate < 1) return nan_value;

  // Generate a floating-point double number from 0 to 1.
  double p = get_random_prob();
  // Manipulate the random number, "p", so that it follows a logarithmic 
  // distribution.    
  double generated_number = (-1 / log(1 - p)) * (pow(p, rate) / rate);

  return generated_number;
}

double Sampling::poisson(double lambda, int max) {
  // This method generates a number between 0 and the provided upper boundary 
  // ("max") that follows a poisson distribution. The hyperparameter "lambda" 
  // is used to represent the averege rate of events. "rate of events" here 
  // describes the number of events that occur within a fixed interval when 
  // these events happen with a known constant mean rate.
  //
  // f(λ) = (λ^u * e-λ) / u!, 
  // where λ is the rate of events, and where u is some random number ∈ [0, "max").

  // We do not accept lambda to be a non-positve number since it would be 
  // irrational to have a negative value for something that is representating
  // the rate of something (in our case, "rate of events"). We return NaN if 
  // the user inputs an invalid value for the parameter "lambda".
  if (lambda <= 0) return nan_value;

  // Generate a number with a uniform distribution from 0 to the provided "max".
  double u = uniform(0, max); 
  // Manipulate the random number, "u", so that it follows a poisson distribution.
  double generated_number = (pow(lambda, u) * exp(-lambda)) / 
    calculate_factorial(u);

  return generated_number;
}

double Sampling::bernoulli(double proba) {
  // This method generates a binary or boolean number (either a 1 or a 0) that  
  // follows a Bernoulli distribution, given a probability ("proba").
  //
  // f(proba) = { p for u = 1; 1 - p for u = 0 }, 
  // where p is our parameter "proba", and where u is some random 
  // number ∈ [0, 1).

  // The next if-statement just ensures that the user can't provide us with a 
  // negative probability (since this would be irrational to have). We return 
  // NaN if the user inputs an invalid value for the parameter "proba".
  if (proba < 0) return nan_value;

  double u = get_random_prob(); // Generate a random number from 0 to 1.
  // Manipulate the random number, "p", so that it follows a bernoulli 
  // distribution.    
  double generated_number;
  if (proba < u) generated_number = 1.;
  else generated_number = 0;

  return generated_number;
}

double Sampling::binomial(int num_trails, double proba) {
  // This method generates a number following a binomial distribution, based 
  // on a given probability of success ("proba") and on a set number of trials 
  // ("num_trials"). The binomial distribution models the number of successes 
  // in a fixed number of independent trials (often called "bernoulli trails)"), 
  // where each trial has the same probability of success.
  //
  // The algorithm first generates 'num_trials' independent uniform random numbers 
  // between 0 and 1. If a generated number is less than the specified probability, 
  // it is considered a success, and the count of successes ("generated_number") is 
  // incremented.
  //
  // f(n, p) = [n! / k!(n - k)!] * p^k * (1 - p)^(n - k),
  // where n is the parameter "num_trails", p is the parameter "proba",
  // and where k is the number of successes we are currently evaluating.

  double generated_number = 0; // initilization. This is our "success count".

  for (int k = 0; k <= num_trails; ++k) {
    double probability = binomial_coefficient(num_trails, k) * pow(proba, k) *
      pow(1 - proba, num_trails - k);
    // Use a random number between 0 and 1 to decide whether k occurs or not.
    double u = get_random_prob(); // Generate a random number from 0 to 1.

    if (u < probability) {
      generated_number = int_to_double(k);
      break;
    }
  }
  return generated_number;
}

double Sampling::beta(double alpha, double beta) {
  // This method generates a number following a beta distribution given two 
  // hyperparameters, "alpha" (α) and "beta" (β). The two hyperparameters 
  // controls the overall shape of the distribution; α controls the shape of 
  // the distribution on the left side (near 0). Larger values of α result in 
  // a distribution that is more focused toward 1. Similarly, β controls the 
  // shape of the distribution on the right side (near 1). Larger values of β 
  // result in a distribution that is more focused toward 0.
  //
  // f(α, β) = u^(α - 1) * (1 - u)^(β - 1),
  // where α and β are the parameters "alpha" and "beta", respectively, and 
  // where u is some random number ∈ [0, 1).

  // We do not accept "alpha" and "beta" to be non-positve since we want to 
  // maintain the distributions coherence and to always keep the it well-defined.
  // we return 0 if the user inputs an invalid value for the parameters 
  // "alpha" and "beta".
  if (alpha <= 0 || beta <= 0) return nan_value;

  double u = get_random_prob(); // Generate a random number from 0 to 1.
  // Manipulate the random number, "p", so that it follows a beta distribution.    
  double generated_number = pow(u, (alpha - 1)) * pow((1 - u), (beta - 1));
  
  return generated_number;
}

double Sampling::gamma(double alpha, double beta, int max) {
  // This method generates a number following a gamma distribution given two 
  // hyperparameters, "alpha" (α) and "beta" (β). The first hyperparameter 
  // ("alpha") controls the shape of the distribution and where the second 
  // hyperparameter ("beta") controls the rate at which the gamma distribution
  // decreases (this is similar to the "rate parameter" ("rate") we encountered 
  // in the exponential distribution). 
  //
  // f(α, β) = [u^(α - 1) * e^(-βu) * β^α] / Γ(α), 
  // where α and β are the parameters "alpha" and "beta", respectively, where u 
  // is some random number ∈ [0, "max"), and where Γ is the gamma function.

  // The reason behind restricting the hyperparameters ("alpha" and "beta") is 
  // very similar to the reason provided in the beta distribution: we do not accept 
  // "alpha" and "beta" to be non-positve since we want to maintain the distributions
  // coherence and to always keep the it well-defined. We return 0 if the user inputs 
  // an invalid value for the parameters "alpha" and "beta".
  if (alpha <= 0 || beta <= 0) return nan_value;

  // Generate a number with a uniform distribution from 0 to the provided "max".
  double u = uniform(0, max);
  // Manipulate the random number, "p", so that it follows a gamma distribution.
  double gamma_of_alpha = int_to_double(gamma_function(int_to_double(alpha)));
  double generated_number = (pow(u, (alpha - 1)) * exp(-beta * u) * pow(beta, alpha)) /
    gamma_of_alpha;

  return generated_number;
}
