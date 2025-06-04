/*
Command Design Pattern (Remote Control & Light Example, C++)
-----------------------------------------------------------
The Command pattern is a behavioral design pattern that turns a request into a stand-alone object containing all information about the request. This allows you to parameterize methods with different requests, delay or queue a request's execution, and support undoable operations.

Key Participants:
- Command (interface): Declares an interface for executing an operation (execute()).
- ConcreteCommand: Implements the Command interface and defines a binding between a Receiver and an action.
- Receiver: Knows how to perform the operations associated with carrying out a request (e.g., Light).
- Invoker: Asks the command to carry out the request (e.g., RemoteControl).
- Client: Creates a ConcreteCommand and sets its receiver.

How it works in this example:
- The Light class is the Receiver, with methods to turn the light on and off.
- The Command interface declares the execute() method.
- LightOnCommand and LightOffCommand are ConcreteCommands that call the appropriate method on the Light.
- RemoteControl is the Invoker, which can be configured with different commands and trigger them.
- The client sets up the commands and assigns them to the remote control.

This pattern is especially useful for implementing undo/redo, macro recording, transactional behavior, and decoupling the sender from the receiver of a request.
*/

#include <iostream>
#include <memory>
#include <vector>

// Receiver
class Light
{
public:
  void on()
  {
    std::cout << "Light is ON" << std::endl;
  }
  void off()
  {
    std::cout << "Light is OFF" << std::endl;
  }
};

// Command interface
class Command
{
public:
  virtual ~Command() = default;
  virtual void execute() = 0;
};

// Concrete Commands
class LightOnCommand : public Command
{
  Light &light;

public:
  LightOnCommand(Light &l) : light(l) {}
  void execute() override
  {
    light.on();
  }
};

class LightOffCommand : public Command
{
  Light &light;

public:
  LightOffCommand(Light &l) : light(l) {}
  void execute() override
  {
    light.off();
  }
};

// Invoker
class RemoteControl
{
  std::vector<std::unique_ptr<Command>> onCommands;
  std::vector<std::unique_ptr<Command>> offCommands;

public:
  void setCommand(size_t slot, std::unique_ptr<Command> onCommand, std::unique_ptr<Command> offCommand)
  {
    if (slot >= onCommands.size())
    {
      onCommands.resize(slot + 1);
      offCommands.resize(slot + 1);
    }
    onCommands[slot] = std::move(onCommand);
    offCommands[slot] = std::move(offCommand);
  }
  void pressOnButton(size_t slot)
  {
    if (slot < onCommands.size() && onCommands[slot])
    {
      onCommands[slot]->execute();
    }
    else
    {
      std::cout << "No ON command set for slot " << slot << std::endl;
    }
  }
  void pressOffButton(size_t slot)
  {
    if (slot < offCommands.size() && offCommands[slot])
    {
      offCommands[slot]->execute();
    }
    else
    {
      std::cout << "No OFF command set for slot " << slot << std::endl;
    }
  }
};

// Demo
int main()
{
  Light livingRoomLight;
  RemoteControl remote;

  remote.setCommand(0, std::make_unique<LightOnCommand>(livingRoomLight), std::make_unique<LightOffCommand>(livingRoomLight));

  std::cout << "Pressing ON button for slot 0:" << std::endl;
  remote.pressOnButton(0);

  std::cout << "Pressing OFF button for slot 0:" << std::endl;
  remote.pressOffButton(0);

  std::cout << "Pressing ON button for slot 1 (no command set):" << std::endl;
  remote.pressOnButton(1);

  return 0;
}
