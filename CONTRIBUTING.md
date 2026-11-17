# Contributing

Thank you for helping improve the RayTracer project.

## Development environment

The dev container is the reference environment. Install Docker and open this
repository with an editor that supports the Dev Container specification, such
as VS Code or Zed, then reopen the project in its container.

The initial container setup configures the development build automatically.
Catch2 is downloaded during the first configuration, so internet access is
required once.

## Everyday commands

Run these commands from the repository root, either natively or in the dev
container:

```sh
make clean
make build
make run
make test
```

## Test-driven development

Use a red-green-refactor cycle:

1. Add a small Catch2 test that describes the desired behaviour.
2. Run `make test` and confirm that the new test fails for
   the expected reason.
3. Write the smallest implementation that makes the test pass.
4. Refactor while keeping the full test suite green.

New test files belong in `tests/` and must be listed in
`tests/CMakeLists.txt`.

## Architecture decisions

Read the records in `docs/adr/` before changing the build, development tools,
test setup or continuous integration. Never work against an accepted ADR.

If a decision needs to change, add a new ADR using the same format, set its
status to `Proposed`, explain what it replaces and ask the maintainer to review
it. Contributors and automated tools must never set an ADR to `Accepted`.

## Submitting a change

1. Create a focused branch from the current default branch.
2. Keep the change small and include tests for changed behaviour.
3. Update documentation when commands, behaviour or architecture change.
4. Run `make test` before opening the pull request.
5. Complete the pull request template and link related issues.

All contributions are submitted under the repository's MIT licence. By
participating, you agree to follow the [Code of Conduct](CODE_OF_CONDUCT.md).
Report security problems privately as described in [SECURITY.md](SECURITY.md).
