/*
Strategy Design Pattern (Video Storage App Example, C++)
--------------------------------------------------------
The Strategy pattern is a behavioral design pattern that enables selecting an algorithm's behavior at runtime. It defines a family of algorithms, encapsulates each one, and makes them interchangeable. This pattern is useful when you want to allow the client to choose from multiple behaviors or algorithms dynamically.

Key Participants:
- Context: The class that uses a Strategy to perform its behavior (VideoStorage).
- Strategy (interface): Declares the interface for a family of algorithms (CompressionStrategy, OverlayStrategy).
- ConcreteStrategy: Implements the Strategy interface for a specific algorithm (e.g., ZipCompression, H264Compression, WatermarkOverlay, TimestampOverlay).

How it works in this example:
- The VideoStorage class allows the user to set a compression strategy and an overlay strategy.
- CompressionStrategy and OverlayStrategy are interfaces for compression and overlay algorithms.
- Several concrete strategies are provided for both compression and overlays.
- The user can dynamically choose which strategies to use for each video.

This pattern is especially useful when you want to avoid large conditional statements and allow easy extension of new algorithms or behaviors.
*/

#include <iostream>
#include <memory>
#include <string>

// Compression Strategy Interface
class CompressionStrategy
{
public:
  virtual ~CompressionStrategy() = default;
  virtual void compress(const std::string &filename) const = 0;
};

// Concrete Compression Strategies
class ZipCompression : public CompressionStrategy
{
public:
  void compress(const std::string &filename) const override
  {
    std::cout << "Compressing '" << filename << "' using ZIP compression.\n";
  }
};

class H264Compression : public CompressionStrategy
{
public:
  void compress(const std::string &filename) const override
  {
    std::cout << "Compressing '" << filename << "' using H.264 compression.\n";
  }
};

class VP9Compression : public CompressionStrategy
{
public:
  void compress(const std::string &filename) const override
  {
    std::cout << "Compressing '" << filename << "' using VP9 compression.\n";
  }
};

// Overlay Strategy Interface
class OverlayStrategy
{
public:
  virtual ~OverlayStrategy() = default;
  virtual void apply(const std::string &filename) const = 0;
};

// Concrete Overlay Strategies
class WatermarkOverlay : public OverlayStrategy
{
public:
  void apply(const std::string &filename) const override
  {
    std::cout << "Applying watermark overlay to '" << filename << "'.\n";
  }
};

class TimestampOverlay : public OverlayStrategy
{
public:
  void apply(const std::string &filename) const override
  {
    std::cout << "Applying timestamp overlay to '" << filename << "'.\n";
  }
};

class NoOverlay : public OverlayStrategy
{
public:
  void apply(const std::string &filename) const override
  {
    std::cout << "No overlay applied to '" << filename << "'.\n";
  }
};

// VideoStorage Context
class VideoStorage
{
  std::unique_ptr<CompressionStrategy> compressionStrategy;
  std::unique_ptr<OverlayStrategy> overlayStrategy;

public:
  VideoStorage(std::unique_ptr<CompressionStrategy> comp, std::unique_ptr<OverlayStrategy> overlay)
      : compressionStrategy(std::move(comp)), overlayStrategy(std::move(overlay)) {}

  void setCompressionStrategy(std::unique_ptr<CompressionStrategy> comp)
  {
    compressionStrategy = std::move(comp);
  }
  void setOverlayStrategy(std::unique_ptr<OverlayStrategy> overlay)
  {
    overlayStrategy = std::move(overlay);
  }

  void storeVideo(const std::string &filename)
  {
    std::cout << "Storing video: '" << filename << "'\n";
    compressionStrategy->compress(filename);
    overlayStrategy->apply(filename);
    std::cout << "Video '" << filename << "' stored successfully.\n\n";
  }
};

// Demo
int main()
{
  // User chooses H264 compression and watermark overlay
  VideoStorage storage(
      std::make_unique<H264Compression>(),
      std::make_unique<WatermarkOverlay>());
  storage.storeVideo("holiday.mp4");

  // User switches to VP9 compression and timestamp overlay
  storage.setCompressionStrategy(std::make_unique<VP9Compression>());
  storage.setOverlayStrategy(std::make_unique<TimestampOverlay>());
  storage.storeVideo("lecture.webm");

  // User switches to ZIP compression and no overlay
  storage.setCompressionStrategy(std::make_unique<ZipCompression>());
  storage.setOverlayStrategy(std::make_unique<NoOverlay>());
  storage.storeVideo("archive.avi");

  return 0;
}
