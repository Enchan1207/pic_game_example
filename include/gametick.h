//
// ゲームティック
//
#ifndef GAMETICK_H
#define GAMETICK_H

#include <stdint.h>

/**
 * @brief ゲームティックタイマを初期化
 */
void gametick_init(void);

/**
 * @brief ゲームティックを有効化
 * @note 内部で16ms周期、62.5FPSのタイマ2が起動します。
 */
void gametick_start(void);

/**
 * @brief ゲームティックを停止
 */
void gametick_stop(void);

/**
 * @brief ゲームティック更新要求をセット
 * @note ISRから呼び出すことを想定しています。ゲームティックに到達したことを示す内部フラグを立てます。
 */
void gametick_set(void);

/**
 * @brief 次のゲームティックに入っているか調べる
 *
 * @return bool
 */
bool gametick_isTickEntered(void);

/**
 * @brief ゲームティック到達まで同期
 */
void gametick_sync(void);

/**
 * @brief ゲームティック到達回数を取得
 *
 * @return uint16_t 到達回数
 */
uint16_t gametick_getTickCount(void);

#endif /* GAMETICK_H */
