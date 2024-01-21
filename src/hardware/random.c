//
// 乱数生成
//
#include "random.h"

#include <xc.h>

static uint32_t state = 0;

void random_init(void) {
    // 分周比1、割込み無効で起動
    T4CONbits.T4CKPS = 0x00;
    TMR4IE = 0;
    T4CONbits.TMR4ON = 1;
}

void random_initSeed(void) {
    // 4回TMR4を読み出してstateを設定
    for (uint8_t i = 0; i < 4; i++) {
        state = TMR4;
        state <<= 8;
    }
}

uint8_t random_next(void) {
    // XORShift32による乱数生成
    uint32_t x = state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state = x;

    return x & 0xFF;
}

uint8_t random_randRange(uint8_t min, uint8_t max) {
    int n = random_next() % (max - min + 1) + min;
    return (uint8_t)n;
}
