// 🤖 RoboWorks — Chapter 14: The Job Queue
//
// STORY: The control panel doesn't shout at the factory floor — every job
// becomes a JOB CARD pushed onto the queue. The floor executes cards in
// its own time, and when a client cancels, the last card is simply
// recalled (undo).
//
// PATTERN: Command — encapsulate a request as an object, letting you
// queue requests, log them, and support undo. Decouples the object that
// invokes an operation (control panel) from the one performing it (floor).
//
// Build: g++ -std=c++17 command.cpp -o command

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Receiver: the object that actually does the work.
class FactoryFloor {
public:
    void start(const std::string& job) { std::cout << "floor starts: " << job << "\n"; }
    void recall(const std::string& job) { std::cout << "floor recalls: " << job << "\n"; }
};

// Command interface with undo support.
class JobCard {
public:
    virtual ~JobCard() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class WeldJob : public JobCard {
public:
    WeldJob(FactoryFloor& floor, std::string seam)
        : floor_(floor), seam_(std::move(seam)) {}
    void execute() override { floor_.start("weld " + seam_); }
    void undo() override { floor_.recall("weld " + seam_); }

private:
    FactoryFloor& floor_;
    std::string seam_;
};

class TransportJob : public JobCard {
public:
    TransportJob(FactoryFloor& floor, std::string cargo)
        : floor_(floor), cargo_(std::move(cargo)) {}
    void execute() override { floor_.start("transport " + cargo_); }
    void undo() override { floor_.recall("transport " + cargo_); }

private:
    FactoryFloor& floor_;
    std::string cargo_;
};

// Invoker: issues job cards and keeps a history for cancellation.
class ControlPanel {
public:
    void issue(std::unique_ptr<JobCard> job) {
        job->execute();
        history_.push_back(std::move(job));
    }

    void cancelLast() {
        if (history_.empty()) return;
        history_.back()->undo();
        history_.pop_back();
    }

private:
    std::vector<std::unique_ptr<JobCard>> history_;
};

int main() {
    FactoryFloor floor;
    ControlPanel panel;

    panel.issue(std::make_unique<WeldJob>(floor, "chassis seam #7"));
    panel.issue(std::make_unique<TransportJob>(floor, "crate of servos"));

    std::cout << "-- client cancels the order --\n";
    panel.cancelLast();
    return 0;
}
