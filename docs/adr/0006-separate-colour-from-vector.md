# Keep Colour separate from Vector

## Context

Both colours and vectors contain three numbers. We could reuse `Vector` for red,
green and blue, or represent colour as its own concept. A colour is not a
position or a direction, and its components have different meanings.

## Decision

Use a separate `Colour` class with red, green and blue components.

## Status

Proposed

## Consequences

The code makes the difference between geometry and colour explicit and prevents
accidentally mixing them. `Colour` duplicates the storage and accessors for
three numbers, and colour operations will need their own implementation instead
of reusing `Vector` operations.

The alternative deliberately not chosen is to use `Vector` for colours. It
would reuse more code, but would allow geometrically meaningless operations and
make function signatures less clear.
