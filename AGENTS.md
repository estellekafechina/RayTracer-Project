# Project instructions

## Commands

- Clean: `make clean`
- Build: `make build`
- Run: `make run`
- Test: `make test`

## How we work

- Use TDD: write a failing test first, then only enough code to make it pass.
- Expected values come from the maths, not from running the code. If a test fails, ask the user before changing what it expects.
- Work one small step at a time and change only what the user asks for.
- Keep the C++ simple; do not use advanced features unless the user asks.
- Do not build or run anything on the host; run the commands in the dev container.

## Architecture decisions

Architecture decisions are in `docs/adr/`. Read them before changing the build, tools, or test setup.

Never go against an accepted ADR. To change a decision, write a new ADR with status `Proposed` and ask the user. Never set an ADR to `Accepted`.

## C++ style

Prefix every private member variable with `_`, for example `_x`.
Do not prefix accessor names with `get`; use `x()` instead of `getX()`.
New classes go in the folder of their concept, and their tests in the matching folder under `tests/`.

## Contributions

Follow `CONTRIBUTING.md`, `CODE_OF_CONDUCT.md` and `SECURITY.md`. Pull request
and issue templates are in `.github/`, and CI must continue to use the dev
container described by `docs/adr/0004-github-actions.md`.
