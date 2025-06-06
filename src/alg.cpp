// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  const int kStackSize = 100;
  TStack<char, kStackSize> stack;
  std::string result;

  for (size_t i = 0; i < inf.length(); ++i) {
    char token = inf[i];

    if (isdigit(token)) {
      while (i < inf.length() && isdigit(inf[i])) {
        result += inf[i];
        ++i;
      }
      --i;
      result += ' ';
    } else if (token == '(') {
      stack.push(token);
    } else if (token == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        result += stack.pop();
        result += ' ';
      }
      stack.pop();
    } else if (token == '+' || token == '-' || token == '*' || token == '/') {
      while (!stack.isEmpty() && precedence(stack.top()) >= precedence(token)) {
        result += stack.pop();
        result += ' ';
      }
      stack.push(token);
    }
  }

  while (!stack.isEmpty()) {
    result += stack.pop();
    result += ' ';
  }

  if (!result.empty())
    result.pop_back();

  return result;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::string num;

  for (size_t i = 0; i < post.length(); ++i) {
    char token = post[i];

    if (token == ' ') continue;

    if (isdigit(token)) {
      num.clear();
      while (i < post.length() && isdigit(post[i])) {
        num += post[i];
        ++i;
      }
      --i;
      stack.push(std::stoi(num));
    } else {
      int b = stack.pop();
      int a = stack.pop();
      switch (token) {
      case '+':stack.push(a + b); break;
      case '-':stack.push(a - b); break;
      case '*':stack.push(a * b); break;
      case '/':stack.push(a / b); break;
      }
    }
  }
  return stack.pop();
}
