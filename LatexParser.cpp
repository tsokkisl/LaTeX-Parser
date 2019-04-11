#include "LatexStack.cpp"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

//Create 2 stacks 1 for \delimiter{environment} and 1 for line numbers
LatexStack *latexstack = new LatexStack;
LatexStack *linenumbers = new LatexStack;

bool latexParse(char** arg) {

  string line,str,del,env;
  int linenum = 0;
  bool flag = false;

  ifstream myfile (arg[1]);

  if (myfile.is_open()) {

    flag = true;
    while (getline(myfile, line)) {

      //read every line of the file
      linenum++;
      str = line;

      //extract delimiter and evironment name
      del = str.substr(0, str.find('{'));
      env = str.substr(str.find('{') + 1, str.find('}') - (str.find('{') + 1));
      ostringstream convert;
      convert << linenum;
      string num(convert.str());

      //if we get \begin delimiter push into stack
      if (del.compare("\\begin") == 0) {
        latexstack->push(env);
        linenumbers->push(num);
      }
      //if we get \end delimiter pop the top element of stack
      else if (del.compare("\\end") == 0) {
        if (latexstack->isEmpty()) {
          cout << "Error : " << endl;
          cout << " line " << linenum << " : \\end " << env << " has no matching \\begin" << endl;
          myfile.close();
          exit (EXIT_FAILURE);
        }
        else {
          if (latexstack->topElement().compare(env) != 0) {
            cout << "Error : "<< endl;
            cout << "line " << linenum << " : \\end " << env << " does not match with \\begin " << latexstack->topElement() << " on line " << linenumbers->topElement() << endl;
            myfile.close();
            exit (EXIT_FAILURE);
          }
          else {
            latexstack->pop();
            linenumbers->pop();
          }
        }
      }
    }
  }
  myfile.close();
  return flag;
}

int main(int argc, char* argv[]) {

  if (!latexParse(argv)) {
    cout << "Error no such file on directory..." << endl;
  }
  else {  
    //if file parsed with no errors check for \begin{environment} with no matching ends
    if (latexstack->isEmpty()) cout << "No errors - All delimiters match... " << endl;
    else {
      cout << "Error : The following environments have no matching \\end:" << endl;
      cout << "__________________________________________________________" << endl;
      while(!latexstack->isEmpty()) {
        cout << "\\begin{" << latexstack->pop() << "}" << " on line " << linenumbers->pop() << endl;
      }
    }
  }

  return 0;
}
