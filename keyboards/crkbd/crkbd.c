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

#include "quantum.h"
#include "ctype.h"
#include "time.h"

#ifdef SWAP_HANDS_ENABLE
__attribute__((weak)) const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    // Left
    {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}},
    {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}},
    {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}},
    {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}},
    // Right
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}},
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}},
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}}};
#endif

#ifdef OLED_ENABLE

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }

    return OLED_ROTATION_270;
}

static const char PROGMEM word_Layer[] = {
       0x0b,0x20, 0x38, 0x24, 0x31,
      0};
static const char PROGMEM word_EMPTYLINE[] = {
        0x80,0x80, 0x80, 0x80, 0x80,
        0};

static void oled_render_layer_state(void) {
    static const char PROGMEM layer_ui_default[] = {
        0x5b,0x5c, 0x5d, 0x5e, 0x5f,
        0x7b,0x7c, 0x7d, 0x7e, 0x7f,
        0x9b,0x9c, 0x9d, 0x9e, 0x9f,
        0};
    static const char PROGMEM layer_ui_0[] = {
        0xb9,0xba, 0x5d, 0x5e, 0x5f,
        0xd9,0xda, 0x7d, 0x7e, 0x7f,
        0x9b,0x9c, 0x9d, 0x9e, 0x9f,
        0};
    static const char PROGMEM layer_ui_1[] = {
        0x5b,0x5c, 0x5d, 0xbb, 0xbc,
        0x7b,0x7c, 0x7d, 0xdb, 0xdc,
        0x9b,0x9c, 0x9d, 0x9e, 0x9f,
        0};
    static const char PROGMEM layer_ui_2[] = {
        0x5b,0x5c, 0x5d, 0x5e, 0x5f,
        0x7b,0x7c, 0xbd, 0xdd, 0x7f,
        0x9b,0x9c, 0x9d, 0x9e, 0x9f,
        0};
    static const char PROGMEM layer_ui_3[] = {
        0x5b,0x5c, 0x5d, 0x5e, 0x5f,
        0x7b,0x7c, 0x7d, 0x7e, 0x7f,
        0xbe,0xbf, 0x9d, 0x9e, 0x9f,
        0};
    static const char PROGMEM layer_ui_4[] = {
        0x5b,0x5c, 0x5d, 0x5e, 0x5f,
        0x7b,0x7c, 0x7d, 0x7e, 0x7f,
        0x9b,0x9c, 0x9d, 0xde, 0xdf,
        0};



    oled_write_P(word_Layer, false); //need to fix this 

    
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(layer_ui_0, false);
            break;
        case 1:
            oled_write_P(layer_ui_1, false);
            break;
        case 2:
            oled_write_P(layer_ui_2, false);
            break;
        case 3:
            oled_write_P(layer_ui_3, false);
            break;
        case 4:
            oled_write_P(layer_ui_4, false);
            break;
        default:
            oled_write_P(layer_ui_default, false);
            break;
    } 

    
    oled_write_P(word_EMPTYLINE, false);
    oled_write_P(word_EMPTYLINE, false);
}


bool is_shift_pressed = false;
bool is_alt_pressed = false;
bool is_control_pressed = false;
bool is_gui_pressed = false;

static const char PROGMEM word_Modif[] = {
       0x0c,0x2e, 0x23, 0x28, 0x25,
      0};


