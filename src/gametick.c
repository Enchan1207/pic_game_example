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

    // タイマを開始(割り込みは許可しない)
    TMR2IE = 0;
    T2CONbits.TMR2ON = 1;
}

void gametick_start(void) {
    TMR2IE = 1;
}

void gametick_stop(void) {
    TMR2IE = 0;
}

void gametick_set(void) {
    isTickEntered = true;
    tickCount++;
}

void gametick_isTickEntered(void) {
    return isTickEntered;
}

void gametick_sync(void) {
    while (!isTickEntered) {
    }
    isTickEntered = false;
}

uint16_t gametick_getTickCount(void) {
    return tickCount;
}
