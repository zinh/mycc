#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

enum TokenType { TK_PUNCT, TK_NUM, TK_EOF };

class Token {
private:
  TokenType type;
  int val;
  string symbol;

public:
  Token(TokenType t, char sym) {
    type = t;
    symbol = sym;
  }

  Token(TokenType t, int value) {
    type = t;
    val = value;
  }

  string toString() const {
    if (type == TK_PUNCT)
      return symbol;
    else if (type == TK_NUM)
      return to_string(val);
    return "";
  }

  bool isNumber() {
    return type == TK_NUM;
  }

  int value(){
    return val;
  }

  string getSymbol(){
    return symbol;
  }
};

ostream &operator<<(ostream &os, const Token &t) {
  os << t.toString();
  return os;
}

bool should_skip(char c) { return c == ' '; }

bool is_puntuation(char c) { return c == '+' || c == '-'; }

bool is_digit(char c) { return c >= '0' && c <= '9'; }

vector<Token> tokenize(string input) {
  vector<Token> tokens{};
  while (input.size() > 0) {
    auto c = input[0];
    if (should_skip(c))
      input = input.substr(1);
    else if (is_puntuation(c)) {
      Token t(TK_PUNCT, c);
      tokens.push_back(t);
      input = input.substr(1);
    } else if (is_digit(c)) {
      size_t pos = 0;
      int val = stoi(input, &pos);
      Token t(TK_NUM, val);
      tokens.push_back(t);
      input = input.substr(pos);
    } else {
      throw runtime_error("syntax error");
    }
  }
  return tokens;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << argv[0] << ": wrong number of arguments";
    return 1;
  }
  string input = argv[1];
  printf(".globl _main\n");
  printf("_main:\n");
  auto tokens = tokenize(input);
  printf("movl $%d, %%eax\n", tokens[0].value());
  int pos = 1;
  while (pos < tokens.size()){
    auto token = tokens[pos];
    string symbol = token.getSymbol();
    if (symbol == "-"){
      printf("subl $%d, %%eax\n", tokens[pos + 1].value());
    } else if (symbol == "+") {
      printf("addl $%d, %%eax\n", tokens[pos + 1].value());
    }
    pos += 2;
  }
  cout << "retq";
  return 0;
}
