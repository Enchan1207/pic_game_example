//
// ドットマトリクスディスプレイの制御
//
#include <hardware/button.h>
#include <hardware/display.h>
#include <stdbool.h>
#include <string.h>
#include <xc.h>

#include "renderer.h"

void main(void) {
    // クロック設定
    OSCCONbits.IRCF = 0x0D;

    // LCD制御機能を無効化
    LCDEN = 0;

    // タクトスイッチ初期化
    button_init();

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

    while (true) {
        if (button_isPressed(RedButton)) {
            displayBuffer[0] = 0xFF;
        } else {
            displayBuffer[0] = 0x00;
        }

        if (button_isPressed(GreenButton)) {
            displayBuffer[1] = 0xFF;
        } else {
            displayBuffer[1] = 0x00;
        }

        if (button_isPressed(BlueButton)) {
            displayBuffer[2] = 0xFF;
        } else {
            displayBuffer[2] = 0x00;
        }
    }
}
