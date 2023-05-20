/**
 * @file keycodes.h
 * @author Ian Ress
 * @brief Keycode values defined by USB HID spec. For normal keys, these are 
 * the Usage IDs that correspond to the Keyboard Usage Page. For modifier keys,
 * these are the bit mapped position that correlates to the appropriate modifier key.
 * In the Report Descriptor, the first byte of data is represented as an 8-bit bitmap
 * that represents each modifier key.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef KEYCODES_H_
#define KEYCODES_H_

/* Modifier Keys */
#define KEY_LEFT_CTRL               (1U << 0)   // Usage ID = 0xE0
#define KEY_LEFT_SHIFT              (1U << 1)   // Usage ID = 0xE1
#define KEY_LEFT_ALT                (1U << 2)   // Usage ID = 0xE2
#define KEY_LEFT_GUI                (1U << 3)   // Usage ID = 0xE3
#define KEY_RIGHT_CTRL              (1U << 4)   // Usage ID = 0xE4
#define KEY_RIGHT_SHIFT             (1U << 5)   // Usage ID = 0xE5
#define KEY_RIGHT_ALT               (1U << 6)   // Usage ID = 0xE6
#define KEY_RIGHT_GUI               (1U << 7)   // Usage ID = 0xE7

/* Regular Keys. Also includes defaults when Shift modifier is pressed.
E.g. KEY_A includes 'a' and 'A'. */
#define KEY_NONE                    0x00    // Includes capitalization equivalent
#define KEY_A                       0x04    // Includes capitalization equivalent
#define KEY_B                       0x05    // Includes capitalization equivalent
#define KEY_C                       0x06    // Includes capitalization equivalent
#define KEY_D                       0x07    // Includes capitalization equivalent
#define KEY_E                       0x08    // Includes capitalization equivalent
#define KEY_F                       0x09    // Includes capitalization equivalent
#define KEY_G                       0x0A    // Includes capitalization equivalent
#define KEY_H                       0x0B    // Includes capitalization equivalent
#define KEY_I                       0x0C    // Includes capitalization equivalent
#define KEY_J                       0x0D    // Includes capitalization equivalent
#define KEY_K                       0x0E    // Includes capitalization equivalent
#define KEY_L                       0x0F    // Includes capitalization equivalent
#define KEY_M                       0x10    // Includes capitalization equivalent
#define KEY_N                       0x11    // Includes capitalization equivalent
#define KEY_O                       0x12    // Includes capitalization equivalent
#define KEY_P                       0x13    // Includes capitalization equivalent
#define KEY_Q                       0x14    // Includes capitalization equivalent
#define KEY_R                       0x15    // Includes capitalization equivalent
#define KEY_S                       0x16    // Includes capitalization equivalent
#define KEY_T                       0x17    // Includes capitalization equivalent
#define KEY_U                       0x18    // Includes capitalization equivalent
#define KEY_V                       0x19    // Includes capitalization equivalent
#define KEY_W                       0x1A    // Includes capitalization equivalent
#define KEY_X                       0x1B    // Includes capitalization equivalent
#define KEY_Y                       0x1C    // Includes capitalization equivalent
#define KEY_Z                       0x1D    // Includes capitalization equivalent   
#define KEY_1                       0x1E    // 1 and !
#define KEY_2                       0x1F    // 2 and @
#define KEY_3                       0x20    // 3 and #
#define KEY_4                       0x21    // 4 and $
#define KEY_5                       0x22    // 5 and %
#define KEY_6                       0x23    // 6 and ^
#define KEY_7                       0x24    // 7 and &
#define KEY_8                       0x25    // 8 and *
#define KEY_9                       0x26    // 9 and (
#define KEY_0                       0x27    // 0 and )
#define KEY_ENTER                   0x28
#define KEY_ESC                     0x29
#define KEY_BACKSPACE               0x2A
#define KEY_TAB                     0x2B
#define KEY_SPACE                   0x2C    
#define KEY_MINUS                   0x2D    // - and _
#define KEY_EQUAL                   0x2E    // = and +
#define KEY_LEFT_BRACE              0x2F    // [ and {
#define KEY_RIGHT_BRACE             0x30    // ] and }
#define KEY_BACKSLASH               0x31    // \ and |
#define KEY_NUMBER                  0x32    // # and ~
#define KEY_SEMICOLON               0x33    // ; and :
#define KEY_QUOTE                   0x34    // ' and ''
#define KEY_TILDE                   0x35    // ` and ~
#define KEY_COMMA                   0x36    // , and <
#define KEY_PERIOD                  0x37    // . and >
#define KEY_SLASH                   0x38    // / and ?
#define KEY_CAPS_LOCK               0x39
#define KEY_F1                      0x3A
#define KEY_F2                      0x3B
#define KEY_F3                      0x3C
#define KEY_F4                      0x3D
#define KEY_F5                      0x3E
#define KEY_F6                      0x3F
#define KEY_F7                      0x40
#define KEY_F8                      0x41
#define KEY_F9                      0x42
#define KEY_F10                     0x43
#define KEY_F11                     0x44
#define KEY_F12                     0x45
#define KEY_PRINTSCREEN             0x46
#define KEY_SCROLL_LOCK             0x47
#define KEY_PAUSE                   0x48
#define KEY_INSERT                  0x49
#define KEY_HOME                    0x4A
#define KEY_PAGE_UP                 0x4B
#define KEY_DELETE                  0x4C
#define KEY_END                     0x4D
#define KEY_PAGE_DOWN               0x4E
#define KEY_RIGHT                   0x4F
#define KEY_LEFT                    0x50
#define KEY_DOWN                    0x51
#define KEY_UP                      0x52
#define KEY_NUM_LOCK                0x53
#define KEYPAD_SLASH                0x54
#define KEYPAD_ASTERIX              0x55
#define KEYPAD_MINUS                0x56
#define KEYPAD_PLUS                 0x57
#define KEYPAD_ENTER                0x58
#define KEYPAD_1                    0x59
#define KEYPAD_2                    0x5A
#define KEYPAD_3                    0x5B
#define KEYPAD_4                    0x5C
#define KEYPAD_5                    0x5D
#define KEYPAD_6                    0x5E
#define KEYPAD_7                    0x5F
#define KEYPAD_8                    0x60
#define KEYPAD_9                    0x61
#define KEYPAD_0                    0x62
#define KEYPAD_PERIOD               0x63    

/* Useful shortcut keys I may use in the future. Modifier (e.g. Shift) keys
do not affect these. */
#define KEYPAD_EQUAL                0x67                                        // =
#define KEY_CUT                     0x7B
#define KEY_COPY                    0x7C
#define KEY_PASTE                   0x7D
#define KEYPAD_XOR                  0xC2                                        // ^=
#define KEYPAD_LOGIC_AND            0xC8                                        // &&
#define KEYPAD_LOGIC_OR             0xCA                                        // ||
#define KEYPAD_AND                  0xC7                                        // &
#define KEYPAD_OR                   0xC9                                        // |
/* These are not defined in the Keyboard Usage table. */
#define KEYPAD_BITWISE_OR           (((KEYPAD_OR) << 8) | (KEYPAD_EQUAL))       // |=
#define KEYPAD_BITWISE_AND          (((KEYPAD_AND) << 8) | (KEYPAD_EQUAL))      // &=

#endif /* KEYCODES_H_ */
