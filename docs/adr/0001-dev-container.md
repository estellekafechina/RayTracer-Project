# Use a dev container as the reference environment

## Context

Contributors may use Linux, macOS or Windows, and native toolchains can differ.
Alternatives are documenting separate native setups or maintaining a plain
Docker workflow outside editor tooling.

## Decision

Use `.devcontainer/devcontainer.json` as the reference development environment
for building and testing the project.

## Status

`Accepted`

## Consequences

Contributors get a consistent Linux toolchain in VS Code, Zed or another
compatible editor. Docker is required, the image takes time to download, and
the container does not reproduce every native operating-system difference.
