# AGENTS.md

Before adding or modifying any `sigma` keymap in this userspace, read [`docs/sigma_keymaps.md`](docs/sigma_keymaps.md). It defines the principles every sigma keymap must satisfy (QWERTY-aligned main rows, OS-aware function row via `SIGMA_FN_ROW`, hyper / hyper_s modifiers, consistent `_FN` layer mappings) and tracks the table of current per-board `_FN` assignments — including known conflicts that need resolving.

If a change would diverge from those principles, update `docs/sigma_keymaps.md` first (in the same commit when feasible) so the contract stays accurate.
