#include "LatexStack.h"

//Default constructor of stack
LatexStack::LatexStack () {
  topEl = NULL;
}

//push method - Takes one argument a string
void LatexStack::push(string item) {

        node *newtopEl = new node;
        if(topEl == NULL) {
            newtopEl->data = item;
            newtopEl->next = NULL;
            topEl = newtopEl;
        }
        else {
            newtopEl->data = item;
            newtopEl->next = topEl;
            topEl = newtopEl;
        }
}

//pop method - Pops the top element of stack
string LatexStack::pop() {
  if(topEl == NULL) {
    cout << "Error stack is empty nothing to pop...";
  }
  else {
    string str;
    node * old = topEl;
    topEl = topEl->next;
    str = old->data;
    delete(old);
    return str;
  }
}

//isEmpty method - Returns true if stack is empty
bool LatexStack::isEmpty() {
  return topEl == NULL;
}

//topElement method - Returns the top element without removing it
string LatexStack::topElement() {
  if(topEl == NULL) {
    cout<< "Stack is empty ...";
  }
  else {
    node * old = topEl;
    return old->data;
  }
}
