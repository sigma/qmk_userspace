# Vendored ZSA community modules

Source: https://github.com/zsa/qmk_modules
Commit: 141fad22045d7c17ff08a0e56e9a71ca753a5d77

Only the `oryx` module is vendored (webHID pairing / live training for
Oryx & Keymapp). It is referenced from
`keyboards/zsa/moonlander/keymaps/sigma/keymap.json`. The `defaults`
module is intentionally omitted: it redefines `TOGGLE_LAYER_COLOR` /
`LED_LEVEL`, which mainline `keyboards/zsa/moonlander/moonlander.h`
already provides, and it only adds trackpad/navigator keycodes this board
does not use.
