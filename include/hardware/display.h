//
// ドットマトリクスディスプレイ
//
#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief ディスプレイモジュール初期化
 */
void display_init(void);

/**
 * @brief 表示状態を設定
 *
 * @param state 状態(表示/非表示)
 * @note 表示を有効にするとタイマ0が動作を開始します。
 */
void display_setVisible(bool state);

/**
 * @brief 表示内容更新割込み
 * @note ISRから呼ばれることを想定しています。表示列をシフトし、ディスプレイに出力します。
 */
void display_onUpdate(void);

/**
 * @brief 描画バッファを取得
 *
 * @return uint8_t* 描画バッファへのポインタ
 */
uint8_t* display_getDrawBuffer(void);

#endif /* DISPLAY_H */
