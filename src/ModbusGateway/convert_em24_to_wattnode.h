#pragma once

#include <ModbusRTU.h>
#include "meter.h"
#include "em24.h"
#include "wattnode.h"
namespace modbus
{
    class ConvertEM24ToWattNode {
    public:

        ConvertEM24ToWattNode(modbus::Slave<EM24>& meter, modbus::Master<WattNode>& wattnode, ModbusRTU& rtu)
        : _meter(meter)
        , _wattnode(wattnode)
        , _rtu(rtu)
        {}

        void Copy();

    private:
        void setFloatValue(const String& reg_name, float i);
        
        modbus::Slave<EM24>& _meter;
        modbus::Master<WattNode>& _wattnode;
        ModbusRTU& _rtu;
    };
}
