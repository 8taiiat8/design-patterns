// Iterator — provide a way to traverse a collection without exposing its
// internal representation.
//
// In modern C++ this pattern is baked into the language: any type that
// provides begin()/end() works with range-based for loops and the STL
// algorithms. This example builds a custom container with its own iterator.
//
// Build: g++ -std=c++17 iterator.cpp -o iterator

#include <iostream>
#include <string>
#include <vector>

// A custom collection whose storage layout is private.
class Playlist {
public:
    void add(std::string song) { songs_.push_back(std::move(song)); }

    // Iterator over the playlist. Clients never see the vector inside.
    class Iterator {
    public:
        Iterator(const Playlist& playlist, size_t pos) : playlist_(playlist), pos_(pos) {}

        const std::string& operator*() const { return playlist_.songs_[pos_]; }
        Iterator& operator++() { ++pos_; return *this; }
        bool operator!=(const Iterator& other) const { return pos_ != other.pos_; }

    private:
        const Playlist& playlist_;
        size_t pos_;
    };

    Iterator begin() const { return Iterator(*this, 0); }
    Iterator end() const { return Iterator(*this, songs_.size()); }

private:
    std::vector<std::string> songs_;
};

int main() {
    Playlist playlist;
    playlist.add("Bohemian Rhapsody");
    playlist.add("Hotel California");
    playlist.add("Stairway to Heaven");

    // Explicit iterator usage...
    for (auto it = playlist.begin(); it != playlist.end(); ++it) {
        std::cout << "playing: " << *it << "\n";
    }

    // ...and the idiomatic range-based for, which uses the same iterator.
    for (const auto& song : playlist) {
        std::cout << "queued: " << song << "\n";
    }
    return 0;
}
