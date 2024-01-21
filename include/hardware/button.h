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

/**
 * @brief 特定のボタンに割り込みがあったことを通知する
 *
 * @param button
 * @note BlueButtonを引数に呼び出した場合は何もしません。ISRでの実行を想定しています。
 */
void button_setInterrupted(Button button);

/**
 * @brief 特定のボタンの外部割り込みがあったかを返す
 *
 * @param button
 * @note BlueButtonを引数に呼び出した場合は常にfalseが返ります。
 */
bool button_isTyped(Button button);

#endif /* BUTTON_H */
