/*
Proxy Design Pattern - C++ Example (YouTube Video Service - Lazy Loading)
--------------------------------------------------------------------------

Definition:
The Proxy pattern provides a surrogate or placeholder for another object to control access to it. The proxy can add additional behavior (e.g., lazy loading, caching, logging, access control) without changing the real object's code.

Use Cases:
- To control access to an object (e.g., authentication, lazy loading, caching).
- To add functionality to an object transparently.
- Useful for remote proxies, virtual proxies, protection proxies, and smart references.

Key Concepts:
- Subject: The common interface for RealSubject and Proxy.
- RealSubject: The real object that does the actual work (e.g., YouTube API service).
- Proxy: Controls access to the RealSubject and may add extra behavior.

Example: YouTube Video Service (Lazy Loading)
---------------------------------------------
Suppose you have a service that fetches YouTube videos via the YouTube API. Creating the API object is expensive, so you want to delay its creation until it is actually needed (lazy loading).

*/

#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
using namespace std;

// Subject interface
class YouTubeService
{
public:
  virtual string getVideo(const string &videoId) = 0;
  virtual ~YouTubeService() {}
};

// RealSubject: Actual YouTube API service
class YouTubeAPI : public YouTubeService
{
public:
  YouTubeAPI()
  {
    cout << "[YouTubeAPI] Initializing YouTube API connection..." << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
  }
  string getVideo(const string &videoId) override
  {
    cout << "[YouTubeAPI] Fetching video '" << videoId << "' from YouTube..." << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    return "VideoData: " + videoId;
  }
};

// Proxy: Lazy loading proxy for YouTubeService
class YouTubeLazyProxy : public YouTubeService
{
  unique_ptr<YouTubeAPI> api;

public:
  YouTubeLazyProxy() : api(nullptr) {}
  string getVideo(const string &videoId) override
  {
    if (!api)
    {
      cout << "[Proxy] YouTubeAPI not initialized. Initializing now..." << endl;
      api = make_unique<YouTubeAPI>();
    }
    else
    {
      cout << "[Proxy] YouTubeAPI already initialized. Using existing instance." << endl;
    }
    return api->getVideo(videoId);
  }
};

// Client code
void clientCode(YouTubeService *service)
{
  cout << service->getVideo("abc123") << endl;
  cout << service->getVideo("xyz789") << endl;
}

int main()
{
  YouTubeLazyProxy proxy;

  cout << "Fetching videos via lazy proxy:\n";
  clientCode(&proxy);

  return 0;
}