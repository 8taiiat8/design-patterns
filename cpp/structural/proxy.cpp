// Proxy — provide a placeholder for another object to control access to it.
//
// Common variants: virtual proxy (lazy, expensive-to-create objects),
// protection proxy (access control), remote proxy, caching/logging proxy.
// This example shows a virtual proxy that delays loading a large image
// until it is actually displayed.
//
// Build: g++ -std=c++17 proxy.cpp -o proxy

#include <iostream>
#include <memory>
#include <string>

class Image {
public:
    virtual ~Image() = default;
    virtual void display() = 0;
};

// Real subject: expensive to construct (pretend it loads from disk).
class RealImage : public Image {
public:
    explicit RealImage(std::string filename) : filename_(std::move(filename)) {
        std::cout << "loading " << filename_ << " from disk (slow!)\n";
    }

    void display() override { std::cout << "displaying " << filename_ << "\n"; }

private:
    std::string filename_;
};

// Proxy: same interface, creates the real subject only on first use.
class ImageProxy : public Image {
public:
    explicit ImageProxy(std::string filename) : filename_(std::move(filename)) {}

    void display() override {
        if (!real_) {
            real_ = std::make_unique<RealImage>(filename_);  // lazy load
        }
        real_->display();
    }

private:
    std::string filename_;
    std::unique_ptr<RealImage> real_;
};

int main() {
    ImageProxy photo("vacation.png");
    std::cout << "proxy created, nothing loaded yet\n";

    photo.display();  // triggers the expensive load
    photo.display();  // reuses the already-loaded image
    return 0;
}
