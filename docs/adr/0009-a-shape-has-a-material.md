# A shape has a material

## Context

Spheres and planes need materials for shading. Creating subclasses such as
`MatteSphere`, `MirrorSphere`, `MattePlane` and `MirrorPlane` would multiply the
number of classes for every shape and material combination. Composition lets
shapes and materials vary independently.

## Decision

Each concrete shape contains a `Material` and includes that material in its
`Hit`. Do not create shape subclasses for each material.

## Status

Proposed

## Consequences

Any shape can use any material without a growing matrix of subclasses, and the
renderer can shade a hit without knowing its concrete shape. Each shape must
carry the material into every hit, and the current design copies it. Shared or
more complex materials may require a different ownership model later.
