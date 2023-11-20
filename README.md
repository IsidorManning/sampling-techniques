# sampling-techniques


# Background and context

First of all, let me provide some information that is relevant to this project: when we generate random numbers we have often used the pseudo-random generator rand() which is a function that provides us with an integer from 0 to RAND_MAX. The process of generating numbers or samples by some specific technique, equation, or distribution is called "sampling".

The idea for this particular project came to me from one thing I remember hearing from my Professor. I remember that he said that there are more ways to generate numbers than to simply use the rand() function such as generating a number based on a normal (or gaussian) distribution. This is where I got the idea to essentially create a class in C++ that would provide a user with many different distributions that they then could use to generate a number.

The goal was to code implementations for many distributions without using any external libraries. I tried to only use the rand() function and not utilize more modern C++ solutions such as the <random> library.
Before moving on, there are a lot of maths included in this project and although I really enjoyed learning more about the details of each distribution, I don't think it is worth covering it in depth here nor in the documentation in the code. This is a computer science class so the goal of this project was to quickly search up the formulas of the distributions and then represent them in code. The goal is not to get a deep sense of what a specific distribution represents, how to calculate it by hand, and to know what every single one of its variables represents. In this case, we just need to have a somewhat broad understanding before we can implement it in code!


# The design

All of the functionality is kept within a class called "Sampling". We define some private methods which are not intended for the user to use (this is the reason why it is private) such as get_random_prob(), calculate_factorial(), binomial_coefficient(), and gamma_function(). These are functions that only we define in order to later use them in the public methods for calculating the distributions themselves!
We then have a bunch of public methods within the class Sampling; firstly, we have our good-old constructor which we only use to initialize the seed for the rand() function using the familiar line: srand((unsigned) time(nullptr)).

Then we have the implementations for the 9 different distributions that our user can call to generate a floating-point number of data type "double", based on the chosen distribution. These distributions also take values for different parameters so the user further can customize the shape of their distribution.

Some values for parameters that are used in some methods/distributions include upper- and lower boundaries, desired mean, desired standard deviation, rate factors, and shape scaling factors. Other than that, it is also important for the end-user3 to note that we also set default values for parameters in some functions such as in the gamma() function where we have the following declaration:

double gamma(double alpha, double beta, int max=50);

What this means is that a value for the parameter int max in the gamma() function will be assigned to 50 by default if not a specific value is inputted by the user.

To actually implement the various equations and formulas for the distributions we sometimes use pre-defined functionality included in the <math.h> header file to calculate cosines, square roots, logarithms, exponentials (e^x), and powers. We also use it to easily get the value of π (pi).

It is crucial for us to note that all of our distributions return numbers that are of type "double". You can see at the top of the header file that we declare a private method called int_to_double(int n) that uses a unary operator4 called static cast (static_cast<>()) to force a data type into another one. This is useful to us since the rand() function returns a number that is of type "int" and since we want to compute and return numbers of type "double" we need to define a method for converting integers to doubles.

One last thing I want to talk about is the type of Not-a-number (nan or NaN)5. We use the nan_value variable to handle errors; more specifically we return this value to the end-user when they have inputted a value for a parameter that is not allowed (for example, giving a value of -0.4 for a parameter representing a probability).


# Challenges and lessons

Other than learning more about the distributions themselves, I learned tons about data conversions as well as pseudo-random number generators (PRNGs) such as the rand() in our case. We also start to handle errors here which we have done before and which is really important when writing more sophisticated programs. I talk more about different challenges and problems that occurred in the comments of the code itself.  However, one thing that I found both very important and interesting is that the modulus operator (%) cannot be directly applied to floating-point numbers in C++. It can only be applied to integer numbers. I found out about this when I, throughout the process of making the project, tried to run the following line of code which produced a compiler error:

double generated_number = int_to_double(rand()) % (max - min + 1) 

Thanks for reading and I hope you found this interesting! I'll update the text and code if bugs or errors appear.


# Additional notes

1) What is "pseudo-random"?: What this term implies is that we have a number that appears to look random but that technically is not fully random. In our case, rand() is still initialized with a seed via the srand() function that ultimately determines what number gets generated.
2) What is "proba"?: An acronym for "probability" :-)
3) What is an "end-user": This would be the person who wants to use our class Sampling to actually use it properly (to generate numbers based on different distributions). An end-user refers to the entity or person who will actually use the final result of some project or product.
4) What is a "unary operator"?: From my understanding so far,  a unary operator is a specific type of operator that only takes in one operand and produces only one result. Some unary operators include the unary minus operator, post-increment and pre-increment operators (as well as their decrement operators), the not-operator, the "address of" operator, and the "sizeof" operator.
5) What is this "nan" thing you're talking about?:  The NaN value is used to represent an undefined result or something that we simply cannot express other than an error of some sort. For example, the operation 0. / 0. will output nan since division by zero is undefined.
