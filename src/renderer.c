//
// オブジェクトレンダラ
//
#include "renderer.h"

/// @brief オブジェクトリスト
struct RenderObject objects[RENDERER_MAX_OBJECT];

void renderer_init(void) {
    for (uint8_t i = 0; i < RENDERER_MAX_OBJECT; i++) {
        objects[i].isVisible = false;
        objects[i].sx = 0;
        objects[i].sy = 0;
        objects[i].width = 0;
        objects[i].height = 0;
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
 * @brief オブジェクトをディスプレイバッファに描画
 *
 * @param displayBuffer ディスプレイバッファ
 * @param obj 描画対象のオブジェクト
 */
static void _renderer_renderObject(uint8_t* displayBuffer, const struct RenderObject* obj) {
    // 範囲外なら描画しない
    if (obj->sx > 7 || obj->sy > 7) {
        return;
    }

    // 実際に描画される範囲を特定
    uint8_t startX = (uint8_t)_clipValue(obj->sx, 0, 7);
    uint8_t endX = (uint8_t)_clipValue(obj->sx + obj->width, 0, 8);
    uint8_t startY = (uint8_t)_clipValue(obj->sy, 0, 7);
    uint8_t endY = (uint8_t)_clipValue(obj->sy + obj->height, 0, 8);

    // 描画サイズがゼロなら何もせず戻る
    if (endX - startX == 0 || endY - startY == 0) {
        return;
    }

    // バッファに反映
    for (uint8_t x = startX; x < endX; x++) {
        // y軸の終点-始点から1の数を求め、その分だけビットを立てた数値を生成
        // height=3 の場合、1<<3 は 0b01000 1引いて 0b0111
        // このままだとy軸が上下逆になってしまうので、差分を左シフト
        displayBuffer[x] |= ((uint8_t)(1 << (endY - startY)) - 1) << (8 - endY);
    }
}

struct RenderObject* renderer_getRenderObjects(void) {
    return objects;
}

void renderer_drawObjects(uint8_t* displayBuffer) {
    for (uint8_t i = 0; i < RENDERER_MAX_OBJECT; i++) {
        struct RenderObject* obj = objects + i;
        // 非表示オブジェクトなら飛ばす
        if (!obj->isVisible) {
            continue;
        }
        _renderer_renderObject(displayBuffer, obj);
    }
}
