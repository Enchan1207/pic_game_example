//
// ドットマトリクスディスプレイの制御
//
#include <hardware/display.h>
#include <hardware/distsens.h>
#include <stdbool.h>
#include <string.h>
#include <xc.h>

#include "renderer.h"

void main(void) {
    // クロック設定
    OSCCONbits.IRCF = 0x0D;

    // LCD制御機能を無効化
    LCDEN = 0;

    // 距離センサを初期化
    distsens_init();

    // ディスプレイモジュールを初期化
    display_init();

    // オブジェクトレンダラ初期化
    renderer_init();

    // グローバル割り込み有効化
    INTCONbits.GIE = 1;

    // 表示の有効化
    display_setVisible(true);

    // 描画バッファ取得
    uint8_t* displayBuffer = display_getDrawBuffer();

    // オブジェクト初期化
    struct RenderObject* obj = renderObjects;
    obj->isVisible = true;
    obj->height = 1;

    // 表示を開始
    display_setVisible(true);

    while (true) {
        // 距離センサ値の更新を要求
        distsens_requireUpdate(DistanceSensor);

        // オブジェクトをレンダリング
        renderer_renderObjects(displayBuffer);

        // 最後に取得した値を反映
        uint16_t distance = distsens_getDistance();
        obj->width = distance >> 13;
    }
}
