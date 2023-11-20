#ifndef Sampling_Techniques_h
#define Sampling_Techniques_h

// Before documenting everything, I will quickly go through the functionality
// and conceptI will utilize in this project. I haven't seen us using them 
// much in class, nor in the coding problems so I felt the need for describing 
// them first:

// static_cast<>(): A type of unary operator which essentially forces one data 
//type to become another data type. This specific type of cast operator is a
// static cast operator and we use it to force conversion between
// different data types such as size_t and double, int and double, 
// and int and size_t. We will want to return our generated numbers 
// as doubles but some operations we will use such as rand() return an int.
// To convert the int to a double we will use the static cast operator.

// The math library: A library included which provides us with more advanced
// mathematical functions and operations other than our standard arithmetic ones.

// Recursion: Basically a programming concept where a function calls itself in 
// order to solve a smaller instance of the same problem. We use recursion
// in the "binomial_coefficient()" function.

// Not-a-number ("NaN" or "nan"): Used to represent an undefined result. We
// will use this special type of number in order to handle situations where
// the user inputs a value for a parameter that is not allowed. 

class Sampling {
private:

  // Here we define our "not-a-value" (nan) representation which we will use to
  // return to the user if they input invalid values for parameters.
  double nan_value = 0. / 0.; // By default, divisiom by zero returns nan in C++.

  // Declare a method to force-convert a double to an integer
  double int_to_double(int n) { return static_cast<double>(n); }

 // This method will be used to generate a decimal value between 0 and 1.
  double get_random_prob();

  // Since the standard C++ library doesn't come with a sophisticated
  // function for calculating facorials, we will need to make one of our own.
  double calculate_factorial(double n); 
  // The binomial coefficient will be used in order to calculate a number based
  // on the binomial distribution.
  double binomial_coefficient(int n, int k);
    // The gamme function is a mathematical function used in calculating both
  // a number based on a beta distribution, as well as on a gamma distribution.
  int gamma_function(int n);

public:
  Sampling();

  // The next chunk of methods are the main methods the user of the class can 
  // use in order to generate a number based on a specific distribution.
  double uniform(int min, int max);
  double gaussian(double mean, double stddev);
  double exponential(double lambda, int max);
  double logarithmic(int k);
  double poisson(double lambda, int max);
  double bernoulli(double proba);
  double binomial(int num_trails, double proba);
  double beta(double alpha, double beta);
  double gamma(double alpha, double beta, int max=50);
};
#endif
