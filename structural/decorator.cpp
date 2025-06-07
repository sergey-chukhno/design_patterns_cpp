/*
Decorator Design Pattern - C++ Example (Coffee Shop)
---------------------------------------------------

Definition:
The Decorator pattern allows you to dynamically add new behavior to objects by placing them inside special wrapper objects (decorators) that add the behavior.

Use Cases:
- When you want to add responsibilities to individual objects, without affecting other objects of the same class.
- When subclassing would lead to an explosion of subclasses to cover every combination of features.
- Useful for UI components, stream processing, and flexible feature addition.

Key Concepts:
- Component: The interface for objects that can have responsibilities added to them.
- ConcreteComponent: The core object to which additional behavior can be added.
- Decorator: Wraps a component and adds new behavior.
- ConcreteDecorator: Implements additional behavior.

Example: Coffee Shop
--------------------
Suppose you are building a coffee shop ordering system. You have a base coffee, and you want to allow customers to add milk, sugar, or other condiments. Each addition should be a decorator that adds its own cost and description.

*/

#include <iostream>
#include <string>
#include <memory>
using namespace std;

// Component
class Coffee
{
public:
  virtual string getDescription() const = 0;
  virtual double cost() const = 0;
  virtual ~Coffee() {}
};

// ConcreteComponent
class SimpleCoffee : public Coffee
{
public:
  string getDescription() const override
  {
    return "Simple Coffee";
  }
  double cost() const override
  {
    return 2.0;
  }
};

// Decorator
class CoffeeDecorator : public Coffee
{
protected:
  shared_ptr<Coffee> coffee;

public:
  CoffeeDecorator(shared_ptr<Coffee> c) : coffee(c) {}
};

// ConcreteDecorator: Milk
class Milk : public CoffeeDecorator
{
public:
  Milk(shared_ptr<Coffee> c) : CoffeeDecorator(c) {}
  string getDescription() const override
  {
    return coffee->getDescription() + ", Milk";
  }
  double cost() const override
  {
    return coffee->cost() + 0.5;
  }
};

// ConcreteDecorator: Sugar
class Sugar : public CoffeeDecorator
{
public:
  Sugar(shared_ptr<Coffee> c) : CoffeeDecorator(c) {}
  string getDescription() const override
  {
    return coffee->getDescription() + ", Sugar";
  }
  double cost() const override
  {
    return coffee->cost() + 0.2;
  }
};

int main()
{
  shared_ptr<Coffee> coffee = make_shared<SimpleCoffee>();
  cout << coffee->getDescription() << " : $" << coffee->cost() << endl;

  coffee = make_shared<Milk>(coffee);
  cout << coffee->getDescription() << " : $" << coffee->cost() << endl;

  coffee = make_shared<Sugar>(coffee);
  cout << coffee->getDescription() << " : $" << coffee->cost() << endl;

  // You can add more decorators as needed
  return 0;
}