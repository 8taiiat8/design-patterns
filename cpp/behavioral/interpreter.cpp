// Interpreter — given a small language, define a class per grammar rule
// and an interpret() method that evaluates sentences of the language.
//
// Use for simple domain-specific languages: filters, arithmetic, rule
// engines. For anything complex, prefer a real parser generator.
//
// This example interprets arithmetic expressions built as an object tree:
// (5 + 3) - 2.
//
// Build: g++ -std=c++17 interpreter.cpp -o interpreter

#include <iostream>
#include <memory>

// Abstract expression
class Expression {
public:
    virtual ~Expression() = default;
    virtual int interpret() const = 0;
};

// Terminal expression: a literal number.
class Number : public Expression {
public:
    explicit Number(int value) : value_(value) {}
    int interpret() const override { return value_; }

private:
    int value_;
};

// Non-terminal expressions combine sub-expressions.
class Add : public Expression {
public:
    Add(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left_(std::move(left)), right_(std::move(right)) {}

    int interpret() const override { return left_->interpret() + right_->interpret(); }

private:
    std::unique_ptr<Expression> left_, right_;
};

class Subtract : public Expression {
public:
    Subtract(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left_(std::move(left)), right_(std::move(right)) {}

    int interpret() const override { return left_->interpret() - right_->interpret(); }

private:
    std::unique_ptr<Expression> left_, right_;
};

int main() {
    // Abstract syntax tree for: (5 + 3) - 2
    auto expression = std::make_unique<Subtract>(
        std::make_unique<Add>(std::make_unique<Number>(5), std::make_unique<Number>(3)),
        std::make_unique<Number>(2));

    std::cout << "(5 + 3) - 2 = " << expression->interpret() << "\n";
    return 0;
}
