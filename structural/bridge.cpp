/*
Bridge Design Pattern - C++ Example (Remote Controls and Devices)
----------------------------------------------------------------

Definition:
The Bridge pattern decouples an abstraction from its implementation so that the two can vary independently. It is used to separate the interface (abstraction) from the implementation, allowing both to be extended without affecting each other.

Use Cases:
- When you want to avoid a permanent binding between an abstraction and its implementation.
- When both the abstractions and their implementations should be independently extensible.
- Useful when you have a class hierarchy in two orthogonal dimensions (e.g., shapes and colors, remotes and devices).

Key Concepts:
- Abstraction: Defines the interface and maintains a reference to the implementor.
- Implementor: Defines the interface for implementation classes.
- RefinedAbstraction: Extends the abstraction interface.
- ConcreteImplementor: Implements the implementor interface.

Example: Remote Controls and Devices
-----------------------------------
Suppose you are building a system for remote controls and electronic devices. You want to be able to add new types of remotes and new types of devices independently.
- Abstraction: RemoteControl (interface for remotes)
- Implementor: Device (interface for devices)
- RefinedAbstraction: AdvancedRemoteControl
- ConcreteImplementor: TV, Radio

*/

#include <iostream>
#include <string>
using namespace std;

// Implementor
class Device
{
public:
  virtual void turnOn() = 0;
  virtual void turnOff() = 0;
  virtual void setChannel(int channel) = 0;
  virtual ~Device() {}
};

// ConcreteImplementor: TV
class TV : public Device
{
public:
  void turnOn() override
  {
    cout << "TV is ON" << endl;
  }
  void turnOff() override
  {
    cout << "TV is OFF" << endl;
  }
  void setChannel(int channel) override
  {
    cout << "TV channel set to " << channel << endl;
  }
};

// ConcreteImplementor: Radio
class Radio : public Device
{
public:
  void turnOn() override
  {
    cout << "Radio is ON" << endl;
  }
  void turnOff() override
  {
    cout << "Radio is OFF" << endl;
  }
  void setChannel(int channel) override
  {
    cout << "Radio station set to " << channel << endl;
  }
};

// Abstraction
class RemoteControl
{
protected:
  Device *device;

public:
  RemoteControl(Device *d) : device(d) {}
  virtual void turnOn()
  {
    device->turnOn();
  }
  virtual void turnOff()
  {
    device->turnOff();
  }
  virtual void setChannel(int channel)
  {
    device->setChannel(channel);
  }
  virtual ~RemoteControl() {}
};

// RefinedAbstraction
class AdvancedRemoteControl : public RemoteControl
{
public:
  AdvancedRemoteControl(Device *d) : RemoteControl(d) {}
  void mute()
  {
    cout << "Device muted" << endl;
  }
};

int main()
{
  TV tv;
  Radio radio;

  RemoteControl basicRemote(&tv);
  AdvancedRemoteControl advancedRemote(&radio);

  cout << "Using basic remote with TV:" << endl;
  basicRemote.turnOn();
  basicRemote.setChannel(5);
  basicRemote.turnOff();

  cout << "\nUsing advanced remote with Radio:" << endl;
  advancedRemote.turnOn();
  advancedRemote.setChannel(101);
  advancedRemote.mute();
  advancedRemote.turnOff();

  return 0;
}