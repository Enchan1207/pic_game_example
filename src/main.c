//
// ドットマトリクスディスプレイの制御
//
#include <hardware/display.h>
#include <hardware/distsens.h>
#include <hardware/joystick.h>
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

    // ジョイスティックを初期化
    joystick_init();

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
    struct RenderObject* distobj = renderObjects;
    struct RenderObject* joyXobj = renderObjects + 1;
    struct RenderObject* joyYobj = renderObjects + 2;
    distobj->isVisible = true;
    joyXobj->isVisible = true;
    joyYobj->isVisible = true;
    distobj->height = 1;
    joyXobj->height = 1;
    joyYobj->height = 1;
    joyXobj->sy = 1;
    joyYobj->sy = 2;

    // 表示を開始
    display_setVisible(true);

    while (true) {
        // 各ペリフェラルの更新を要求
        distsens_requireUpdate();
        joystick_requireUpdate();

        // オブジェクトをレンダリング
        renderer_renderObjects(displayBuffer);

        // ジョイスティックの値を反映
        int8_t x = 0;
        int8_t y = 0;
        joystick_getPosition(&x, &y);
        joyXobj->width = x;
        joyYobj->width = y;

        // 距離センサの値を反映
        uint16_t distance = distsens_getDistance();
        distobj->width = distance >> 13;
    }
}
