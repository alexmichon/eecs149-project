#include "audio.h"
#include <math.h>
#include <fftw3.h>
#include <QObject>
#include <stdint.h>
#include <qendian.h>


#define MAX_AMPLITUDE 40
#define MAX_VALUE 32000

void audio_to_rgb(unsigned char *buffer, int buffer_size, long rate, RGB *leds, int leds_strips, int leds_columns) {
    fftw_complex *in = (fftw_complex *) malloc(sizeof(fftw_complex) * buffer_size/2);
    for (int i = 0; i < buffer_size/2; i++) {
        in[i][0] = buffer[2*i];
        in[i][1] = buffer[2*i+1];
    }
    fftw_complex *out = (fftw_complex *) malloc(sizeof(fftw_complex) * buffer_size/2);
    fftw_plan plan = fftw_plan_dft_1d(buffer_size/2, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);


    double *levels = (double *) malloc(sizeof(double) * leds_strips);
    for (int i = 0; i < buffer_size/4; i++) {
        double mag = 2 * sqrt(out[i][0]*out[i][0] + out[i][1]*out[i][1]) / buffer_size;
        double freq = i * (double)rate / buffer_size/2;

        if (freq > 19 && freq <= 140) {
            if (mag > levels[0]) {
                levels[0] = mag;
            }
        }
        else if (freq > 140 && freq <= 400) {
            if (mag > levels[1]) {
                levels[1] = mag;
            }   
        }
        else if (freq > 400 && freq <= 2600) {
            if (mag > levels[2]) {
                levels[2] = mag;
            }   
        }
        else if (freq > 2600 && freq <= 5200) {
            if (mag > levels[3]) {
                levels[3] = mag;
            }   
        }
        else if (freq > 5200) {
            if (mag > levels[4]) {
                levels[4] = mag;
            }   
        }
    }

/*
    for (int i = 0; i < leds_strips; i++) {
        qDebug("Level %d: %.2f", i, levels[i]);
    }
*/
    for (int i = 0; i < leds_strips; i++) {
        levels[i] /= MAX_AMPLITUDE;
        if (levels[i] >= 1) { levels[i] = 1; }
    }

    for (int i = 0; i < leds_strips; i++) {
        for (int j = 0; j < leds_columns; j++) {
            leds[i*leds_columns + j].r = (int) (255 * (1 - pow(levels[i], leds_columns - j)));
            leds[i*leds_columns + j].g = (int) (255 * (1 - pow(levels[i], leds_columns - j)));
            leds[i*leds_columns + j].b = (int) (255 * (1 - pow(levels[i], leds_columns - j)));
        }
    }

    fftw_destroy_plan(plan);
    fftw_cleanup();
    free(in);
    free(out);
    free(levels);
}
