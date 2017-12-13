#ifndef MICROPHONE_H
#define MICROPHONE_H


#include <ArduinoSound.h>


#define HISTORY_SIZE 20

class Microphone {
public:
	Microphone(int fftSize, uint8_t nbBins, uint8_t maxHeights);

	bool available();
	void begin(int sampleRate);
	void read(uint8_t *amplitudes);

private:
	FFTAnalyzer * mFftAnalyzer;

	int mSpectrumSize;
	int *mSpectrum;

	uint8_t mNbBins;
	uint8_t mMaxHeight;
	double *mMagnitudes;

	uint8_t mNbPerBin;
	uint8_t *mCounters;

	double *mHistory[HISTORY_SIZE];
	uint16_t mHistoryIndex;

	int freqToBin(int freqIndex);
};

#endif