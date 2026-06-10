// ☕ Café Patterna — Chapter 16: The Vinyl Crate
//
// STORY: The café's atmosphere lives and dies by its playlist. The
// records sit in a crate behind the counter — customers can flip through
// the playlist song by song, but NOBODY touches the crate itself or needs
// to know how the records are stored.
//
// PATTERN: Iterator — provide a way to traverse a collection without
// exposing its internal representation. In modern C++ this is built into
// the language: any type with begin()/end() works with range-based for
// loops and the STL algorithms.
//
// Build: g++ -std=c++17 iterator.cpp -o iterator

#include <iostream>
#include <string>
#include <vector>

// The café playlist; the storage (vinyl crate) stays private.
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
    Playlist morningSet;
    morningSet.add("Blue in Green");
    morningSet.add("Take Five");
    morningSet.add("Misty");

    // Explicit iterator usage...
    for (auto it = morningSet.begin(); it != morningSet.end(); ++it) {
        std::cout << "now playing: " << *it << "\n";
    }

    // ...and the idiomatic range-based for, which uses the same iterator.
    for (const auto& song : morningSet) {
        std::cout << "up next: " << song << "\n";
    }
    return 0;
}
