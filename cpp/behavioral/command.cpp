// Command — encapsulate a request as an object, letting you parameterize
// clients with operations, queue them, and support undo.
//
// Use for undo/redo stacks, task queues, macro recording, and decoupling
// the object that invokes an operation from the one that performs it.
//
// Build: g++ -std=c++17 command.cpp -o command

#include <iostream>
#include <memory>
#include <vector>

// Receiver: the object that actually does the work.
class Light {
public:
    void on() { std::cout << "light is ON\n"; }
    void off() { std::cout << "light is OFF\n"; }
};

// Command interface with undo support.
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class LightOnCommand : public Command {
public:
    explicit LightOnCommand(Light& light) : light_(light) {}
    void execute() override { light_.on(); }
    void undo() override { light_.off(); }

private:
    Light& light_;
};

class LightOffCommand : public Command {
public:
    explicit LightOffCommand(Light& light) : light_(light) {}
    void execute() override { light_.off(); }
    void undo() override { light_.on(); }

private:
    Light& light_;
};

// Invoker: triggers commands and keeps a history for undo.
class RemoteControl {
public:
    void press(std::unique_ptr<Command> command) {
        command->execute();
        history_.push_back(std::move(command));
    }

    void undoLast() {
        if (history_.empty()) return;
        history_.back()->undo();
        history_.pop_back();
    }

private:
    std::vector<std::unique_ptr<Command>> history_;
};

int main() {
    Light livingRoom;
    RemoteControl remote;

    remote.press(std::make_unique<LightOnCommand>(livingRoom));
    remote.press(std::make_unique<LightOffCommand>(livingRoom));

    std::cout << "-- undo twice --\n";
    remote.undoLast();
    remote.undoLast();
    return 0;
}
