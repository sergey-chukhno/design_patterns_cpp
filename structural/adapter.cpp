/*
Adapter Design Pattern - C++ Example (Video Editing App: Color Interface)
-------------------------------------------------------------------------

Definition:
The Adapter pattern allows objects with incompatible interfaces to work together. It acts as a bridge between two incompatible interfaces by wrapping an existing class with a new interface.

Use Cases:
- When you want to use an existing class, but its interface does not match what you need.
- To enable classes to work together that couldn't otherwise because of incompatible interfaces.
- Useful for integrating third-party libraries or legacy code.

Key Concepts:
- Target: The interface your code expects (e.g., `Color`).
- Adaptee: The existing class with a different interface (e.g., `LegacyColorFilter`).
- Adapter: Wraps the adaptee and makes it compatible with the target interface.

Example: Video Editing App (Color Interface)
-------------------------------------------
Suppose you are building a video editing app that expects to use a `Color` interface to change a video's colors. However, you have a third-party or legacy class called `LegacyColorFilter` with a different interface. You want to use this class without modifying it, so you create an adapter.

*/

#include <iostream>
#include <string>
using namespace std;

// Target interface
class Color
{
public:
  virtual void applyColor(const string &videoFile) = 0;
  virtual ~Color() {}
};

// Adaptee (legacy or third-party class)
class LegacyColorFilter
{
public:
  void changeColor(const string &fileName, int rgb)
  {
    cout << "[LegacyColorFilter] Changing color of '" << fileName << "' to RGB: " << rgb << endl;
  }
};

// Adapter
class ColorAdapter : public Color
{
  LegacyColorFilter *legacyFilter;
  int rgbValue;

public:
  ColorAdapter(LegacyColorFilter *filter, int rgb) : legacyFilter(filter), rgbValue(rgb) {}
  void applyColor(const string &videoFile) override
  {
    // Adapts the call to the legacy interface
    legacyFilter->changeColor(videoFile, rgbValue);
  }
};

// Client code (Video Editor)
class VideoEditor
{
public:
  void changeVideoColor(Color *color, const string &videoFile)
  {
    color->applyColor(videoFile);
  }
};

int main()
{
  VideoEditor editor;
  string video = "holiday.mp4";

  // Suppose we want to use a legacy filter to apply a blue color (RGB: 255)
  LegacyColorFilter legacyFilter;
  ColorAdapter blueAdapter(&legacyFilter, 255); // 255 = blue

  // The editor uses the Color interface, unaware of the legacy filter
  editor.changeVideoColor(&blueAdapter, video);

  // You could easily add more adapters for other color filters
  ColorAdapter redAdapter(&legacyFilter, 16711680); // 16711680 = red
  editor.changeVideoColor(&redAdapter, video);

  return 0;
}