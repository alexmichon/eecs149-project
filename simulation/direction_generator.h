#ifndef DIRECTION_GENERATOR_H
#define DIRECTION_GENERATOR_H

#include "signal_generator.h"

#define DIRECTION_RIGHT 1
#define DIRECTION_LEFT -1

class DirectionGenerator: public SignalGenerator {
    Q_OBJECT
public:
    DirectionGenerator(LedGridLayout *LedGridLayout, int direction);

public slots:
    virtual void generate();

private:
    const int mDirection;
    int mCount;
};

#endif // DIRECTION_GENERATOR_H
