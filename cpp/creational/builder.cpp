// Builder — separate the construction of a complex object from its
// representation, so the same construction process can create different
// configurations step by step.
//
// Use when an object has many optional parts and a constructor with a long
// parameter list would be unreadable ("telescoping constructor" problem).
//
// Build: g++ -std=c++17 builder.cpp -o builder

#include <iostream>
#include <string>

class Computer {
public:
    std::string cpu;
    std::string ram;
    int usbPorts = 0;
    std::string display;

    void describe() const {
        std::cout << "Computer{cpu=" << cpu << ", ram=" << ram
                  << ", usbPorts=" << usbPorts << ", display=" << display << "}\n";
    }
};

// Fluent builder: each setter returns *this so calls can be chained.
class ComputerBuilder {
public:
    ComputerBuilder& cpu(std::string value) { computer_.cpu = std::move(value); return *this; }
    ComputerBuilder& ram(std::string value) { computer_.ram = std::move(value); return *this; }
    ComputerBuilder& usbPorts(int value) { computer_.usbPorts = value; return *this; }
    ComputerBuilder& display(std::string value) { computer_.display = std::move(value); return *this; }

    Computer build() { return computer_; }

private:
    Computer computer_;
};

// Optional "director": encapsulates well-known build recipes.
class Director {
public:
    static Computer gamingPc() {
        return ComputerBuilder{}
            .cpu("Ryzen 9")
            .ram("64GB DDR5")
            .usbPorts(6)
            .display("4K 144Hz")
            .build();
    }

    static Computer officePc() {
        return ComputerBuilder{}
            .cpu("Core i5")
            .ram("16GB DDR4")
            .usbPorts(4)
            .display("1080p")
            .build();
    }
};

int main() {
    // Build a custom machine step by step.
    Computer custom = ComputerBuilder{}.cpu("Apple M3").ram("32GB").usbPorts(2).display("Retina").build();
    custom.describe();

    // Or use the director's predefined recipes.
    Director::gamingPc().describe();
    Director::officePc().describe();
    return 0;
}
