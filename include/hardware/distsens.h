//
// 距離センサ
//
#ifndef DISTSENS_H
#define DISTSENS_H

#include <stdint.h>

/**
 * @brief 距離センサモジュールの初期化
 * @note 現在のAD変換が終了するまでブロックします。
 */
void distsens_init(void);

/**
 * @brief 距離センサ値の更新を要求する
 * @note 現在のAD変換が終了するまでブロックします。
 */
void distsens_requireUpdate(void);

/**
 * @brief 距離センサの値を取得する
 *
 * @return uint16_t 測距結果
 * @note 最後にAD変換した際の結果から距離を算出します。更新するには `distsens_requireUpdate` を呼び出してください。
 */
uint16_t distsens_getDistance(void);

#endif /* DISTSENS_H */
