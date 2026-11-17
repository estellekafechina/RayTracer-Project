# Use CMake and CTest for builds and test execution

## Context

The project needs consistent commands on Linux, macOS and Windows. Alternatives
include platform-specific IDE projects, Makefiles and another build system such
as Meson.

## Decision

Use CMake 3.25 or newer with committed presets for configuration and builds,
and use CTest as the common test runner.

## Status

`Accepted`

## Consequences

One project definition and the same workflow commands work across supported
platforms. Contributors must install or use a container with CMake and Ninja,
and they must learn CMake's syntax and configure/build distinction.
