//
// AD変換器
//
#ifndef ADC_H
#define ADC_H

#include <stdint.h>

/// @brief 有効なADCチャネル数
#define ADC_AVAILABLE_CHANNELS 4

/**
 * @brief AD変換チャネル
 */
typedef enum {
    /// @brief 距離センサ
    DistanceSensor = 1,

    /// @brief ジョイスティックX軸
    JoyStickX = 2,

    /// @brief ジョイスティックY軸
    JoyStickY = 3,

    /// @brief 何のチャネルも指定されていない
    None = 0xFF
} ADCChannel;

/**
 * @brief AD変換器を初期化
 */
void adc_init(void);

/**
 * @brief 指定したチャネルのAD変換を要求
 *
 * @param channel チャネル
 * @note 現在行われているAD変換が完了するまでブロックされます。
 */
void adc_requestConversion(ADCChannel channel);

/**
 * @brief ADC更新割込み
 * @note ISRから呼ばれることを想定しています。現在選択されているチャネルに対応する計測結果を更新します。
 */
void adc_onUpdate(void);

/**
 * @brief 最後にAD変換した値を返す
 *
 * @param channel チャネル
 * @return uint8_t 最新の変換結果
 *
 * @note 値の更新には adc_requestConversion を呼び出してください。範囲外のチャネルが指定された場合は0が返ります。
 */
uint8_t adc_getLastValueByChannel(ADCChannel channel);

#endif /* ADC_H */
