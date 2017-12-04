#include "music_led_converter.h"

#include <math.h>

MusicLedConverter::MusicLedConverter() {
    mMaxAmplitude = 0;
}


void MusicLedConverter::convert(int bin, int freqAmpl) {
    if (freqAmpl > mMaxAmplitude) {
        mMaxAmplitude = freqAmpl;
    }

    double dAmplitude = 20*log(freqAmpl / mMaxAmplitude);

    int amplitude = (dAmplitude + 80) / 10;
    if (amplitude < 0) {
        amplitude = 0;
    }

    RGB color = {
        255, 0, 0
    };

    emit(newValue(bin, amplitude, color));
}
