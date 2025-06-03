/*
Iterator Design Pattern (Shopping List Example, C++)
----------------------------------------------------
The Iterator pattern is a behavioral design pattern that provides a way to access the elements of an aggregate object sequentially without exposing its underlying representation. It decouples the collection from the traversal logic, allowing multiple ways to iterate over a collection and supporting multiple iterators at once.

Key Participants:
- Iterator (interface): Declares methods for traversing elements (e.g., next(), hasNext(), current()).
- ConcreteIterator: Implements the Iterator interface for a specific collection.
- Aggregate (interface): Declares a method to create an iterator.
- ConcreteAggregate: Implements the Aggregate interface and returns an instance of the ConcreteIterator.

How it works in this example:
- ShoppingList is the aggregate (collection) of shopping items.
- ShoppingListIterator is the iterator that allows sequential access to the items in the ShoppingList.
- The client uses the iterator to traverse the shopping list without knowing its internal structure.

This pattern is especially useful when you want to provide multiple ways to traverse a collection, or when you want to hide the internal structure of the collection from the client.
*/

#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Iterator interface
class Iterator
{
public:
  virtual ~Iterator() = default;
  virtual bool hasNext() const = 0;
  virtual const std::string &next() = 0;
};

// Aggregate interface
class Aggregate
{
public:
  virtual ~Aggregate() = default;
  virtual std::unique_ptr<Iterator> createIterator() const = 0;
};

// ConcreteAggregate: ShoppingList
class ShoppingList : public Aggregate
{
  std::vector<std::string> items;

public:
  void addItem(const std::string &item)
  {
    items.push_back(item);
  }
  size_t size() const { return items.size(); }
  const std::string &getItem(size_t index) const { return items.at(index); }
  std::unique_ptr<Iterator> createIterator() const override;
};

// ConcreteIterator: ShoppingListIterator
class ShoppingListIterator : public Iterator
{
  const ShoppingList &shoppingList;
  size_t index;

public:
  ShoppingListIterator(const ShoppingList &list) : shoppingList(list), index(0) {}
  bool hasNext() const override
  {
    return index < shoppingList.size();
  }
  const std::string &next() override
  {
    return shoppingList.getItem(index++);
  }
};

std::unique_ptr<Iterator> ShoppingList::createIterator() const
{
  return std::make_unique<ShoppingListIterator>(*this);
}

// Demo
int main()
{
  ShoppingList list;
  list.addItem("Milk");
  list.addItem("Eggs");
  list.addItem("Bread");
  list.addItem("Butter");

  std::unique_ptr<Iterator> it = list.createIterator();
  std::cout << "Shopping List Items:\n";
  while (it->hasNext())
  {
    std::cout << "- " << it->next() << std::endl;
  }
  return 0;
}