# Homemade Ray Tracer

| [![Clock](./renders/clock.png)](./src/clock.cpp) | [![Circle](./renders/circle.png)](./src/circle.cpp) |
| - | -|

The ray tracer is written in C++23 with [modules](https://en.cppreference.com/w/cpp/language/modules.html) and no dependencies except for running tests, the [μt](https://github.com/boost-ext/ut) unit testing framework is required ([CMake](./CMakeLists.txt) will automatically install it).

## Building

- Install CMake 4.0.2
- [Set up vcpkg](https://learn.microsoft.com/en-us/vcpkg/)
- Clone the repository and build the project

```
git clone http://github.com/faresbakhit/raytracer && cd raytracer
cmake --preset release
cmake --build --preset release
```
