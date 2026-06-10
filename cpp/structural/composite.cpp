// ☕ Café Patterna — Chapter 8: The Menu Grows
//
// STORY: The menu used to be five drinks. Now it has sections, sections
// inside sections, and combo deals. The owner just wants to ask any line
// on the menu — a single croissant or the entire "Breakfast" section —
// the same question: "what does this cost?"
//
// PATTERN: Composite — compose objects into tree structures and let
// clients treat individual items and groups uniformly.
//
// Build: g++ -std=c++17 composite.cpp -o composite

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Component: common interface for single items and whole sections.
class MenuComponent {
public:
    explicit MenuComponent(std::string name) : name_(std::move(name)) {}
    virtual ~MenuComponent() = default;

    virtual long priceCents() const = 0;
    virtual void print(int indent) const = 0;

protected:
    std::string name_;
};

// Leaf
class MenuItem : public MenuComponent {
public:
    MenuItem(std::string name, long priceCents)
        : MenuComponent(std::move(name)), priceCents_(priceCents) {}

    long priceCents() const override { return priceCents_; }

    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << "- " << name_
                  << " ($" << priceCents_ / 100.0 << ")\n";
    }

private:
    long priceCents_;
};

// Composite: holds children and forwards operations to them.
class MenuSection : public MenuComponent {
public:
    explicit MenuSection(std::string name) : MenuComponent(std::move(name)) {}

    void add(std::unique_ptr<MenuComponent> child) {
        children_.push_back(std::move(child));
    }

    long priceCents() const override {
        long total = 0;
        for (const auto& child : children_) total += child->priceCents();
        return total;
    }

    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << "+ " << name_ << "\n";
        for (const auto& child : children_) child->print(indent + 2);
    }

private:
    std::vector<std::unique_ptr<MenuComponent>> children_;
};

int main() {
    auto menu = std::make_unique<MenuSection>("Café Patterna Menu");
    menu->add(std::make_unique<MenuItem>("espresso", 200));

    auto breakfast = std::make_unique<MenuSection>("Breakfast combo");
    breakfast->add(std::make_unique<MenuItem>("latte", 350));
    breakfast->add(std::make_unique<MenuItem>("croissant", 300));
    menu->add(std::move(breakfast));

    menu->print(0);
    std::cout << "whole menu, one of each: $" << menu->priceCents() / 100.0 << "\n";
    return 0;
}
