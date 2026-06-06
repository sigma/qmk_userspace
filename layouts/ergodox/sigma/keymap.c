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

#include QMK_KEYBOARD_H
#include "sigma.h"

// Indirection so SIGMA_*_L/R halves expand before LAYOUT counts its args.
#define KMAP(...) LAYOUT_ergodox(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_QWERTY] = KMAP(
       // ----- left hand -----
       KC_GRV,     SIGMA_NUM_L,                                  KC_LEFT,
       KC_TAB,     SIGMA_QWE_L,                                  TG(_FN),
       SIGMA_CTL,  SIGMA_ASD_L,
       SIGMA_LSFT, SIGMA_ZXC_L,                                  KC_LBRC,
       LCAG(KC_NO),KC_LGUI, KC_LALT, KC_LEFT, KC_RGHT,
                                              KC_LGUI, KC_LALT,
                                                       KC_DEL,
                              LT(_FN, KC_SPC), KC_BSPC, KC_HOME,

       // ----- right hand -----
       KC_RGHT,    SIGMA_NUM_R,                                  KC_MINS,
       TG(_FN),    SIGMA_QWE_R,                                  KC_BSLS,
                   SIGMA_ASD_R,                                  KC_QUOT,
       KC_RBRC,    SIGMA_ZXC_R,                                  SIGMA_RSFT,
                   KC_UP,   KC_DOWN, KC_RGUI, KC_APP, MEH_T(KC_NO),
       CTL_T(KC_ESC), KC_RALT,
       KC_PGUP,
       KC_PGDN, KC_TAB, KC_ENT
       ),

   [_FN] = KMAP(
       // ----- left hand -----
       KC_F11,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,
       _______, _______,_______,_______,_______,_______,_______,
       _______, _______,_______,_______,_______,_______,
       _______, _______,_______,_______,_______,MD_BOOT,_______,
       _______, _______,_______,_______,_______,
                                       _______,_______,
                                               _______,
                              _______, _______, _______,

       // ----- right hand -----
       _______, KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F12,
       _______, _______,KC_MPRV,KC_MPLY,KC_MNXT,_______,_______,
                _______,KC_VOLD,KC_MUTE,KC_VOLU,KC_MSTP,_______,
       _______, NK_TOGG,_______,_______,_______,_______,_______,
                _______,_______,_______,_______,_______,
       KC_OS_LOCK, _______,
       _______,
       _______, _______, _______
       ),
};
