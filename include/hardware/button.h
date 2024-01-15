//
// タクトスイッチ
//
#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

/**
 * @brief ボタンタイプ
 */
typedef enum {

    /// @brief 赤ボタン
    RedButton,

    /// @brief 緑ボタン
    GreenButton,

    /// @brief 青ボタン
    BlueButton
} Button;

/**
 * @brief タクトスイッチモジュールを初期化
 */
void button_init(void);

/**
 * @brief 特定のボタンの状態を調べる
 *
 * @param button ボタン
 * @return bool 押されているかどうか
 */
bool button_isPressed(Button button);

#endif /* BUTTON_H */
