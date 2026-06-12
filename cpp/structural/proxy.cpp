// 🤖 RoboWorks — Chapter 12: The Heavy Diagnostics Suite
//
// STORY: The full diagnostics suite takes ages to boot — gigabytes of
// sensor models and calibration tables. On most shifts nobody needs it.
// So the workbench keeps a stand-in: it looks exactly like the suite, but
// only boots the real thing the FIRST time an engineer runs a scan.
//
// PATTERN: Proxy — provide a placeholder for another object to control
// access to it. Variants: virtual proxy (lazy loading, shown here),
// protection proxy, remote proxy, caching/logging proxy.
//
// Build: g++ -std=c++17 proxy.cpp -o proxy

#include <iostream>
#include <memory>
#include <string>

class Diagnostics {
public:
    virtual ~Diagnostics() = default;
    virtual void scan(const std::string& robot) = 0;
};

// Real subject: expensive to construct (boots the full suite).
class FullDiagnosticsSuite : public Diagnostics {
public:
    FullDiagnosticsSuite() {
        std::cout << "booting the full diagnostics suite (slow!)\n";
    }

    void scan(const std::string& robot) override {
        std::cout << "running deep scan on " << robot << "\n";
    }
};

// Proxy: same interface, boots the real suite only on first use.
class DiagnosticsProxy : public Diagnostics {
public:
    void scan(const std::string& robot) override {
        if (!real_) {
            real_ = std::make_unique<FullDiagnosticsSuite>();  // lazy load
        }
        real_->scan(robot);
    }

private:
    std::unique_ptr<FullDiagnosticsSuite> real_;
};

int main() {
    DiagnosticsProxy workbench;
    std::cout << "proxy ready, suite not booted yet\n";

    workbench.scan("WelderBot #7");   // triggers the expensive boot
    workbench.scan("ScoutDrone #42"); // reuses the already-booted suite
    return 0;
}
