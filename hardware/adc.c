//
// AD変換器
//
#include "adc.h"

#include <xc.h>

/// @brief 最後にAD変換を要求されたチャネル
static volatile ADCChannel currentChannel = None;

/// @brief チャネル別AD変換結果
static volatile uint8_t _convResult[ADC_AVAILABLE_CHANNELS] = {0};

void adc_init(void) {
    // references: https://www.haljion.net/index.php/2019-11-13-03-27-18/118-2019-11-13-03-22-16/pic/213-a-d

    // ペリフェラルの接続
    //  - RA1: 距離センサ
    //  - RA2: x軸
    //  - RA3: y軸

    // ジョイスティックピンの入出力設定
    TRISA1 = 1;
    TRISA2 = 1;
    TRISA3 = 1;

    // アナログ入力の有効化
    ANSA1 = 1;
    ANSA2 = 1;
    ANSA3 = 1;

    // 変換周波数の設定 この設定では、1us@4MHz でAD変換できる
    ADCS2 = 1;
    ADCS1 = 0;
    ADCS0 = 0;

    // リファレンス電圧の設定 この設定では、上限Vdd, 下限Vssとなる
    ADPREF0 = 0;
    ADPREF1 = 0;
    ADNREF = 0;

    // 測定結果はレジスタ ADRESH/ADRESL に格納される
    // ADFMはこれを左右どちらに詰めるかの指定 ここでは左に詰めて上位(ADRESH)のみ用いる
    ADFM = 0;

    // ペリフェラル割込み、AD変換割込みを有効化
    INTCONbits.PEIE = 1;
    ADIE = 1;

    // ADコンバータを起動
    ADON = 1;
}

void adc_requestConversion(ADCChannel channel) {
    // 現在のAD変換が終了するまで待つ
    while (ADGO) {
    }

    // 一旦ADC割込みを止め、チャネルを設定
    ADIE = 0;
    ADIF = 0;
    currentChannel = channel;
    ADCON0bits.CHS = currentChannel;
    ADIE = 1;

    // AD変換開始
    ADGO = 1;
}

void adc_onUpdate(void) {
    // 選択中のチャネルが結果格納先の範囲外なら何もしない
    if (currentChannel < ADC_AVAILABLE_CHANNELS) {
        return;
    }

    // 現在のチャネルに対応する結果格納先を保存
    _convResult[currentChannel] = ADRESH;
}

uint8_t adc_getValue(ADCChannel channel) {
    // チャネルが結果格納先の範囲外なら何もしない
    if (channel < ADC_AVAILABLE_CHANNELS) {
        return 0x00;
    }
    return _convResult[channel];
}
