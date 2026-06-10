// Bridge — decouple an abstraction from its implementation so the two can
// vary independently.
//
// Use when a class hierarchy would otherwise explode combinatorially
// (e.g. Shape x RenderApi: VectorCircle, RasterCircle, VectorSquare, ...).
// Instead, the abstraction (Shape) holds a reference to the
// implementation (Renderer) and the two hierarchies grow separately.
//
// Build: g++ -std=c++17 bridge.cpp -o bridge

#include <iostream>
#include <memory>

// Implementation hierarchy
class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void renderCircle(double radius) const = 0;
};

class VectorRenderer : public Renderer {
public:
    void renderCircle(double radius) const override {
        std::cout << "drawing a circle of radius " << radius << " with vectors\n";
    }
};

class RasterRenderer : public Renderer {
public:
    void renderCircle(double radius) const override {
        std::cout << "drawing pixels for a circle of radius " << radius << "\n";
    }
};

// Abstraction hierarchy: holds the "bridge" to the implementation.
class Shape {
public:
    explicit Shape(const Renderer& renderer) : renderer_(renderer) {}
    virtual ~Shape() = default;
    virtual void draw() const = 0;

protected:
    const Renderer& renderer_;
};

class Circle : public Shape {
public:
    Circle(const Renderer& renderer, double radius)
        : Shape(renderer), radius_(radius) {}

    void draw() const override { renderer_.renderCircle(radius_); }

    void resize(double factor) { radius_ *= factor; }

private:
    double radius_;
};

int main() {
    VectorRenderer vec;
    RasterRenderer raster;

    // Any shape can be combined with any renderer at run time.
    Circle a(vec, 5.0);
    Circle b(raster, 5.0);
    a.draw();
    b.draw();

    a.resize(2.0);
    a.draw();
    return 0;
}
