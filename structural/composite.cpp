/*
Composite Design Pattern - C++ Example (Amazon Package: Boxes and Items)
------------------------------------------------------------------------

Definition:
The Composite pattern lets you compose objects into tree structures to represent part-whole hierarchies. Composite lets clients treat individual objects and compositions of objects uniformly.

Use Cases:
- When you want to represent part-whole hierarchies (e.g., folders/files, boxes/items).
- When clients should treat single objects and compositions in the same way.
- Useful for recursive structures (trees, organization charts, etc.).

Key Concepts:
- Component: Declares the interface for objects in the composition.
- Leaf: Represents leaf objects in the composition (no children).
- Composite: Represents objects that have children (can contain other components).

Example: Amazon Package (Boxes and Items)
-----------------------------------------
We will model an Amazon package:
- `Item` is a leaf (e.g., "Book", "Phone").
- `Box` is a composite that can contain items and/or other boxes.
- The client can treat both items and boxes uniformly (e.g., to calculate total price or print contents).

*/

#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

// Component
class PackageComponent
{
public:
  virtual void printContents(const string &prefix = "") const = 0;
  virtual double getPrice() const = 0;
  virtual ~PackageComponent() {}
};

// Leaf: Item
class Item : public PackageComponent
{
  string name;
  double price;

public:
  Item(const string &n, double p) : name(n), price(p) {}
  void printContents(const string &prefix = "") const override
  {
    cout << prefix << "Item: " << name << " ($" << price << ")" << endl;
  }
  double getPrice() const override
  {
    return price;
  }
};

// Composite: Box
class Box : public PackageComponent
{
  string label;
  vector<shared_ptr<PackageComponent>> contents;

public:
  Box(const string &l) : label(l) {}
  void add(const shared_ptr<PackageComponent> &component)
  {
    contents.push_back(component);
  }
  void printContents(const string &prefix = "") const override
  {
    cout << prefix << "Box: " << label << endl;
    for (const auto &c : contents)
    {
      c->printContents(prefix + "  ");
    }
  }
  double getPrice() const override
  {
    double total = 0;
    for (const auto &c : contents)
    {
      total += c->getPrice();
    }
    return total;
  }
};

int main()
{
  // Create items
  auto book = make_shared<Item>("Book", 12.99);
  auto phone = make_shared<Item>("Phone", 299.99);
  auto charger = make_shared<Item>("Charger", 19.99);
  auto pen = make_shared<Item>("Pen", 2.49);

  // Create boxes
  auto smallBox = make_shared<Box>("Small Box");
  smallBox->add(book);
  smallBox->add(pen);

  auto mediumBox = make_shared<Box>("Medium Box");
  mediumBox->add(phone);
  mediumBox->add(charger);
  mediumBox->add(smallBox);

  auto package = make_shared<Box>("Amazon Package");
  package->add(mediumBox);

  // Print contents and total price
  cout << "Package Contents:" << endl;
  package->printContents();
  cout << "\nTotal Price: $" << package->getPrice() << endl;

  return 0;
}
