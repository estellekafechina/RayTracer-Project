# Run continuous integration with GitHub Actions

## Context

Every pull request should build and run tests in the same dev container used by
contributors. Alternatives include installing tools directly on a hosted
runner, invoking the Dev Container CLI manually, or using another CI service.

## Decision

Use GitHub Actions with the official `devcontainers/ci` action to execute
`cmake --workflow --preset test` from `.devcontainer/devcontainer.json`.

## Status

`Accepted`

## Consequences

Pull requests are checked in the reference environment before review. The
project depends on GitHub Actions and a third-party action, CI consumes hosted
runner time, and rebuilding the container can make checks slower.
