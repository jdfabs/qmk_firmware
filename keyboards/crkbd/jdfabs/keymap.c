/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

enum Layer{
  Base,
  Symbols,
  Numbers,
  Hidden,
  AltGr,
  OS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [Base] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P, KC_RBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESC,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_NUHS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                              LT(2,KC_LGUI),   KC_LSFT,    KC_SPC,     KC_BSPC,   LT(1,KC_ENT), KC_LALT
                                      //`--------------------------'  `--------------------------'

  ),

    [Symbols] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_EXLM,    KC_AT,    KC_HASH,    KC_DLR,    KC_PERC,                         KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESC, KC_NO, RALT(KC_2), RALT(KC_E), KC_UNDS, KC_MINS,                      KC_TILD, RALT(KC_7),   RALT(KC_8),RALT(KC_9), RALT(KC_0), KC_LCBR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS, KC_NO, KC_NO, KC_NO, KC_NO, KC_GRV,                      KC_NO, KC_NUBS, LSFT(KC_NUBS), KC_EQL, LSFT(KC_EQL), KC_LBRC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          MO(3), KC_NO,  KC_SPC,     KC_BSPC,  KC_TRNS, KC_NO
                                      //`--------------------------'  `--------------------------'
  ),

    [Numbers] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_1,   KC_2, KC_3,  KC_4, KC_5,                      KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                      KC_LEFT,  KC_DOWN, KC_UP, KC_RGHT, KC_PSCR,  KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,                      KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_INS, KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_TRNS,  KC_NO,  KC_SPC,     KC_BSPC, LT(3,KC_ENT), MO(4)
                                      //`--------------------------'  `--------------------------'
  ),

    [Hidden] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        QK_BOOT, BL_BRTG, BL_STEP, BL_TOGG, NK_ON, RGB_M_R,                      KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_MPRV, KC_ACL2,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_M_B,                      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, KC_ACL1,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, RGB_M_P,                      KC_VOLU, KC_VOLD, KC_MUTE, KC_MNXT, KC_BTN2, KC_ACL0,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_NO,  KC_SPC,     KC_BSPC, KC_TRNS, KC_NO
                                      //`--------------------------'  `--------------------------'
  ),

    [AltGr] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        LALT(KC_TAB), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LALT(KC_ESC), KC_NO, KC_NO, LALT(KC_F4), KC_NO, KC_NO,                      LCA(KC_LEFT), LCA(KC_DOWN), LCA(KC_UP), LCA(KC_RGHT), KC_NO, KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_NO,  LALT(KC_SPC),     KC_NO, LALT(KC_ENT), KC_TRNS
                                      //`--------------------------'  `--------------------------'
  )
  }; 
