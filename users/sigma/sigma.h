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
#pragma once

#include "quantum.h"
#include "version.h"
#include "os_detection.h"

// Define layer names
enum userspace_layers
  {
   _QWERTY = 0,
   _FN,
  };

enum userspace_custom_keycodes
  {
   EPRM = SAFE_RANGE, // Resets EEPROM
   VRSN,              // Prints QMK Firmware and board info
   KC_QWERTY,         // Sets default layer to QWERTY
   KC_MAKE,           // Rebuild the current firmware
   KC_OS_CUT,
   KC_OS_COPY,
   KC_OS_PASTE,
   KC_OS_UNDO,
   KC_OS_REDO,
   KC_OS_LOCK,
   KC_SCRT,
   MD_BOOT,           // Hold to reset into bootloader
   SIGMA_SAFE_RANGE   // base for keymap-specific custom keycodes
  };

// Shared layout primitives: each keyboard's LAYOUT(...) wraps these inner
// rows with whatever extra keys its physical chassis carries. Each row is
// split into L/R halves so split keyboards can grab one hand at a time.
#define SIGMA_NUM_L KC_1, KC_2, KC_3, KC_4, KC_5
#define SIGMA_NUM_R KC_6, KC_7, KC_8, KC_9, KC_0
#define SIGMA_NUM_ROW SIGMA_NUM_L, SIGMA_NUM_R

#define SIGMA_QWE_L KC_Q, KC_W, KC_E, KC_R, KC_T
#define SIGMA_QWE_R KC_Y, KC_U, KC_I, KC_O, KC_P
#define SIGMA_QWE_ROW SIGMA_QWE_L, SIGMA_QWE_R

#define SIGMA_ASD_L KC_A, KC_S, KC_D, KC_F, KC_G
#define SIGMA_ASD_R KC_H, KC_J, KC_K, KC_L, KC_SCLN
#define SIGMA_ASD_ROW SIGMA_ASD_L, SIGMA_ASD_R, KC_QUOT

#define SIGMA_ZXC_L KC_Z, KC_X, KC_C, KC_V, KC_B
#define SIGMA_ZXC_R KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH
#define SIGMA_ZXC_ROW SIGMA_ZXC_L, SIGMA_ZXC_R

// Behavior tokens shared across keymaps.
#define SIGMA_CTL     LCTL_T(KC_ENT)
#define SIGMA_CTL_R   RCTL_T(KC_ENT)
#define SIGMA_LSFT    SC_LSPO
#define SIGMA_RSFT    SC_RSPC
#define SIGMA_FN      MO(_FN)
#define SIGMA_HYPER   LCAG(KC_NO)       // Ctrl+Alt+GUI hold (3 mods, no shift)
#define SIGMA_HYPER_S HYPR(KC_NO)       // SIGMA_HYPER + Shift (all 4 mods)
