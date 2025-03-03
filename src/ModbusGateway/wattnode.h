#ifndef _WATTNODE_H
#define _WATTNODE_H

#include <Arduino.h>
#include <meter.h>
#include <vector>

class WattNode
{
    public:
    static std::vector<ModbusRegisterBlock> getRegisterBlocks();

};
#endif
