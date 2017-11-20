#ifndef RIGHT_GENERATOR_H
#define RIGHT_GENERATOR_H

#include "direction_generator.h"

class RightGenerator: public DirectionGenerator {
    Q_OBJECT

public:
    RightGenerator(LedGridLayout *ledGridLayout) : DirectionGenerator(ledGridLayout, DIRECTION_RIGHT) {};

};

#endif // RIGHT_GENERATOR_H
