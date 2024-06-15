#include "polynomial.h"
#include <cstddef>

Polynomial::Polynomial(Node *h) : head(h) {}

Polynomial::Polynomial(const Polynomial &p) {
  head = NULL;
  Node *curold = p.head;
  Node *current = head;
  while (curold != NULL) {
    Node *newNode = new Node;
    newNode->coef = curold->coef;
    newNode->exp = curold->exp;
    newNode->next = NULL;
    if (head == NULL) {
      head = newNode;
      current = head;
      curold = curold->next;
      continue;
    } else
      current->next = newNode;
    current = current->next;
    curold = curold->next;
  }
}

Polynomial::~Polynomial() {
  Node *old = head;
  while (head != NULL) {
    head = head->next;
    delete old;
    old = head;
  }
  delete head;
}

void Polynomial::print() const {
  Node *current = head;
  while (current != NULL) {
    if (current == head) {
      if (current->exp == 1) {
        if (current->coef == 0) {
          current = current->next;
          continue;
        }
        if (current->coef == 1) {
          cout << "x";
          current = current->next;
          continue;
        }
        if (current->coef == -1) {
          cout << "-x";
          current = current->next;
          continue;
        } else {
          cout << current->coef << "x";
          current = current->next;
          continue;
        }
      }
      if (current->exp == 0) {
        if (current->coef == 0) {
          current = current->next;
          continue;
        } else {
          cout << current->coef;
          current = current->next;
          continue;
        }
      }
      if (current->coef == 0) {
        current = current->next;
        continue;
      }
      if (current->coef == 1) {
        cout << "x^" << current->exp;
        current = current->next;
        continue;
      }
      if (current->coef == -1) {
        cout << "-x^" << current->exp;
        current = current->next;
        continue;
      } else {
        cout << current->coef << "x^" << current->exp;
        current = current->next;
        continue;
      }
    }
    if (current->exp == 1) {
      if (current->coef == 0) {
        current = current->next;
        continue;
      } else if (current->coef == 1) {
        cout << "+x";
        current = current->next;
        continue;
      } else if (current->coef == -1) {
        cout << "-x";
        current = current->next;
        continue;
      } else if (current->coef > 0) {
        cout << "+" << current->coef << "x";
        current = current->next;
        continue;
      } else if (current->coef < 0) {
        cout << current->coef << "x";
        current = current->next;
        continue;
      }
    }
    if (current->exp == 0) {
      if (current->coef == 0) {
        current = current->next;
        continue;
      } else if (current->coef > 0) {
        cout << "+" << current->coef;
        current = current->next;
        continue;
      } else if (current->coef < 0) {
        cout << current->coef;
        current = current->next;
        continue;
      }
    }
    if (current->coef == 0) {
      current = current->next;
      continue;
    } else if (current->coef == 1) {
      cout << "+x^" << current->exp;
      current = current->next;
      continue;
    } else if (current->coef == -1) {
      cout << "-x^" << current->exp;
      current = current->next;
      continue;
    } else if (current->coef > 0) {
      cout << "+" << current->coef << "x^" << current->exp;
      current = current->next;
      continue;
    } else if (current->coef < 0) {
      cout << current->coef << "x^" << current->exp;
      current = current->next;
      continue;
    }
  }
}

void Polynomial::add_term(const double &c, const int &e) {
  if (e < 0) {
    cout << "Error in exponent\n";
    return;
  }
  if (c == 0) {
    remove_term(e);
    return;
  }
  Node *old = head;
  if (head == NULL) {
    Node *newNode = new Node;
    newNode->coef = c;
    newNode->exp = e;
    newNode->next = head;
    head = newNode;
    return;
  }
  if (head->exp == e) {
    head->coef = c;
    return;
  }
  while (old != NULL) {
    if (old->exp == e) {
      old->coef = c;
      return;
    }
    old = old->next;
  }

  Node *newNode = new Node;
  newNode->coef = c;
  newNode->exp = e;
  newNode->next = head;
  head = newNode;

  // for sort
  int test = 1;
  while (test) {
    if (head == NULL || head->next == NULL) {
      test = 0;
      continue;
    }
    Node *current = head;
    Node *pre = current;
    Node *next = current;
    while (current != NULL) {
      pre = current;
      while (pre->next != NULL) {
        next = pre->next;
        if (current->exp < next->exp && current == head) {
          pre->next = next->next;
          next->next = current;
          current = next;
          head = current;
          continue;
        }
        if (current->exp < next->exp) {
          Node *prec = head;
          while (prec->next != current) {
            prec = prec->next;
          }
          pre->next = next->next;
          next->next = current;
          prec->next = next;
          current = next;
          continue;
        }
        pre = pre->next;
      }
      current = current->next;
    }
    test = 0;
  }
}

