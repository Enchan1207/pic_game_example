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

#endif /* RANDOM_H */
