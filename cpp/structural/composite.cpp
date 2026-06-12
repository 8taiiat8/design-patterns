// 🤖 RoboWorks — Chapter 8: Assemblies of Assemblies
//
// STORY: A robot isn't one part — it's assemblies inside assemblies. The
// torso contains the arm assembly, which contains servos and grippers.
// The cost engineer wants to ask any node — a single bolt or the entire
// torso — the same question: "what does this cost?"
//
// PATTERN: Composite — compose objects into tree structures and let
// clients treat individual parts and whole assemblies uniformly.
//
// Build: g++ -std=c++17 composite.cpp -o composite

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Component: common interface for single parts and whole assemblies.
class PartComponent {
public:
    explicit PartComponent(std::string name) : name_(std::move(name)) {}
    virtual ~PartComponent() = default;

    virtual long costCents() const = 0;
    virtual void print(int indent) const = 0;

protected:
    std::string name_;
};

// Leaf
class Part : public PartComponent {
public:
    Part(std::string name, long costCents)
        : PartComponent(std::move(name)), costCents_(costCents) {}

    long costCents() const override { return costCents_; }

    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << "- " << name_
                  << " ($" << costCents_ / 100.0 << ")\n";
    }

private:
    long costCents_;
};

// Composite: holds children and forwards operations to them.
class Assembly : public PartComponent {
public:
    explicit Assembly(std::string name) : PartComponent(std::move(name)) {}

    void add(std::unique_ptr<PartComponent> child) {
        children_.push_back(std::move(child));
    }

    long costCents() const override {
        long total = 0;
        for (const auto& child : children_) total += child->costCents();
        return total;
    }

    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << "+ " << name_ << "\n";
        for (const auto& child : children_) child->print(indent + 2);
    }

private:
    std::vector<std::unique_ptr<PartComponent>> children_;
};

int main() {
    auto torso = std::make_unique<Assembly>("torso assembly");
    torso->add(std::make_unique<Part>("steel frame", 12000));

    auto arm = std::make_unique<Assembly>("arm assembly");
    arm->add(std::make_unique<Part>("servo motor", 4500));
    arm->add(std::make_unique<Part>("gripper", 3000));
    torso->add(std::move(arm));

    torso->print(0);
    std::cout << "total cost: $" << torso->costCents() / 100.0 << "\n";
    return 0;
}