Polynomial Polynomial::p_copy() const {
  Polynomial temp;
  if (head == NULL) {
    temp.head = NULL;
    return temp;
  }
  temp.head = NULL;
  Node *cur = head;
  while (cur != NULL) {
    temp.add_term(cur->coef, cur->exp);
    cur = cur->next;
  }
  return temp;
}

void Polynomial::remove_term(const int &e) {
  Node *old = head;
  if (head == NULL)
    return;
  if (head->exp == e) {
    head = head->next;
    delete old;
    return;
  }
  Node *pre = old;
  old = old->next;
  while (old != NULL) {
    if (old->exp == e) {
      pre->next = old->next;
      delete old;
      return;
    }
    pre = old;
    old = old->next;
  }
}

double Polynomial::poly_val(const double &x) const {
  double ans = 0;
  if (head == NULL) {
    cout << "empty\n";
    return 0;
  }
  Node *cur = head;
  double temp;
  while (cur != NULL) {
    temp = 1;
    for (int i = 1; i <= cur->exp; i++) {
      temp *= x;
    }
    ans += cur->coef * temp;
    cur = cur->next;
  }
  return ans;
}

Polynomial Polynomial::mul_term(const double &c, const int &e) const {
  Polynomial temp;
  if (head == NULL) {
    cout << "empty\n";
    return temp;
  }
  Node *cur = head;
  while (cur != NULL) {
    if (e + cur->exp < 0) {
      cout << "Cann't multiple this\n";
      exit(0);
    }
    cur = cur->next;
  }
  cur = head;
  while (cur != NULL) {
    temp.add_term(c * cur->coef, e + cur->exp);
    cur = cur->next;
  }
  return temp;
}

bool Polynomial::operator==(const Polynomial &p) const {
  Node *curorg = head;
  Node *curout = p.head;
  if (curorg == NULL && curout == NULL)
    return true;
  {
    int count1 = 0, count2 = 0;
    while (curorg != NULL) {
      count1++;
      curorg = curorg->next;
    }
    while (curout != NULL) {
      count2++;
      curout = curout->next;
    }
    if (count1 != count2)
      return false;
  }
  curorg = head;
  curout = p.head;
  while (curorg != NULL) {
    curout = p.head;
    while (curout != NULL) {
      if (curout->exp == curorg->exp && curorg->coef == curout->coef) {
        break;
      }
      curout = curout->next;
      if (curout == NULL)
        return false;
    }
    curorg = curorg->next;
  }
  return true;
}

bool Polynomial::operator!=(const Polynomial &p) const {
  Node *curorg = head;
  Node *curout = p.head;
  if (curorg == NULL && curout == NULL)
    return false;
  {
    int count1 = 0, count2 = 0;
    while (curorg != NULL) {
      count1++;
      curorg = curorg->next;
    }
    while (curout != NULL) {
      count2++;
      curout = curout->next;
    }
    if (count1 != count2)
      return true;
  }
  curorg = head;
  curout = p.head;
  while (curorg != NULL) {
    curout = p.head;
    while (curout != NULL) {
      if (curout->exp == curorg->exp && curorg->coef == curout->coef) {
        break;
      }
      curout = curout->next;
      if (curout == NULL)
        return true;
    }
    curorg = curorg->next;
  }
  return false;
}

Polynomial Polynomial::operator+(const Polynomial &p) const {
  Polynomial temp;
  Node *curorg = head;
  Node *curout = p.head;
  if (curorg == NULL && curout == NULL)
    return temp;
  if (curorg == NULL) {
    temp.head = NULL;
    Node *cur = p.head;
    while (cur != NULL) {
      temp.add_term(cur->coef, cur->exp);
      cur = cur->next;
    }
    return temp;
  }
  if (curout == NULL) {
    temp.head = NULL;
    Node *cur = head;
    while (cur != NULL) {
      temp.add_term(cur->coef, cur->exp);
      cur = cur->next;
    }
    return temp;
  }
  while (curorg != NULL) {
    curout = p.head;
    while (curout != NULL) {
      if (curout->exp == curorg->exp) {
        temp.add_term(curorg->coef + curout->coef, curorg->exp);
        break;
      }
      curout = curout->next;
      if (curout == NULL)
        temp.add_term(curorg->coef, curorg->exp);
    }
    curorg = curorg->next;
  }
  {
    curorg = head;
    curout = p.head;
    while (curout != NULL) {
      curorg = head;
      while (curorg != NULL) {
        if (curout->exp == curorg->exp)
          break;
        curorg = curorg->next;
        if (curorg == NULL) {
          temp.add_term(curout->coef, curout->exp);
          break;
        }
      }
      curout = curout->next;
    }
  }
  return temp;
}

