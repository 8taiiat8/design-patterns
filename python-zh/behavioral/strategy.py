"""机器人工厂 RoboWorks — 第 21 章：电源模式

故事：同一台机器人在不同时刻耗电不同：白班高峰满功率，节能模式
半功率，夜间模式九折。机器人不关心当前是哪条规则——它只问当前的
电源策略该用多少电；夜班开始时，你把策略一换就行。

模式：策略（Strategy）——定义一族可互换的算法，在运行时通过统一
接口切换。在 Python 中，普通函数本身就能充当轻量级策略——
两种风格都在下面演示。

运行：python3 strategy.py
"""

from abc import ABC, abstractmethod


# 经典 OO 风格：策略接口 + 具体策略。
class PowerStrategy(ABC):
    @abstractmethod
    def draw(self, base_watts: float) -> float: ...


class PerformanceMode(PowerStrategy):
    def draw(self, base_watts: float) -> float:
        return base_watts


class EcoMode(PowerStrategy):
    def draw(self, base_watts: float) -> float:
        return base_watts * 0.5


class NightMode(PowerStrategy):
    def draw(self, base_watts: float) -> float:
        return base_watts * 0.9


class Robot:
    """上下文：配置了某个策略，但不知道具体是哪一个。"""

    def __init__(self, strategy: PowerStrategy):
        self.strategy = strategy

    def run_task(self, base_watts: float) -> None:
        print(f"任务基准 {base_watts} 瓦 -> 实际消耗 {self.strategy.draw(base_watts)} 瓦")


def main():
    robot = Robot(PerformanceMode())
    robot.run_task(400.0)

    robot.strategy = EcoMode()  # 电费账单到了
    robot.run_task(400.0)

    robot.strategy = NightMode()
    robot.run_task(400.0)

    # Python 风格的替代方案：任何可调用对象都能当策略。
    modes = {
        "待机": lambda base: base * 0.1,
        "超频": lambda base: base * 1.5,
    }
    for name, draw in modes.items():
        print(f"{name}：消耗 {draw(400.0)} 瓦")


if __name__ == "__main__":
    main()
