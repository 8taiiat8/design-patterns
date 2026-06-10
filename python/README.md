# Design Patterns in Python

Self-contained, runnable examples of all 23 GoF design patterns. Each
`.py` file is a complete script with a `main()` that demonstrates one
pattern, plus a docstring explaining the intent and when to use it.

Where Python offers a more idiomatic alternative to the classic GoF
formulation, the example shows both — e.g. functions as strategies,
`@decorator` syntax, generators as iterators, `copy.deepcopy` for
prototypes, and modules as singletons.

## Run

Requires Python 3.10+. No third-party dependencies.

```bash
cd python
python3 creational/singleton.py     # run any single example

# run everything:
for f in creational/*.py structural/*.py behavioral/*.py; do
  echo "===== $f ====="; python3 "$f"; echo
done
```

## Patterns

### Creational — how objects get created
| Pattern | File | One-liner |
|---|---|---|
| Singleton | [creational/singleton.py](creational/singleton.py) | One instance, global access point |
| Factory Method | [creational/factory_method.py](creational/factory_method.py) | Subclasses decide which class to instantiate |
| Abstract Factory | [creational/abstract_factory.py](creational/abstract_factory.py) | Create families of related objects |
| Builder | [creational/builder.py](creational/builder.py) | Construct complex objects step by step |
| Prototype | [creational/prototype.py](creational/prototype.py) | Create objects by cloning an existing one |

### Structural — how objects are composed
| Pattern | File | One-liner |
|---|---|---|
| Adapter | [structural/adapter.py](structural/adapter.py) | Make an incompatible interface fit |
| Bridge | [structural/bridge.py](structural/bridge.py) | Split abstraction from implementation |
| Composite | [structural/composite.py](structural/composite.py) | Treat trees and leaves uniformly |
| Decorator | [structural/decorator.py](structural/decorator.py) | Add behavior by wrapping |
| Facade | [structural/facade.py](structural/facade.py) | One simple entry point to a subsystem |
| Flyweight | [structural/flyweight.py](structural/flyweight.py) | Share heavy state between many objects |
| Proxy | [structural/proxy.py](structural/proxy.py) | A stand-in that controls access |

### Behavioral — how objects communicate
| Pattern | File | One-liner |
|---|---|---|
| Chain of Responsibility | [behavioral/chain_of_responsibility.py](behavioral/chain_of_responsibility.py) | Pass a request along handlers |
| Command | [behavioral/command.py](behavioral/command.py) | Requests as objects, with undo |
| Interpreter | [behavioral/interpreter.py](behavioral/interpreter.py) | Evaluate sentences of a small language |
| Iterator | [behavioral/iterator.py](behavioral/iterator.py) | Traverse without exposing internals |
| Mediator | [behavioral/mediator.py](behavioral/mediator.py) | Centralize many-to-many communication |
| Memento | [behavioral/memento.py](behavioral/memento.py) | Snapshot & restore state |
| Observer | [behavioral/observer.py](behavioral/observer.py) | Notify dependents on state change |
| State | [behavioral/state.py](behavioral/state.py) | Behavior changes with internal state |
| Strategy | [behavioral/strategy.py](behavioral/strategy.py) | Swap algorithms at run time |
| Template Method | [behavioral/template_method.py](behavioral/template_method.py) | Fixed skeleton, overridable steps |
| Visitor | [behavioral/visitor.py](behavioral/visitor.py) | New operations without touching classes |

## Suggested learning order

Start with the patterns you'll meet most often in real code:
**Strategy → Observer → Factory Method → Decorator → Singleton → Adapter →
Template Method → Command** — then explore the rest.