static void oled_render_toggle_status(void) {
    oled_write_P(word_Modif, false); //need to fix this 

   //ONLY TOP OF FRAME
    static const char PROGMEM modefier_ui_top_off[] = {
        0x57,0x58, 0x58, 0x58, 0x59,
        0};
    static const char PROGMEM modefier_ui_top_on[] = {
        0x77,0x78, 0x78, 0x78, 0x79,
        0};
    //TOP AND BOTTOM OF FRAME
    static const char PROGMEM modefier_ui_mid_off[] = {
        0x92,0x93, 0x93, 0x93, 0x94,
        0};
    static const char PROGMEM modefier_ui_mid_on[] = {
        0x95,0x96, 0x96, 0x96, 0x97,
        0};
    static const char PROGMEM modefier_ui_mid_top_on[] = {
        0xb2,0xb3, 0xb3, 0xb3, 0xb4,
        0};
    static const char PROGMEM modefier_ui_mid_bot_on[] = {
        0xd2,0xd3, 0xd3, 0xd3, 0xd4,
        0};


    //ONLY BOTTOM OF FRAME
    static const char PROGMEM modefier_ui_bot_off[] = {
        0x54,0x55, 0x55, 0x55, 0x56,
        0};
    static const char PROGMEM modefier_ui_bot_on[] = {
        0x74,0x75, 0x75, 0x75, 0x76,
        0};


   
    static const char PROGMEM modefier_ui_shift_off[] = {
        0x5a,0x12, 0x05, 0x13, 0x9a,

        0};
    static const char PROGMEM modefier_ui_shift_on[] = {
        0x7a,0xd7, 0xb7, 0xd8, 0x99,
        0};
    
    static const char PROGMEM modefier_ui_control_off[] = {
        0x5a,0x02, 0x13, 0x0b, 0x9a,
        0};
    static const char PROGMEM modefier_ui_control_on[] = {
        0x7a,0xb6, 0xd8, 0xb8, 0x99,
        0};

      static const char PROGMEM modefier_ui_alt_off[] = {
        0x5a,0x85, 0x0b, 0x13, 0x9a,
        0};
    static const char PROGMEM modefier_ui_alt_on[] = {
        0x7a,0xb5, 0xb8, 0xd8, 0x99,
        0};
    
  static const char PROGMEM modefier_ui_super_off[] = {
        0x5a,0x12, 0x0f, 0x11, 0x9a,
        0};
    static const char PROGMEM modefier_ui_super_on[] = {
        0x7a,0xd7, 0xd5, 0xd6, 0x99,
        0};
    






    // Host Keyboard LED Status
    if (is_shift_pressed) {
        oled_write_P(modefier_ui_top_on, false);
        oled_write_P(modefier_ui_shift_on, false);
    } else {
        oled_write_P(modefier_ui_top_off, false);
        oled_write_P(modefier_ui_shift_off, false);
    }

    if(is_shift_pressed && is_control_pressed){
        oled_write_P(modefier_ui_mid_on, false);
    } else if (is_shift_pressed && !is_control_pressed) {
        oled_write_P(modefier_ui_mid_top_on, false);
    } else if (!is_shift_pressed && is_control_pressed){
        oled_write_P(modefier_ui_mid_bot_on, false);
    } else {
        oled_write_P(modefier_ui_mid_off, false);
    }

    if (is_control_pressed) {
        oled_write_P(modefier_ui_control_on, false);
    } else {
        oled_write_P(modefier_ui_control_off, false);
    }

    if(is_control_pressed && is_alt_pressed){
        oled_write_P(modefier_ui_mid_on, false);
    } else if (is_control_pressed && !is_alt_pressed) {
        oled_write_P(modefier_ui_mid_top_on, false);
    } else if (!is_control_pressed && is_alt_pressed){
        oled_write_P(modefier_ui_mid_bot_on, false);
    } else {
        oled_write_P(modefier_ui_mid_off, false);
    }


    if (is_alt_pressed) {
        oled_write_P(modefier_ui_alt_on, false);
    } else {
        oled_write_P(modefier_ui_alt_off, false);
    }


    if(is_alt_pressed && is_gui_pressed){
        oled_write_P(modefier_ui_mid_on, false);
    } else if (is_alt_pressed && !is_gui_pressed) {
        oled_write_P(modefier_ui_mid_top_on, false);
    } else if (!is_alt_pressed && is_gui_pressed){
        oled_write_P(modefier_ui_mid_bot_on, false);
    } else {
        oled_write_P(modefier_ui_mid_off, false);
    }

    if (is_gui_pressed) {
        oled_write_P(modefier_ui_super_on, false);
        oled_write_P(modefier_ui_bot_on, false);
        

    } else {
        oled_write_P(modefier_ui_super_off, false);
        oled_write_P(modefier_ui_bot_off, false);
        
    }
}

char     key_name = ' ';
uint16_t last_keycode;
uint8_t  last_row;
uint8_t  last_col;

