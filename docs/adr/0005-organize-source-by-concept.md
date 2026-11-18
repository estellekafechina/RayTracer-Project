# Organize source files by concept

## Context

A single flat `src/` folder will not scale as the raytracer gains more classes.
Contributors should be able to find a class and its tests from the concept it
belongs to, such as maths, geometry or rendering.

## Decision

Create one folder per concept under `src/`, and mirror those folders under
`tests/`. Keep each class header and implementation together in its concept
folder, and write includes from the `src/` root, for example
`#include "math/vector.h"`.

## Status

Proposed

## Consequences

Related classes and tests have predictable locations, and the structure can
grow without turning `src/` into a long flat list. Moving a class between
concepts changes its include path, small concepts may initially contain only
one class, and using `src/` as an include root does not distinguish public
headers from private implementation headers.

The following refinements are deliberately left out for now:

- Namespaces such as `raytracer::Vector` become worthwhile when concepts risk
  name collisions or partner studios use this code inside their own projects.
- One library per concept becomes worthwhile when folders need independent
  dependencies, build options, reuse or compile-time isolation.
- A separate `include/` folder becomes worthwhile when the project exposes an
  installable public API or needs a clear boundary between public and private
  headers.
