/**
 * @file      meter.h
 * @author    Guido Jansen (guido@l-agraph.be)
 * @license   MIT
 * @copyright Copyright (c) 2025 l'agraph
 * @date      04-Mar-2025
 * @note      EM24 Modbus Definitions
 */
#pragma once


#include <Arduino.h>
#include <meter.h>
#include <vector>
namespace modbus
{
    class EM24
    {
        public:
        static std::vector<modbus::RegisterBlock> getRegisterBlocks();

    };

}
