// 🤖 机器人工厂 RoboWorks — 第 16 章：巡视传送带
//
// 故事：生产队列在传送带系统里。主管可以一项一项地巡视队列——
// 但谁也不许把手伸进传送带的机械结构，也不需要知道任务在里面
// 是怎么存放的。
//
// 模式：迭代器（Iterator）——提供遍历集合的方法，而不暴露其内部表示。
// 在现代 C++ 中这一模式已内置于语言：任何提供 begin()/end() 的类型
// 都能用于范围 for 循环和 STL 算法。
//
// 编译：g++ -std=c++17 iterator.cpp -o iterator

#include <iostream>
#include <string>
#include <vector>

// 生产队列；存储方式（传送带内部）保持私有。
class ProductionQueue {
public:
    void add(std::string job) { jobs_.push_back(std::move(job)); }

    // 队列的迭代器。客户端永远看不到里面的 vector。
    class Iterator {
    public:
        Iterator(const ProductionQueue& queue, size_t pos) : queue_(queue), pos_(pos) {}

        const std::string& operator*() const { return queue_.jobs_[pos_]; }
        Iterator& operator++() { ++pos_; return *this; }
        bool operator!=(const Iterator& other) const { return pos_ != other.pos_; }

    private:
        const ProductionQueue& queue_;
        size_t pos_;
    };

    Iterator begin() const { return Iterator(*this, 0); }
    Iterator end() const { return Iterator(*this, jobs_.size()); }

private:
    std::vector<std::string> jobs_;
};

int main() {
    ProductionQueue morningShift;
    morningShift.add("焊接 7 号底盘");
    morningShift.add("喷涂 12 号无人机外壳");
    morningShift.add("为第 3 批安装固件");

    // 显式使用迭代器……
    for (auto it = morningShift.begin(); it != morningShift.end(); ++it) {
        std::cout << "执行中：" << *it << "\n";
    }

    // ……以及惯用的范围 for——用的是同一个迭代器。
    for (const auto& job : morningShift) {
        std::cout << "排队中：" << job << "\n";
    }
    return 0;
}
