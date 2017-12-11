#ifndef MUSIC_SIGNAL_H
#define MUSIC_SIGNAL_H

#include "../../sensors/microphone.h"
#include "signal.h"

class MusicSignal: public Signal {
public:
	MusicSignal(int nbRows, int nbColumns, Microphone * microphone);

	virtual void refresh() override;
	virtual uint32_t getColor(int index) override;

protected:
	Microphone * mMicrophone;

	int *mLastHeights;

};

#endif