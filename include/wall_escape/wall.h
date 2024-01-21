//
// 壁の生成と移動
//
#ifndef WALL_H
#define WALL_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief 壁生成器を初期化
 */
void wall_init(void);

/**
 * @brief 新しい壁オブジェクトを生成
 *
 * @return true 生成結果
 * @note レンダリングオブジェクトテーブルからオブジェクトを割り当てます。テーブルがいっぱいの場合はfalseが返ります。
 */
bool wall_generateNewWall(void);

/**
 * @brief 通過した壁の数を返す
 *
 * @return uint8_t
 */
uint8_t wall_getPassedCount(void);

/**
 * @brief 壁の出現頻度を返す
 *
 * @return uint8_t
 */
uint8_t wall_getSpawnRate(void);

/**
 * @brief 壁オブジェクトを更新
 * @note ゲームティックごとに呼ばれることを想定しています。壁オブジェクトの位置を更新します。
 */
void wall_updateWalls(void);

#endif /* WALL_H */
