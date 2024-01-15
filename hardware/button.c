//
// タクトスイッチ
//
#include "button.h"

#include <xc.h>

void button_init(void) {
    // 入力モードをデジタルに設定(初期状態ではアナログ)
    ANSA0 = 0;
    ANSB3 = 0;
    ANSB4 = 0;

    // 信号方向を入力に設定
    TRISA0 = 1;
    TRISB3 = 1;
    TRISB4 = 1;
}

bool button_isPressed(Button button) {
    switch (button) {
        case RedButton:
            return !RB3;

        case GreenButton:
            return !RB4;

        case BlueButton:
            return !RA0;

        default:
            return false;
    }
}
