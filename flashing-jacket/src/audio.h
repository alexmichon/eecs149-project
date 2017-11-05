
#ifndef AUDIO_H
#define AUDIO_H

//Mneumonics
#define HIGH 3
#define NORMAL 2

//Confirmed microphone low value, and max value
#define MIC_LOW 0.0
#define MIC_HIGH 737.0
/** Other macros */
//How many previous sensor values effects the operating average?
#define AVGLEN 5
//How many previous sensor values decides if we are on a peak/HIGH (e.g. in a song)
#define LONG_SECTOR 20

//How long do we keep the "current average" sound, before restarting the measuring
#define MSECS 30 * 1000
#define CYCLES MSECS / DELAY

/*Sometimes readings are wrong or strange. How much is a reading allowed
to deviate from the average to not be discarded? **/
#define DEV_THRESH 0.8

typedef struct {
	int r;
	int g;
	int b;
} RGB;


void audio_to_rgb(unsigned char *buffer, int buffer_size, long rate, RGB *leds, int leds_strips, int leds_columns);

#endif
