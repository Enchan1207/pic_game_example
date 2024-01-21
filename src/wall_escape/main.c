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
    struct RenderObject* player = renderer_getRenderObjectByID(0x07);
    player->isVisible = true;
    player->type = PlayerObject;

    struct RenderObject* vWall = renderer_getRenderObjectByID(0x01);
    vWall->isVisible = true;
    vWall->type = VerticalWallObject;
    vWall->sx = 1;
    vWall->property.wall.holePosition = 0;
    vWall->property.wall.holeWidth = 2;

    struct RenderObject* hWall = renderer_getRenderObjectByID(0x02);
    hWall->isVisible = true;
    hWall->type = HorizontalWallObject;
    hWall->sy = 1;
    hWall->property.wall.holePosition = 0;
    hWall->property.wall.holeWidth = 5;

    while (true) {
        // ゲームティックに入ったら
        if (gametick_isTickEntered()) {
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
            player->sx = (stickX + 7) >> 1;
            player->sy = (stickY + 7) >> 1;

            if ((gametick_getTickCount() % 64) == 0) {
                vWall->property.wall.holePosition = (vWall->property.wall.holePosition + 1) % 16;
                hWall->property.wall.holePosition = (hWall->property.wall.holePosition + 1) % 16;
            }
        }
    }
}
