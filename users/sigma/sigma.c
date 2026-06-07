/*
  Copyright 2018 Yann Hodique <yann.hodique@gmail.com> @sigma

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "sigma.h"

__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void startup_keymap(void) {}

__attribute__ ((weak))
void shutdown_keymap(void) {}

__attribute__ ((weak))
void suspend_power_down_keymap(void) {}

__attribute__ ((weak))
void suspend_wakeup_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}


__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

__attribute__ ((weak))
layer_state_t default_layer_state_set_keymap (layer_state_t state) {
  return state;
}

__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE)
bool process_detected_host_os_user(os_variant_t os) {
  switch (os) {
  case OS_MACOS:
  case OS_IOS:
    set_unicode_input_mode(UNICODE_MODE_MACOS);
    break;
  case OS_LINUX:
    set_unicode_input_mode(UNICODE_MODE_LINUX);
    break;
  case OS_WINDOWS:
    set_unicode_input_mode(UNICODE_MODE_WINDOWS);
    break;
  case OS_UNSURE:
    break;
  }
  return true;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint32_t md_boot_timer;
  os_variant_t os_target = detected_host_os();
  bool pressed = record->event.pressed;

  switch (keycode) {
  case KC_QWERTY:
    if (pressed) {
      set_single_persistent_default_layer(_QWERTY);
    }
    return false;
    break;

  case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
    if (!pressed) {
      send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP
#if defined(__ARM__)
                   ":dfu-util"
#elif defined(BOOTLOADER_DFU)
                   ":dfu"
#elif defined(BOOTLOADER_HALFKAY)
                   ":teensy"
#elif defined(BOOTLOADER_CATERINA)
                   ":avrdude"
#endif // bootloader options
                   SS_TAP(X_ENTER)), 10);
    }
    return false;
    break;

  case EPRM: // Resets EEPROM
    if (pressed) {
      eeconfig_init();
      default_layer_set(1UL<<eeconfig_read_default_layer());
      layer_state_set(layer_state);
    }
    return false;
    break;
  case VRSN: // Prints firmware version
    if (pressed) {
      send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), MACRO_TIMER);
    }
    return false;
    break;

  case KC_OS_CUT:
    switch (os_target) {
    case OS_MACOS:
    case OS_IOS:
      if (pressed)
        SEND_STRING(SS_LGUI("x"));
      break;
    case OS_LINUX:
      pressed ?
        register_code(KC_CUT)
        : unregister_code(KC_CUT);
      break;
    default:
      if (pressed)
        SEND_STRING(SS_LCTL("x"));
      break;
    }
    break;

  case KC_OS_COPY:
    switch (os_target) {
    case OS_MACOS:
    case OS_IOS:
      if (pressed)
        SEND_STRING(SS_LGUI("c"));
      break;
    case OS_LINUX:
      pressed ?
        register_code(KC_COPY)
        : unregister_code(KC_COPY);
      break;
    default:
      if (pressed)
        SEND_STRING(SS_LCTL("c"));
      break;
    }
    break;

  case KC_OS_PASTE:
    switch (os_target) {
    case OS_MACOS:
    case OS_IOS:
      if (pressed)
        SEND_STRING(SS_LGUI("v"));
      break;
    case OS_LINUX:
      pressed ?
        register_code(KC_PASTE)
        : unregister_code(KC_PASTE);
      break;
    default:
      if (pressed)
        SEND_STRING(SS_LCTL("v"));
      break;
    }
    break;

  case KC_OS_UNDO:
    switch (os_target) {
    case OS_MACOS:
    case OS_IOS:
      if (pressed)
        SEND_STRING(SS_LGUI("z"));
      break;
    case OS_LINUX:
      pressed ?
        register_code(KC_UNDO)
        : unregister_code(KC_UNDO);
      break;
    default:
      if (pressed)
        SEND_STRING(SS_LCTL("z"));
      break;
    }
    break;

  case KC_OS_REDO:
    switch (os_target) {
    case OS_MACOS:
    case OS_IOS:
      if (pressed)
        SEND_STRING(SS_LGUI(SS_LSFT("z")));
      break;
    case OS_LINUX:
      pressed ?
        register_code(KC_AGAIN)
        : unregister_code(KC_AGAIN);
      break;
    default:
      if (pressed)
        SEND_STRING(SS_LCTL(SS_LSFT("z")));
      break;
    }
    break;

  case KC_OS_LOCK:
    switch (os_target) {
    case OS_MACOS:
    case OS_IOS:
      if (pressed)
        SEND_STRING(SS_LGUI(SS_LCTL("q")));
      break;
    case OS_LINUX:
      pressed ?
        register_code(KC_PWR)
        : unregister_code(KC_PWR);
      break;
    default:
      if (pressed)
        SEND_STRING(SS_LGUI("l"));
      break;
    }
    break;

  case KC_SCRT:
    if (pressed) {
      SEND_STRING(SS_LGUI("`"));
    }
    break;

  case MD_BOOT:
    if (pressed) {
      md_boot_timer = timer_read32();
    } else if (timer_elapsed32(md_boot_timer) >= 500) {
      reset_keyboard();
    }
    return false;

  // OS-aware function row. On the base layer: F1-F12 on Win/Linux/unsure,
  // the Mac media row on macOS/iOS. On the _FN layer the meaning is
  // inverted, so on Mac fn+Play sends F8 and on Win/Linux fn+F8 sends
  // Play. F5/F6 are special-cased on the media side to drive the
  // keyboard's lighting directly (RM_*/UG_* aren't HID keycodes and can't
  // be (un)registered).
  case OS_F1: case OS_F2: case OS_F3: case OS_F4: case OS_F5: case OS_F6:
  case OS_F7: case OS_F8: case OS_F9: case OS_F10: case OS_F11: case OS_F12: {
    // Remember which keycode each slot registered on press, so the matching
    // unregister fires even if the user releases _FN before the F-row key.
    static uint16_t os_f_active[12] = {0};
    static const uint16_t mac_keys[12] = {
      KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD,
      KC_NO,   KC_NO,                    // F5/F6: lighting, handled inline
      KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,
    };
    uint8_t idx = keycode - OS_F1;
    if (pressed) {
      bool is_mac = (os_target == OS_MACOS || os_target == OS_IOS);
      bool on_fn = (get_highest_layer(layer_state) == _FN);
      bool wants_media = is_mac ^ on_fn;
      if (wants_media) {
        switch (idx) {
          case 4: // F5 — lighting value down
#if defined(RGB_MATRIX_ENABLE)
            rgb_matrix_decrease_val_noeeprom();
#elif defined(RGBLIGHT_ENABLE)
            rgblight_decrease_val_noeeprom();
#endif
            os_f_active[idx] = KC_NO;
            break;
          case 5: // F6 — lighting value up
#if defined(RGB_MATRIX_ENABLE)
            rgb_matrix_increase_val_noeeprom();
#elif defined(RGBLIGHT_ENABLE)
            rgblight_increase_val_noeeprom();
#endif
            os_f_active[idx] = KC_NO;
            break;
          default:
            os_f_active[idx] = mac_keys[idx];
            register_code16(mac_keys[idx]);
            break;
        }
      } else {
        os_f_active[idx] = KC_F1 + idx;
        register_code16(KC_F1 + idx);
      }
    } else if (os_f_active[idx] != KC_NO) {
      unregister_code16(os_f_active[idx]);
      os_f_active[idx] = KC_NO;
    }
    return false;
  }
  }

  return process_record_keymap(keycode, record);
}
