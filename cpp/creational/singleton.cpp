// Singleton — ensure a class has only one instance and provide a global
// access point to it.
//
// Use when exactly one object is needed to coordinate actions across a
// system (configuration, logging, connection pools).
//
// Key points in C++:
// - A function-local static (the "Meyers singleton") is initialized lazily
//   and is thread-safe since C++11.
// - Delete the copy/move operations so the instance cannot be duplicated.
//
// Build: g++ -std=c++17 singleton.cpp -o singleton

#include <iostream>
#include <string>

class Logger {
public:
    // The single global access point.
    static Logger& instance() {
        static Logger logger;  // created on first use, thread-safe
        return logger;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(const std::string& message) {
        ++count_;
        std::cout << "[log #" << count_ << "] " << message << "\n";
    }

private:
    Logger() = default;  // private: clients cannot construct their own
    int count_ = 0;
};

int main() {
    Logger::instance().log("application started");
    Logger::instance().log("doing some work");

    // Both references point to the same object.
    Logger& a = Logger::instance();
    Logger& b = Logger::instance();
    std::cout << "same instance? " << std::boolalpha << (&a == &b) << "\n";
    return 0;
}
