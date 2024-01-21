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
    /// @brief プレイヤー
    PlayerObject,

    /// @brief 垂直壁
    VerticalWallObject,

    /// @brief 水平壁
    HorizontalWallObject,

    /// @brief 数値
    NumberObject
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
        /// @brief 数値オブジェクト
        struct {
            /// @brief 表示する数値
            uint8_t value : 4;
        } number;

        /// @brief 壁オブジェクト
        struct {
            /// @brief 穴の相対位置
            uint8_t holePosition : 4;

            /// @brief 穴の大きさ
            uint8_t holeWidth : 4;

            /// @brief 速度
            uint8_t speed;
        } wall;
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
 * @brief IDを指定してオブジェクトへのポインタを取得
 *
 * @param id オブジェクトID
 * @return struct RenderObject* オブジェクトへのポインタ
 *
 * @note 範囲外参照に対してはNULLを返します。
 */
struct RenderObject* renderer_getRenderObjectByID(uint8_t id);

/**
 * @brief フリーの描画オブジェクトを探して返す
 *
 * @return struct RenderObject* オブジェクトへのポインタ
 *
 * @note 内部オブジェクトテーブルがいっぱいの場合はnullが返ります。
 */
struct RenderObject* renderer_getFreeObject(void);

/**
 * @brief オブジェクトをバッファに描画
 */
void renderer_drawObjects(uint8_t* displayBuffer);

#endif /* RENDERER_H */
