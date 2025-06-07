/*
Prototype Design Pattern - C++ Example (Game Characters)
-------------------------------------------------------

Definition:
The Prototype pattern is a creational pattern that allows you to create new objects by copying (cloning) existing ones, rather than creating them from scratch. This is useful when object creation is expensive or complex, or when you want to avoid subclassing for every possible configuration.

Use Cases:
- When the cost of creating a new object is more expensive than copying an existing one.
- When you want to avoid building a complex object from scratch every time.
- When you want to keep the code flexible and decoupled from specific classes.

Key Concepts:
- Prototype: An interface with a clone method.
- ConcretePrototype: Implements the clone method to return a copy of itself.
- Client: Creates new objects by cloning prototypes.

Example: Game Characters
------------------------
Suppose you are building a game where you have different types of characters (e.g., Warrior, Mage). Instead of creating each character from scratch, you can define prototypes for each type and clone them to create new characters.

*/

#include <iostream>
#include <string>
#include <memory>
using namespace std;

// Prototype interface
class Character
{
public:
  virtual unique_ptr<Character> clone() const = 0;
  virtual void display() const = 0;
  virtual ~Character() {}
};

// ConcretePrototype: Warrior
class Warrior : public Character
{
  string weapon;

public:
  Warrior(const string &w) : weapon(w) {}
  unique_ptr<Character> clone() const override
  {
    return make_unique<Warrior>(*this);
  }
  void display() const override
  {
    cout << "Warrior with " << weapon << endl;
  }
};

// ConcretePrototype: Mage
class Mage : public Character
{
  string spell;

public:
  Mage(const string &s) : spell(s) {}
  unique_ptr<Character> clone() const override
  {
    return make_unique<Mage>(*this);
  }
  void display() const override
  {
    cout << "Mage casting " << spell << endl;
  }
};

int main()
{
  // Create prototypes
  unique_ptr<Character> warriorPrototype = make_unique<Warrior>("Sword");
  unique_ptr<Character> magePrototype = make_unique<Mage>("Fireball");

  // Clone characters
  auto warrior1 = warriorPrototype->clone();
  auto warrior2 = warriorPrototype->clone();
  auto mage1 = magePrototype->clone();

  // Display characters
  warrior1->display();
  warrior2->display();
  mage1->display();

  return 0;
}