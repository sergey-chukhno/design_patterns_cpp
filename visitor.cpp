/*
Visitor Design Pattern - C++ Example (Shapes and Area/Perimeter Visitors)
--------------------------------------------------------------------------

Definition:
The Visitor pattern lets you define a new operation without changing the classes of the elements on which it operates. It separates an algorithm from the objects on which it operates, allowing you to add new operations to existing object structures without modifying them.

Use Cases:
- When you need to perform operations across a set of objects with different types.
- When the object structure is stable, but you want to define new operations without changing the classes.
- Useful for traversing complex object structures (e.g., ASTs, file systems).

Key Concepts:
- Visitor: Declares a visit operation for each type of element.
- ConcreteVisitor: Implements each operation for every element type.
- Element: Defines an accept method that takes a visitor.
- ConcreteElement: Implements the accept method to call the visitor's method for its type.

Example: Shapes and Area/Perimeter Visitors
-------------------------------------------
We will model a simple shape hierarchy:
- Elements: Circle, Rectangle
- Visitors: AreaVisitor, PerimeterVisitor
- Each visitor can "visit" each shape and perform a calculation (area or perimeter).
- The shape classes do not need to know the details of the operations.

*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Forward declarations
class Circle;
class Rectangle;

// Visitor interface
class ShapeVisitor
{
public:
  virtual void visit(Circle &c) = 0;
  virtual void visit(Rectangle &r) = 0;
  virtual ~ShapeVisitor() {}
};

// Element interface
class Shape
{
public:
  virtual void accept(ShapeVisitor &visitor) = 0;
  virtual ~Shape() {}
};

// Concrete Element: Circle
class Circle : public Shape
{
public:
  double radius;
  Circle(double r) : radius(r) {}
  void accept(ShapeVisitor &visitor) override
  {
    visitor.visit(*this);
  }
};

// Concrete Element: Rectangle
class Rectangle : public Shape
{
public:
  double width, height;
  Rectangle(double w, double h) : width(w), height(h) {}
  void accept(ShapeVisitor &visitor) override
  {
    visitor.visit(*this);
  }
};

// Concrete Visitor: AreaVisitor
class AreaVisitor : public ShapeVisitor
{
public:
  void visit(Circle &c) override
  {
    double area = M_PI * c.radius * c.radius;
    cout << "Area of Circle (r=" << c.radius << ") = " << area << endl;
  }
  void visit(Rectangle &r) override
  {
    double area = r.width * r.height;
    cout << "Area of Rectangle (" << r.width << "x" << r.height << ") = " << area << endl;
  }
};

// Concrete Visitor: PerimeterVisitor
class PerimeterVisitor : public ShapeVisitor
{
public:
  void visit(Circle &c) override
  {
    double perimeter = 2 * M_PI * c.radius;
    cout << "Perimeter of Circle (r=" << c.radius << ") = " << perimeter << endl;
  }
  void visit(Rectangle &r) override
  {
    double perimeter = 2 * (r.width + r.height);
    cout << "Perimeter of Rectangle (" << r.width << "x" << r.height << ") = " << perimeter << endl;
  }
};

int main()
{
  vector<Shape *> shapes;
  shapes.push_back(new Circle(3));
  shapes.push_back(new Rectangle(4, 5));

  AreaVisitor areaVisitor;
  PerimeterVisitor perimeterVisitor;

  cout << "-- Calculating Areas --" << endl;
  for (auto *shape : shapes)
  {
    shape->accept(areaVisitor);
  }

  cout << "\n-- Calculating Perimeters --" << endl;
  for (auto *shape : shapes)
  {
    shape->accept(perimeterVisitor);
  }

  // Clean up
  for (auto *shape : shapes)
    delete shape;
  return 0;
}