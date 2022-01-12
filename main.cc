#include <iostream>
#include <stdio.h>

using namespace std;
int main(int argc, char **argv) {
  if (argc != 2) {
    cout << argv[0] << ": wrong number of arguments";
    return 1;
  }
  cout << ".globl _main" << endl;
  cout << "_main:" << endl;
  printf("movl $%d, %%eax\n", stoi(argv[1]));
  cout << "retq";
  return 0;
}