static const char PROGMEM code_to_name[60] = {'Z', 'X', 'V', 'N', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', 'C', ' ', ' '};


static void set_keylog(uint16_t keycode, keyrecord_t *record) {
    // save the row and column (useful even if we can't find a keycode to show)
    last_row = record->event.key.row;
    last_col = record->event.key.col;

    key_name     = ' ';
    last_keycode = keycode;
    if (IS_QK_MOD_TAP(keycode)) {
        if (record->tap.count) {
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
        } else {
            keycode = 0xE0 + biton(QK_MOD_TAP_GET_MODS(keycode) & 0xF) + biton(QK_MOD_TAP_GET_MODS(keycode) & 0x10);
        }
    } else if (IS_QK_LAYER_TAP(keycode) && record->tap.count) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_MODS(keycode)) {
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    } else if (IS_QK_ONE_SHOT_MOD(keycode)) {
        keycode = 0xE0 + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0xF) + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0x10);
    }
    if (keycode > ARRAY_SIZE(code_to_name)) {
        return;
    }

    // update keylog
    key_name = pgm_read_byte(&code_to_name[keycode]);
}
/*
static void oled_render_keylog(void) {
    oled_write_P(PSTR("KyLog"), false);
    oled_write_char(' ', false);
    oled_write_char('0' + last_row, false);
    oled_write_P(PSTR("x"), false);
    if (last_row == 3 || last_row == 7) {
        oled_write_char('0' + last_col - 3, false);
    } else {
        oled_write_char('0' + last_col, false);
    }
    oled_write_P(PSTR(" "), false);
    if (last_row == 2 && last_col == 0) {
        oled_write_P(PSTR("CTRL "), false);
    } else if (last_row == 3 && last_col == 4) {
        oled_write_P(PSTR("SHIFT"), false);
    } else if (last_row == 7 && last_col == 3) {
        oled_write_P(PSTR(" ALT "), false);
    } else if (last_row == 3 && last_col == 3) {
        if (get_highest_layer(layer_state) == 0) {
            oled_write_P(PSTR(" GUI "), false);
        } else {
            oled_write_P(PSTR("LAYER"), false);
        }
    }

    else {
        switch (key_name) {
            case 'R':
                oled_write_P(PSTR("ENTER"), false);
                break;
            case 'E':
                oled_write_P(PSTR("ESCPE"), false);
                break;
            case 'B':
                oled_write_P(PSTR("BCKSP"), false);
                break;
            case 'T':
                oled_write_P(PSTR(" TAB "), false);
                break;
            case ']':
                oled_write_P(PSTR("DELET"), false);
                break;
            case '_':
                oled_write_P(PSTR("SPACE"), false);
                break;
            case 'C':
                oled_write_P(PSTR("CAPS "), false);
                break;
            case ';':
                oled_write_P(PSTR("CEDLA"), false);
                break;
            case '/':
                oled_write_P(PSTR("  "), false);
                oled_write_char(toupper('-'), false);
                oled_write_P(PSTR("  "), false);
                break;
            case '#':
                oled_write_P(PSTR("  "), false);
                oled_write_char(toupper('~'), false);
                oled_write_P(PSTR("  "), false);
                break;
            case '\'':
                oled_write_P(PSTR("ORDIN"), false);
                break;
            default:
                if (key_name != ' ') {
                    oled_write_P(PSTR("  "), false);
                    oled_write_char(toupper(key_name), false);
                    oled_write_P(PSTR("  "), false);
                } else {
                    oled_write_P(PSTR("LAYER"), false);
                }
                break;
        }
    }
}
*/
int         keyCounter = 0;
/*
static void oled_render_pressed_keys(void) {
    // Display static text
    oled_write_P(PSTR("     "), false); // Clear the display line (assuming 5 spaces clear)
    oled_write_P(PSTR("CONTR"), false);

    char buffer[11];                                    // Buffer to hold the string representation of keyCounter
    snprintf(buffer, sizeof(buffer), "%d", keyCounter); // Convert keyCounter to a string

    int len     = strlen(buffer); // Length of the number as a string
    int padding = (5 - len) / 2;  // Calculate padding

    char centered_text[5 + 1];     // Buffer for centered text
    memset(centered_text, ' ', 5); // Fill buffer with spaces
    centered_text[5] = '\0';       // Null-terminate the string

    // Copy the number into the centered position
    strncpy(centered_text + padding, buffer, len);

    // Write the centered text to the OLED display
    oled_write(centered_text, false);

    return;
}
*/
__attribute__((weak)) void oled_render_logo(void) { //UPDATED

    // clang-format off
    static const char PROGMEM crkbd_logo[] = {
        0x80,0x80, 0x81, 0x82, 0x83, 0x84, 0x80, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x80, 0x80,
        0x80,0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0x80, 0x80, 
        0x80,0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0x80, 0x80,
        0};

    // clang-format on
    oled_write_P(crkbd_logo, false);
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {
        oled_render_layer_state();

        oled_render_toggle_status();
        //oled_write_ln_P(PSTR("    "), false);
        //oled_render_keylog();

        //oled_render_pressed_keys();
        //oled_render_current_time();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
        keyCounter++;
    }

    last_row = record->event.key.row;
    last_col = record->event.key.col;

    if (last_row == 3 && last_col == 4) {
        is_shift_pressed = !is_shift_pressed;
    } else if (last_row == 2 && last_col == 0) {
        is_control_pressed = !is_control_pressed;
    } else if (last_row == 7 && last_col == 3) {
        is_alt_pressed = !is_alt_pressed;
    }  else if (last_row == 3 && last_col == 3) {
        is_gui_pressed = !is_gui_pressed;
    } 
    return true;
}
#endif // OLED_ENABLE
