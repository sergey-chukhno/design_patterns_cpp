/*
Flyweight Design Pattern - C++ Example (Game: Trees in a Forest)
----------------------------------------------------------------

Definition:
The Flyweight pattern is used to minimize memory usage or computational expenses by sharing as much data as possible with similar objects. It is especially useful when you need to create a large number of similar objects.

Use Cases:
- When an application uses a large number of objects that share common state (intrinsic state).
- To reduce memory footprint by sharing objects instead of duplicating them.
- Useful in games (e.g., rendering many trees, bullets, or characters), text editors (characters), or GUIs (icons).

Key Concepts:
- Flyweight: The shared object that contains intrinsic (shared) state.
- FlyweightFactory: Creates and manages flyweight objects, ensuring sharing.
- Extrinsic State: State that is unique to each object and passed in at runtime.

Example: Game (Trees in a Forest)
---------------------------------
Suppose you are building a game with a large forest. Each tree has a type (species, texture, color) that can be shared, and a position (x, y) that is unique. The Flyweight pattern allows you to share tree types and only store unique positions for each tree.

*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
using namespace std;

// Flyweight: Shared tree type
class TreeType
{
  string name;
  string color;
  string texture;

public:
  TreeType(const string &n, const string &c, const string &t)
      : name(n), color(c), texture(t) {}
  void draw(int x, int y) const
  {
    cout << "Drawing tree '" << name << "' at (" << x << ", " << y << ") with color " << color << " and texture " << texture << endl;
  }
};

// Flyweight Factory: Manages tree types
class TreeFactory
{
  unordered_map<string, shared_ptr<TreeType>> types;

public:
  shared_ptr<TreeType> getTreeType(const string &name, const string &color, const string &texture)
  {
    string key = name + ":" + color + ":" + texture;
    if (types.find(key) == types.end())
    {
      types[key] = make_shared<TreeType>(name, color, texture);
    }
    return types[key];
  }
};

// Context: Individual tree with extrinsic state
class Tree
{
  int x, y;
  shared_ptr<TreeType> type;

public:
  Tree(int x, int y, shared_ptr<TreeType> t) : x(x), y(y), type(t) {}
  void draw() const
  {
    type->draw(x, y);
  }
};

// Forest: Holds many trees
class Forest
{
  vector<Tree> trees;
  TreeFactory factory;

public:
  void plantTree(int x, int y, const string &name, const string &color, const string &texture)
  {
    auto type = factory.getTreeType(name, color, texture);
    trees.emplace_back(x, y, type);
  }
  void draw() const
  {
    for (const auto &tree : trees)
    {
      tree.draw();
    }
  }
};

int main()
{
  Forest forest;
  // Plant many trees, reusing types
  forest.plantTree(1, 2, "Oak", "Green", "Rough");
  forest.plantTree(3, 4, "Pine", "Dark Green", "Smooth");
  forest.plantTree(5, 6, "Oak", "Green", "Rough"); // Same type as first
  forest.plantTree(7, 8, "Birch", "Light Green", "Striped");
  forest.plantTree(9, 10, "Oak", "Green", "Rough"); // Same type as first

  cout << "Drawing the forest:\n";
  forest.draw();

  return 0;
}