/*
State Design Pattern (Document Publishing Example, C++)
------------------------------------------------------
This example demonstrates the State pattern applied to a document publishing workflow. The Document class delegates its publish() behavior to a DocumentState interface, which is implemented by various concrete states (Draft, UnderReview, Published, Archived, etc.). The behavior of publish() depends on both the current state and the user's role (Editor, Moderator, Admin). This design satisfies the Open/Closed Principle: new states or roles can be added by extending classes, not by modifying existing ones.

Key Participants:
- Document: The context class, representing a document. It maintains a reference to a DocumentState and delegates state-specific behavior to it.
- DocumentState (interface): Declares the interface for state-specific behavior (publish).
- Concrete States: Implement state-specific behavior for publish (Draft, UnderReview, Published, Archived, etc.).
- UserRole (enum): Represents user roles (Editor, Moderator, Admin).

How it works in this example:
- The Document class has a state and a publish() method, which delegates to the current state's publish() method.
- Each state implements its own logic for publish(), possibly transitioning the document to a new state depending on the user's role.
- The design is open for extension (new states/roles) and closed for modification (existing code doesn't need to change).
*/

#include <iostream>
#include <memory>
#include <string>

// User roles
enum class UserRole
{
  Editor,
  Moderator,
  Admin
};

std::string roleToString(UserRole role)
{
  switch (role)
  {
  case UserRole::Editor:
    return "Editor";
  case UserRole::Moderator:
    return "Moderator";
  case UserRole::Admin:
    return "Admin";
  default:
    return "Unknown";
  }
}

class Document;

// State interface
class DocumentState
{
public:
  virtual ~DocumentState() = default;
  virtual void publish(Document &doc, UserRole user) = 0;
  virtual std::string name() const = 0;
};

// Forward declaration for state transitions
class DraftState;
class UnderReviewState;
class PublishedState;
class ArchivedState;

// Document class
class Document
{
  std::unique_ptr<DocumentState> state;
  std::string title;

public:
  Document(std::string t);
  void setState(std::unique_ptr<DocumentState> newState);
  void publish(UserRole user);
  std::string getStateName() const;
  std::string getTitle() const { return title; }
};

// Concrete States
class DraftState : public DocumentState
{
public:
  void publish(Document &doc, UserRole user) override;
  std::string name() const override { return "Draft"; }
};

class UnderReviewState : public DocumentState
{
public:
  void publish(Document &doc, UserRole user) override;
  std::string name() const override { return "Under Review"; }
};

class PublishedState : public DocumentState
{
public:
  void publish(Document &doc, UserRole user) override;
  std::string name() const override { return "Published"; }
};

class ArchivedState : public DocumentState
{
public:
  void publish(Document &doc, UserRole user) override;
  std::string name() const override { return "Archived"; }
};

// Document implementation
Document::Document(std::string t)
    : state(std::make_unique<DraftState>()), title(std::move(t)) {}

void Document::setState(std::unique_ptr<DocumentState> newState)
{
  state = std::move(newState);
}

void Document::publish(UserRole user)
{
  state->publish(*this, user);
}

std::string Document::getStateName() const
{
  return state->name();
}

// State transitions and logic
void DraftState::publish(Document &doc, UserRole user)
{
  if (user == UserRole::Editor)
  {
    std::cout << "[Draft] " << doc.getTitle() << ": Editor submits for review.\n";
    doc.setState(std::make_unique<UnderReviewState>());
  }
  else if (user == UserRole::Admin)
  {
    std::cout << "[Draft] " << doc.getTitle() << ": Admin publishes directly.\n";
    doc.setState(std::make_unique<PublishedState>());
  }
  else
  {
    std::cout << "[Draft] " << doc.getTitle() << ": Only Editor or Admin can publish.\n";
  }
}

void UnderReviewState::publish(Document &doc, UserRole user)
{
  if (user == UserRole::Moderator)
  {
    std::cout << "[Under Review] " << doc.getTitle() << ": Moderator approves and publishes.\n";
    doc.setState(std::make_unique<PublishedState>());
  }
  else if (user == UserRole::Admin)
  {
    std::cout << "[Under Review] " << doc.getTitle() << ": Admin publishes.\n";
    doc.setState(std::make_unique<PublishedState>());
  }
  else
  {
    std::cout << "[Under Review] " << doc.getTitle() << ": Only Moderator or Admin can publish.\n";
  }
}

void PublishedState::publish(Document &doc, UserRole user)
{
  if (user == UserRole::Admin)
  {
    std::cout << "[Published] " << doc.getTitle() << ": Admin archives the document.\n";
    doc.setState(std::make_unique<ArchivedState>());
  }
  else
  {
    std::cout << "[Published] " << doc.getTitle() << ": Only Admin can archive.\n";
  }
}

void ArchivedState::publish(Document &doc, UserRole user)
{
  std::cout << "[Archived] " << doc.getTitle() << ": No further actions allowed.\n";
}

// Demo
int main()
{
  Document doc("Design Patterns in C++");
  std::cout << "Initial State: " << doc.getStateName() << "\n";

  doc.publish(UserRole::Editor); // Draft -> Under Review
  std::cout << "Current State: " << doc.getStateName() << "\n";

  doc.publish(UserRole::Moderator); // Under Review -> Published
  std::cout << "Current State: " << doc.getStateName() << "\n";

  doc.publish(UserRole::Admin); // Published -> Archived
  std::cout << "Current State: " << doc.getStateName() << "\n";

  doc.publish(UserRole::Editor); // Archived: No further actions
  std::cout << "Current State: " << doc.getStateName() << "\n";

  return 0;
}
