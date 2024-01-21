//
// ゲームティック
//
#include "gametick.h"

#include <stdbool.h>
#include <xc.h>

/// @brief ゲームティックに達したかどうか
static bool isTickEntered = false;

/// @brief ティック到達回数
static uint16_t tickCount = 0;

void gametick_init(void) {
    // ソースクロック1MHz, プリスケーラで64分周
    T2CONbits.T2CKPS = 3;

    // コンペアマッチするまでの値を設定 -> 250 * 64 = 16000us = 16msごとに割り込み
    PR2 = 249;

    // タイマ割り込みを有効化
    TMR2IE = 1;
}

void gametick_start(void) {
    T2CONbits.TMR2ON = 1;
}

void gametick_stop(void) {
    T2CONbits.TMR2ON = 0;
}

void gametick_set(void) {
    isTickEntered = true;
    tickCount++;
}

bool gametick_isTickEntered(void) {
    if (isTickEntered) {
        isTickEntered = false;
        return true;
    }
    return false;
}

void gametick_sync(void) {
    while (!isTickEntered) {
    }
    isTickEntered = false;
}

uint16_t gametick_getTickCount(void) {
    return tickCount;
}
