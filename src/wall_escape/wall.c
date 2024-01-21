//
// 壁の生成と移動
//
#include "wall_escape/wall.h"

#include <stdio.h>

#include "core/gametick.h"
#include "core/renderer.h"
#include "hardware/random.h"

/// @brief 通過した壁の個数
static uint8_t passedCount;

/// @brief 壁のスポーンレート
static uint8_t spawnRate;

/// @brief 壁のスピード
static uint8_t wallSpeed;

void wall_init(void) {
    passedCount = 0;
    wallSpeed = 24;
    spawnRate = 128;
}

bool wall_generateNewWall(void) {
    // オブジェクトテーブルから借用
    struct RenderObject* obj = renderer_getFreeObject();
    if (obj == NULL) {
        return false;
    }

    // タイプと速度を設定し、初期位置に移動
    obj->type = (random_next() % 2) == 0 ? VerticalWallObject : HorizontalWallObject;
    obj->sx = 0;
    obj->sy = 0;
    int8_t* objPos = obj->type == VerticalWallObject ? &(obj->sx) : &(obj->sy);
    *objPos = 8;
    obj->property.wall.holeWidth = random_randRange(2, 4);
    obj->property.wall.holePosition = random_randRange(0, 7 - obj->property.wall.holeWidth);
    obj->property.wall.speed = wallSpeed;
    obj->isVisible = true;
    return true;
}

uint8_t wall_getPassedCount(void) {
    return passedCount;
}

uint8_t wall_getSpawnRate(void) {
    return spawnRate;
}

void wall_updateWalls(void) {
    // オブジェクトテーブルを走査
    for (uint8_t i = 0; i < RENDERER_MAX_OBJECT; i++) {
        // 表示中の壁オブジェクトを探す
        struct RenderObject* obj = renderer_getRenderObjectByID(i);
        if (obj->type != VerticalWallObject && obj->type != HorizontalWallObject) {
            continue;
        }
        if (!obj->isVisible) {
            continue;
        }

        // ゲームティックが周期と一致するなら動かす
        uint8_t speed = obj->property.wall.speed;
        if (gametick_getTickCount() % speed != 0) {
            continue;
        }
        int8_t* objPos = obj->type == VerticalWallObject ? &(obj->sx) : &(obj->sy);
        *objPos -= 1;

        // 範囲外に行ったらオブジェクトをリリースし、カウントアップ
        if (*objPos < 0) {
            obj->isVisible = false;
            passedCount++;
        }

        // 通過数に応じてレベルが上がる
        if (passedCount % 4 == 0) {
            // スポーンレートは最大で32まで
            spawnRate--;
            if (spawnRate < 32) {
                spawnRate = 32;
            }

            // スピードは最大で8まで上昇する
            wallSpeed--;
            if (wallSpeed < 8) {
                wallSpeed = 8;
            }
        }
    }
}
