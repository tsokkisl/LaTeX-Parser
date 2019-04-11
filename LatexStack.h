#ifndef LATEXSTACK_H
#define LATEXSTACK_H

#include <cstdlib>
#include <iostream>

using namespace std;

struct node {
public:
  string data;
  struct node* next;
};

class LatexStack {
public:
  LatexStack ();
  void push(string item);
  string pop();
  void show();
  bool isEmpty();
  string topElement();

private:
  struct node *topEl;
};

#endif
