#include <Arduino.h>
#include <wattnode.h>
#include <vector>

/*
myOnRequest 3 3 1010 6
myOnRequest 3 3 1600 23
myOnRequest 3 3 1010 6
myOnRequest 3 3 1700 23
myOnRequest 3 3 1010 6
myOnRequest 3 3 1736 2
myOnRequest 3 3 1010 6
myOnRequest 3 3 1600 23
myOnRequest 3 3 1010 6
myOnRequest 3 3 1650 6
myOnRequest 3 3 1010 6
myOnRequest 3 3 1010 6
myOnRequest 3 3 1010 6
myOnRequest 3 3 1700 23
myOnRequest 3 3 1010 6
myOnRequest 3 3 1000 34
myOnRequest 3 3 1010 6
myOnRequest 3 3 1 1
*/
std::vector<ModbusRegisterBlock> WattNode::getRegisterBlocks() 
{
    std::vector<ModbusRegisterBlock> blocks; // byteorder=Endian.BIG, wordorder=Endian.LITTLE

    ModbusRegisterBlock block_0001("block0001");
    block_0001._registers.push_back({"dummy1", 0, 1, ModbusRegister::data_type_e::uint16, "Dummy 1 always returns 0", "", 1, ModbusRegister::value_t::_uint16_t(0)}); // 
    block_0001._registers.push_back({"dummy2", 1, 1, ModbusRegister::data_type_e::uint16, "Dummy 2 always returns 0", "", 1, ModbusRegister::value_t::_uint16_t(0)}); // 
    blocks.push_back(block_0001);

    ModbusRegisterBlock block_1001("block1001");
    block_1001._registers.push_back({"energy_active", 1000, 2, ModbusRegister::data_type_e::float32, "Total Energy (Active)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"import_energy_active", 1002, 2, ModbusRegister::data_type_e::float32, "Imported Total Energy (Active)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"energy_active_nr", 1004, 2, ModbusRegister::data_type_e::float32, "Total Energy (Active) NR", "kWh", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"import_energy_active_nr", 1006, 2, ModbusRegister::data_type_e::float32,  "Imported Total Energy NR (Active)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"power_active", 1008, 2, ModbusRegister::data_type_e::float32, "Total Power (Active)", "W", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"l1_power_active", 1010, 2, ModbusRegister::data_type_e::float32, "L1 Power (Active)", "W", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"l2_power_active", 1012, 2, ModbusRegister::data_type_e::float32, "L2 Power (Active)", "W", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"l3_power_active", 1014, 2, ModbusRegister::data_type_e::float32, "L3 Power (Active)", "W", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"voltage_ln", 1016, 2, ModbusRegister::data_type_e::float32,  "Voltage L-N", "V", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"l1n_voltage", 1018, 2, ModbusRegister::data_type_e::float32, "Voltage L1-N", "V", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"l2n_voltage", 1020, 2, ModbusRegister::data_type_e::float32, "Voltage L2-N", "V", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"l3n_voltage", 1022, 2, ModbusRegister::data_type_e::float32, "Voltage L3-N", "V", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"voltage_ll", 1024, 2, ModbusRegister::data_type_e::float32,  "Voltage LL", "V", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"l12_voltage", 1026, 2, ModbusRegister::data_type_e::float32, "Voltage L1-L2", "V", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"l23_voltage", 1028, 2, ModbusRegister::data_type_e::float32, "Voltage L2-L3", "V", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"l31_voltage", 1030, 2, ModbusRegister::data_type_e::float32, "Voltage L3-L1", "V", 1, ModbusRegister::value_t::_float32_t(0)});  
    block_1001._registers.push_back({"frequency", 1032, 2, ModbusRegister::data_type_e::float32,   "Frequency", "", 1, ModbusRegister::value_t::_float32_t(0)});  
    blocks.push_back(block_1001);

    ModbusRegisterBlock block_1101("block1101");    
    block_1101._registers.push_back({"l1_energy_active",            1100, 2, ModbusRegister::data_type_e::float32, "L1 Energy (Active)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); // total active energy l1
    block_1101._registers.push_back({"l2_energy_active",            1102, 2, ModbusRegister::data_type_e::float32, "L2 Energy (Active)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); // total active energy l2
    block_1101._registers.push_back({"l3_energy_active",            1104, 2, ModbusRegister::data_type_e::float32, "L3 Energy (Active)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); // total active energy l3
    block_1101._registers.push_back({"l1_import_energy_active",     1106, 2, ModbusRegister::data_type_e::float32, "L1 Imported Energy (Active)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  imported active energy l1
    block_1101._registers.push_back({"l2_import_energy_active",     1108, 2, ModbusRegister::data_type_e::float32, "L2 Imported Energy (Active)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  imported active energy l2
    block_1101._registers.push_back({"l3_import_energy_active",     1110, 2, ModbusRegister::data_type_e::float32, "L3 Imported Energy (Active)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  imported active energy l3
    block_1101._registers.push_back({"export_energy_active",        1112, 2, ModbusRegister::data_type_e::float32, "Exported Energy (Active)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  total exported active energy 
    block_1101._registers.push_back({"export_energy_active_nr",     1114, 2, ModbusRegister::data_type_e::float32, "Exported Energy (Active)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  total exported active energy non-reset
    block_1101._registers.push_back({"l1_export_energy_active",     1116, 2, ModbusRegister::data_type_e::float32, "L1 Exported Energy (Active)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  exported energy l1
    block_1101._registers.push_back({"l2_export_energy_active",     1118, 2, ModbusRegister::data_type_e::float32, "L2 Exported Energy (Active)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  exported energy l2
    block_1101._registers.push_back({"l3_export_energy_active",     1120, 2, ModbusRegister::data_type_e::float32, "L3 Exported Energy (Active)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  exported energy l3
    block_1101._registers.push_back({"energy_reactive",             1122, 2, ModbusRegister::data_type_e::float32, "Energy (Reactive)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); // total reactive energy
    block_1101._registers.push_back({"l1_energy_reactive",          1124, 2, ModbusRegister::data_type_e::float32, "L1 Energy (Reactive)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  reactive energy l1
    block_1101._registers.push_back({"l2_energy_reactive",          1126, 2, ModbusRegister::data_type_e::float32, "L2 Energy (Reactive)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  reactive energy l2
    block_1101._registers.push_back({"l3_energy_reactive",          1128, 2, ModbusRegister::data_type_e::float32, "L3 Energy (Reactive)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  reactive energy l3
    block_1101._registers.push_back({"energy_apparent",             1130, 2, ModbusRegister::data_type_e::float32, "Energy (Apparent)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  total apparent energy
    block_1101._registers.push_back({"l1_energy_apparent",          1132, 2, ModbusRegister::data_type_e::float32, "L1 Energy (Apparent)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  apparent energy l1
    block_1101._registers.push_back({"l2_energy_apparent",          1134, 2, ModbusRegister::data_type_e::float32, "L2 Energy (Apparent)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  apparent energy l2
    block_1101._registers.push_back({"l3_energy_apparent",          1136, 2, ModbusRegister::data_type_e::float32, "L3 Energy (Apparent)", "kWh", 1, ModbusRegister::value_t::_float32_t(0)}); //  apparent energy l3
    block_1101._registers.push_back({"power_factor",                1138, 2, ModbusRegister::data_type_e::float32, "Power Factor", "", 1, ModbusRegister::value_t::_float32_t(0)}); //  power factor
    block_1101._registers.push_back({"l1_power_factor",             1140, 2, ModbusRegister::data_type_e::float32, "L1 Power Factor", "", 1, ModbusRegister::value_t::_float32_t(0)}); //  power factor l1
    block_1101._registers.push_back({"l2_power_factor",             1142, 2, ModbusRegister::data_type_e::float32, "L1 Power Factor", "", 1, ModbusRegister::value_t::_float32_t(0)}); //  power factor l2
    block_1101._registers.push_back({"l3_power_factor",             1144, 2, ModbusRegister::data_type_e::float32, "L1 Power Factor", "", 1, ModbusRegister::value_t::_float32_t(0)}); //  power factor l3
    block_1101._registers.push_back({"power_reactive",              1146, 2, ModbusRegister::data_type_e::float32, "Power (Reactive)", "VAr", 1, ModbusRegister::value_t::_float32_t(0)}); //  total reactive power
    block_1101._registers.push_back({"l1_power_reactive",           1148, 2, ModbusRegister::data_type_e::float32, "L1 Power (Reactive)", "VAr", 1, ModbusRegister::value_t::_float32_t(0)}); //  reactive power l1
    block_1101._registers.push_back({"l2_power_reactive",           1150, 2, ModbusRegister::data_type_e::float32, "L2 Power (Reactive)", "VAr", 1, ModbusRegister::value_t::_float32_t(0)}); //  reactive power l2
    block_1101._registers.push_back({"l3_power_reactive",           1152, 2, ModbusRegister::data_type_e::float32, "L3 Power (Reactive)", "VAr", 1, ModbusRegister::value_t::_float32_t(0)}); //  reactive power l3
    block_1101._registers.push_back({"power_apparent",              1154, 2, ModbusRegister::data_type_e::float32, "Power (Apparent)", "VA", 1, ModbusRegister::value_t::_float32_t(0)}); //  total apparent power
    block_1101._registers.push_back({"l1_power_apparent",           1156, 2, ModbusRegister::data_type_e::float32, "L1 Power (Apparent)", "VA", 1, ModbusRegister::value_t::_float32_t(0)}); //  apparent power l1
    block_1101._registers.push_back({"l2_power_apparent",           1158, 2, ModbusRegister::data_type_e::float32, "L2 Power (Apparent)", "VA", 1, ModbusRegister::value_t::_float32_t(0)}); //  apparent power l2
    block_1101._registers.push_back({"l3_power_apparent",           1160, 2, ModbusRegister::data_type_e::float32, "L3 Power (Apparent)", "VA", 1, ModbusRegister::value_t::_float32_t(0)}); //  apparent power l3
    block_1101._registers.push_back({"l1_current",                  1162, 2, ModbusRegister::data_type_e::float32, "L1 Current", "A", 1, ModbusRegister::value_t::_float32_t(0)}); // current l1
    block_1101._registers.push_back({"l2_current",                  1164, 2, ModbusRegister::data_type_e::float32, "L2 Current", "A", 1, ModbusRegister::value_t::_float32_t(0)}); //  current l2
    block_1101._registers.push_back({"l3_current",                  1166, 2, ModbusRegister::data_type_e::float32, "L3 Current", "A", 1, ModbusRegister::value_t::_float32_t(0)}); //  current l3
    block_1101._registers.push_back({"demand_power_active",         1168, 2, ModbusRegister::data_type_e::float32, "Demand Power (Active)", "W", 1, ModbusRegister::value_t::_float32_t(0)}); //  demand power
    block_1101._registers.push_back({"minimum_demand_power_active", 1170, 2, ModbusRegister::data_type_e::float32, "Minimum Demand Power (Active)", "W", 1, ModbusRegister::value_t::_float32_t(0)}); //  minimum demand power
    block_1101._registers.push_back({"maximum_demand_power_active", 1172, 2, ModbusRegister::data_type_e::float32, "Maximum Demand Power (Active)", "W", 1, ModbusRegister::value_t::_float32_t(0)}); //  maximum demand power
    block_1101._registers.push_back({"demand_power_apparent",       1174, 2, ModbusRegister::data_type_e::float32, "Demand Power (Apparent)", "VA", 1, ModbusRegister::value_t::_float32_t(0)}); //  apparent demand power
    block_1101._registers.push_back({"l1_demand_power_active",      1176, 2, ModbusRegister::data_type_e::float32, "L1 Demand Power (Active)", "W", 1, ModbusRegister::value_t::_float32_t(0)}); // demand power l1
    block_1101._registers.push_back({"l2_demand_power_active",      1178, 2, ModbusRegister::data_type_e::float32, "L2 Demand Power (Active)", "W", 1, ModbusRegister::value_t::_float32_t(0)}); //  demand power l2
    block_1101._registers.push_back({"l3_demand_power_active",      1180, 2, ModbusRegister::data_type_e::float32, "L3 Demand Power (Active)", "W", 1, ModbusRegister::value_t::_float32_t(0)}); //  demand power l3
    blocks.push_back(block_1101);

    ModbusRegisterBlock block_1601("block1601");
    block_1601._registers.push_back({"passcode", 1600, 2, ModbusRegister::data_type_e::uint32,     "Passcode", "", 1, ModbusRegister::value_t::_uint32_t(1234)}); // 1234
    block_1601._registers.push_back({"ct_current", 1602, 1, ModbusRegister::data_type_e::int16,    "CT Current", "A", 1, ModbusRegister::value_t::_int16_t(0)}); // 0?
    block_1601._registers.push_back({"ct_current_l1", 1603, 1, ModbusRegister::data_type_e::int16, "L1 CT Current", "A", 1, ModbusRegister::value_t::_int16_t(0)}); // 0?
    block_1601._registers.push_back({"ct_current_l2", 1604, 1, ModbusRegister::data_type_e::int16, "L1 CT Current", "A", 1, ModbusRegister::value_t::_int16_t(0)}); // 0?
    block_1601._registers.push_back({"ct_current_l3", 1605, 1, ModbusRegister::data_type_e::int16, "L1 CT Current", "A", 1, ModbusRegister::value_t::_int16_t(0)}); // 0?
    block_1601._registers.push_back({"ct_inverted", 1606, 1, ModbusRegister::data_type_e::int16,   "CT Inverted", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1601._registers.push_back({"measurement_averaging", 1607, 1, ModbusRegister::data_type_e::int16,  "Measurement Averaging", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1601._registers.push_back({"power_scale", 1608, 1, ModbusRegister::data_type_e::int16, "Power Scale", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1601._registers.push_back({"demand_period", 1609, 1, ModbusRegister::data_type_e::int16, "Demand Period", "Minute", 1, ModbusRegister::value_t::_int16_t(15)}); // 15
    block_1601._registers.push_back({"demand_subintervals", 1610, 1, ModbusRegister::data_type_e::int16, "Demand Subintervals", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 1
    block_1601._registers.push_back({"l1_power_energy_adj", 1611, 1, ModbusRegister::data_type_e::int16, "Power/Energy adjustment l1", "", 1, ModbusRegister::value_t::_int16_t(10000)}); // 10000
    block_1601._registers.push_back({"l2_power_energy_adj", 1612, 1, ModbusRegister::data_type_e::int16, "Power/Energy adjustment l2", "", 1, ModbusRegister::value_t::_int16_t(10000)}); // 10000
    block_1601._registers.push_back({"l3_power_energy_adj", 1613, 1, ModbusRegister::data_type_e::int16, "Power/Energy adjustment l3", "", 1, ModbusRegister::value_t::_int16_t(10000)}); // 10000
    block_1601._registers.push_back({"l1_ct_phase_angle_adj", 1614, 1, ModbusRegister::data_type_e::int16, "L1 Voltage", "V", 1, ModbusRegister::value_t::_int16_t(-1000)}); // -1000
    block_1601._registers.push_back({"l2_ct_phase_angle_adj", 1615, 1, ModbusRegister::data_type_e::int16, "L1 Voltage", "V", 1, ModbusRegister::value_t::_int16_t(-1000)}); // -1000
    block_1601._registers.push_back({"l3_ct_phase_angle_adj", 1616, 1, ModbusRegister::data_type_e::int16, "L1 Voltage", "V", 1, ModbusRegister::value_t::_int16_t(-1000)}); // -1000
    block_1601._registers.push_back({"minimum_power_reading", 1617, 1, ModbusRegister::data_type_e::int16, "Minimum Power Reading", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 1500
    block_1601._registers.push_back({"phase_offset", 1618, 1, ModbusRegister::data_type_e::int16, "Phase Offset", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0?
    block_1601._registers.push_back({"reset_energy", 1619, 1, ModbusRegister::data_type_e::int16, "Reset Energy", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1601._registers.push_back({"reset_demand", 1620, 1, ModbusRegister::data_type_e::int16, "Reset Demand", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1601._registers.push_back({"current_scale", 1621, 1, ModbusRegister::data_type_e::int16, "Current Scale", "", 1, ModbusRegister::value_t::_int16_t(20000)}); // 20000
    block_1601._registers.push_back({"io_pin_mode", 1622, 1, ModbusRegister::data_type_e::int16,  "IO Pin Mode", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    blocks.push_back(block_1601);

    ModbusRegisterBlock block_1651("block1651");
    block_1651._registers.push_back({"apply_config", 1650, 1, ModbusRegister::data_type_e::int16, "Apply Config", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1651._registers.push_back({"modbus_address", 1651, 1, ModbusRegister::data_type_e::int16,  "Modbus Address", "", 1, ModbusRegister::value_t::_int16_t(0)}); // modbus address
    block_1651._registers.push_back({"baud_rate", 1652, 1, ModbusRegister::data_type_e::int16, "Baud Rate", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 4
    block_1651._registers.push_back({"parity_mode", 1653, 1, ModbusRegister::data_type_e::int16, "Parity Mode", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1651._registers.push_back({"modbus_mode", 1654, 1, ModbusRegister::data_type_e::int16, "Modbus Mode", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1651._registers.push_back({"message_delay", 1655, 1, ModbusRegister::data_type_e::int16, "Message Delay", "ms", 10, ModbusRegister::value_t::_int16_t(0)}); // 5
    blocks.push_back(block_1651);

    ModbusRegisterBlock block_1701("block1700");
    block_1701._registers.push_back({"serial_number", 1700, 2, ModbusRegister::data_type_e::uint32,     "Serial Number", "", 1, ModbusRegister::value_t::_uint32_t(12345678)}); // serial number
    block_1701._registers.push_back({"uptime", 1702, 2, ModbusRegister::data_type_e::uint32,            "Uptime", "s", 1, ModbusRegister::value_t::_uint32_t(0)}); // 0
    block_1701._registers.push_back({"total_uptime", 1704, 2, ModbusRegister::data_type_e::uint32,      "Total Uptime", "2", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"wattnode_model", 1706, 1, ModbusRegister::data_type_e::int16,     "Wattnode Model", "", 1, ModbusRegister::value_t::_int16_t(202)}); // 202
    block_1701._registers.push_back({"firmware_version", 1707, 1, ModbusRegister::data_type_e::int16,   "Firmware Version", "", 1, ModbusRegister::value_t::_int16_t(31)}); // 31
    block_1701._registers.push_back({"options", 1708, 1, ModbusRegister::data_type_e::int16,            "Options", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"error_status", 1709, 1, ModbusRegister::data_type_e::int16,       "Error Status", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"power_fail_count", 1710, 1, ModbusRegister::data_type_e::int16,   "Power Fail Count", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"crc_error_count", 1711, 1, ModbusRegister::data_type_e::int16,    "CRC Error Count", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"frame_error_count", 1712, 1, ModbusRegister::data_type_e::int16,  "Frame Error Count", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"packet_error_count", 1713, 1, ModbusRegister::data_type_e::int16, "Packet Error Count", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"overrun_count", 1714, 1, ModbusRegister::data_type_e::int16,  "Overrun Count", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"error_status_1", 1715, 1, ModbusRegister::data_type_e::int16, "Error Status 1", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"error_status_2", 1716, 1, ModbusRegister::data_type_e::int16, "Error Status 2", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"error_status_3", 1717, 1, ModbusRegister::data_type_e::int16, "Error Status 3", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"error_status_4", 1718, 1, ModbusRegister::data_type_e::int16, "Error Status 4", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"error_status_5", 1719, 1, ModbusRegister::data_type_e::int16, "Error Status 5", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"error_status_6", 1720, 1, ModbusRegister::data_type_e::int16, "Error Status 6", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"error_status_7", 1721, 1, ModbusRegister::data_type_e::int16, "Error Status 7", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    block_1701._registers.push_back({"error_status_8", 1722, 1, ModbusRegister::data_type_e::int16, "Error Status 8", "", 1, ModbusRegister::value_t::_int16_t(0)}); // 0
    blocks.push_back(block_1701);

    // SolarEdge requests the value for the register 1736
    // Unclear what it is
    ModbusRegisterBlock block_1737("block_1736");
    block_1737._registers.push_back({"unknown", 1736, 2, ModbusRegister::data_type_e::uint32, "Unknown", "", 1, ModbusRegister::value_t::_uint32_t(0)});  // 0
    blocks.push_back(block_1737);
    
    // SolarEdge requests the value for the register 2127
    // If you don't supply it, it will keep asking
    // if you supply it, it will only ask it once
    ModbusRegisterBlock block_2128("block_2127");
    block_2128._registers.push_back({"unknown", 2127, 1, ModbusRegister::data_type_e::uint16,  "Unknown", "", 1, ModbusRegister::value_t::_uint16_t(1)});  // 0
    blocks.push_back(block_2128);


    return blocks;
}