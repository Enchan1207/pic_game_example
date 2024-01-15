//
// ドットマトリクスディスプレイの制御
//
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

    // オブジェクトを初期化
    for (uint8_t i = 0; i < RENDERER_MAX_OBJECT; i++) {
        struct RenderObject* obj = renderObjects + i;
        obj->isVisible = true;
        obj->sx = i >> 1;
        obj->sy = i;
        obj->width = 1;
        obj->height = 1;
    }

    // 表示を開始
    display_setVisible(true);

    // タイマ6を計時機として構成し、開始
    // ソースクロック1MHz, 分周比64 -> 64usごとにカウントアップ
    T6CONbits.T6CKPS = 3;
    PR6 = 0xFF;
    T6CONbits.TMR6ON = 1;
    TMR6IE = 1;

    // オブジェクトをレンダリング
    renderer_renderObjects(displayBuffer);

    // レンダリングが終了したところで止めてTMRレジスタをディスプレイバッファに書き出す
    T6CONbits.TMR6ON = 0;
    displayBuffer[6] = TMR6IF;
    displayBuffer[7] = TMR6;

    while (true) {
    }
}
