# Sigma keymap design

This document captures the principles every `sigma` keymap in this userspace must follow. Treat it as a contract: when adding or changing a keymap, preserve these properties — and if a principle itself needs to change, update this document first.

The intent is consistency across very different chassis. The same finger should reach the same logical key on a Drop CTRL, a Keychron Q1, a Sun Type 5 converter, and an Ergodox.

## Principles

### 1. QWERTY-aligned main keys

The four central rows hold standard QWERTY content, ten keys per row:

| Row | Keys |
|-----|------|
| Numbers | `1 2 3 4 5 6 7 8 9 0` |
| Top alphas | `Q W E R T Y U I O P` |
| Home alphas | `A S D F G H J K L ;` |
| Bottom alphas | `Z X C V B N M , . /` |

`KC_QUOT` (`'`) sits *outside* the home-row ten on full-size boards. `SIGMA_ASD_R` is therefore 5 keys (H J K L `;`) and `SIGMA_ASD_ROW` adds `KC_QUOT` after it, so each row macro stays symmetric (5+5).

On split keyboards, each row breaks into a left-hand block of five and a right-hand block of five, positioned symmetrically. The `SIGMA_*_L` / `SIGMA_*_R` macros in `users/sigma/sigma.h` exist for exactly this.

### 2. OS-aware function row

When the chassis has a dedicated function row, populate it with `SIGMA_FN_ROW` (`OS_F1`..`OS_F12`). Runtime dispatch in `users/sigma/sigma.c` decides what to send:

- macOS / iOS — Mac media row (BRID / BRIU / MCTL / LPAD / lighting / lighting / MPRV / MPLY / MNXT / MUTE / VOLD / VOLU)
- Windows / Linux / unsure — `KC_F1`..`KC_F12`
- Holding `_FN` inverts the mapping (so on Mac `fn+Play` sends F8, on Win/Linux `fn+F8` sends Play). F5/F6 on the media side call the lighting API directly (`rgb_matrix_*` / `rgblight_*`) because `RM_*`/`UG_*` aren't HID keycodes.

On chassis *without* a dedicated function row (e.g. Ergodox), F-keys live on the `_FN` layer at the digit positions and are **not** OS-aware. There they're plain `KC_F1`..`KC_F12`.

### 3. Hyper modifiers

Two pure-modifier chords are reserved for window-manager bindings:

- `SIGMA_HYPER` = `LCAG(KC_NO)` — Ctrl+Alt+GUI (3 mods)
- `SIGMA_HYPER_S` = `HYPR(KC_NO)` — Ctrl+Alt+GUI+Shift (4 mods)

Place `SIGMA_HYPER` on the outer-left modifier slot of the bottom row, and `SIGMA_HYPER_S` on the outer-right modifier slot. They are *not* layer-tap; pressing one only sends modifiers.

### 4. Consistent `_FN` layer assignments

The `_FN` layer overlays the base. Slots that aren't assigned should stay `_______` (transparent — fall through to base) or `XXXXXXX` (no-op) per board convention.

#### Current per-board `_FN` mappings

Use this table to spot conflicts before editing any keymap. A slot is "consistent" only when every column has the same value (allowing for `_______` to mean "intentionally unused on this board").

Legend: `· ` = `_______`/`XXXXXXX`. Conflicts are flagged in the **Notes** column.

##### Number row

| Slot | drop (tkl_ansi) | sun (type5) | ergodox (community) | k8_pro | q1_max | Notes |
|------|-----------------|-------------|---------------------|--------|--------|-------|
| `1`  | `SIGMA_BT1`     | `·`         | `KC_F1`             | `SIGMA_BT1` | `SIGMA_BT1` | ergodox borrows the slot for F1 (no dedicated F-row) — accept as principle-2 carve-out |
| `2`  | `SIGMA_BT2`     | `·`         | `KC_F2`             | `SIGMA_BT2` | `SIGMA_BT2` | same carve-out |
| `3`  | `SIGMA_BT3`     | `·`         | `KC_F3`             | `SIGMA_BT3` | `SIGMA_BT3` | same carve-out |
| `4`  | `·`             | `·`         | `KC_F4`             | `·`         | `SIGMA_P2P4G` | q1_max-only 2.4G mode toggle (no-op on other boards) |
| `5`  | `·`             | `·`         | `KC_F5`             | `·`         | `·`         | — |
| `6`  | `·`             | `·`         | `KC_F6`             | `·`         | `·`         | — |
| `7`  | `·`             | `·`         | `KC_F7`             | `·`         | `·`         | — |
| `8`  | `·`             | `·`         | `KC_F8`             | `·`         | `·`         | — |
| `9`  | `·`             | `·`         | `KC_F9`             | `·`         | `·`         | — |
| `0`  | `·`             | `·`         | `KC_F10`            | `·`         | `·`         | — |

