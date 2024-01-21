//
// オブジェクトとの衝突
//

#include "app/collision.h"

#include "core/renderer.h"

bool isPlayerCollidedWall(void) {
    // プレイヤーオブジェクト
    struct RenderObject* player = renderer_getRenderObjectByID(0x07);

    // オブジェクトリストを走査
    for (uint8_t i = 0; i < RENDERER_MAX_OBJECT; i++) {
        // 表示中のオブジェクトを探す
        struct RenderObject* obj = renderer_getRenderObjectByID(i);
        if (!obj->isVisible) {
            continue;
        }

        uint8_t holePos = obj->property.wall.holePosition;
        uint8_t holeWidth = obj->property.wall.holeWidth;

        // オブジェクトタイプ分岐
        switch (obj->type) {
            case VerticalWallObject:
                // プレイヤーとx座標が同じ?
                if (obj->sx != player->sx) {
                    break;
                }

                // y座標は穴の範囲内?
                if (player->sy >= holePos && player->sy < (holePos + holeWidth)) {
                    break;
                }
                return true;

            case HorizontalWallObject:
                // プレイヤーとy座標が同じ?
                if (obj->sy != player->sy) {
                    break;
                }

                // x座標は穴の範囲内?
                if (player->sx >= holePos && player->sx < (holePos + holeWidth)) {
                    break;
                }
                return true;

            default:
                break;
        }
    }
    return false;
}
