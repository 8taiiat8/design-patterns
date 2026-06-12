"""机器人工厂 RoboWorks — 第 9 章：升级模块

故事：装甲板、太阳能充电器、AI 语音模块……客户把升级件以各种组合
拧到基础机器人上。你不可能为每种组合写一个"装甲太阳能会说话机器人"
类——正确做法是每个升级模块"包裹"下面的机器人，
加上自己的配置说明和价格。

模式：装饰器（Decorator）——通过用共享同一接口的对象层层包装，
在运行时为对象动态附加职责。注意：这是 GoF 的"对象装饰器"；
Python 的 `@decorator` 语法是同一思想在函数上的应用——下面两种都演示。

运行：python3 decorator.py
"""

import functools
from abc import ABC, abstractmethod


# --- GoF 对象装饰器 --------------------------------------------------------
class Robot(ABC):
    @abstractmethod
    def specs(self) -> str: ...

    @abstractmethod
    def cost(self) -> float: ...


class BasicBot(Robot):
    def specs(self) -> str:
        return "基础机器人"

    def cost(self) -> float:
        return 2000.0


class UpgradeDecorator(Robot):
    """装饰器基类：包裹一个 Robot，默认原样转发。"""

    def __init__(self, inner: Robot):
        self._inner = inner

    def specs(self) -> str:
        return self._inner.specs()

    def cost(self) -> float:
        return self._inner.cost()


class ArmorPlating(UpgradeDecorator):
    def specs(self) -> str:
        return super().specs() + " + 装甲板"

    def cost(self) -> float:
        return super().cost() + 500.0


class SolarCharger(UpgradeDecorator):
    def specs(self) -> str:
        return super().specs() + " + 太阳能充电器"

    def cost(self) -> float:
        return super().cost() + 200.0


class AiVoice(UpgradeDecorator):
    def specs(self) -> str:
        return super().specs() + " + AI 语音"

    def cost(self) -> float:
        return super().cost() + 700.0


# --- Python 风格的函数装饰器：同一模式，作用于可调用对象 -------------------
def logged_to_mcu(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        print(f"MCU 日志：{func.__name__}{args}")
        return func(*args, **kwargs)

    return wrapper


@logged_to_mcu
def deploy(model):
    return f"{model} 已部署到车间"


def main():
    order = AiVoice(SolarCharger(ArmorPlating(BasicBot())))  # 任意叠加升级
    print(f"{order.specs()}，售价 ${order.cost():.2f}")

    plain = BasicBot()
    print(f"{plain.specs()}，售价 ${plain.cost():.2f}")

    print(deploy("焊接机器人 Mk2"))


if __name__ == "__main__":
    main()
