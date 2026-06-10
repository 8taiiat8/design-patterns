# Design Patterns in C++ — the Café Patterna story

Self-contained, runnable examples of all 23 GoF design patterns. Each
`.cpp` file is a complete program with a `main()` that demonstrates one
pattern, plus a header comment explaining the intent and when to use it.

All 23 examples are chapters of one continuous story — **Café Patterna**,
a coffee shop you grow into an empire. Creational patterns are Act 1
(Opening Day), structural are Act 2 (The Expansion), behavioral are Act 3
(The Daily Grind). Read the full storyline, study plan, and mastery quiz
in the [study guide](../document/cafe-patterna-study-guide.html).

## Build & run

Requires a C++17 compiler. With make:

```bash
cd cpp
make            # build everything into bin/
make run        # build and run every example
./bin/singleton # run a single example
```

Or compile any file directly:

```bash
g++ -std=c++17 creational/singleton.cpp -o singleton && ./singleton
```

## Patterns

### Creational — how objects get created
| Pattern | File | One-liner |
|---|---|---|
| Singleton | [creational/singleton.cpp](creational/singleton.cpp) | One instance, global access point |
| Factory Method | [creational/factory_method.cpp](creational/factory_method.cpp) | Subclasses decide which class to instantiate |
| Abstract Factory | [creational/abstract_factory.cpp](creational/abstract_factory.cpp) | Create families of related objects |
| Builder | [creational/builder.cpp](creational/builder.cpp) | Construct complex objects step by step |
| Prototype | [creational/prototype.cpp](creational/prototype.cpp) | Create objects by cloning an existing one |

### Structural — how objects are composed
| Pattern | File | One-liner |
|---|---|---|
| Adapter | [structural/adapter.cpp](structural/adapter.cpp) | Make an incompatible interface fit |
| Bridge | [structural/bridge.cpp](structural/bridge.cpp) | Split abstraction from implementation |
| Composite | [structural/composite.cpp](structural/composite.cpp) | Treat trees and leaves uniformly |
| Decorator | [structural/decorator.cpp](structural/decorator.cpp) | Add behavior by wrapping |
| Facade | [structural/facade.cpp](structural/facade.cpp) | One simple entry point to a subsystem |
| Flyweight | [structural/flyweight.cpp](structural/flyweight.cpp) | Share heavy state between many objects |
| Proxy | [structural/proxy.cpp](structural/proxy.cpp) | A stand-in that controls access |

### Behavioral — how objects communicate
| Pattern | File | One-liner |
|---|---|---|
| Chain of Responsibility | [behavioral/chain_of_responsibility.cpp](behavioral/chain_of_responsibility.cpp) | Pass a request along handlers |
| Command | [behavioral/command.cpp](behavioral/command.cpp) | Requests as objects, with undo |
| Interpreter | [behavioral/interpreter.cpp](behavioral/interpreter.cpp) | Evaluate sentences of a small language |
| Iterator | [behavioral/iterator.cpp](behavioral/iterator.cpp) | Traverse without exposing internals |
| Mediator | [behavioral/mediator.cpp](behavioral/mediator.cpp) | Centralize many-to-many communication |
| Memento | [behavioral/memento.cpp](behavioral/memento.cpp) | Snapshot & restore state |
| Observer | [behavioral/observer.cpp](behavioral/observer.cpp) | Notify dependents on state change |
| State | [behavioral/state.cpp](behavioral/state.cpp) | Behavior changes with internal state |
| Strategy | [behavioral/strategy.cpp](behavioral/strategy.cpp) | Swap algorithms at run time |
| Template Method | [behavioral/template_method.cpp](behavioral/template_method.cpp) | Fixed skeleton, overridable steps |
| Visitor | [behavioral/visitor.cpp](behavioral/visitor.cpp) | New operations without touching classes |

## Suggested learning order

Start with the patterns you'll meet most often in real code:
**Strategy → Observer → Factory Method → Decorator → Singleton → Adapter →
Template Method → Command** — then explore the rest.
