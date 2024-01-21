//
// 避けゲー
//
#include <stdbool.h>
#include <string.h>
#include <xc.h>

#include "app/collision.h"
#include "app/state.h"
#include "app/wall.h"
#include "core/gametick.h"
#include "core/renderer.h"
#include "hardware/button.h"
#include "hardware/display.h"
#include "hardware/distsens.h"
#include "hardware/joystick.h"
#include "hardware/random.h"

void main(void) {
    // クロック設定
    OSCCONbits.IRCF = 0x0D;

    // LCD制御機能を無効化
    LCDEN = 0;

    // 各モジュールの初期化
    button_init();
    gametick_init();
    joystick_init();
    distsens_init();
    display_init();
    renderer_init();
    random_init();
    wall_init();

    // グローバル割り込み有効化
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;

    // 表示の有効化, ゲームティック開始
    display_setVisible(true);
    gametick_start();

    // ゲームステート
    GameStateType gameState = Ready;

    // ジョイスティックの値
    int8_t stickX = 0;
    int8_t stickY = 0;

    // 距離センサの値
    uint16_t distance = 0;

    // プレイヤーオブジェクト
    struct RenderObject* player = renderer_getRenderObjectByID(0x07);
    player->isVisible = true;
    player->type = PlayerObject;

    // ゲームループ
    while (true) {
        // オブジェクトを描画し、バッファの参照を切り替える
        uint8_t* displayBuffer = display_getDrawBuffer();
        memset(displayBuffer, 0x00, 8);
        renderer_drawObjects(displayBuffer);
        display_switchBuffer();

        // プレイヤーの位置を更新
#ifndef FLAPPY_BIRD
        joystick_requireUpdate();
        joystick_getPosition(&stickX, &stickY);
        player->sx = (stickX + 7) >> 1;
        player->sy = (stickY + 7) >> 1;
#else
        distsens_requireUpdate();
        distsens_getDistance(&distance);
        player->sx = 2;
        uint8_t dist = ((distance & 0xFF) >> 5) - 1;
        if (dist > 7) {
            dist = 7;
        }
        player->sy = (int8_t)dist;
#endif

        // ゲームステートによって分岐
        switch (gameState) {
            case Ready:
                // プレイヤーを表示
                player->isVisible = true;

                // キー入力待ち
                if (!button_isTyped(RedButton)) {
                    break;
                }

                // 乱数シードを設定
                random_initSeed();

                gameState = Playing;
                break;

            case Playing:
                // 壁の位置を更新
                wall_updateWalls();

                // 壁にぶつかったらステート分岐
                if (isPlayerCollidedWall()) {
                    gameState = Gameover;
                    break;
                }

                // スポーンレートごとに壁オブジェクトを生成
                if ((gametick_getTickCount() % wall_getSpawnRate()) == 0) {
                    wall_generateNewWall();
                }
                break;

            case Gameover:
                // プレイヤーを隠す
                player->isVisible = false;

                // キー入力待ち
                if (!button_isTyped(RedButton)) {
                    break;
                }

                // オブジェクトテーブルをクリア
                for (uint8_t i = 0; i < RENDERER_MAX_OBJECT; i++) {
                    struct RenderObject* obj = renderer_getRenderObjectByID(i);
                    obj->isVisible = false;
                    obj->sx = -1;
                    obj->sy = -1;
                }

                // 壁の状態をリセット
                wall_init();

                // 状態遷移
                gameState = Ready;
                break;
        }

        // ゲームティック同期
        gametick_sync();
    }
}
