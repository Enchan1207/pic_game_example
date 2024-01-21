//
// ゲームステート
//
#ifndef STATE_H
#define STATE_H

/**
 * @brief ゲームステート
 */
typedef enum {

    /// @brief 準備完了
    Ready,

    /// @brief ゲームプレイ中
    Playing,

    /// @brief ゲームオーバー
    Gameover
} GameStateType;

#endif /* STATE_H */
