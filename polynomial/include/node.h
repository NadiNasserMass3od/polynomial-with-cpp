#ifndef NODE_H
#define NODE_H

class Node {
private:
  int exp;
  double coef;
  Node *next;
  friend class Polynomial;
};

#endif // NODE_H
