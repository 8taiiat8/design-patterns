// Flyweight — share common (intrinsic) state between many objects to save
// memory, while the varying (extrinsic) state is passed in from outside.
//
// Use when a program creates a huge number of similar objects (glyphs in a
// text editor, trees in a game forest) and memory is a concern.
//
// Build: g++ -std=c++17 flyweight.cpp -o flyweight

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// Flyweight: stores the heavy intrinsic state shared by many objects
// (imagine the texture/mesh of a tree type).
class TreeType {
public:
    TreeType(std::string name, std::string color)
        : name_(std::move(name)), color_(std::move(color)) {}

    // Extrinsic state (position) is supplied by the caller.
    void draw(int x, int y) const {
        std::cout << "draw " << color_ << " " << name_ << " at (" << x << ", " << y << ")\n";
    }

private:
    std::string name_;
    std::string color_;
};

// Flyweight factory: caches and reuses TreeType instances.
class TreeTypeFactory {
public:
    const TreeType& get(const std::string& name, const std::string& color) {
        std::string key = name + "/" + color;
        auto it = cache_.find(key);
        if (it == cache_.end()) {
            it = cache_.emplace(key, std::make_unique<TreeType>(name, color)).first;
            std::cout << "(created new flyweight: " << key << ")\n";
        }
        return *it->second;
    }

    size_t uniqueTypes() const { return cache_.size(); }

private:
    std::map<std::string, std::unique_ptr<TreeType>> cache_;
};

// Context object: tiny, holds only extrinsic state plus a shared flyweight.
struct Tree {
    int x;
    int y;
    const TreeType* type;
};

int main() {
    TreeTypeFactory factory;
    std::vector<Tree> forest;

    // Plant 6 trees, but only 2 unique TreeType objects exist in memory.
    forest.push_back({1, 2, &factory.get("oak", "green")});
    forest.push_back({3, 1, &factory.get("oak", "green")});
    forest.push_back({5, 7, &factory.get("pine", "dark-green")});
    forest.push_back({2, 8, &factory.get("oak", "green")});
    forest.push_back({9, 4, &factory.get("pine", "dark-green")});
    forest.push_back({6, 6, &factory.get("oak", "green")});

    for (const auto& tree : forest) tree.type->draw(tree.x, tree.y);
    std::cout << "trees: " << forest.size()
              << ", flyweights: " << factory.uniqueTypes() << "\n";
    return 0;
}
