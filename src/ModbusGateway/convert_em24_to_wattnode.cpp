#include "Arduino.h"
#include "convert_em24_to_wattnode.h"

void modbus::ConvertEM24ToWattNode::setFloatValue(const String& reg_name, float i)
{
    modbus::Register::value_t v;
    modbus::Register r;
    v.f32 = i;
    if (_wattnode.get_register(reg_name, r))
    {
        //Serial.printf("CopyDateFromEM24ToWattnode %s %i=%f\n\r", reg_name.c_str(), r._offset, i) ;

        _rtu.Reg(TAddress({ TAddress::HREG, r._offset}), v.w1);
        _rtu.Reg(TAddress({ TAddress::HREG, uint16_t(r._offset+1)}), v.w2);   
    }

}

void modbus::ConvertEM24ToWattNode::Copy()
{   
    //Serial.printf("CopyDateFromEM24ToWattnode\n\r");
    // Block 1001
    setFloatValue("energy_active", _meter.get_float_value("import_energy_active")+_meter.get_float_value("export_energy_active"));// # total active energy
    setFloatValue("import_energy_active", _meter.get_float_value("import_energy_active"));//  # imported active energy
    setFloatValue("energy_active_nr", _meter.get_float_value("import_energy_active")+_meter.get_float_value("export_energy_active"));//  # total active energy non-reset
    setFloatValue("import_energy_active_nr", _meter.get_float_value("import_energy_active"));//  # imported active energy non-reset
    setFloatValue("power_active", _meter.get_float_value("power_active"));//  # total power
    setFloatValue("l1_power_active", _meter.get_float_value("l1_power_active"));
    setFloatValue("l2_power_active", _meter.get_float_value("l2_power_active"));
    setFloatValue("l3_power_active", _meter.get_float_value("l3_power_active"));
    setFloatValue("voltage_ln", _meter.get_float_value("voltage_ln"));//  # l-n voltage
    setFloatValue("l1n_voltage", _meter.get_float_value("l1_voltage"));//  # l1-n voltage
    setFloatValue("l2n_voltage", _meter.get_float_value("l2_voltage"));//  # l2-n voltage
    setFloatValue("l3n_voltage", _meter.get_float_value("l3_voltage"));//  # l3-n voltage
    setFloatValue("voltage_ll", _meter.get_float_value("voltage_ll"));//  # l-l voltage
    setFloatValue("l12_voltage", _meter.get_float_value("l12_voltage"));//  # l1-l2 voltage
    setFloatValue("l23_voltage", _meter.get_float_value("l23_voltage"));//  # l2-l3 voltage
    setFloatValue("l31_voltage", _meter.get_float_value("l31_voltage"));//  # l3-l1 voltage
    setFloatValue("frequency", _meter.get_float_value("frequency"));//  # line frequency    
    
    // Block 1101
    setFloatValue("l1_energy_active", _meter.get_float_value("l1_import_energy_active")+_meter.get_float_value("export_energy_active")/3); //  total active energy l1
    setFloatValue("l2_energy_active", _meter.get_float_value("l2_import_energy_active")+_meter.get_float_value("export_energy_active")/3); //  total active energy l2
    setFloatValue("l3_energy_active", _meter.get_float_value("l3_import_energy_active")+_meter.get_float_value("export_energy_active")/3); //  total active energy l3
    setFloatValue("l1_import_energy_active", _meter.get_float_value("l1_import_energy_active")); //  imported active energy l1
    setFloatValue("l2_import_energy_active", _meter.get_float_value("l2_import_energy_active")); //  imported active energy l2
    setFloatValue("l3_import_energy_active", _meter.get_float_value("l3_import_energy_active")); //  imported active energy l3
    setFloatValue("export_energy_active", _meter.get_float_value("export_energy_active")); //  total exported active energy
    setFloatValue("export_energy_active_nr", _meter.get_float_value("export_energy_active")); //  total exported active energy non-reset
    setFloatValue("l1_export_energy_active", _meter.get_float_value("export_energy_active")/3); //  exported energy l1
    setFloatValue("l2_export_energy_active", _meter.get_float_value("export_energy_active")/3); //  exported energy l2
    setFloatValue("l3_export_energy_active", _meter.get_float_value("export_energy_active")/3); //  exported energy l3
    setFloatValue("energy_reactive", _meter.get_float_value("import_energy_reactive") + _meter.get_float_value("export_energy_reactive")); //  total reactive energy
    //setFloatValue("l1_energy_reactive", _meter.get_float_value("l1_energy_reactive")); //  reactive energy l1
    //setFloatValue("l2_energy_reactive", _meter.get_float_value("l2_energy_reactive")); //  reactive energy l2
    //setFloatValue("l3_energy_reactive", _meter.get_float_value("l3_energy_reactive")); //  reactive energy l3
    //setFloatValue("energy_apparent", _meter.get_float_value("energy_apparent")); //  total apparent energy
    //setFloatValue("l1_energy_apparent", _meter.get_float_value("l1_energy_apparent")); //  apparent energy l1
    //setFloatValue("l2_energy_apparent", _meter.get_float_value("l2_energy_apparent")); //  apparent energy l2
    //setFloatValue("l3_energy_apparent", _meter.get_float_value("l3_energy_apparent")); //  apparent energy l3
    setFloatValue("power_factor", _meter.get_float_value("total_pf")); //  power factor
    setFloatValue("l1_power_factor", _meter.get_float_value("l1_power_factor")); //  power factor l1
    setFloatValue("l2_power_factor", _meter.get_float_value("l2_power_factor")); //  power factor l2
    setFloatValue("l3_power_factor", _meter.get_float_value("l3_power_factor")); //  power factor l3
    setFloatValue("power_reactive", _meter.get_float_value("power_reactive")); //  total reactive power
    setFloatValue("l1_power_reactive", _meter.get_float_value("l1_power_reactive")); //  reactive power l1
    setFloatValue("l2_power_reactive", _meter.get_float_value("l2_power_reactive")); //  reactive power l2
    setFloatValue("l3_power_reactive", _meter.get_float_value("l3_power_reactive")); //  reactive power l3
    setFloatValue("power_apparent", _meter.get_float_value("power_apparent")); //  total apparent power
    setFloatValue("l1_power_apparent", _meter.get_float_value("l1_power_apparent")); //  apparent power l1
    setFloatValue("l2_power_apparent", _meter.get_float_value("l2_power_apparent")); //  apparent power l2
    setFloatValue("l3_power_apparent", _meter.get_float_value("l3_power_apparent")); //  apparent power l3
    setFloatValue("l1_current", _meter.get_float_value("l1_current")); //  current l1
    setFloatValue("l2_current", _meter.get_float_value("l2_current")); //  current l2
    setFloatValue("l3_current", _meter.get_float_value("l3_current")); //  current l3
    setFloatValue("demand_power_active", _meter.get_float_value("demand_power_active")); //  demand power
    //setFloatValue("minimum_demand_power_active", _meter.get_float_value("minimum_demand_power_active")); //  minimum demand power
    setFloatValue("maximum_demand_power_active", _meter.get_float_value("maximum_demand_power_active")); //  maximum demand power
    setFloatValue("demand_power_apparent", _meter.get_float_value("demand_power_apparent")); //  apparent demand power
    //setFloatValue("l1_demand_power_active", _meter.get_float_value("l1_demand_power_active")); //  demand power l1
    //setFloatValue("l2_demand_power_active", _meter.get_float_value("l2_demand_power_active")); //  demand power l2
    //setFloatValue("l3_demand_power_active", _meter.get_float_value("l3_demand_power_active")); //  demand power l3
}
