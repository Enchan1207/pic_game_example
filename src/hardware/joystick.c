//
// ジョイスティック
//
#include "joystick.h"

#include "adc.h"

void joystick_init(void) {
    adc_init();
    joystick_requireUpdate();
}

void joystick_requireUpdate(void) {
    adc_requestConversion(JoyStickX);
    adc_requestConversion(JoyStickY);
}

/**
 * @brief ジョイスティックの位置を取得する
 *
 * @param x x軸位置
 * @param y y軸位置
 *
 * @note 最後にAD変換した際の結果から位置を算出します。更新するには `joystick_requireUpdate` を呼び出してください。
 */
void joystick_getPosition(int8_t* x, int8_t* y) {
    // ADCから値を持ってきて上位4bitを持ってくる y軸は上下逆なのでflip
    uint8_t rawX = (adc_getValue(JoyStickX) >> 4);
    uint8_t rawY = 0x0F - (adc_getValue(JoyStickY) >> 4);

    // 値を -7 ~ +7 にスケーリング
    *x = (int8_t)rawX - 7;
    *y = (int8_t)rawY - 7;
}
