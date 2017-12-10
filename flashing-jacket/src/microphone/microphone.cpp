#include "microphone.h"
#include <math.h>

Microphone::Microphone(int fftSize, int nbBins, int maxHeight) {
  mFftAnalyzer = new FFTAnalyzer(fftSize);
  mSpectrumSize = fftSize / 2;
  mSpectrum = (int *) malloc(sizeof(int) * mSpectrumSize);

  mNbBins = nbBins;
  mMaxHeight = maxHeight;
  mMagnitudes = (double *) malloc(sizeof(double) * mNbBins);

  mCounters = (int *) malloc(sizeof(int) * mNbBins);
  mNbPerBin = mSpectrumSize / (mNbBins - 1);

  for (int i = 0; i < HISTORY_SIZE; i++) {
    mHistory[i] = (double *) malloc(sizeof(double) * mNbBins);
  }
  mHistoryIndex = 0;
}

void Microphone::begin(int sampleRate) {
  // setup the I2S audio input for the sample rate with 32-bits per sample
  if (!AudioInI2S.begin(sampleRate, 32)) {
    Serial.println("Failed to initialize I2S input!");
    while (1); // do nothing
  }

  // configure the I2S input as the input for the FFT analyzer
  if (!mFftAnalyzer->input(AudioInI2S)) {
    Serial.println("Failed to set FFT analyzer input!");
    while (1); // do nothing
  }
}

bool Microphone::available() {
  return mFftAnalyzer->available();
}

int Microphone::freqToBin(int freqIndex) {
  return freqIndex / mNbPerBin;
}

void Microphone::read(int *amplitudes) {
  // read the new spectrum
  mFftAnalyzer->read(mSpectrum, mSpectrumSize);

  for (int i = 0; i < mNbBins; i++) {
    mMagnitudes[i] = 0;
    mCounters[i] = 0;
  }

  // print out the spectrum
  for (int i = 0; i < mSpectrumSize; i++) {
    if (mSpectrum[i] > 0) {
      int bin = freqToBin(i);
      mMagnitudes[bin] += 20*log10(mSpectrum[i]) - 120.0;
      mCounters[bin]++;
    }
  }

  for (int i = 0; i < mNbBins; i++) {
    if (mCounters[i] > 0) {
      mMagnitudes[i] = mMagnitudes[i] / mCounters[i];

      double average = 0;
      for (int j = 0; j < HISTORY_SIZE; j++) {
        average += mHistory[j][i];
      }
      average /= HISTORY_SIZE;

      mHistory[mHistoryIndex][i] = mMagnitudes[i];

      if (average != 0) {
        double variation = abs((mMagnitudes[i] - average) / average);
        variation =   constrain(variation, 0.0, 0.2);
        int height = (int) (variation * 5 * mMaxHeight);
        amplitudes[i] = height;
      }
      else {
        amplitudes[i] = 0;
      }
    }
    else {
      amplitudes[i] = 0;
    }
  }
  mHistoryIndex = (mHistoryIndex + 1) % HISTORY_SIZE;
} 