Polynomial Polynomial::operator-(const Polynomial &p) const {
  Polynomial temp;
  Node *curorg = head;
  Node *curout = p.head;
  if (curorg == NULL && curout == NULL)
    return temp;
  if (curorg == NULL) {
    temp.head = NULL;
    Node *cur = p.head;
    while (cur != NULL) {
      temp.add_term(-cur->coef, cur->exp);
      cur = cur->next;
    }
    return temp;
  }
  if (curout == NULL) {
    temp.head = NULL;
    Node *cur = head;
    while (cur != NULL) {
      temp.add_term(cur->coef, cur->exp);
      cur = cur->next;
    }
    return temp;
  }
  while (curorg != NULL) {
    curout = p.head;
    while (curout != NULL) {
      if (curout->exp == curorg->exp) {
        temp.add_term(curorg->coef - curout->coef, curorg->exp);
        break;
      }
      curout = curout->next;
      if (curout == NULL)
        temp.add_term(curorg->coef, curorg->exp);
    }
    curorg = curorg->next;
  }
  {
    curorg = head;
    curout = p.head;
    while (curout != NULL) {
      curorg = head;
      while (curorg != NULL) {
        if (curout->exp == curorg->exp)
          break;
        curorg = curorg->next;
        if (curorg == NULL) {
          temp.add_term(-curout->coef, curout->exp);
          break;
        }
      }
      curout = curout->next;
    }
  }
  return temp;
}

Polynomial Polynomial::operator*(const Polynomial &p) const {
  Polynomial temp;
  Node *first = head;
  Node *second = p.head;
  Node *tempcur;
  if (first == NULL || second == NULL) {
    return temp;
  }
  int tt;
  double tans;
  while (first != NULL) {
    second = p.head;
    while (second != NULL) {
      tt = first->exp + second->exp;
      tans = first->coef * second->coef;
      tempcur = temp.head;
      while (tempcur != NULL) {
        if (tempcur->exp == tt) {
          tans += tempcur->coef;
          break;
        }
        tempcur = tempcur->next;
      }
      temp.add_term(tans, first->exp + second->exp);
      second = second->next;
    }
    first = first->next;
  }
  return temp;
}

Polynomial Polynomial::operator/(const Polynomial &divisor) const {
  Node *first = head;
  Node *second = divisor.head;
  Polynomial q;
  if (second == NULL) {
    cout << "Divide by zero\n";
    exit(0);
  }
  if (first->exp < second->exp || first == NULL) {
    return q;
  }

  q.add_term(first->coef / second->coef, first->exp - second->exp);
  Polynomial rtemp = divisor * q;
  Polynomial r;

  Node *curorg = head;
  Node *curout = rtemp.head;

  while (curorg != NULL) {
    curout = rtemp.head;
    while (curout != NULL) {
      if (curout->exp == curorg->exp) {
        r.add_term(curorg->coef - curout->coef, curorg->exp);
        break;
      }
      curout = curout->next;
      if (curout == NULL)
        r.add_term(curorg->coef, curorg->exp);
    }
    curorg = curorg->next;
  }
  {
    curorg = head;
    curout = rtemp.head;
    while (curout != NULL) {
      curorg = head;
      while (curorg != NULL) {
        if (curout->exp == curorg->exp)
          break;
        curorg = curorg->next;
        if (curorg == NULL) {
          r.add_term(-curout->coef, curout->exp);
          break;
        }
      }
      curout = curout->next;
    }
  }
  while (r.head->exp >= divisor.head->exp) {
    q.add_term(r.head->coef / divisor.head->coef,
               r.head->exp - divisor.head->exp);

    Polynomial temp = r;
    Polynomial rtemp = divisor.mul_term(r.head->coef / divisor.head->coef,
                                        r.head->exp - divisor.head->exp);

    Node *old = r.head;
    while (r.head != NULL) {
      r.head = r.head->next;
      delete old;
      old = r.head;
    }
    r.head = NULL;

    Node *curorg = temp.head;
    Node *curout = rtemp.head;
    while (curorg != NULL) {
      curout = rtemp.head;
      while (curout != NULL) {
        if (curout->exp == curorg->exp) {
          r.add_term(curorg->coef - curout->coef, curorg->exp);
          break;
        }
        curout = curout->next;
        if (curout == NULL)
          r.add_term(curorg->coef, curorg->exp);
      }
      curorg = curorg->next;
    }
    {
      curorg = temp.head;
      curout = rtemp.head;
      while (curout != NULL) {
        curorg = head;
        while (curorg != NULL) {
          if (curout->exp == curorg->exp)
            break;
          curorg = curorg->next;
          if (curorg == NULL) {
            r.add_term(-curout->coef, curout->exp);
            break;
          }
        }
        curout = curout->next;
      }
    }
    if (r.head == NULL)
      break;
  }

  return q;
}

