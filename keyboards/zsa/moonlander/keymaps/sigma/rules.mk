# Oryx / Keymapp support comes from the vendored `zsa/oryx` community module,
# enabled via keymap.json's `modules` list (see ../../../../modules/zsa). That
# module defines the C `ORYX_ENABLE` macro and pulls in RAW_ENABLE itself, so
# no feature flags are needed here.
#
# MOUSEKEY / EXTRAKEY / NKRO / RGB_MATRIX are already on at the keyboard level
# (keyboards/zsa/moonlander/keyboard.json), so the mouse layer, media keys,
# NK_TOGG and the per-key RGB all work without extra flags too.

# Silence the piezo: the moonlander enables audio by default, which plays the
# startup / goodbye / bootloader tunes. Turn it off so flashing is quiet.
AUDIO_ENABLE = no
