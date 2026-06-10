// State — let an object change its behavior when its internal state
// changes, by delegating behavior to a state object.
//
// Use when an object has large conditionals on its current state
// (switch(status) everywhere); each state becomes a class and transitions
// swap the current state object.
//
// Build: g++ -std=c++17 state.cpp -o state

#include <iostream>
#include <memory>

class VendingMachine;

// State interface: one method per event the machine can receive.
class State {
public:
    virtual ~State() = default;
    virtual void insertCoin(VendingMachine& machine) = 0;
    virtual void dispense(VendingMachine& machine) = 0;
};

class VendingMachine {
public:
    VendingMachine();

    void insertCoin();
    void dispense();
    void setState(std::unique_ptr<State> state) { state_ = std::move(state); }

private:
    std::unique_ptr<State> state_;
};

// Concrete states
class HasCoinState : public State {
public:
    void insertCoin(VendingMachine&) override {
        std::cout << "coin already inserted, returning it\n";
    }
    void dispense(VendingMachine& machine) override;
};

class IdleState : public State {
public:
    void insertCoin(VendingMachine& machine) override {
        std::cout << "coin accepted\n";
        machine.setState(std::make_unique<HasCoinState>());
    }
    void dispense(VendingMachine&) override {
        std::cout << "insert a coin first\n";
    }
};

void HasCoinState::dispense(VendingMachine& machine) {
    std::cout << "dispensing snack, back to idle\n";
    machine.setState(std::make_unique<IdleState>());
}

VendingMachine::VendingMachine() : state_(std::make_unique<IdleState>()) {}
void VendingMachine::insertCoin() { state_->insertCoin(*this); }
void VendingMachine::dispense() { state_->dispense(*this); }

int main() {
    VendingMachine machine;
    machine.dispense();    // idle: refuses
    machine.insertCoin();  // idle -> has coin
    machine.insertCoin();  // has coin: rejects second coin
    machine.dispense();    // has coin -> idle, dispenses
    machine.dispense();    // idle again: refuses
    return 0;
}
