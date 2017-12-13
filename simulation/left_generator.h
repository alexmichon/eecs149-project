#ifndef LEFT_GENERATOR_H
#define LEFT_GENERATOR_H

#include "direction_generator.h"

class LeftGenerator: public DirectionGenerator {
    Q_OBJECT
public:
    LeftGenerator(LedGridLayout * ledGridLayout) : DirectionGenerator(ledGridLayout, DIRECTION_LEFT) {};
};

#endif // LEFT_GENERATOR_H
