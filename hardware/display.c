//
// ドットマトリクスディスプレイ
//
#include "display.h"

#include <xc.h>

/// @brief 表示バッファ
static uint8_t displayBuffer[8];

/**
 * @brief ディスプレイバッファの初期化
 */
static void _initDisplayBuffer(void);

/**
 * @brief 列消去
 */
static void _clearColumn(void);

/**
 * @brief 列出力内容設定
 *
 * @param data 出力内容
 */
static void _setColumnData(uint8_t data);

/**
 * @brief 表示列をシフト
 *
 * @param column
 */
static void _shiftColumn(uint8_t column);

void display_init(void) {
    // IO設定
    // 行ピン
    TRISA6 = 0;
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    TRISC5 = 0;
    TRISA7 = 0;
    TRISB1 = 0;
    TRISB2 = 0;
    ANSB1 = 0;
    ANSB2 = 0;

    // 列制御シフトレジスタ
    TRISA4 = 0;
    TRISA5 = 0;
    ANSA4 = 0;
    ANSA5 = 0;

    // 表示内容更新タイマ (Timer0)
    // クロック設定 1MHz
    TMR0CS = 0;

    // 分周比1 -> 256 - TMR0 (us) ごとに割込みがかかる
    // TMR0=131の場合125usごとに割込むので、8列表示するとちょうど1msで表示が完了することになる
    PSA = 1;
    TMR0 = 131;

    // ディスプレイバッファ初期化
    _initDisplayBuffer();
}

void display_setVisible(bool state) {
    TMR0IE = state;
    if (!state) {
        _clearColumn();
    }
}

void display_onUpdate(void) {
    static uint8_t column = 0;

    // 表示データ消去
    _clearColumn();

    // 行移動
    _shiftColumn(column);

    // 列に対応するデータを設定
    _setColumnData(displayBuffer[column]);

    // 次の列へ
    column = (column + 1) % 8;
}

uint8_t* display_getDrawBuffer(void) {
    return displayBuffer;
}

static void _initDisplayBuffer(void) {
    for (uint8_t n = 0; n < 8; n++) {
        displayBuffer[n] = 0;
    }
}

static void _clearColumn(void) {
    LATA6 = 0;
    LATC0 = 0;
    LATC1 = 0;
    LATC2 = 0;
    LATC5 = 0;
    LATA7 = 0;
    LATB1 = 0;
    LATB2 = 0;
}

static void _setColumnData(uint8_t data) {
    // ディスプレイ上方
    LATA6 = ((data & 0x80) ? 1 : 0);
    LATC0 = ((data & 0x40) ? 1 : 0);
    LATC1 = ((data & 0x20) ? 1 : 0);
    LATC2 = ((data & 0x10) ? 1 : 0);
    LATC5 = ((data & 0x08) ? 1 : 0);
    LATA7 = ((data & 0x04) ? 1 : 0);
    LATB1 = ((data & 0x02) ? 1 : 0);
    LATB2 = ((data & 0x01) ? 1 : 0);
    // ディスプレイの下方
}

static void _shiftColumn(uint8_t column) {
    // 最初だけ1を出力し、あとはゼロ -> 最初に入力した1が各行を伝わっていく
    LATA4 = column == 0;

    // 1bitシフトする
    LATA5 = 1;
    LATA5 = 0;
}