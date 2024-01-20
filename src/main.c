//
// ドットマトリクスディスプレイの制御
//
#include <hardware/button.h>
#include <hardware/display.h>
#include <hardware/distsens.h>
#include <hardware/joystick.h>
#include <stdbool.h>
#include <string.h>
#include <xc.h>

#include "gametick.h"
#include "renderer.h"

void main(void) {
    // クロック設定
    OSCCONbits.IRCF = 0x0D;

    // LCD制御機能を無効化
    LCDEN = 0;

    // ゲームティック初期化
    gametick_init();

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
    INTCONbits.PEIE = 1;

    // 表示の有効化
    display_setVisible(true);

    // 表示を開始
    display_setVisible(true);

    // ゲームティックを開始
    gametick_start();

    // 格納先
    int8_t stickX = 0;
    int8_t stickY = 0;
    uint16_t distance = 0;

    // オブジェクト初期化
    struct RenderObject* object = renderer_getRenderObjects();
    object->isVisible = true;
    object->width = 1;
    object->height = 1;

    while (true) {
        // オブジェクトを描画し、バッファの参照を切り替える
        uint8_t* displayBuffer = display_getDrawBuffer();
        memset(displayBuffer, 0x00, 8);
        renderer_drawObjects(displayBuffer);
        display_switchBuffer();

        // 各ペリフェラルの更新を要求
        distsens_requireUpdate();
        joystick_requireUpdate();

        // 値を更新
        joystick_getPosition(&stickX, &stickY);
        distsens_getDistance(&distance);

        // 移動
        object->sx = (stickX + 7) >> 1;
        object->sy = (stickY + 7) >> 1;

        // 1ゲームティックあたり16msなので、64回待つと大体1.024秒
        if (gametick_getTickCount() % 64 == 0) {
            object->width = (object->width + 1) % 4;
        }

        // 次のゲームティックに到達するまで待つ 割り込みは待機しない
        gametick_sync();
    }
}
