# Sigma's QMK Userspace

Personal [QMK](https://github.com/qmk/qmk_firmware) keymaps for the boards I use, sharing a common `users/sigma/` core so the central QWERTY block stays consistent across very different chassis.

## Keyboards

| Target | Keymap location |
|--------|-----------------|
| `drop/ctrl/v2` | `layouts/tkl_ansi/sigma/` (community layout) |
| `converter/sun_usb/type5` | `keyboards/converter/sun_usb/type5/keymaps/sigma/` |
| `ergodox_ez`, `input_club/ergodox_infinity` | `layouts/ergodox/sigma/` (community layout) |

All four are listed in `qmk.json`'s `build_targets`.

## Shared userspace (`users/sigma/`)

- Auto OS detection via QMK's [`os_detection`](https://docs.qmk.fm/features/os_detection) feature, driving `set_unicode_input_mode` when unicode is enabled.
- `KC_OS_CUT/COPY/PASTE/UNDO/REDO/LOCK` keycodes that translate to the right shortcut per OS (macOS/iOS/Linux/Windows).
- `KC_MAKE`, `KC_QWERTY`, `KC_SCRT`, `MD_BOOT` (hold-to-bootloader), `VRSN`, `EPRM`.
- Layout primitives for the central QWERTY block, each row split into hand-halves so split keyboards can grab one at a time:
  - `SIGMA_NUM_L/R/ROW`, `SIGMA_QWE_L/R/ROW`, `SIGMA_ASD_L/R/ROW`, `SIGMA_ZXC_L/R/ROW`
- Behavior tokens shared across keymaps:
  - `SIGMA_CTL` = `LCTL_T(KC_ENT)` (home-row Ctrl/Enter mod-tap)
  - `SIGMA_LSFT` / `SIGMA_RSFT` = `SC_LSPO` / `SC_RSPC` (space-cadet shifts)
  - `SIGMA_FN` = `MO(_FN)`

Every keymap uses `_QWERTY` and `_FN` layers, and wraps the keyboard's `LAYOUT(...)` macro with a local `KMAP(...)` indirection so the row macros expand before LAYOUT counts its args.

## Building

A Nix flake provides QMK via [firefly-engineering/toolbox](https://github.com/firefly-engineering/toolbox)'s `kbd-toolchain` (bundles `qmk`, `qmk_hid`, `vitaly`). `direnv` activates the shell automatically.

```sh
direnv allow                                 # one-time
qmk userspace-compile                        # build every qmk.json target
qmk compile -kb drop/ctrl/v2 -km sigma       # build a single target
make clean                                   # wipe .build/ and lingering binaries
```

The top-level `Makefile` forwards to `qmk_firmware` and overrides `clean` to also remove the `*.hex`/`*.bin`/`*.uf2` that `cpfirmware` copies into the repo root.

## GitHub Actions

`.github/workflows/build_binaries.yaml` builds every `qmk.json` target on push and uploads firmware to the Releases tab; it delegates to the reusable workflows at `qmk/.github`.
