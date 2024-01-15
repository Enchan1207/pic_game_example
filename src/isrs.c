//
// ISR
//
#include <hardware/adc.h>
#include <hardware/display.h>
#include <xc.h>

#include "gametick.h"

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
}
