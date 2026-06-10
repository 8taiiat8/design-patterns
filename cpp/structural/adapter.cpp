// Adapter — convert the interface of an existing class into the interface
// clients expect, letting otherwise incompatible classes work together.
//
// Use when you want to reuse an existing class (often third-party or
// legacy) whose interface doesn't match what your code needs.
//
// Build: g++ -std=c++17 adapter.cpp -o adapter

#include <iostream>
#include <memory>
#include <string>

// The interface our application expects.
class MediaPlayer {
public:
    virtual ~MediaPlayer() = default;
    virtual void play(const std::string& file) = 0;
};

// Existing/legacy class with an incompatible interface (the adaptee).
// Imagine we cannot modify it.
class VlcEngine {
public:
    void startVlcPlayback(const std::string& path) {
        std::cout << "VLC engine playing: " << path << "\n";
    }
};

// The adapter implements the expected interface and delegates to the adaptee.
class VlcAdapter : public MediaPlayer {
public:
    void play(const std::string& file) override {
        engine_.startVlcPlayback(file);  // translate the call
    }

private:
    VlcEngine engine_;
};

// A native implementation, for comparison.
class Mp3Player : public MediaPlayer {
public:
    void play(const std::string& file) override {
        std::cout << "MP3 player playing: " << file << "\n";
    }
};

int main() {
    std::unique_ptr<MediaPlayer> players[] = {
        std::make_unique<Mp3Player>(),
        std::make_unique<VlcAdapter>(),  // legacy engine behind the same interface
    };

    for (auto& p : players) {
        p->play("song.mp3");
    }
    return 0;
}
