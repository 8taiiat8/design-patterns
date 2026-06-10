// ☕ Café Patterna — Chapter 23: The Inspectors
//
// STORY: Two visitors walk the menu today: the nutritionist tallies
// calories, the accountant prints price tags. The menu items themselves
// (espresso, muffin) don't change — each item simply ACCEPTS the visitor
// and the visitor does its own job per item type. Next month a new
// inspector can visit without touching a single menu class.
//
// PATTERN: Visitor — represent an operation on the elements of an object
// structure, letting you add new operations without modifying the element
// classes. The key mechanism is double dispatch via accept()/visit().
//
// Build: g++ -std=c++17 visitor.cpp -o visitor

#include <iostream>
#include <memory>
#include <vector>

class EspressoItem;
class MuffinItem;

// Visitor interface: one visit overload per element type.
class MenuVisitor {
public:
    virtual ~MenuVisitor() = default;
    virtual void visit(const EspressoItem& espresso) = 0;
    virtual void visit(const MuffinItem& muffin) = 0;
};

// Element interface
class MenuItem {
public:
    virtual ~MenuItem() = default;
    virtual void accept(MenuVisitor& visitor) const = 0;
};

class EspressoItem : public MenuItem {
public:
    explicit EspressoItem(int shots) : shots_(shots) {}
    int shots() const { return shots_; }
    void accept(MenuVisitor& visitor) const override { visitor.visit(*this); }

private:
    int shots_;
};

class MuffinItem : public MenuItem {
public:
    explicit MuffinItem(int grams) : grams_(grams) {}
    int grams() const { return grams_; }
    void accept(MenuVisitor& visitor) const override { visitor.visit(*this); }

private:
    int grams_;
};

// New operations are added as new visitors — no MenuItem class changes.
class CalorieCounter : public MenuVisitor {
public:
    void visit(const EspressoItem& espresso) override { total_ += 5 * espresso.shots(); }
    void visit(const MuffinItem& muffin) override { total_ += 4 * muffin.grams(); }
    int total() const { return total_; }

private:
    int total_ = 0;
};

class PriceTagPrinter : public MenuVisitor {
public:
    void visit(const EspressoItem& espresso) override {
        std::cout << "tag: espresso, " << espresso.shots() << " shot(s) — $2.00\n";
    }
    void visit(const MuffinItem& muffin) override {
        std::cout << "tag: muffin, " << muffin.grams() << "g — $3.50\n";
    }
};

int main() {
    std::vector<std::unique_ptr<MenuItem>> menu;
    menu.push_back(std::make_unique<EspressoItem>(2));
    menu.push_back(std::make_unique<MuffinItem>(120));

    CalorieCounter nutritionist;
    PriceTagPrinter accountant;
    for (const auto& item : menu) {
        item->accept(nutritionist);
        item->accept(accountant);
    }
    std::cout << "total calories on the menu: " << nutritionist.total() << "\n";
    return 0;
}
