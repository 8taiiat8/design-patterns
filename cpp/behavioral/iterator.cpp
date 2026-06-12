// 🤖 RoboWorks — Chapter 16: Walking the Conveyor
//
// STORY: The production queue lives on the conveyor system. Supervisors
// can walk the queue job by job — but NOBODY reaches into the conveyor's
// machinery or needs to know how jobs are stored inside it.
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

// The production queue; the storage (conveyor internals) stays private.
class ProductionQueue {
public:
    void add(std::string job) { jobs_.push_back(std::move(job)); }

    // Iterator over the queue. Clients never see the vector inside.
    class Iterator {
    public:
        Iterator(const ProductionQueue& queue, size_t pos) : queue_(queue), pos_(pos) {}

        const std::string& operator*() const { return queue_.jobs_[pos_]; }
        Iterator& operator++() { ++pos_; return *this; }
        bool operator!=(const Iterator& other) const { return pos_ != other.pos_; }

    private:
        const ProductionQueue& queue_;
        size_t pos_;
    };

    Iterator begin() const { return Iterator(*this, 0); }
    Iterator end() const { return Iterator(*this, jobs_.size()); }

private:
    std::vector<std::string> jobs_;
};

int main() {
    ProductionQueue morningShift;
    morningShift.add("weld chassis #7");
    morningShift.add("paint drone shell #12");
    morningShift.add("install firmware on batch 3");

    // Explicit iterator usage...
    for (auto it = morningShift.begin(); it != morningShift.end(); ++it) {
        std::cout << "executing: " << *it << "\n";
    }

    // ...and the idiomatic range-based for, which uses the same iterator.
    for (const auto& job : morningShift) {
        std::cout << "queued: " << job << "\n";
    }
    return 0;
}
