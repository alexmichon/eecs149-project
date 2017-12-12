#ifndef BRAKE_GENERATOR_H
#define BRAKE_GENERATOR_H

#include "signal_generator.h"

class BrakeGenerator: public SignalGenerator {
    Q_OBJECT

public:
    BrakeGenerator(LedGridLayout *ledGridLayout);

public slots:
    virtual void generate() override;

};

#endif // BRAKE_GENERATOR_H
