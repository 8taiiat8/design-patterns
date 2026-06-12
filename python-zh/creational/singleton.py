"""机器人工厂 RoboWorks — 第 1 章：唯一的中央控制器

故事：你的工厂只有一台中央控制器（MCU）。所有装配线都向同一台 MCU
汇报——如果有两台，它们会发出互相矛盾的指令，工厂就乱套了。
MCU 在第一次被使用时启动，之后所有人共享同一台。

模式：单例（Singleton）——确保一个类只有一个实例，并提供全局访问点。
注意：在 Python 中，一个普通模块往往就是最简单的单例——模块级状态
只创建一次并被共享。本文件演示两种最常见的基于类的实现方式。

运行：python3 singleton.py
"""


class SingletonMeta(type):
    """元类方式：拦截实例化过程并缓存唯一实例。"""

    _instances = {}

    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = super().__call__(*args, **kwargs)
        return cls._instances[cls]


class MasterControlUnit(metaclass=SingletonMeta):
    def __init__(self):
        self.tasks = 0

    def log_task(self, task):
        self.tasks += 1
        print(f"[MCU 任务 #{self.tasks}] {task}")


class FactoryConfig:
    """__new__ 方式：类自己缓存唯一实例。"""

    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.settings = {"夜班模式": False}
        return cls._instance


def main():
    MasterControlUnit().log_task("启动 A 号装配线")
    MasterControlUnit().log_task("校准焊接激光")
    print("同一台 MCU？", MasterControlUnit() is MasterControlUnit())

    line_a = FactoryConfig()
    line_b = FactoryConfig()
    line_a.settings["夜班模式"] = True
    print("同一份配置？", line_a is line_b, "| B 线看到：", line_b.settings)


if __name__ == "__main__":
    main()
