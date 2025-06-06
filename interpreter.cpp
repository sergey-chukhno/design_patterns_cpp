/*
Interpreter Design Pattern - C++ Example (Simple Arithmetic Expressions)
-----------------------------------------------------------------------

Definition:
The Interpreter pattern defines a representation for a grammar and an interpreter that uses the representation to interpret sentences in the language. It is used to define a language's grammar and provide an interpreter to deal with this grammar.

Use Cases:
- When you have a simple language to interpret (e.g., mathematical expressions, scripting languages, configuration files).
- When the grammar is simple and efficiency is not the main concern.
- Useful for parsing and evaluating expressions.

Key Concepts:
- AbstractExpression: Declares an interface for interpreting operations.
- TerminalExpression: Implements an interpret operation for terminal symbols in the grammar.
- NonTerminalExpression: Implements an interpret operation for nonterminal symbols in the grammar.
- Context: Contains information that is global to the interpreter.

Example: Simple Arithmetic Expressions
--------------------------------------
We will model a simple interpreter for arithmetic expressions involving addition and subtraction of integers, e.g., "5 + 3 - 2".
- Each number and operator is an expression.
- The interpreter will parse and evaluate the expression.

*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
using namespace std;

// Abstract Expression
class Expression
{
public:
  virtual int interpret() const = 0;
  virtual ~Expression() {}
};

// Terminal Expression: Number
class NumberExpression : public Expression
{
  int number;

public:
  NumberExpression(int n) : number(n) {}
  int interpret() const override
  {
    return number;
  }
};

// NonTerminal Expression: Addition
class AddExpression : public Expression
{
  unique_ptr<Expression> left, right;

public:
  AddExpression(unique_ptr<Expression> l, unique_ptr<Expression> r)
      : left(move(l)), right(move(r)) {}
  int interpret() const override
  {
    return left->interpret() + right->interpret();
  }
};

// NonTerminal Expression: Subtraction
class SubtractExpression : public Expression
{
  unique_ptr<Expression> left, right;

public:
  SubtractExpression(unique_ptr<Expression> l, unique_ptr<Expression> r)
      : left(move(l)), right(move(r)) {}
  int interpret() const override
  {
    return left->interpret() - right->interpret();
  }
};

// Parser for simple expressions like "5 + 3 - 2"
unique_ptr<Expression> parse(const string &expr)
{
  istringstream iss(expr);
  vector<unique_ptr<Expression>> terms;
  vector<char> ops;
  int num;
  iss >> num;
  terms.push_back(make_unique<NumberExpression>(num));
  char op;
  while (iss >> op)
  {
    ops.push_back(op);
    iss >> num;
    terms.push_back(make_unique<NumberExpression>(num));
  }
  // Build the expression tree left-to-right (no operator precedence)
  unique_ptr<Expression> result = move(terms[0]);
  for (size_t i = 0; i < ops.size(); ++i)
  {
    if (ops[i] == '+')
    {
      result = make_unique<AddExpression>(move(result), move(terms[i + 1]));
    }
    else if (ops[i] == '-')
    {
      result = make_unique<SubtractExpression>(move(result), move(terms[i + 1]));
    }
  }
  return result;
}

int main()
{
  string expr1 = "5 + 3 - 2";
  string expr2 = "10 - 4 + 2";
  cout << "Expression: " << expr1 << endl;
  auto tree1 = parse(expr1);
  cout << "Result: " << tree1->interpret() << endl;

  cout << "\nExpression: " << expr2 << endl;
  auto tree2 = parse(expr2);
  cout << "Result: " << tree2->interpret() << endl;

  return 0;
}