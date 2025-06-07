/*
Chain of Responsibility Design Pattern - C++ Example (HTTP Request Access)
------------------------------------------------------------------------

Definition:
The Chain of Responsibility pattern allows an incoming request to be passed along a chain of handlers. Each handler decides either to process the request or to pass it to the next handler in the chain. This decouples the sender of a request from its receivers, giving more than one object a chance to handle the request.

Use Cases:
- When more than one object may handle a request, and the handler isn't known a priori.
- To avoid coupling the sender of a request to its receiver.
- To allow dynamic arrangement of request handlers.
- Commonly used in event processing, middleware, and validation pipelines.

Key Concepts:
- Handler: Defines an interface for handling requests and for setting the next handler in the chain.
- ConcreteHandler: Handles requests it is responsible for, or forwards them to the next handler.
- Client: Initiates the request and sets up the chain.

Example: HTTP Request Access
---------------------------
We will model a simple HTTP request access pipeline where:
- A user makes an HTTP request to access a web page.
- The request passes through a chain of handlers:
  1. AuthenticationHandler: Checks if the user is authenticated.
  2. AuthorizationHandler: Checks if the user has permission to access the page.
  3. ContentHandler: Serves the page if all checks pass.
- Each handler can approve, reject, or pass the request to the next handler.

*/

#include <iostream>
#include <string>
using namespace std;

// Request object
struct HttpRequest
{
  string username;
  bool authenticated;
  bool authorized;
  string page;
};

// Handler interface
class Handler
{
protected:
  Handler *next;

public:
  Handler() : next(nullptr) {}
  void setNext(Handler *n) { next = n; }
  virtual void handle(HttpRequest &request)
  {
    if (next)
      next->handle(request);
  }
  virtual ~Handler() {}
};

// Concrete Handler: Authentication
class AuthenticationHandler : public Handler
{
public:
  void handle(HttpRequest &request) override
  {
    cout << "AuthenticationHandler: Checking authentication...\n";
    if (request.authenticated)
    {
      cout << "User '" << request.username << "' is authenticated.\n";
      if (next)
        next->handle(request);
    }
    else
    {
      cout << "Access denied: User is not authenticated.\n";
    }
  }
};

// Concrete Handler: Authorization
class AuthorizationHandler : public Handler
{
public:
  void handle(HttpRequest &request) override
  {
    cout << "AuthorizationHandler: Checking authorization...\n";
    if (request.authorized)
    {
      cout << "User '" << request.username << "' is authorized to access '" << request.page << "'.\n";
      if (next)
        next->handle(request);
    }
    else
    {
      cout << "Access denied: User is not authorized to access '" << request.page << "'.\n";
    }
  }
};

// Concrete Handler: Content
class ContentHandler : public Handler
{
public:
  void handle(HttpRequest &request) override
  {
    cout << "ContentHandler: Serving page '" << request.page << "' to user '" << request.username << "'.\n";
  }
};

int main()
{
  // Set up the chain
  AuthenticationHandler authn;
  AuthorizationHandler authz;
  ContentHandler content;
  authn.setNext(&authz);
  authz.setNext(&content);

  // Test cases
  HttpRequest req1{"alice", true, true, "home.html"};
  HttpRequest req2{"bob", false, false, "admin.html"};
  HttpRequest req3{"carol", true, false, "admin.html"};

  cout << "\n--- Request 1: Authenticated and Authorized ---\n";
  authn.handle(req1);

  cout << "\n--- Request 2: Not Authenticated ---\n";
  authn.handle(req2);

  cout << "\n--- Request 3: Authenticated but Not Authorized ---\n";
  authn.handle(req3);

  return 0;
}
