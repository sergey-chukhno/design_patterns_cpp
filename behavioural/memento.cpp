#include <iostream>
#include <string>
#include <vector>

/*
Memento Design Pattern (C++)
---------------------------
The Memento pattern is a behavioral design pattern that allows an object to save and restore its state without exposing its internal representation. It is useful for implementing features like undo/redo, checkpoints, or history tracking.

Key Participants:
- Originator: The object whose state needs to be saved and restored. It creates a Memento containing a snapshot of its current state and can restore its state from a Memento.
- Memento: Stores the internal state of the Originator. It should only be accessible to the Originator and the Caretaker.
- Caretaker: Manages the history of Mementos. It requests Mementos from the Originator, stores them, and provides them back to the Originator when needed.

How it works in this example:
- The Originator class has a string state. It can save its state to a Memento and restore it from a Memento.
- The Memento class encapsulates the state of the Originator.
- The Caretaker class keeps a list of Mementos, allowing the user to save and restore previous states, and to display the history of saved states.

This pattern is especially useful when you want to provide undo/redo functionality or maintain a history of changes without violating encapsulation.
*/

// Memento class
class Memento
{
  std::string state;

public:
  Memento(const std::string &s) : state(s) {}
  std::string getState() const { return state; }
};

// Originator class
class Originator
{
  std::string state;

public:
  void setState(const std::string &s) { state = s; }
  std::string getState() const { return state; }
  Memento saveToMemento() const { return Memento(state); }
  void restoreFromMemento(const Memento &m) { state = m.getState(); }
};

// Caretaker class
class Caretaker
{
  std::vector<Memento> mementos;

public:
  void addMemento(const Memento &m) { mementos.push_back(m); }
  Memento getMemento(size_t index) const { return mementos.at(index); }
  void showHistory() const
  {
    std::cout << "History of saved states:" << std::endl;
    for (size_t i = 0; i < mementos.size(); ++i)
    {
      std::cout << i << ": " << mementos[i].getState() << std::endl;
    }
  }
};

int main()
{
  Originator originator;
  Caretaker caretaker;

  originator.setState("State #1");
  originator.setState("State #2");
  caretaker.addMemento(originator.saveToMemento());

  originator.setState("State #3");
  caretaker.addMemento(originator.saveToMemento());

  originator.setState("State #4");
  std::cout << "Current State: " << originator.getState() << std::endl;

  caretaker.showHistory();

  // Restore to previous states
  originator.restoreFromMemento(caretaker.getMemento(0));
  std::cout << "First saved State: " << originator.getState() << std::endl;

  originator.restoreFromMemento(caretaker.getMemento(1));
  std::cout << "Second saved State: " << originator.getState() << std::endl;

  return 0;
}
