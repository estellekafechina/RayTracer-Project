# Save PNG files with LodePNG

## Context

The client opens rendered images in ordinary viewers, so the project saves PNG
files. PNG is compressed and includes checksums, so we will use a library
instead of writing the format ourselves.

We compared:

- libpng, the reference library, but it has a C API that takes many calls to
  save one image and it is not installed in the dev container;
- stb_image_write, a single public-domain header, but it has a C API with raw
  pointers and produces larger PNG files;
- LodePNG, one `.cpp` and one `.h` under the zlib licence, with no dependencies
  and a C++ API using `std::vector`, but slower saving than the other libraries;
- writing PPM ourselves, which needs no library, but most viewers cannot open
  it and its files are much larger.

## Decision

Use LodePNG from <https://github.com/lvandeve/lodepng>, downloaded by CMake
with `FetchContent` and pinned to commit
`7b2893e35891c0c85bee5595caafaf3c2044b409` because LodePNG has no releases.
Only `src/output/` uses it, behind our `ImageSaver` interface, so changing the
library or format means writing a new saver class.

## Status

Proposed

## Consequences

The project saves lossless PNG files without changing the dev container, and
application code depends on our interface rather than LodePNG. The first build
needs network access, LodePNG adds build time, saving is slower than the other
libraries considered, upgrading requires changing the pinned commit, and the
interface is one more layer with only one implementation for now.
