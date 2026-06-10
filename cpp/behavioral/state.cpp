// ☕ Café Patterna — Chapter 20: The Moody Espresso Machine
//
// STORY: The espresso machine has moods. When idle, it accepts an order;
// when loaded, pressing "order" again just beeps angrily, but pressing
// "brew" pours the shot and returns it to idle. Instead of one giant
// if/else on a status flag, each mood is its own class.
//
// PATTERN: State — let an object change its behavior when its internal
// state changes, by delegating behavior to a state object and swapping it
// on transitions.
//
// Build: g++ -std=c++17 state.cpp -o state

#include <iostream>
#include <memory>

class EspressoMachine;

// State interface: one method per event the machine can receive.
class MachineState {
public:
    virtual ~MachineState() = default;
    virtual void pressOrder(EspressoMachine& machine) = 0;
    virtual void pressBrew(EspressoMachine& machine) = 0;
};

class EspressoMachine {
public:
    EspressoMachine();

    void pressOrder();
    void pressBrew();
    void setState(std::unique_ptr<MachineState> state) { state_ = std::move(state); }

private:
    std::unique_ptr<MachineState> state_;
};

// Concrete states
class LoadedState : public MachineState {
public:
    void pressOrder(EspressoMachine&) override {
        std::cout << "machine beeps: already loaded with an order\n";
    }
    void pressBrew(EspressoMachine& machine) override;
};

class IdleState : public MachineState {
public:
    void pressOrder(EspressoMachine& machine) override {
        std::cout << "order accepted, grounds loaded\n";
        machine.setState(std::make_unique<LoadedState>());
    }
    void pressBrew(EspressoMachine&) override {
        std::cout << "nothing loaded, place an order first\n";
    }
};

void LoadedState::pressBrew(EspressoMachine& machine) {
    std::cout << "brewing... shot poured, back to idle\n";
    machine.setState(std::make_unique<IdleState>());
}

EspressoMachine::EspressoMachine() : state_(std::make_unique<IdleState>()) {}
void EspressoMachine::pressOrder() { state_->pressOrder(*this); }
void EspressoMachine::pressBrew() { state_->pressBrew(*this); }

int main() {
    EspressoMachine machine;
    machine.pressBrew();   // idle: refuses
    machine.pressOrder();  // idle -> loaded
    machine.pressOrder();  // loaded: beeps
    machine.pressBrew();   // loaded -> idle, pours the shot
    machine.pressBrew();   // idle again: refuses
    return 0;
}
