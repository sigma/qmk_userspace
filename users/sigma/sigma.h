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
   // OS-aware function row: F1-F12 on Win/Linux, Mac media-row equivalents
   // on macOS/iOS. Holding _FN inverts the mapping (so on Mac fn+Play
   // sends F8). Dispatched at runtime in sigma.c via detected_host_os().
   OS_F1, OS_F2, OS_F3,  OS_F4,  OS_F5,  OS_F6,
   OS_F7, OS_F8, OS_F9, OS_F10, OS_F11, OS_F12,
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

// Function row: OS-aware F1-F12 (see OS_F* dispatch in sigma.c).
#define SIGMA_FN_ROW \
  OS_F1, OS_F2, OS_F3,  OS_F4,  OS_F5,  OS_F6, \
  OS_F7, OS_F8, OS_F9, OS_F10, OS_F11, OS_F12

// Behavior tokens shared across keymaps.
#define SIGMA_CTL     LCTL_T(KC_ENT)
#define SIGMA_CTL_R   RCTL_T(KC_ENT)
#define SIGMA_LSFT    SC_LSPO
#define SIGMA_RSFT    SC_RSPC
#define SIGMA_FN      MO(_FN)
#define SIGMA_HYPER   LCAG(KC_NO)       // Ctrl+Alt+GUI hold (3 mods, no shift)
#define SIGMA_HYPER_S HYPR(KC_NO)       // SIGMA_HYPER + Shift (all 4 mods)

// Capability-conditional macros: real keycode when the board supports the
// feature, KC_NO otherwise. Each one expects whatever header defines the
// underlying keycode (e.g. keychron_common.h for BT_HST*/BAT_LVL/KC_SNAP/
// KC_SIRI) to be included before sigma.h.

// Backlight controls: RGB matrix > rgblight underglow > no-op. Naming
// mirrors the RM_*/UG_* keycode family so the mapping is obvious.
#ifdef RGB_MATRIX_ENABLE
  #define SIGMA_BL_TOGG RM_TOGG
  #define SIGMA_BL_NEXT RM_NEXT
  #define SIGMA_BL_PREV RM_PREV
  #define SIGMA_BL_VALU RM_VALU
  #define SIGMA_BL_VALD RM_VALD
  #define SIGMA_BL_HUEU RM_HUEU
  #define SIGMA_BL_HUED RM_HUED
  #define SIGMA_BL_SATU RM_SATU
  #define SIGMA_BL_SATD RM_SATD
  #define SIGMA_BL_SPDU RM_SPDU
  #define SIGMA_BL_SPDD RM_SPDD
#elif defined(RGBLIGHT_ENABLE)
  #define SIGMA_BL_TOGG UG_TOGG
  #define SIGMA_BL_NEXT UG_NEXT
  #define SIGMA_BL_PREV UG_PREV
  #define SIGMA_BL_VALU UG_VALU
  #define SIGMA_BL_VALD UG_VALD
  #define SIGMA_BL_HUEU UG_HUEU
  #define SIGMA_BL_HUED UG_HUED
  #define SIGMA_BL_SATU UG_SATU
  #define SIGMA_BL_SATD UG_SATD
  #define SIGMA_BL_SPDU UG_SPDU
  #define SIGMA_BL_SPDD UG_SPDD
#else
  #define SIGMA_BL_TOGG KC_NO
  #define SIGMA_BL_NEXT KC_NO
  #define SIGMA_BL_PREV KC_NO
  #define SIGMA_BL_VALU KC_NO
  #define SIGMA_BL_VALD KC_NO
  #define SIGMA_BL_HUEU KC_NO
  #define SIGMA_BL_HUED KC_NO
  #define SIGMA_BL_SATU KC_NO
  #define SIGMA_BL_SATD KC_NO
  #define SIGMA_BL_SPDU KC_NO
  #define SIGMA_BL_SPDD KC_NO
#endif

// Keychron Bluetooth host switching + battery indicator.
#if defined(KC_BLUETOOTH_ENABLE) || defined(LK_WIRELESS_ENABLE)
  #define SIGMA_BT1 BT_HST1
  #define SIGMA_BT2 BT_HST2
  #define SIGMA_BT3 BT_HST3
  #define SIGMA_BAT BAT_LVL
#else
  #define SIGMA_BT1 KC_NO
  #define SIGMA_BT2 KC_NO
  #define SIGMA_BT3 KC_NO
  #define SIGMA_BAT KC_NO
#endif

// Keychron 2.4 GHz mode toggle (boards with the P24G_MODE_SELECT_PIN or
// KEYCOMBO_CONN_SWITCH_ENABLE wiring; e.g. Q1 Max).
#if defined(P24G_MODE_SELECT_PIN) || defined(KEYCOMBO_CONN_SWITCH_ENABLE)
  #define SIGMA_P2P4G P2P4G
#else
  #define SIGMA_P2P4G KC_NO
#endif

// Mac convenience keys provided by keychron_common.h.
#ifdef KC_SNAP
  #define SIGMA_SCRN_SHOT KC_SNAP
#else
  #define SIGMA_SCRN_SHOT KC_NO
#endif

#ifdef KC_SIRI
  #define SIGMA_SIRI KC_SIRI
#else
  #define SIGMA_SIRI KC_NO
#endif
