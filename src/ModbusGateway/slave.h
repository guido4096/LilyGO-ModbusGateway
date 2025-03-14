/**
 * @file      slave.h
 * @author    Guido Jansen (guido@ngjansen.be)
 * @license   MIT
 * @copyright Copyright (c) 2025 Guido Jansen
 * @date      04-Mar-2025
 * @note      Object that acts as a slave to answer requests from the SolarEdge inverter
 */
#pragma once

#include "definitions.h"
#include "ModbusRTU.h"

namespace modbus
{
    template <class MODBUS_TYPE>
    class Slave
    {
    public:
    Slave(ModbusRTU& rtu, uint8_t slaveId) : _dd(MODBUS_TYPE::getDeviceDescription()), _rtu(rtu) 
        {
            createRegistersInModbusDevice();
            _rtu.slave(slaveId);
            _rtu.onRequest(myOnRequest);
        }
        
        void setFloatValue(const DeviceDescription::RegisterReference& rr, float i)
        {
            if (rr._block_idx >= 0 && rr._register_idx >= 0)
            {
                modbus::Register::value_t v;
                v.f32 = i;
                modbus::Register r = _dd._blocks[rr._block_idx]._registers[rr._register_idx];
                _rtu.Reg(TAddress({ TAddress::HREG, r._offset}), v.w1);
                _rtu.Reg(TAddress({ TAddress::HREG, uint16_t(r._offset+1)}), v.w2);  
                //Serial.printf("setFloatValue %s %i %i=%f\r\n", rr._name, rr._block_idx, rr._register_idx, i);
            }
            else 
            {
                Serial.printf("modbus::ConvertEM24ToWattNode::setFloatValue invalid reference for register %s %i %i\r\n", rr._name, rr._block_idx, rr._register_idx) ;
            } 
        }

        float getFloatValue(const Register& r)
        {
            float f = 0;
            modbus::Register::value_t v;
            if (r._r_type == Register::data_type_e::float32) {
                v.w1 = _rtu.Reg(TAddress({ TAddress::HREG, r._offset}));
                v.w2 = _rtu.Reg(TAddress({ TAddress::HREG, uint16_t(r._offset+1)}));  
                f=v.f32;
            }
            return f;
        }
        const DeviceDescription& _dd;

        private:
        ModbusRTU&               _rtu;
        static Modbus::ResultCode myOnRequest(Modbus::FunctionCode fc, const Modbus::RequestData data)
        {
            //Serial.printf("myOnRequest %i %i %i %i\n\r", fc, data.reg.type, data.reg.address, data.regCount);
            return Modbus::EX_SUCCESS;
        }
        void createRegistersInModbusDevice()
        {
            for (auto i = _dd._blocks.begin(); i < _dd._blocks.end(); i++) {
                for (auto j = i->_registers.begin(); j < i->_registers.end(); j++)
                {
                    switch (j->_r_type)
                    {
                    case modbus::Register::data_type_e::int16:
                        _rtu.addHreg(j->_offset, j->_default.w);
                        //Serial.printf("int16 reg %i count=%i val=%i\r\n", i->_offset, 1, i->_default.w);
                        break;
                    case modbus::Register::data_type_e::uint16:
                        _rtu.addHreg(j->_offset, j->_default.w);
                        //Serial.printf("uint16 reg %i count=%i val=%i\r\n", i->_offset, 1, i->_default.w);
                        break;
                    case modbus::Register::data_type_e::int32:
                        _rtu.addHreg(j->_offset, j->_default.w1);
                        _rtu.addHreg(j->_offset + 1, j->_default.w2);
                        //Serial.printf("int32 reg %i count=%i val1=%i val2=%i\r\n", i->_offset, 2, i->_default.w1, i->_default.w2);
                        break;
                    case modbus::Register::data_type_e::uint32:
                        _rtu.addHreg(j->_offset, j->_default.w1);
                        _rtu.addHreg(j->_offset + 1, j->_default.w2);
                        //Serial.printf("uint32 reg %i count=%i val1=%i val2=%i\r\n", i->_offset, 2, i->_default.w1, i->_default.w2);
                    break;
                    case modbus::Register::data_type_e::float32:
                        _rtu.addHreg(j->_offset, j->_default.w1);
                        _rtu.addHreg(j->_offset + 1, j->_default.w2);
                        //Serial.printf("uint32 reg %i count=%i val1=%i val2=%i float=%f\r\n", i->_offset, 2, i->_default.w1, i->_default.w2, i->_default.f32);
                    break;
                            default:
                        Serial.printf("error\r\n");
                    }
                }
            }
        }
    };
}