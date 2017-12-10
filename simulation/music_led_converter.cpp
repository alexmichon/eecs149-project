#include "music_led_converter.h"

#include <math.h>

MusicLedConverter::MusicLedConverter() {
    mMaxAmplitude = 0;
}


void MusicLedConverter::convert(int bin, int *amplitude) {
    RGB color = {
        255, 0, 0
    };

    //emit(newValue(bin, color));
}
