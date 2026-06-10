// Chain of Responsibility — pass a request along a chain of handlers; each
// handler decides to process the request or forward it to the next one.
//
// Use when more than one object may handle a request and the handler isn't
// known in advance (approval workflows, middleware, event bubbling).
//
// Build: g++ -std=c++17 chain_of_responsibility.cpp -o chain_of_responsibility

#include <iostream>
#include <memory>
#include <string>

// Handler: knows its successor and the amount it is allowed to approve.
class Approver {
public:
    explicit Approver(std::string title, double limit)
        : title_(std::move(title)), limit_(limit) {}
    virtual ~Approver() = default;

    void setNext(Approver* next) { next_ = next; }

    void approve(const std::string& item, double amount) {
        if (amount <= limit_) {
            std::cout << title_ << " approved \"" << item << "\" ($" << amount << ")\n";
        } else if (next_) {
            std::cout << title_ << " can't approve $" << amount << ", escalating...\n";
            next_->approve(item, amount);
        } else {
            std::cout << "nobody can approve \"" << item << "\" ($" << amount << ")\n";
        }
    }

private:
    std::string title_;
    double limit_;
    Approver* next_ = nullptr;
};

int main() {
    Approver teamLead("Team lead", 1000);
    Approver manager("Manager", 10000);
    Approver cfo("CFO", 100000);

    // Build the chain: team lead -> manager -> CFO.
    teamLead.setNext(&manager);
    manager.setNext(&cfo);

    // Clients always talk to the head of the chain.
    teamLead.approve("new keyboards", 400);
    teamLead.approve("team offsite", 8000);
    teamLead.approve("office renovation", 75000);
    teamLead.approve("private jet", 5000000);
    return 0;
}
