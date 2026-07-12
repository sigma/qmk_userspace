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

# MIDI note/control keycodes (MI_*) for the _MIDI layer. config.h defines
# MIDI_ADVANCED to get the full note/octave/velocity/etc. keycode set.
MIDI_ENABLE = yes

# The STM32F303 runs out of USB endpoints with RAW (oryx) + Console + MIDI +
# Mousekey/Extrakey/NKRO. Drop Console (the sigma userspace turns it on for
# debugging; this board doesn't need it) to make room for MIDI.
CONSOLE_ENABLE = no
