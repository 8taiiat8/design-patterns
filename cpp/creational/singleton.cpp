// 🤖 RoboWorks — Chapter 1: The Master Control Unit
//
// STORY: Your factory has exactly ONE Master Control Unit. Every assembly
// line reports to the same MCU — if there were two, they would issue
// conflicting orders and the factory would tear itself apart. The MCU
// boots the first time someone needs it, and everyone shares it.
//
// PATTERN: Singleton — ensure a class has only one instance and provide a
// global access point to it. Use when exactly one object must coordinate
// something factory-wide (configuration, logging, the control core).
//
// Key points in C++:
// - A function-local static (the "Meyers singleton") is initialized lazily
//   and is thread-safe since C++11.
// - Delete the copy/move operations so the instance cannot be duplicated.
//
// Build: g++ -std=c++17 singleton.cpp -o singleton

#include <iostream>
#include <string>

class MasterControlUnit {
public:
    // The single global access point.
    static MasterControlUnit& instance() {
        static MasterControlUnit mcu;  // created on first use, thread-safe
        return mcu;
    }

    MasterControlUnit(const MasterControlUnit&) = delete;
    MasterControlUnit& operator=(const MasterControlUnit&) = delete;

    void logTask(const std::string& task) {
        ++tasks_;
        std::cout << "[MCU task #" << tasks_ << "] " << task << "\n";
    }

private:
    MasterControlUnit() = default;  // private: nobody can build a second MCU
    int tasks_ = 0;
};

int main() {
    MasterControlUnit::instance().logTask("power up line A");
    MasterControlUnit::instance().logTask("calibrate welding lasers");

    // Both assembly lines report to the same control core.
    MasterControlUnit& lineA = MasterControlUnit::instance();
    MasterControlUnit& lineB = MasterControlUnit::instance();
    std::cout << "same MCU? " << std::boolalpha << (&lineA == &lineB) << "\n";
    return 0;
}
