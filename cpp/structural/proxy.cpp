// ☕ Café Patterna — Chapter 12: The Secret Recipe Book
//
// STORY: The original recipe book lives in the office safe. Fetching it is
// slow and you'd rather not do it at all on quiet days. So the counter
// keeps a stand-in: it looks exactly like the recipe book, but only walks
// to the safe the FIRST time someone actually asks for a recipe.
//
// PATTERN: Proxy — provide a placeholder for another object to control
// access to it. Variants: virtual proxy (lazy loading, shown here),
// protection proxy, remote proxy, caching/logging proxy.
//
// Build: g++ -std=c++17 proxy.cpp -o proxy

#include <iostream>
#include <memory>
#include <string>

class RecipeBook {
public:
    virtual ~RecipeBook() = default;
    virtual void lookUp(const std::string& drink) = 0;
};

// Real subject: expensive to construct (a trip to the safe).
class SecretRecipeBook : public RecipeBook {
public:
    SecretRecipeBook() {
        std::cout << "walking to the safe, unlocking the recipe book (slow!)\n";
    }

    void lookUp(const std::string& drink) override {
        std::cout << "reading the secret recipe for " << drink << "\n";
    }
};

// Proxy: same interface, fetches the real book only on first use.
class RecipeBookProxy : public RecipeBook {
public:
    void lookUp(const std::string& drink) override {
        if (!real_) {
            real_ = std::make_unique<SecretRecipeBook>();  // lazy load
        }
        real_->lookUp(drink);
    }

private:
    std::unique_ptr<SecretRecipeBook> real_;
};

int main() {
    RecipeBookProxy book;
    std::cout << "proxy on the counter, safe still locked\n";

    book.lookUp("midnight mocha");  // triggers the trip to the safe
    book.lookUp("winter chai");     // reuses the already-fetched book
    return 0;
}
