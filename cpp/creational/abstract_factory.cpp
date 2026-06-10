// Abstract Factory — provide an interface for creating families of related
// objects without specifying their concrete classes.
//
// Use when your code must work with various families of related products
// (e.g. UI widgets for different operating systems) and you want to
// guarantee that products from one family are used together.
//
// Build: g++ -std=c++17 abstract_factory.cpp -o abstract_factory

#include <iostream>
#include <memory>
#include <string>

// Abstract products
class Button {
public:
    virtual ~Button() = default;
    virtual void render() const = 0;
};

class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void render() const = 0;
};

// Concrete products: the "Windows" family
class WindowsButton : public Button {
public:
    void render() const override { std::cout << "render a Windows button\n"; }
};

class WindowsCheckbox : public Checkbox {
public:
    void render() const override { std::cout << "render a Windows checkbox\n"; }
};

// Concrete products: the "Mac" family
class MacButton : public Button {
public:
    void render() const override { std::cout << "render a Mac button\n"; }
};

class MacCheckbox : public Checkbox {
public:
    void render() const override { std::cout << "render a Mac checkbox\n"; }
};

// Abstract factory: one creation method per product type
class GuiFactory {
public:
    virtual ~GuiFactory() = default;
    virtual std::unique_ptr<Button> createButton() const = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() const = 0;
};

class WindowsFactory : public GuiFactory {
public:
    std::unique_ptr<Button> createButton() const override { return std::make_unique<WindowsButton>(); }
    std::unique_ptr<Checkbox> createCheckbox() const override { return std::make_unique<WindowsCheckbox>(); }
};

class MacFactory : public GuiFactory {
public:
    std::unique_ptr<Button> createButton() const override { return std::make_unique<MacButton>(); }
    std::unique_ptr<Checkbox> createCheckbox() const override { return std::make_unique<MacCheckbox>(); }
};

// Client code only depends on the abstract interfaces.
void renderDialog(const GuiFactory& factory) {
    factory.createButton()->render();
    factory.createCheckbox()->render();
}

int main() {
    std::cout << "-- Windows family --\n";
    renderDialog(WindowsFactory{});
    std::cout << "-- Mac family --\n";
    renderDialog(MacFactory{});
    return 0;
}
