#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "node.h"
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class Polynomial {
private:
  Node *head;

public:
  Polynomial(Node *h = NULL);
  Polynomial(const Polynomial &p);
  ~Polynomial();
  void print() const;
  void add_term(const double &c, const int &e);
  Polynomial p_copy() const;
  void remove_term(const int &e);
  double poly_val(const double &x) const;
  Polynomial mul_term(const double &c, const int &e) const;
  bool operator==(const Polynomial &p) const;
  bool operator!=(const Polynomial &p) const;
  Polynomial operator+(const Polynomial &p) const;
  Polynomial operator-(const Polynomial &p) const;
  Polynomial operator*(const Polynomial &p) const; // complexity O(n^2)?
  Polynomial operator/(const Polynomial &divisor) const;
  Polynomial operator%(const Polynomial &divisor) const;
  Polynomial integrate() const;
  Polynomial differentiate() const;
};

#endif // POLYNOMIAL_H
