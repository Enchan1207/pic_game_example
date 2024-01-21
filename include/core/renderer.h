//
// オブジェクトレンダラ
//
#ifndef RENDERER_H
#define RENDERER_H

#include <stdbool.h>
#include <stdint.h>

#define RENDERER_MAX_OBJECT 8

/**
 * @brief オブジェクトタイプ
 */
typedef enum {
    /// @brief 矩形
    RectObject = 0,

    /// @brief 数値
    NumberObject = 1
} RenderObjectType;

/**
 * @brief 描画オブジェクト
 */
struct RenderObject {
    /// @brief オブジェクト表示/非表示
    bool isVisible;

    /// @brief オブジェクトタイプ
    RenderObjectType type;

    /// @brief 始点x
    int8_t sx;

    /// @brief 始点y
    int8_t sy;

    /// @brief オブジェクトプロパティ
    union ObjectProperty {
        /// @brief 矩形オブジェクト
        struct {
            /// @brief 幅
            uint8_t width : 4;

            /// @brief 高さ
            uint8_t height : 4;
        } rect;

        /// @brief 数値オブジェクト
        struct {
            /// @brief 表示する数値
            uint8_t value : 4;
        } number;
    } property;
};

/**
 * @brief オブジェクトレンダラを初期化
 */
void renderer_init(void);

/**
 * @brief オブジェクトレンダラが管理するオブジェクトリストへのポインタを返す
 *
 * @return struct RenderObject* オブジェクトリストへのポインタ
 */
struct RenderObject* renderer_getRenderObjects(void);

/**
 * @brief オブジェクトをバッファに描画
 */
void renderer_drawObjects(uint8_t* displayBuffer);

#endif /* RENDERER_H */
