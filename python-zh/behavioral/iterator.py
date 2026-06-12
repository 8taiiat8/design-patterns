"""机器人工厂 RoboWorks — 第 16 章：巡视传送带

故事：生产队列在传送带系统里。主管可以一项一项地巡视队列——
但谁也不许把手伸进传送带的机械结构，也不需要知道任务在里面
是怎么存放的。

模式：迭代器（Iterator）——提供遍历集合的方法，而不暴露其内部表示。
Python 把这一模式内置进了语言：迭代器协议就是 __iter__/__next__，
`for` 循环隐式使用它，生成器几乎不用写代码就能创建迭代器。

运行：python3 iterator.py
"""


class ProductionQueue:
    """生产队列；存储方式（传送带内部）保持私有。"""

    def __init__(self):
        self._jobs: list[str] = []

    def add(self, job: str) -> "ProductionQueue":
        self._jobs.append(job)
        return self

    def __iter__(self):
        """返回一个全新的迭代器（显式协议）。"""
        return QueueIterator(self._jobs)

    def rush_orders_first(self):
        """生成器：Python 风格的"另一种遍历顺序"。"""
        rush = [j for j in self._jobs if j.startswith("加急")]
        normal = [j for j in self._jobs if not j.startswith("加急")]
        yield from rush + normal


class QueueIterator:
    """实现 __next__ 的显式迭代器对象。"""

    def __init__(self, jobs):
        self._jobs = jobs
        self._pos = 0

    def __iter__(self):
        return self

    def __next__(self) -> str:
        if self._pos >= len(self._jobs):
            raise StopIteration
        job = self._jobs[self._pos]
        self._pos += 1
        return job


def main():
    morning_shift = (
        ProductionQueue()
        .add("焊接 7 号底盘")
        .add("加急：喷涂 12 号无人机外壳")
        .add("为第 3 批安装固件")
    )

    # `for` 在底层调用 __iter__/__next__。
    for job in morning_shift:
        print("执行中：", job)

    # 手动使用协议——这就是 `for` 内部做的事。
    it = iter(morning_shift)
    print("用 next() 取第一项：", next(it))

    print("加急优先：", list(morning_shift.rush_orders_first()))


if __name__ == "__main__":
    main()
