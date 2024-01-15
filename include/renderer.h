//
// オブジェクトレンダラ
//
#ifndef RENDERER_H
#define RENDERER_H

#include <stdbool.h>
#include <stdint.h>

#define RENDERER_MAX_OBJECT 8

/**
 * @brief 描画オブジェクト
 */
struct RenderObject {
    /// @brief オブジェクト表示/非表示
    bool isVisible;

    /// @brief 始点x
    int8_t sx;

    /// @brief 始点y
    int8_t sy;

    /// @brief 幅
    uint8_t width : 4;

    /// @brief 高さ
    uint8_t height : 4;
};

extern struct RenderObject renderObjects[RENDERER_MAX_OBJECT];

/**
 * @brief オブジェクトレンダラを初期化
 */
void renderer_init(void);

/**
 * @brief オブジェクトをバッファにレンダリング
 */
void renderer_renderObjects(uint8_t* displayBuffer);

#endif /* RENDERER_H */
