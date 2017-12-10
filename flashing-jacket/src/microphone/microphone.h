#ifndef MICROPHONE_H
#define MICROPHONE_H


#include <ArduinoSound.h>


#define HISTORY_SIZE 20

class Microphone {
public:
	Microphone(int fftSize, int nbBins, int maxHeights);

	bool available();
	void begin(int sampleRate);
	void read(int *amplitudes);

private:
	FFTAnalyzer * mFftAnalyzer;

	int mSpectrumSize;
	int *mSpectrum;

	int mNbBins;
	int mMaxHeight;
	double *mMagnitudes;

	int mNbPerBin;
	int *mCounters;

	double *mHistory[HISTORY_SIZE];
	int mHistoryIndex;

	int freqToBin(int freqIndex);
};

#endif