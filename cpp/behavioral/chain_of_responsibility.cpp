// ☕ Café Patterna — Chapter 13: "I'd Like a Refund"
//
// STORY: An unhappy customer asks for money back. The barista can refund
// up to $5 on the spot. More than that? The shift manager. A catering
// disaster? Only the owner. The customer just complains once — the
// request climbs the chain until someone can handle it.
//
// PATTERN: Chain of Responsibility — pass a request along a chain of
// handlers; each one processes it or forwards it to the next.
//
// Build: g++ -std=c++17 chain_of_responsibility.cpp -o chain_of_responsibility

#include <iostream>
#include <string>

// Handler: knows its successor and the amount it is allowed to refund.
class RefundHandler {
public:
    RefundHandler(std::string title, double limit)
        : title_(std::move(title)), limit_(limit) {}

    void setNext(RefundHandler* next) { next_ = next; }

    void handle(const std::string& complaint, double amount) {
        if (amount <= limit_) {
            std::cout << title_ << " refunds $" << amount << " for \"" << complaint << "\"\n";
        } else if (next_) {
            std::cout << title_ << " can't refund $" << amount << ", escalating...\n";
            next_->handle(complaint, amount);
        } else {
            std::cout << "nobody can refund $" << amount << " for \"" << complaint << "\"\n";
        }
    }

private:
    std::string title_;
    double limit_;
    RefundHandler* next_ = nullptr;
};

int main() {
    RefundHandler barista("Barista", 5);
    RefundHandler shiftManager("Shift manager", 50);
    RefundHandler owner("Owner", 500);

    // Build the chain: barista -> shift manager -> owner.
    barista.setNext(&shiftManager);
    shiftManager.setNext(&owner);

    // Customers always complain to whoever is at the counter.
    barista.handle("latte was cold", 4.5);
    barista.handle("birthday cake never arrived", 35);
    barista.handle("catering for 50 was a disaster", 400);
    barista.handle("you ruined my wedding", 25000);
    return 0;
}
