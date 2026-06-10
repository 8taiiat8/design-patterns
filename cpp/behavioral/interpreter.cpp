// ☕ Café Patterna — Chapter 15: The Regulars' Shorthand
//
// STORY: Regulars order in shorthand: "espresso + milk - coupon". The
// till understands this tiny language: each word is a grammar rule, and
// evaluating the sentence computes the price in cents.
//
// PATTERN: Interpreter — for a small language, define a class per grammar
// rule and an interpret() method that evaluates sentences. Use for simple
// DSLs (filters, pricing rules); for anything complex use a real parser.
//
// This example evaluates the order tree: (espresso + milk) - coupon.
//
// Build: g++ -std=c++17 interpreter.cpp -o interpreter

#include <iostream>
#include <memory>
#include <string>

// Abstract expression: everything evaluates to a price in cents.
class OrderExpression {
public:
    virtual ~OrderExpression() = default;
    virtual int priceCents() const = 0;
};

// Terminal expression: a single menu item.
class Item : public OrderExpression {
public:
    Item(std::string name, int cents) : name_(std::move(name)), cents_(cents) {}
    int priceCents() const override { return cents_; }

private:
    std::string name_;
    int cents_;
};

// Non-terminal expressions combine sub-expressions.
class Plus : public OrderExpression {
public:
    Plus(std::unique_ptr<OrderExpression> left, std::unique_ptr<OrderExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {}

    int priceCents() const override { return left_->priceCents() + right_->priceCents(); }

private:
    std::unique_ptr<OrderExpression> left_, right_;
};

class Coupon : public OrderExpression {
public:
    Coupon(std::unique_ptr<OrderExpression> order, int discountCents)
        : order_(std::move(order)), discountCents_(discountCents) {}

    int priceCents() const override { return order_->priceCents() - discountCents_; }

private:
    std::unique_ptr<OrderExpression> order_;
    int discountCents_;
};

int main() {
    // Syntax tree for: (espresso + milk) - coupon(100)
    auto order = std::make_unique<Coupon>(
        std::make_unique<Plus>(std::make_unique<Item>("espresso", 200),
                               std::make_unique<Item>("milk", 50)),
        100);

    std::cout << "\"espresso + milk - coupon\" = "
              << order->priceCents() / 100.0 << " dollars\n";
    return 0;
}
