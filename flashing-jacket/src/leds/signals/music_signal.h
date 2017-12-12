#ifndef MUSIC_SIGNAL_H
#define MUSIC_SIGNAL_H

#include "../../sensors/microphone.h"
#include "signal.h"

class MusicSignal: public Signal {
public:
	MusicSignal(uint8_t nbRows, uint8_t nbColumns, Microphone * microphone);

	virtual void refresh() override;
	virtual uint32_t getColor(uint16_t index) override;

protected:
	Microphone * mMicrophone;

	uint8_t *mLastHeights;

};

#endif