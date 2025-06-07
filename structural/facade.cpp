/*
Facade Design Pattern - C++ Example (Ecommerce Application)
-----------------------------------------------------------

Definition:
The Facade pattern provides a simplified interface to a complex subsystem. It hides the complexities of the subsystem and provides a higher-level interface that makes the subsystem easier to use.

Use Cases:
- When you want to provide a simple interface to a complex system.
- To decouple a client from the implementation details of a subsystem.
- Useful for libraries, frameworks, or any system with many moving parts.

Key Concepts:
- Facade: The class that provides the simple interface.
- Subsystem Classes: The complex classes that do the actual work.

Example: Ecommerce Application
------------------------------
Suppose you are building an ecommerce application. Placing an order involves multiple subsystems: inventory, payment, and shipping. The Facade pattern allows you to provide a simple `placeOrder` method that hides all the complexity from the client.

*/

#include <iostream>
#include <string>
using namespace std;

// Subsystem: Inventory
class Inventory
{
public:
  bool checkStock(const string &item)
  {
    cout << "[Inventory] Checking stock for '" << item << "'..." << endl;
    return true; // Assume always in stock for this example
  }
  void reserveItem(const string &item)
  {
    cout << "[Inventory] Reserving '" << item << "'..." << endl;
  }
};

// Subsystem: Payment
class Payment
{
public:
  bool processPayment(const string &customer, double amount)
  {
    cout << "[Payment] Processing payment of $" << amount << " for '" << customer << "'..." << endl;
    return true; // Assume payment always succeeds
  }
};

// Subsystem: Shipping
class Shipping
{
public:
  void createShipment(const string &item, const string &address)
  {
    cout << "[Shipping] Shipping '" << item << "' to '" << address << "'..." << endl;
  }
};

// Facade
class OrderFacade
{
  Inventory inventory;
  Payment payment;
  Shipping shipping;

public:
  void placeOrder(const string &customer, const string &item, double amount, const string &address)
  {
    cout << "\n[OrderFacade] Placing order for '" << customer << "'..." << endl;
    if (!inventory.checkStock(item))
    {
      cout << "[OrderFacade] Item out of stock!" << endl;
      return;
    }
    inventory.reserveItem(item);
    if (!payment.processPayment(customer, amount))
    {
      cout << "[OrderFacade] Payment failed!" << endl;
      return;
    }
    shipping.createShipment(item, address);
    cout << "[OrderFacade] Order placed successfully!" << endl;
  }
};

// Client code
int main()
{
  OrderFacade facade;
  facade.placeOrder("Alice", "Laptop", 999.99, "123 Main St");
  facade.placeOrder("Bob", "Phone", 499.99, "456 Elm St");
  return 0;
}