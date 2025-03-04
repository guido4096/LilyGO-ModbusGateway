/**
 * @file      meter.h
 * @author    Guido Jansen (guido@l-agraph.be)
 * @license   MIT
 * @copyright Copyright (c) 2025 l'agraph
 * @date      04-Mar-2025
 * @note      Definitions to support formalization modbus register definitions
 */
#pragma once


#include <Arduino.h>
#include <vector>

// ModbusRegister
struct ModbusRegister
{
    union value_t {
        static value_t _uint32_t(uint32_t v) { value_t r; r.ui32 = v; return r;}
        static value_t _int32_t(int32_t v)  { value_t r; r.i32 = v; return r;}
        static value_t _int16_t(int16_t v) { value_t r; r.i16 = v; return r;}    
        static value_t _uint16_t(uint16_t v) { value_t r; r.ui16 = v; return r;}        
        static value_t _float32_t(float v) { value_t r; r.f32 = v; return r;}        
        struct {
            uint8_t b1;
            uint8_t b2;
            uint8_t b3;
            uint8_t b4;
        };
       struct {
            uint16_t w1;
            uint16_t w2;
        };
        struct {
            uint16_t w;
        };
        struct {
            float f32;
        };
        struct {
            uint16_t ui16;
        };
        struct {
            uint16_t i16;
        };
        struct {
            uint32_t ui32;
        };
        struct {
            int32_t i32;
        };
    };

    enum data_type_e
    {
        float32,
        int16,
        uint16,
        int32,
        uint32
    };

    String _name;
    uint16_t _offset;
    uint8_t _number;
    data_type_e _r_type;
    String _desc;
    String _unit;
    uint32_t _scaling;
    value_t _default;

    String to_string(const uint16_t *r)
    {
        String result = "unknown";
        char buf[40] = {0};
        value_t v;
        switch(_r_type)
        {
            case float32:
                v.w1=r[0];
                v.w2=r[1];
                sprintf(buf, "%f", v.f32/_scaling);
                result=buf;
                break;
            case int16:
                v.w1=r[0];
                if (_scaling==1)
                    sprintf(buf, "%i", v.i16);
                else
                    sprintf(buf, "%.*f", lround(log10(_scaling)), float(v.i16)/_scaling);
                result=buf;
                break;
            case uint16:
                v.w1=r[0];
                if (_scaling==1)
                    sprintf(buf, "%u", v.ui16);
                else
                    sprintf(buf, "%.*f", lround(log10(_scaling)), float(v.ui16)/_scaling);    
                result=buf;
                break;
            case int32:
                v.w1=r[0];
                v.w2=r[1];
                if (_scaling==1)
                    sprintf(buf, "%i", v.i32);
                else
                    sprintf(buf, "%.*f", lround(log10(_scaling)), float(v.i32)/_scaling);
                result=buf;
                break;
            case uint32:
                v.w1=r[0];
                v.w2=r[1];
                if (_scaling==1)
                    sprintf(buf, "%u", v.ui32);
                else
                    sprintf(buf, "%.*f", lround(log10(_scaling)), float(v.ui32)/_scaling);
                result=buf;
            break;
        }

        return result;
    }

    float to_float32(const uint16_t *r)
    {
        float result = 0;
        value_t v;
        switch(_r_type)
        {
            case float32:
                v.w1=r[0];
                v.w2=r[1];
                result = round(float(v.f32) * _scaling) / _scaling;
                break;
            case int16:
                v.w1=r[0];
                result = round(float(v.i16) * _scaling) / _scaling;
                break;
            case uint16:
                v.w1=r[0];
                result = round(float(v.ui16) * _scaling) / _scaling; 
                break;
            case int32:
                v.w1=r[0];
                v.w2=r[1];
                result = round(float(v.i32) * _scaling) / _scaling;
                break;
            case uint32:
                v.w1=r[0];
                v.w2=r[1];
                result = round(float(v.ui32) * _scaling) / _scaling;
            break;
        }
        return result;
    }
};

// ModbusRegisterBlock
class ModbusRegisterBlock
{
    private:

public:
    ModbusRegisterBlock() {}
    ModbusRegisterBlock(const char* name) : _name(name) {}
    ~ModbusRegisterBlock() {}

    std::vector<ModbusRegister> _registers;
    String   _name;
    uint16_t _offset = 0;
    uint16_t _number_reg = 0;

