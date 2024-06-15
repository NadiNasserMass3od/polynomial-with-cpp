# polynomial-with-cpp

A polynomial is an expression that is constructed from one or more variables and constants, using only the operations of addition, subtraction, multiplication, and constant positive integer number exponents. For example, x^2-4x+7 is a polynomial, but x^2- 4/x+ 7x^(3/2) is not a polynomial because it involves division by a variable and because it has an exponent that is not a positive integer number.

This code implements a polynomial using C++ with a linked list data structure.

The functions in this code include:

  1. Constructor to build an empty polynomial and a copy constructor.
  2. print() to print the polynomial in mathematical form.
  3. add_term(double &c, int &e) to add a term to the polynomial.
  4. remove_term(int &e) to remove the term with exponent e.
  5. p_copy() to return a copy of the polynomial.
  6. poly_val(double &x) to return the polynomial's value at x.
  7. mul_term(double &c, int &e) to multiply all terms in the polynomial by 𝑐𝑥^𝑒 and return the result as another polynomial.
  8. operator==(Polynomial &p) to check if the current polynomial is equal to p.
  9. operator!=(Polynomial &p) to check if the current polynomial is not equal to p.
  10. operator+(Polynomial &p) to add the current polynomial to p and return the result.
  11. operator-(Polynomial &p) to subtract p from the current polynomial and return the result.
  12. operator*(Polynomial &p) to multiply the current polynomial with p and return the result.
  13. operator/(Polynomial &divisor) to divide the current polynomial by divisor and return the result.
  14. operator%(Polynomial &divisor) to divide the current polynomial by divisor and return the remainder.
  15. integrate() to integrate the current polynomial and return the result.
  16. differentiate() to differentiate the current polynomial and return the result.
