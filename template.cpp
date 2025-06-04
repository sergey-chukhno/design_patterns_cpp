/*
Template Method Design Pattern - C++ Example (Beverages)
--------------------------------------------------------

Definition:
The Template Method pattern defines the skeleton of an algorithm in a base class, allowing subclasses to redefine certain steps of the algorithm without changing its structure. It lets subclasses override specific steps of the algorithm, but not the overall sequence.

Use Cases:
- When you have multiple classes with similar algorithms, but with some steps that differ.
- To avoid code duplication by extracting common behavior into a base class.
- To enforce a specific sequence of steps in an algorithm.

Key Concepts:
- The base class implements the template method (the algorithm's skeleton), which calls abstract or hook methods for steps that may vary.
- Subclasses override these steps to provide specific behavior.
- The template method itself is usually final (not overridden by subclasses).

Example: Beverages (Tea, Coffee, and another beverage)
------------------------------------------------------
We will model the process of making a beverage. The steps are:
 1. Boil water
 2. Brew or steep the beverage
 3. Pour into cup
 4. Add condiments (optional)

The steps for boiling water and pouring into cup are the same for all beverages, but brewing/steeping and adding condiments differ.

*/

#include <iostream>
using namespace std;

// Abstract base class
class CaffeineBeverage
{
public:
  // The template method (final, not to be overridden)
  void prepareRecipe()
  {
    boilWater();
    brew();
    pourInCup();
    if (customerWantsCondiments())
    {
      addCondiments();
    }
  }

  // Common steps
  void boilWater()
  {
    cout << "Boiling water" << endl;
  }
  void pourInCup()
  {
    cout << "Pouring into cup" << endl;
  }

  // Steps to be implemented by subclasses
  virtual void brew() = 0;
  virtual void addCondiments() = 0;

  // Hook (can be overridden)
  virtual bool customerWantsCondiments()
  {
    return true;
  }

  virtual ~CaffeineBeverage() {}
};

// Concrete subclass: Tea
class Tea : public CaffeineBeverage
{
public:
  void brew() override
  {
    cout << "Steeping the tea" << endl;
  }
  void addCondiments() override
  {
    cout << "Adding lemon" << endl;
  }
};

// Concrete subclass: Coffee
class Coffee : public CaffeineBeverage
{
public:
  void brew() override
  {
    cout << "Dripping coffee through filter" << endl;
  }
  void addCondiments() override
  {
    cout << "Adding sugar and milk" << endl;
  }
};

// Another beverage: Hot Chocolate
class HotChocolate : public CaffeineBeverage
{
public:
  void brew() override
  {
    cout << "Mixing hot chocolate powder" << endl;
  }
  void addCondiments() override
  {
    cout << "Adding whipped cream" << endl;
  }
  // Override hook to ask user
  bool customerWantsCondiments() override
  {
    char answer;
    cout << "Would you like whipped cream (y/n)? ";
    cin >> answer;
    return (answer == 'y' || answer == 'Y');
  }
};

int main()
{
  cout << "Making tea..." << endl;
  Tea tea;
  tea.prepareRecipe();
  cout << endl;

  cout << "Making coffee..." << endl;
  Coffee coffee;
  coffee.prepareRecipe();
  cout << endl;

  cout << "Making hot chocolate..." << endl;
  HotChocolate hotChocolate;
  hotChocolate.prepareRecipe();
  cout << endl;

  return 0;
}
