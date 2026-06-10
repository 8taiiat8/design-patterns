// Composite — compose objects into tree structures and let clients treat
// individual objects and compositions uniformly.
//
// Use when your domain is naturally a tree (file systems, GUI widgets,
// organization charts) and you want one interface for both leaves and
// groups.
//
// Build: g++ -std=c++17 composite.cpp -o composite

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Component: common interface for files and directories.
class FileSystemNode {
public:
    explicit FileSystemNode(std::string name) : name_(std::move(name)) {}
    virtual ~FileSystemNode() = default;

    virtual long size() const = 0;
    virtual void print(int indent) const = 0;

protected:
    std::string name_;
};

// Leaf
class File : public FileSystemNode {
public:
    File(std::string name, long size) : FileSystemNode(std::move(name)), size_(size) {}

    long size() const override { return size_; }

    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << "- " << name_ << " (" << size_ << " bytes)\n";
    }

private:
    long size_;
};

// Composite: holds children and forwards operations to them.
class Directory : public FileSystemNode {
public:
    explicit Directory(std::string name) : FileSystemNode(std::move(name)) {}

    void add(std::unique_ptr<FileSystemNode> child) {
        children_.push_back(std::move(child));
    }

    long size() const override {
        long total = 0;
        for (const auto& child : children_) total += child->size();
        return total;
    }

    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << "+ " << name_ << "/\n";
        for (const auto& child : children_) child->print(indent + 2);
    }

private:
    std::vector<std::unique_ptr<FileSystemNode>> children_;
};

int main() {
    auto root = std::make_unique<Directory>("project");
    root->add(std::make_unique<File>("README.md", 1200));

    auto src = std::make_unique<Directory>("src");
    src->add(std::make_unique<File>("main.cpp", 3400));
    src->add(std::make_unique<File>("util.cpp", 2100));
    root->add(std::move(src));

    root->print(0);
    std::cout << "total size: " << root->size() << " bytes\n";
    return 0;
}
