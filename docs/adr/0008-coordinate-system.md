# Use x right, y up and z forward

## Context

The camera needs one coordinate convention for the world and another for image
pixels. We need the convention to be explicit before adding more camera and
geometry operations. An alternative, used by *Ray Tracing in One Weekend*, is
to look along negative z instead of positive z.

## Decision

Use x to the right, y up and z forward in the world. Count image columns from
left to right and rows from top to bottom, starting at the top-left pixel.

## Status

Proposed

## Consequences

Objects in front of the current camera have positive z directions, matching the
pinhole spike. Converting a row to world y must reverse its direction, and rays
must target the centre of a pixel by adding half a pixel. This convention
differs from ray tracers that look along negative z, so formulas and imported
data may need conversion later.
