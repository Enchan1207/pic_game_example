//
// 乱数生成器
//
#ifndef RANDOM_H
#define RANDOM_H

#include <stdint.h>

/**
 * @brief 乱数生成器の初期化
 * @note 乱数初期シードを決定するためタイマ4が起動します。
 */
void random_init(void);

/**
 * @brief 乱数シードの初期化
 * @note 呼び出された時点のタイマの値からシードを生成します。
 */
void random_initSeed(void);

/**
 * @brief 乱数を生成して返す
 *
 * @return uint8_t 生成結果
 */
uint8_t random_next(void);

/**
 * @brief ある範囲の乱数を生成する
 *
 * @param min 最小値
 * @param max 最大値
 * @return uint8_t 生成結果
 */
uint8_t random_randRange(uint8_t min, uint8_t max);

#endif /* RANDOM_H */
