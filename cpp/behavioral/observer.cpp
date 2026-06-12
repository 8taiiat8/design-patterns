// 🤖 RoboWorks — Chapter 19: "Unit 42 Rolled Off the Line!"
//
// STORY: Managers used to phone the floor every hour asking "is batch 42
// done yet?" Now they subscribe: when a unit rolls off the line, the
// dashboard updates AND the engineer's pager buzzes — automatically,
// without the line knowing or caring who's listening.
//
// PATTERN: Observer — define a one-to-many dependency so that when the
// subject changes state, all registered observers are notified. The
// backbone of event systems and UI updates.
//
// Build: g++ -std=c++17 observer.cpp -o observer

#include <algorithm>
#include <iostream>
#include <vector>

// Observer interface
class LineObserver {
public:
    virtual ~LineObserver() = default;
    virtual void unitFinished(int serial) = 0;
};

// Subject: maintains a list of observers and notifies them on change.
class AssemblyLine {
public:
    void attach(LineObserver* observer) { observers_.push_back(observer); }

    void detach(LineObserver* observer) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), observer),
                         observers_.end());
    }

    void rollOff(int serial) {
        std::cout << "line: unit #" << serial << " rolled off\n";
        for (LineObserver* observer : observers_) observer->unitFinished(serial);
    }

private:
    std::vector<LineObserver*> observers_;
};

class Dashboard : public LineObserver {
public:
    void unitFinished(int serial) override {
        std::cout << "  dashboard updates: unit #" << serial << " complete\n";
    }
};

class EngineerPager : public LineObserver {
public:
    void unitFinished(int serial) override {
        std::cout << "  pager buzzes: unit #" << serial << " ready for QA!\n";
    }
};

int main() {
    AssemblyLine line;
    Dashboard dashboard;
    EngineerPager pager;

    line.attach(&dashboard);
    line.attach(&pager);

    line.rollOff(41);
    line.rollOff(42);

    line.detach(&pager);  // engineer went home
    line.rollOff(43);     // only the dashboard reacts now
    return 0;
}
