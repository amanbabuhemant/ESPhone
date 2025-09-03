#ifndef KEYS_H
#define KEYS_H

// keypad keys

/*
 * design in mind:
 -----------
 |   ^     |
 | < O >   |
 |   v     |
 | 1 2 3 A |
 | 4 5 6 B |
 | 7 8 9 C |
 | 0 F E D |
 -----------
 */

typedef enum {
    KEY__ = 0, // none key
    KEY_NONE = KEY__,
    KEY_OK,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
} Key;

#endif
