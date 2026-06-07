#include QMK_KEYBOARD_H
#include "sigma_tkl.h"

// Drop CTRL adds an LED-flag cycle on RM_TOGG: ALL → keylight+mod+indicator
// → underglow → off → ALL. Other tkl_ansi sigma keymaps that don't pull
// in this handler get the default RM_TOGG (whole-matrix on/off).
#ifdef RGB_MATRIX_ENABLE
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RM_TOGG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true;
    }
}
#endif