##### Top alpha row

| Slot | drop | sun | ergodox | k8_pro | q1_max | Notes |
|------|------|-----|---------|--------|--------|-------|
| `Q`  | `SIGMA_BL_NEXT` | `·` | `·` | `SIGMA_BL_NEXT` | `SIGMA_BL_NEXT` | lighting: next animation |
| `W`  | `SIGMA_BL_VALU` | `·` | `·` | `SIGMA_BL_VALU` | `SIGMA_BL_VALU` | lighting: value up |
| `E`  | `SIGMA_BL_HUEU` | `·` | `·` | `SIGMA_BL_HUEU` | `SIGMA_BL_HUEU` | lighting: hue up |
| `R`  | `SIGMA_BL_SATU` | `·` | `·` | `SIGMA_BL_SATU` | `SIGMA_BL_SATU` | lighting: saturation up |
| `T`  | `SIGMA_BL_SPDU` | `·` | `·` | `SIGMA_BL_SPDU` | `SIGMA_BL_SPDU` | lighting: speed up |
| `Y`  | `·` | `·` | `·` | `·` | `·` | — |
| `U`  | `·` | `·` | `KC_MPRV` | `·` | `·` | ergodox-only media binding |
| `I`  | `·` | `·` | `KC_MPLY` | `·` | `·` | ergodox-only |
| `O`  | `·` | `·` | `KC_MNXT` | `·` | `·` | ergodox-only |
| `P`  | `SIGMA_BAT` | `·` | `·` | `SIGMA_BAT` | `SIGMA_BAT` | battery indicator (no-op on non-Keychron) |

##### Home alpha row

| Slot | drop | sun | ergodox | k8_pro | q1_max | Notes |
|------|------|-----|---------|--------|--------|-------|
| `A`  | `SIGMA_BL_PREV` | `·` | `·` | `SIGMA_BL_PREV` | `SIGMA_BL_PREV` | lighting: previous animation |
| `S`  | `SIGMA_BL_VALD` | `·` | `·` | `SIGMA_BL_VALD` | `SIGMA_BL_VALD` | lighting: value down |
| `D`  | `SIGMA_BL_HUED` | `·` | `·` | `SIGMA_BL_HUED` | `SIGMA_BL_HUED` | lighting: hue down |
| `F`  | `SIGMA_BL_SATD` | `·` | `·` | `SIGMA_BL_SATD` | `SIGMA_BL_SATD` | lighting: saturation down |
| `G`  | `SIGMA_BL_SPDD` | `·` | `·` | `SIGMA_BL_SPDD` | `SIGMA_BL_SPDD` | lighting: speed down |
| `H`  | `·` | `·` | `KC_VOLD` (ergodox) | `·` | `·` | ergodox-only |
| `J`  | `·` | `·` | `KC_MUTE` (ergodox) | `·` | `·` | ergodox-only |
| `K`  | `·` | `·` | `KC_VOLU` (ergodox) | `·` | `·` | ergodox-only |
| `L`  | `·` | `·` | `KC_MSTP` (ergodox) | `·` | `·` | ergodox-only |
| `;`  | `·` | `·` | `·` | `·` | `·` | — |

The `TAB` slot just outside the alpha block (row-2 outer) is reserved for `SIGMA_BL_TOGG` on every board with lighting — that's the lighting toggle, sitting next to the `Q–T` value/hue/sat/speed controls.

##### Bottom alpha row

