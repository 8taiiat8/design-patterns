// 🤖 RoboWorks — Chapter 13: The Fault Report
//
// STORY: A robot jams on line B. The line technician can authorize
// repairs up to $100 on the spot. More than that? The floor engineer.
// A melted assembly cell? Only the chief engineer. The fault is reported
// once — it climbs the chain until someone can authorize the fix.
//
// PATTERN: Chain of Responsibility — pass a request along a chain of
// handlers; each one processes it or forwards it to the next.
//
// Build: g++ -std=c++17 chain_of_responsibility.cpp -o chain_of_responsibility

#include <iostream>
#include <string>

// Handler: knows its successor and the repair budget it may authorize.
class FaultHandler {
public:
    FaultHandler(std::string title, double budget)
        : title_(std::move(title)), budget_(budget) {}

    void setNext(FaultHandler* next) { next_ = next; }

    void handle(const std::string& fault, double cost) {
        if (cost <= budget_) {
            std::cout << title_ << " authorizes $" << cost << " repair: \"" << fault << "\"\n";
        } else if (next_) {
            std::cout << title_ << " can't authorize $" << cost << ", escalating...\n";
            next_->handle(fault, cost);
        } else {
            std::cout << "nobody can authorize $" << cost << " for \"" << fault << "\"\n";
        }
    }

private:
    std::string title_;
    double budget_;
    FaultHandler* next_ = nullptr;
};

int main() {
    FaultHandler technician("Line technician", 100);
    FaultHandler floorEngineer("Floor engineer", 1000);
    FaultHandler chiefEngineer("Chief engineer", 10000);

    // Build the chain: technician -> floor engineer -> chief engineer.
    technician.setNext(&floorEngineer);
    floorEngineer.setNext(&chiefEngineer);

    // Faults are always reported to whoever is on the line.
    technician.handle("gripper misaligned", 45);
    technician.handle("conveyor belt torn", 800);
    technician.handle("assembly cell melted", 7500);
    technician.handle("the whole west wing is on fire", 2000000);
    return 0;
}
