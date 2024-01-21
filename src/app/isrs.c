//
// ISR
//
#include <xc.h>

#include "core/gametick.h"
#include "hardware/adc.h"
#include "hardware/button.h"
#include "hardware/display.h"

void __interrupt() Interrupt_interrupt(void) {
    // ディスプレイ描画更新タイマ
    if (TMR0IF) {
        display_onUpdate();
        TMR0IF = 0;
    }

    // AD変換器
    if (ADIF) {
        adc_onUpdate();
        ADIF = 0;
    }

    // ゲームティック
    if (TMR2IF) {
        gametick_set();
        TMR2IF = 0;
    }

    // 赤ボタン
    if (IOCBFbits.IOCBF3) {
        button_setInterrupted(RedButton);
        IOCBFbits.IOCBF3 = 0;
    }

    // 緑ボタン
    if (IOCBFbits.IOCBF4) {
        button_setInterrupted(GreenButton);
        IOCBFbits.IOCBF4 = 0;
    }
}