| Slot | drop | sun | ergodox | k8_pro | q1_max | Notes |
|------|------|-----|---------|--------|--------|-------|
| `Z`  | `·` | `·` | `·` | `·` | `·` | — |
| `X`  | `·` | `·` | `·` | `·` | `·` | — |
| `C`  | `·` | `·` | `·` | `·` | `·` | — |
| `V`  | `·` | `·` | `·` | `·` | `·` | — |
| `B`  | `MD_BOOT` | `MD_BOOT` | `MD_BOOT` | `MD_BOOT` | `MD_BOOT` | hold to reset into bootloader |
| `N`  | `NK_TOGG` | `NK_TOGG` | `NK_TOGG` | `NK_TOGG` | `NK_TOGG` | toggle NKRO (keychrons enable NKRO at the keyboard level + wireless NKRO) |
| `M`  | `·` | `·` | `·` | `·` | `·` | — |
| `,`  | `·` | `·` | `·` | `·` | `·` | — |
| `.`  | `·` | `·` | `·` | `·` | `·` | — |
| `/`  | `·` | `·` | `·` | `·` | `·` | — |

#### Pending conflict resolutions

None right now. Add new entries here when conflicts surface during keymap changes.

When resolving an entry, update this table in the same change.

## Board-specific divergences

Most boards follow the principles above verbatim. A board may deliberately
depart from them when its hardware or intended use calls for it — but the
departure must be recorded here (per `AGENTS.md`) so the contract stays honest.

### `zsa/moonlander`

An ergonomic split (like the Ergodox) that keeps the shared QWERTY block
(`SIGMA_*_L/R`, principle 1) and the `SIGMA_HYPER` / `SIGMA_HYPER_S` chords
(principle 3), but diverges on three counts:

- **Home-row mods.** `A S D F` / `J K L ;` are mod-taps (Ctrl / Alt / GUI /
  Shift, pinky→index, mirrored) via the local `HR_*` / `SIGMA_HOME_L/R` macros.
  The rest of the userspace uses plain letters plus `SIGMA_CTL` on the caps
  slot; the Moonlander does not. Timing lives in the keymap's `config.h`
  (`TAPPING_TERM`, `PERMISSIVE_HOLD`, `QUICK_TAP_TERM`).
- **Three layers, restructured.** `_QWERTY` + `_FN` + a local `_MOUSE`. `_FN`
  carries function keys (plain `KC_F1`..`KC_F12` at the digit positions, the
  principle-2 no-dedicated-F-row carve-out), arrows as an inverted-T under the
  index finger (`R` up, `D`/`F`/`G` left/down/right), media / volume /
  brightness, and a right-hand keypad — *no* `SIGMA_FN_ROW`,
  `SIGMA_BT*` or the shared `_FN` table above, which target row-staggered
  boards. `_MOUSE` puts pointer movement on the same `R`/`D`/`F`/`G` inverted-T
  as the `_FN` arrows, wheel on the right top row, buttons on the right home
  row and left thumb, and acceleration on `Z X C`. `MD_BOOT` (B, hold ~500 ms then release) and `NK_TOGG` (N) live on
  `_MOUSE` only — `_FN` intentionally omits them.
- **Thumb clusters.** Space / Backspace / Tab / Enter (plus Esc, Del) live on
  the thumb arcs. The two big thumb keys are custom `TH_FNL` / `TH_FNR`
  (`process_record_keymap`): hold either for momentary `_FN`, press both
  together to switch to `_MOUSE`, and press either again to return from
  `_MOUSE` to `_QWERTY`.
- **Per-key category RGB.** `rgb_matrix_indicators_advanced_user()` colours
  every key by what it types on the active layer — letters blue, home-row mods a
  darker blue (letter hue, dimmed), numbers green, symbols red, function keys
  yellow, the space cluster (Space/Enter/Tab/Backspace) cyan, navigation
  (arrows, Home/End, PgUp/PgDn) pink, layer keys magenta, system keys
  (bootloader, NKRO & other magic toggles, RGB-matrix controls) orange, and any
  other special key purple; transparent keys stay dark. Colours are read back out of the keymap, so they never drift from the
  layout. The indicator yields (`rawhid_state.rgb_control`) whenever Oryx /
  Keymapp drives the LEDs.
- **Oryx / Keymapp support.** Enabled through the `zsa/oryx` community module,
  vendored under `modules/zsa/` and referenced from the keymap's `keymap.json`.
  The sibling `zsa/defaults` module is deliberately **not** used: it redefines
  `TOGGLE_LAYER_COLOR` / `LED_LEVEL` (already provided by mainline
  `moonlander.h`) and only adds trackpad/navigator keycodes this board lacks.
  Because `defaults` normally supplies the fallback, the keymap's `config.h`
  defines `SERIAL_NUMBER` itself.
