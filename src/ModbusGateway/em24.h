#ifndef _EM24_H
#define _EM24_H

#include <Arduino.h>
#include <meter.h>
#include <vector>

class EM24
{
    public:
    static std::vector<ModbusRegisterBlock> getRegisterBlocks();

};
#endif
