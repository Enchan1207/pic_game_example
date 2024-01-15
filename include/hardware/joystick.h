//
// ジョイスティック
//
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>

/**
 * @brief ジョイスティックモジュールの初期化
 * @note 現在のAD変換が終了するまでブロックします。
 */
void joystick_init(void);

/**
 * @brief ジョイスティック値の更新を要求する
 * @note 現在のAD変換が終了するまでブロックします。
 */
void joystick_requireUpdate(void);

/**
 * @brief ジョイスティックの位置を取得する
 *
 * @param x x軸位置
 * @param y y軸位置
 *
 * @note 最後にAD変換した際の結果から位置を算出します。更新するには `joystick_requireUpdate` を呼び出してください。
 */
void joystick_getPosition(int8_t* x, int8_t* y);

#endif /* JOYSTICK_H */
