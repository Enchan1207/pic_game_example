//
// ジョイスティック
//
#include "joystick.h"

#include "adc.h"

void joystick_init(void) {
    adc_init();
    adc_requestConversion(JoyStickX);
    adc_requestConversion(JoyStickY);
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
    uint8_t rawX = adc_getValue(JoyStickX);
    uint8_t rawY = adc_getValue(JoyStickY);

    // TODO: 変換式
}
