//
// オブジェクトレンダラ
//
#include "renderer.h"

#include <stdio.h>

/// @brief オブジェクトリスト
struct RenderObject objects[RENDERER_MAX_OBJECT];

/// @brief 数列パターン
static const uint8_t numPattern[16][3] = {
    {0x6C, 0x82, 0x6C},  // 0
    {0x00, 0x00, 0xFE},  // 1
    {0x8C, 0x92, 0x62},  // 2
    {0x92, 0x92, 0x6C},  // 3
    {0xE0, 0x10, 0xFC},  // 4
    {0x62, 0x92, 0x8C},  // 5
    {0x7C, 0x92, 0x8C},  // 6
    {0x80, 0x80, 0x7C},  // 7
    {0x6C, 0x92, 0x6C},  // 8
    {0x60, 0x92, 0x7C},  // 9
    {0x7E, 0x90, 0x7E},  // A
    {0x6C, 0x12, 0x0C},  // B
    {0x7C, 0x82, 0x82},  // C
    {0x0C, 0x12, 0x6C},  // D
    {0x6C, 0x92, 0x92},  // E
    {0x6C, 0x90, 0x90},  // F
};

void renderer_init(void) {
    for (uint8_t i = 0; i < RENDERER_MAX_OBJECT; i++) {
        objects[i].isVisible = false;
        objects[i].sx = 0;
        objects[i].sy = 0;
    }
}

/**
 * @brief 値をクリップする
 *
 * @param n 値
 * @param min 最小値
 * @param max 最大値
 *
 * @return int8_t
 */
static int8_t _clipValue(int8_t n, int8_t min, int8_t max) {
    if (n < min) {
        return min;
    }
    if (n > max) {
        return max;
    }
    return n;
}

/**
 * @brief プレイヤーを描画
 *
 * @param displayBuffer ディスプレイバッファ
 * @param obj 描画対象のオブジェクト
 */
static void _drawPlayer(uint8_t* displayBuffer, const struct RenderObject* obj) {
    // 描画範囲外なら戻る
    if (obj->sx < 0 || obj->sy < 0) {
        return;
    }

    displayBuffer[obj->sx] |= 1 << (7 - obj->sy);
}

/**
 * @brief 垂直壁を描画
 *
 * @param displayBuffer ディスプレイバッファ
 * @param obj 描画対象のオブジェクト
 */
static void _drawVerticalWall(uint8_t* displayBuffer, const struct RenderObject* obj) {
    // 描画範囲外なら戻る
    if (obj->sx < 0) {
        return;
    }

    // オブジェクトプロパティから壁の形状を把握
    uint8_t startY = (uint8_t)_clipValue(obj->property.wall.holePosition, 0, 8);
    uint8_t endY = (uint8_t)_clipValue((int8_t)(obj->property.wall.holePosition + obj->property.wall.holeWidth), 0, 8);
    uint8_t wallShape = (uint8_t)(((1 << (endY - startY)) - 1) << (8 - endY));

    // 高さゼロなら戻る
    if (endY - startY == 0) {
        displayBuffer[obj->sx] = 0xFF;
        return;
    }

    // 描画 今作った1の列が穴になるのでビット反転
    displayBuffer[obj->sx] = ~wallShape;
}

/**
 * @brief 水平壁を描画
 *
 * @param displayBuffer ディスプレイバッファ
 * @param obj 描画対象のオブジェクト
 */
static void _drawHorizontalWall(uint8_t* displayBuffer, const struct RenderObject* obj) {
    // 描画範囲外なら戻る
    if (obj->sy < 0) {
        return;
    }

    // 穴の形状を把握
    uint8_t startX = (uint8_t)_clipValue(obj->property.wall.holePosition, 0, 8);
    uint8_t endX = (uint8_t)_clipValue((int8_t)(obj->property.wall.holePosition + obj->property.wall.holeWidth), 0, 8);
    uint8_t wallShape = (uint8_t)(1 << (7 - obj->sy - 1));

    // 反映していく
    for (uint8_t x = 0; x < 8; x++) {
        if (x >= startX && x < endX) {
            displayBuffer[x] &= ~wallShape;
        } else {
            displayBuffer[x] |= wallShape;
        }
    }
}

/**
 * @brief 数値を描画
 *
 * @param displayBuffer ディスプレイバッファ
 * @param obj 描画するオブジェクト
 */
static void _drawNumber(uint8_t* displayBuffer, const struct RenderObject* obj) {
    // 描画範囲を取得 数値は 3*7
    uint8_t startX = (uint8_t)_clipValue(obj->sx, 0, 7);
    uint8_t endX = (uint8_t)_clipValue(obj->sx + 3, 0, 8);

    for (uint8_t x = startX; x < endX; x++) {
        // 相対描画位置を取得して出力
        uint8_t colIndex = x - startX;
        displayBuffer[x] |= numPattern[obj->property.number.value][colIndex];
    }
}

struct RenderObject* renderer_getRenderObjects(void) {
    return objects;
}

struct RenderObject* renderer_getRenderObjectByID(uint8_t id) {
    if (id >= RENDERER_MAX_OBJECT) {
        return NULL;
    }
    return objects + id;
}

struct RenderObject* renderer_getFreeObject(void) {
    for (uint8_t i = 0; i < RENDERER_MAX_OBJECT; i++) {
        struct RenderObject* obj = objects + i;
        if (!obj->isVisible) {
            // 確保して描画範囲外に置いておく
            obj->sx = 10;
            obj->sy = 10;
            obj->isVisible = true;
            return obj;
        }
    }
    return NULL;
}

void renderer_drawObjects(uint8_t* displayBuffer) {
    for (uint8_t i = 0; i < RENDERER_MAX_OBJECT; i++) {
        struct RenderObject* obj = objects + i;
        // 非表示オブジェクトなら飛ばす
        if (!obj->isVisible) {
            continue;
        }

        // 範囲外なら飛ばす
        if (obj->sx > 7 || obj->sy > 7) {
            continue;
        }

        // タイプで分岐
        switch (obj->type) {
            case PlayerObject:
                _drawPlayer(displayBuffer, obj);
                break;

            case VerticalWallObject:
                _drawVerticalWall(displayBuffer, obj);
                break;

            case HorizontalWallObject:
                _drawHorizontalWall(displayBuffer, obj);
                break;

            case NumberObject:
                _drawNumber(displayBuffer, obj);
                break;
        }
    }
}
