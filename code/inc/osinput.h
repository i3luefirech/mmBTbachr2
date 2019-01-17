//
// Created by Rico on 2019-01-16.
//

#ifndef CODE_OSINPUT_H
#define CODE_OSINPUT_H

struct input_event {
    timeval time;
    uint16_t type;
    uint16_t code;
    int32_t value;
};

#define EV_KEY            0x01
#define EV_REL            0x02
#define EV_ABS            0x03
#define REL_X            0x00
#define REL_Y            0x01
#define REL_WHEEL        0x08
#define ABS_X            0x00
#define ABS_Y            0x01
#define ABS_WHEEL        0x08
#define BTN_LEFT        0x110
#define BTN_RIGHT        0x111
#define BTN_MIDDLE        0x112

#endif //CODE_OSINPUT_H
