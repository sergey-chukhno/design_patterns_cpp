/*
Mediator Design Pattern - C++ Example (Blog and Blog Posts)
----------------------------------------------------------

Definition:
The Mediator pattern defines an object (the mediator) that encapsulates how a set of objects interact. It promotes loose coupling by preventing objects from referring to each other explicitly, allowing their interaction to be varied independently.

Use Cases:
- When a set of objects communicate in complex but well-defined ways.
- To centralize complex communications and control between related objects.
- To reduce dependencies between communicating objects, making them easier to maintain and extend.

Key Concepts:
- Mediator: Defines an interface for communicating with Colleague objects.
- ConcreteMediator: Implements cooperative behavior by coordinating Colleague objects.
- Colleague: Each object communicates with the Mediator instead of directly with other Colleagues.

Example: Blog and Blog Posts
---------------------------
We will model a blog system where:
- The Blog acts as a mediator between BlogPosts.
- BlogPosts notify the Blog when they are created or updated.
- The Blog can notify all posts of certain events (e.g., a new post is published, or a post is updated).
- BlogPosts do not communicate directly with each other, but only through the Blog (mediator).

*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Forward declaration
class BlogPost;

// Mediator interface
class BlogMediator
{
public:
  virtual void notify(BlogPost *sender, const string &event) = 0;
  virtual void registerPost(BlogPost *post) = 0;
  virtual ~BlogMediator() {}
};

// Colleague: BlogPost
class BlogPost
{
  string title;
  string content;
  BlogMediator *mediator;

public:
  BlogPost(const string &t, const string &c, BlogMediator *m = nullptr)
      : title(t), content(c), mediator(m) {}
  void setMediator(BlogMediator *m)
  {
    mediator = m;
  }
  void publish()
  {
    cout << "Publishing post: '" << title << "'" << endl;
    if (mediator)
      mediator->notify(this, "publish");
  }
  void updateContent(const string &newContent)
  {
    content = newContent;
    cout << "Updating post: '" << title << "'" << endl;
    if (mediator)
      mediator->notify(this, "update");
  }
  string getTitle() const { return title; }
  string getContent() const { return content; }
  void notifyEvent(const string &event, BlogPost *source)
  {
    if (source != this)
    {
      cout << "Post '" << title << "' received notification: '" << event << "' from post '" << source->getTitle() << "'" << endl;
    }
  }
};

// Concrete Mediator: Blog
class Blog : public BlogMediator
{
  vector<BlogPost *> posts;

public:
  void registerPost(BlogPost *post) override
  {
    posts.push_back(post);
    post->setMediator(this);
  }
  void notify(BlogPost *sender, const string &event) override
  {
    for (auto *post : posts)
    {
      post->notifyEvent(event, sender);
    }
  }
};

int main()
{
  Blog blog;
  BlogPost post1("Observer Pattern", "Details about observer pattern...");
  BlogPost post2("Mediator Pattern", "Details about mediator pattern...");
  BlogPost post3("Strategy Pattern", "Details about strategy pattern...");

  blog.registerPost(&post1);
  blog.registerPost(&post2);
  blog.registerPost(&post3);

  post1.publish();
  cout << endl;
  post2.updateContent("Updated content for mediator pattern...");
  cout << endl;
  post3.publish();

  return 0;
}