    bool check_block()
    {
        bool result = false;
        Serial.print("Check block ");
        Serial.println(_name);

        if (_registers.size() == 0)
        {
            Serial.println("ERROR: Block of size 0");
            return result;
        }
        int offset = _registers[0]._offset;
        int number = 0;
        for (auto i = _registers.begin(); i < _registers.end(); i++)
        {
            if (i->_offset != offset)
            {
                Serial.print("Offset ");
                Serial.print(i->_offset);
                Serial.print(" doesn't start at expected Offset ");
                Serial.println(offset);
                return result;
            }
            number += i->_number;
            offset += i->_number;
        }

        if (number)
        {
            Serial.println("Check block OK");
            _offset = _registers[0]._offset;
            _number_reg = number;
            result = true;
        }
        else
        {
            Serial.println("ERROR: Check block NOK");
        }
        return result;
    }

    bool get_register(String iParam, ModbusRegister& o)
    {
        for (auto i = _registers.begin(); i < _registers.end(); i++)
        {
            if (i->_name == iParam)
            {   
                o=*i;
                return true;
            }
        }
        return false;
    }

};

struct BlockValues 
{
    BlockValues() {}

    ModbusRegisterBlock    _block;
    std::vector<uint16_t>  _values;
    uint16_t               _transaction;

    String to_string()
    {
        String result;
        char buffer[200] = {0};

        // Transaction id
        sprintf(buffer, "TransactionID=%i\n", _transaction);
        result = result + String(buffer);
        buffer[0] = 0;

        int d = 0;
        for (auto i = _block._registers.begin(); i < _block._registers.end(); i++)
        {
            String value = i->to_string(&(_values[d]));
            sprintf(buffer, "%s=%s\n", i->_desc.c_str(), value.c_str());
            result = result + String(buffer);
            buffer[0] = 0;
            d += i->_number;
        }
        return result;
    }

    bool get_float_value(const String& iParam, float& o)
    {
        for (auto i = _block._registers.begin(); i < _block._registers.end(); i++)
        {
            if (i->_name == iParam)
            {   
                o=i->to_float32(&(_values[i->_offset - _block._offset]))/i->_scaling;
                return true;
            }
        }
        return false;
    }

    bool get_register(const String& iParam, ModbusRegister& o)
    {
        return _block.get_register(iParam, o);
    }
};

template <class MODBUS_TYPE>
class Master 
{
    public:
    

    Master()
    {
        std::vector<ModbusRegisterBlock> blocks = MODBUS_TYPE::getRegisterBlocks();
        for (auto i = blocks.begin(); i < blocks.end(); i++)
        {
            if (i->check_block())
            {
                _blocks.push_back(*i);
            }
        }
    }
    ModbusRegisterBlock* get_block(const String& name)
    {
        for (auto i = _blocks.begin(); i < _blocks.end(); i++)
        {
            if (i->_name == name)
                return &(*i);
        }
        return 0;
    }

    bool get_register(String iParam, ModbusRegister& o)
    {
        for (auto i = _blocks.begin(); i < _blocks.end(); i++)
        {
            if (i->get_register(iParam, o))
                return true;
        }
        Serial.printf("Can't find register %s\r\n", iParam.c_str());
        return false;
    }

    std::vector<ModbusRegisterBlock> _blocks;
};

template <class MODBUS_TYPE>
class Slave 
{
    public:
    

    Slave()
    {
        std::vector<ModbusRegisterBlock> blocks = MODBUS_TYPE::getRegisterBlocks();
        for (auto i = blocks.begin(); i < blocks.end(); i++)
        {
            if (i->check_block())
            {
                BlockValues v;
                v._block = *i;
                v._transaction = 0;
                v._values.resize(i->_number_reg);
                _blockValues.push_back(v);
            }
        }
    }
    BlockValues* get_block(const String& name)
    {
        for (auto i = _blockValues.begin(); i < _blockValues.end(); i++)
        {
            if (i->_block._name == name)
                return &(*i);
        }
        return 0;
    }

    float get_float_value(const String& iParam)
    {
        float o = 0;
        for (auto i = _blockValues.begin(); i < _blockValues.end(); i++)
        {
            if (i->get_float_value(iParam, o)) {
                return o;
            }
        }
        Serial.printf("Can't find value %s\r\n", iParam.c_str());
        return 0;
    }

    bool get_register(String iParam, ModbusRegister& o)
    {
        for (auto i = _blockValues.begin(); i < _blockValues.end(); i++)
        {
            if (i->get_register(iParam, o))
                return true;
        }
        Serial.printf("Can't find register %s\r\n", iParam.c_str());
        return false;
    }

    std::vector<BlockValues>   _blockValues;
};

