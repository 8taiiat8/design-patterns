// ☕ Café Patterna — Chapter 17: The Counter Intercom
//
// STORY: With cashier, barista and baker all working at once, the shop
// turned into a shouting match — everyone yelling at everyone. So you
// installed an intercom: staff speak INTO the intercom, and it relays the
// message to everyone else. Nobody needs to know who else is on shift.
//
// PATTERN: Mediator — define an object that encapsulates how a set of
// objects interact, so they don't reference each other directly; turns
// many-to-many links into one-to-many.
//
// Build: g++ -std=c++17 mediator.cpp -o mediator

#include <iostream>
#include <string>
#include <vector>

class StaffMember;

// Mediator interface
class Intercom {
public:
    virtual ~Intercom() = default;
    virtual void relay(const std::string& from, const std::string& message) = 0;
    virtual void signIn(StaffMember* member) = 0;
};

// Colleague: only knows the intercom, not the other staff.
class StaffMember {
public:
    StaffMember(std::string name, Intercom& intercom)
        : name_(std::move(name)), intercom_(intercom) {
        intercom_.signIn(this);
    }

    const std::string& name() const { return name_; }

    void announce(const std::string& message) {
        std::cout << name_ << " announces: " << message << "\n";
        intercom_.relay(name_, message);
    }

    void hear(const std::string& from, const std::string& message) {
        std::cout << "  " << name_ << " hears " << from << ": " << message << "\n";
    }

private:
    std::string name_;
    Intercom& intercom_;
};

// Concrete mediator: relays announcements to everyone else on shift.
class CounterIntercom : public Intercom {
public:
    void signIn(StaffMember* member) override { staff_.push_back(member); }

    void relay(const std::string& from, const std::string& message) override {
        for (StaffMember* member : staff_) {
            if (member->name() != from) member->hear(from, message);
        }
    }

private:
    std::vector<StaffMember*> staff_;
};

int main() {
    CounterIntercom intercom;
    StaffMember cleo("Cleo (cashier)", intercom);
    StaffMember ben("Ben (barista)", intercom);
    StaffMember mara("Mara (baker)", intercom);

    cleo.announce("two lattes and a croissant for table 4!");
    ben.announce("milk steamer is free again");
    return 0;
}
