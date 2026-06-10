// Prototype — create new objects by copying an existing object (the
// prototype) instead of building them from scratch.
//
// Use when object creation is expensive (e.g. requires I/O or heavy
// computation) or when the code shouldn't depend on the concrete classes
// of the objects it copies.
//
// Build: g++ -std=c++17 prototype.cpp -o prototype

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
};

class Circle : public Shape {
public:
    Circle(double radius, std::string color)
        : radius_(radius), color_(std::move(color)) {}

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);  // copy constructor does the work
    }

    void setColor(std::string color) { color_ = std::move(color); }

    void draw() const override {
        std::cout << "Circle(radius=" << radius_ << ", color=" << color_ << ")\n";
    }

private:
    double radius_;
    std::string color_;
};

class Rectangle : public Shape {
public:
    Rectangle(double w, double h) : width_(w), height_(h) {}

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }

    void draw() const override {
        std::cout << "Rectangle(" << width_ << " x " << height_ << ")\n";
    }

private:
    double width_;
    double height_;
};

int main() {
    Circle original(5.0, "red");

    // Clone without knowing the concrete type.
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(original.clone());
    shapes.push_back(std::make_unique<Rectangle>(3.0, 4.0));
    shapes.push_back(shapes.back()->clone());  // clone via the base interface

    // Modifying the copy does not affect the original.
    auto copy = original.clone();
    static_cast<Circle*>(copy.get())->setColor("blue");

    std::cout << "original: ";
    original.draw();
    std::cout << "modified copy: ";
    copy->draw();

    std::cout << "all shapes:\n";
    for (const auto& s : shapes) s->draw();
    return 0;
}
