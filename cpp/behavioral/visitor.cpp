// Visitor — represent an operation on the elements of an object structure,
// letting you add new operations without modifying the element classes.
//
// Use when you have a stable hierarchy of element types and frequently
// need new operations across all of them (exporters, pretty-printers,
// metrics). The key mechanism is double dispatch via accept()/visit().
//
// Build: g++ -std=c++17 visitor.cpp -o visitor

#include <iostream>
#include <memory>
#include <vector>

class Circle;
class Square;

// Visitor interface: one visit overload per element type.
class ShapeVisitor {
public:
    virtual ~ShapeVisitor() = default;
    virtual void visit(const Circle& circle) = 0;
    virtual void visit(const Square& square) = 0;
};

// Element interface
class Shape {
public:
    virtual ~Shape() = default;
    virtual void accept(ShapeVisitor& visitor) const = 0;
};

class Circle : public Shape {
public:
    explicit Circle(double radius) : radius_(radius) {}
    double radius() const { return radius_; }
    void accept(ShapeVisitor& visitor) const override { visitor.visit(*this); }

private:
    double radius_;
};

class Square : public Shape {
public:
    explicit Square(double side) : side_(side) {}
    double side() const { return side_; }
    void accept(ShapeVisitor& visitor) const override { visitor.visit(*this); }

private:
    double side_;
};

// New operations are added as new visitors — no Shape class changes.
class AreaCalculator : public ShapeVisitor {
public:
    void visit(const Circle& circle) override { total_ += 3.14159 * circle.radius() * circle.radius(); }
    void visit(const Square& square) override { total_ += square.side() * square.side(); }
    double total() const { return total_; }

private:
    double total_ = 0;
};

class SvgExporter : public ShapeVisitor {
public:
    void visit(const Circle& circle) override {
        std::cout << "<circle r=\"" << circle.radius() << "\"/>\n";
    }
    void visit(const Square& square) override {
        std::cout << "<rect width=\"" << square.side() << "\" height=\"" << square.side() << "\"/>\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.0));
    shapes.push_back(std::make_unique<Square>(3.0));

    AreaCalculator area;
    SvgExporter svg;
    for (const auto& shape : shapes) {
        shape->accept(area);
        shape->accept(svg);
    }
    std::cout << "total area: " << area.total() << "\n";
    return 0;
}
