// Factory Method — define an interface for creating an object, but let
// subclasses decide which concrete class to instantiate.
//
// Use when a class can't anticipate the type of objects it must create,
// or when you want to localize the knowledge of which class gets created.
//
// Build: g++ -std=c++17 factory_method.cpp -o factory_method

#include <iostream>
#include <memory>
#include <string>

// Product interface
class Transport {
public:
    virtual ~Transport() = default;
    virtual std::string deliver() const = 0;
};

class Truck : public Transport {
public:
    std::string deliver() const override { return "deliver by land in a truck"; }
};

class Ship : public Transport {
public:
    std::string deliver() const override { return "deliver by sea in a ship"; }
};

// Creator: contains business logic that relies on the product interface;
// the factory method defers the choice of concrete product to subclasses.
class Logistics {
public:
    virtual ~Logistics() = default;

    void planDelivery() const {
        auto transport = createTransport();  // the factory method
        std::cout << "Planning: " << transport->deliver() << "\n";
    }

protected:
    virtual std::unique_ptr<Transport> createTransport() const = 0;
};

class RoadLogistics : public Logistics {
protected:
    std::unique_ptr<Transport> createTransport() const override {
        return std::make_unique<Truck>();
    }
};

class SeaLogistics : public Logistics {
protected:
    std::unique_ptr<Transport> createTransport() const override {
        return std::make_unique<Ship>();
    }
};

int main() {
    RoadLogistics road;
    SeaLogistics sea;
    road.planDelivery();
    sea.planDelivery();
    return 0;
}
