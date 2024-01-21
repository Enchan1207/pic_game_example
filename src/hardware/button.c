//
// タクトスイッチ
//
#include "button.h"

#include <xc.h>

/// @brief 赤ボタン割り込みがあったか
static bool isRedButtonInterrupted = false;

/// @brief 緑ボタン割り込みがあったか
static bool isGreenButtonInterrupted = false;

void button_init(void) {
    // 入力モードをデジタルに設定(初期状態ではアナログ)
    ANSA0 = 0;
    ANSB3 = 0;
    ANSB4 = 0;

    // 信号方向を入力に設定
    TRISA0 = 1;
    TRISB3 = 1;
    TRISB4 = 1;

    // 外部割り込みの有効化 (立下りエッジ)
    IOCBNbits.IOCBN3 = 1;
    IOCBNbits.IOCBN4 = 1;
    INTCONbits.IOCIE = 1;
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

void button_setInterrupted(Button button) {
    switch (button) {
        case RedButton:
            isRedButtonInterrupted = true;
            break;

        case GreenButton:
            isGreenButtonInterrupted = true;
            break;

        default:
            break;
    }
}

bool button_isTyped(Button button) {
    switch (button) {
        case RedButton:
            if (isRedButtonInterrupted) {
                isRedButtonInterrupted = false;
                __delay_ms(2);
                return button_isPressed(RedButton);
            }
            break;

        case GreenButton:
            if (isGreenButtonInterrupted) {
                isGreenButtonInterrupted = false;
                __delay_ms(2);
                return button_isPressed(GreenButton);
            }
            break;

        default:
            break;
    }
    return false;
}
