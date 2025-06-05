/*
Observer Design Pattern - C++ Example (Spreadsheets and Charts)
--------------------------------------------------------------

Definition:
The Observer pattern defines a one-to-many dependency between objects so that when one object (the subject) changes state, all its dependents (observers) are notified and updated automatically.

Use Cases:
- When a change to one object requires changing others, and you don't know how many objects need to change.
- When an object should be able to notify other objects without making assumptions about who these objects are.
- Commonly used in event handling systems, GUIs, and data models (e.g., spreadsheets, charts, etc.).

Key Concepts:
- Subject: Maintains a list of observers and notifies them of state changes.
- Observer: Defines an updating interface for objects that should be notified of changes in a subject.
- ConcreteSubject: Stores state of interest to ConcreteObservers and sends notifications.
- ConcreteObserver: Implements the Observer interface to keep its state consistent with the subject's.

Example: Spreadsheet and Charts
------------------------------
We will model a spreadsheet application where:
- Spreadsheet1 has data and a bar chart that should update when the data changes.
- Spreadsheet2 is another observer that also updates when Spreadsheet1's data changes.

*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Observer interface
class Observer
{
public:
  virtual void update() = 0;
  virtual ~Observer() {}
};

// Subject interface
class Subject
{
public:
  virtual void attach(Observer *o) = 0;
  virtual void detach(Observer *o) = 0;
  virtual void notify() = 0;
  virtual ~Subject() {}
};

// Concrete Subject: Spreadsheet1 (with data)
class Spreadsheet1 : public Subject
{
  vector<Observer *> observers;
  vector<int> data;

public:
  void setData(const vector<int> &newData)
  {
    data = newData;
    notify();
  }
  const vector<int> &getData() const
  {
    return data;
  }
  void attach(Observer *o) override
  {
    observers.push_back(o);
  }
  void detach(Observer *o) override
  {
    observers.erase(remove(observers.begin(), observers.end(), o), observers.end());
  }
  void notify() override
  {
    for (auto *o : observers)
    {
      o->update();
    }
  }
};

// Concrete Observer: BarChart (for Spreadsheet1)
class BarChart : public Observer
{
  Spreadsheet1 &sheet;

public:
  BarChart(Spreadsheet1 &s) : sheet(s) {}
  void update() override
  {
    cout << "BarChart updated: ";
    for (int value : sheet.getData())
    {
      cout << string(value, '|') << " (" << value << ") ";
    }
    cout << endl;
  }
};

// Concrete Observer: Spreadsheet2 (observes Spreadsheet1)
class Spreadsheet2 : public Observer
{
  Spreadsheet1 &sheet;

public:
  Spreadsheet2(Spreadsheet1 &s) : sheet(s) {}
  void update() override
  {
    cout << "Spreadsheet2 updated: Data = ";
    for (int value : sheet.getData())
    {
      cout << value << " ";
    }
    cout << endl;
  }
};

int main()
{
  Spreadsheet1 sheet1;
  BarChart chart(sheet1);
  Spreadsheet2 sheet2(sheet1);

  // Attach observers
  sheet1.attach(&chart);
  sheet1.attach(&sheet2);

  // Change data
  cout << "Setting data to {3, 5, 2}:" << endl;
  sheet1.setData({3, 5, 2});

  cout << "\nSetting data to {1, 4, 6, 2}:" << endl;
  sheet1.setData({1, 4, 6, 2});

  // Detach Spreadsheet2
  sheet1.detach(&sheet2);
  cout << "\nSetting data to {7, 2}: (Spreadsheet2 will not update)" << endl;
  sheet1.setData({7, 2});

  return 0;
}