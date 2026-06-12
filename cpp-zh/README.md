# C++ 设计模式 — 机器人工厂 RoboWorks 故事版（中文）

用最浅显的故事呈现全部 23 种 GoF 设计模式。每个 `.cpp` 文件都是一个
带 `main()` 的完整可运行程序，文件头部用中文讲述本章故事、模式意图
和适用场景，代码注释与输出也全部为中文。

23 个示例共同组成一个连续的故事——**机器人工厂 RoboWorks**：
你白手起家，把一座机器人工厂做成商业帝国。

- **第一幕 · 创业车间** = 创建型（`creational/`，5 个模式）
- **第二幕 · 流水线扩张** = 结构型（`structural/`，7 个模式）
- **第三幕 · 车间日常** = 行为型（`behavioral/`，11 个模式）

完整故事、四周分步学习计划和掌握度测验请见
[中文学习指南](../document/roboworks-study-guide-zh.html)。
英文版代码在 [`cpp/`](../cpp/)。

## 构建与运行

需要 C++17 编译器。使用 make：

```bash
cd cpp-zh
make            # 全部构建到 bin/
make run        # 构建并运行全部示例
./bin/singleton # 运行单个示例
```

也可以直接编译任意文件：

```bash
g++ -std=c++17 creational/singleton.cpp -o singleton && ./singleton
```

## 模式索引

### 创建型 —— 对象如何被创建
| 章节 | 模式 | 文件 | 故事锚点 |
|---|---|---|---|
| 1 | 单例 Singleton | [creational/singleton.cpp](creational/singleton.cpp) | 唯一的中央控制器 |
| 2 | 工厂方法 Factory Method | [creational/factory_method.cpp](creational/factory_method.cpp) | 每条装配线造自己的机型 |
| 3 | 抽象工厂 Abstract Factory | [creational/abstract_factory.cpp](creational/abstract_factory.cpp) | 配套的产品系列 |
| 4 | 建造者 Builder | [creational/builder.cpp](creational/builder.cpp) | 定制机器人分步组装 |
| 5 | 原型 Prototype | [creational/prototype.cpp](creational/prototype.cpp) | 克隆成熟图纸 |

### 结构型 —— 对象如何组装拼接
| 章节 | 模式 | 文件 | 故事锚点 |
|---|---|---|---|
| 6 | 适配器 Adapter | [structural/adapter.cpp](structural/adapter.cpp) | 老焊接臂接新产线 |
| 7 | 桥接 Bridge | [structural/bridge.cpp](structural/bridge.cpp) | 任意机器人配任意控制器 |
| 8 | 组合 Composite | [structural/composite.cpp](structural/composite.cpp) | 组件套组件 |
| 9 | 装饰器 Decorator | [structural/decorator.cpp](structural/decorator.cpp) | 升级模块层层包裹 |
| 10 | 外观 Facade | [structural/facade.cpp](structural/facade.cpp) | 那个绿色大按钮 |
| 11 | 享元 Flyweight | [structural/flyweight.cpp](structural/flyweight.cpp) | 千架无人机共享三张图纸 |
| 12 | 代理 Proxy | [structural/proxy.cpp](structural/proxy.cpp) | 诊断套件的替身 |

### 行为型 —— 对象如何互相沟通
| 章节 | 模式 | 文件 | 故事锚点 |
|---|---|---|---|
| 13 | 责任链 Chain of Responsibility | [behavioral/chain_of_responsibility.cpp](behavioral/chain_of_responsibility.cpp) | 故障逐级上报 |
| 14 | 命令 Command | [behavioral/command.cpp](behavioral/command.cpp) | 可撤回的工单 |
| 15 | 解释器 Interpreter | [behavioral/interpreter.cpp](behavioral/interpreter.cpp) | 调度器读机器人脚本 |
| 16 | 迭代器 Iterator | [behavioral/iterator.cpp](behavioral/iterator.cpp) | 巡视传送带 |
| 17 | 中介者 Mediator | [behavioral/mediator.cpp](behavioral/mediator.cpp) | 调度塔 |
| 18 | 备忘录 Memento | [behavioral/memento.cpp](behavioral/memento.cpp) | 固件回滚 |
| 19 | 观察者 Observer | [behavioral/observer.cpp](behavioral/observer.cpp) | "42 号下线了！" |
| 20 | 状态 State | [behavioral/state.cpp](behavioral/state.cpp) | 机器人的工作模式 |
| 21 | 策略 Strategy | [behavioral/strategy.cpp](behavioral/strategy.cpp) | 电源模式切换 |
| 22 | 模板方法 Template Method | [behavioral/template_method.cpp](behavioral/template_method.cpp) | 开机流程 |
| 23 | 访问者 Visitor | [behavioral/visitor.cpp](behavioral/visitor.cpp) | 巡检员走访车间 |

## 推荐学习顺序

先学实际代码中最常遇到的模式：
**策略 → 观察者 → 工厂方法 → 装饰器 → 单例 → 适配器 → 模板方法 → 命令**，
再探索其余模式。