Polynomial Polynomial::operator%(const Polynomial &divisor) const {
  Node *first = head;
  Node *second = divisor.head;
  Polynomial r;

  if (second == NULL) {
    cout << "Divide by zero\n";
    exit(0);
  }
  if (first == NULL) {
    return r;
  }
  if (first->exp < second->exp) {
    Node *curold = head;
    Node *current = r.head;
    while (curold != NULL) {
      Node *newNode = new Node;
      newNode->coef = curold->coef;
      newNode->exp = curold->exp;
      newNode->next = NULL;
      if (r.head == NULL) {
        r.head = newNode;
        current = r.head;
        curold = curold->next;
        continue;
      } else
        current->next = newNode;
      current = current->next;
      curold = curold->next;
    }
    return r;
  }

  Polynomial q;
  q.add_term(first->coef / second->coef, first->exp - second->exp);
  Polynomial rtemp = divisor * q;

  Node *curorg = head;
  Node *curout = rtemp.head;

  while (curorg != NULL) {
    curout = rtemp.head;
    while (curout != NULL) {
      if (curout->exp == curorg->exp) {
        r.add_term(curorg->coef - curout->coef, curorg->exp);
        break;
      }
      curout = curout->next;
      if (curout == NULL)
        r.add_term(curorg->coef, curorg->exp);
    }
    curorg = curorg->next;
  }
  {
    curorg = head;
    curout = rtemp.head;
    while (curout != NULL) {
      curorg = head;
      while (curorg != NULL) {
        if (curout->exp == curorg->exp)
          break;
        curorg = curorg->next;
        if (curorg == NULL) {
          r.add_term(-curout->coef, curout->exp);
          break;
        }
      }
      curout = curout->next;
    }
  }

  while (r.head->exp >= divisor.head->exp) {
    q.add_term(r.head->coef / divisor.head->coef,
               r.head->exp - divisor.head->exp);

    Polynomial temp = r;
    Polynomial rtemp = divisor.mul_term(r.head->coef / divisor.head->coef,
                                        r.head->exp - divisor.head->exp);

    Node *old = r.head;
    while (r.head != NULL) {
      r.head = r.head->next;
      delete old;
      old = r.head;
    }
    r.head = NULL;

    Node *curorg = temp.head;
    Node *curout = rtemp.head;
    while (curorg != NULL) {
      curout = rtemp.head;
      while (curout != NULL) {
        if (curout->exp == curorg->exp) {
          r.add_term(curorg->coef - curout->coef, curorg->exp);
          break;
        }
        curout = curout->next;
        if (curout == NULL)
          r.add_term(curorg->coef, curorg->exp);
      }
      curorg = curorg->next;
    }
    {
      curorg = temp.head;
      curout = rtemp.head;
      while (curout != NULL) {
        curorg = head;
        while (curorg != NULL) {
          if (curout->exp == curorg->exp)
            break;
          curorg = curorg->next;
          if (curorg == NULL) {
            r.add_term(-curout->coef, curout->exp);
            break;
          }
        }
        curout = curout->next;
      }
    }
    if (r.head == NULL)
      break;
  }
  return r;
}

Polynomial Polynomial::differentiate() const {
  Polynomial temp;
  Node *cur = head;
  while (cur != NULL) {
    if (cur->exp != 0)
      temp.add_term(cur->coef * cur->exp, cur->exp - 1);
    cur = cur->next;
  }
  return temp;
}

Polynomial Polynomial::integrate() const {
  Polynomial temp;
  Node *cur = head;
  while (cur != NULL) {
    temp.add_term(cur->coef / (cur->exp + 1), cur->exp + 1);
    cur = cur->next;
  }
  return temp;
}
