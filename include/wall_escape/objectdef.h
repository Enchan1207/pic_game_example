//
// オブジェクトID定義
//
#ifndef OBJECT_DEF_H
#define OBJECT_DEF_H

#include <stdint.h>

/**
 * @brief オブジェクトID
 */
typedef enum {
    /// @brief プレイヤーのオブジェクトID
    playerObject = 0x00,

    /// @brief 水平壁1のオブジェクトID
    hWall1Object = 0x01,

    /// @brief 水平壁2のオブジェクトID
    hWall2Object = 0x02,

    /// @brief 垂直壁1のオブジェクトID
    vWall1Object = 0x03,

    /// @brief 垂直壁2のオブジェクトID
    vWall2Object = 0x04,

    /// @brief スコア10の位のオブジェクトID
    score10Object = 0x05,

    /// @brief スコア1の位のオブジェクトID
    score1Object = 0x06,

} ObjectIDType;

#endif /* OBJECT_DEF_H */
