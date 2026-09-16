# engine1

A 2D game engine written from scratch in C++20, using SDL2 for windowing and
input and OpenGL (via glad) for rendering. No game framework underneath it —
the renderer, the physics, the collision detection and the world format are all
built here.

## What's in it

**Fixed-timestep physics, decoupled rendering.** Physics runs at a fixed
240 Hz in an accumulator loop while rendering runs as fast as the machine
allows. This keeps the simulation deterministic and stable regardless of frame
rate, and stops expensive draw calls from slowing the physics down:

```cpp
accumulator += Engine::getDeltaTime();
while (accumulator >= PHYSICS_STEP) {   // 1.0 / 240.0
    update(PHYSICS_STEP);
    accumulator -= PHYSICS_STEP;
}
render(Engine::getDeltaTime());
```

**Separate physics and controller velocity.** A `PhysicsObject` tracks
`physicsVelocity` and `controllerVelocity` independently and sums them on
read. Without this, gravity and player input fight each other — the controller
overwrites the velocity the integrator just set, and you get jitter. Keeping
them apart means a controller can set movement directly without stomping on
the simulation.

**Collision.** Separating Axis Theorem for convex polygons, plus AABB for the
cheap cases. Resolution cancels velocity along the collision normal rather than
reflecting it, so objects slide along surfaces instead of bouncing.

**Composition over inheritance for entities.** A `GameObject` owns an optional
`Shape`, `Animation` and `PhysicsObject`, plus a list of `Controller`s.
Behaviour comes from attaching controllers (`TopDownController`,
`PlatformerController`) rather than subclassing, and controllers declare whether
they override velocity or add to it.

**Worlds are authored as images.** Rather than hand-writing entity coordinates,
a world is a PNG plus a small text file that maps pixel colours to object
templates. Paint a level in any image editor and the engine builds it:

```
#object(platform)#hbox(rect,50,50)#animation(single,textures/cat.png,50,50)
#color(00FF00FF,platform)
#image(worlds/world.png)
#world(800,600)
```

| Directive | Meaning |
| --- | --- |
| `#object(name)` | starts an object template |
| `#hbox(rect,w,h)` / `#hbox(regular,sides,r)` | its collision shape |
| `#animation(single,path,w,h)` | a static sprite; `animation` and `index` forms take a sheet |
| `#color(RRGGBBAA,name)` | every pixel of this colour becomes one of `name` |
| `#image(path)` | the layout image |
| `#world(w,h)` | world dimensions |

**Also here:** a `Camera` that writes a view matrix uniform, `TextureMap` for
sprite sheets, frame-timed `Animation`, a `Shader` RAII wrapper, `Mat4`/`Vector2`
math, and bitmap `Font`/`Text` rendering.

## Building

Requires CMake 4.2+, a C++20 compiler, and SDL2 + glad from vcpkg.

```sh
cmake -B build -DCMAKE_TOOLCHAIN_FILE=<your-vcpkg>/scripts/buildsystems/vcpkg.cmake
cmake --build build
./build/physics     # run from the repo root so worlds/ and textures/ resolve
```

Note: `CMakeLists.txt` currently hardcodes my vcpkg prefix path. Override
`CMAKE_PREFIX_PATH` and `CMAKE_TOOLCHAIN_FILE` for your own install.

## Writing a game against it

Include `engine/Game.h`, define `start()`, `update(double)` and
`render(double)`, and use the `RUN` macro to get the main loop. `game/main.cpp`
is a working example: a platformer-controlled rectangle colliding with a world
loaded from an image.

## Current state

Working: rendering, sprites, animation, texture maps, camera, AABB and SAT
collision, world loading, both controllers.

Known issues:
- Font and text classes are implemented but untested — there's no sprite sheet
  for them yet.
- The platformer controller sometimes bounces slightly on landing. Likely
  overcorrection in collision resolution.
- `GameObject` has seven constructor overloads. It works, but it wants a
  builder.
