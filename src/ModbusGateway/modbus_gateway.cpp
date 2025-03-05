/**
 * @file      meter.h
 * @author    Guido Jansen (guido@l-agraph.be)
 * @license   MIT
 * @copyright Copyright (c) 2025 l'agraph
 * @date      04-Mar-2025
 * @note      Setup and main loop to mediate between SolarEdge and the EnergyMeter
 */
#include <Arduino.h>
#if ESP_ARDUINO_VERSION < ESP_ARDUINO_VERSION_VAL(3, 0, 0)
#include <ETHClass2.h> //Is to use the modified ETHClass
#define ETH ETH2
#else
#include <ETH.h>
#endif
#include <SPI.h>
#include <SD.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "utilities.h" //Board PinMap
#include <WiFi.h>
#include <ModbusTCP.h>
#include <ModbusRTU.h>
#include "meter.h"
#include "em24.h"
#include "wattnode.h"
#include "convert_em24_to_wattnode.h"

static bool eth_connected = false;
WebServer server(80);

//TCP Master
ModbusTCP tcp;
modbus::Slave<modbus::EM24> meter;
IPAddress remote(192, 168, 20, 2);


// RTU Slave
ModbusRTU rtu;
modbus::Master<modbus::WattNode> wattnode;
#define SLAVE_ID 2

// Converter mapping
modbus::ConvertEM24ToWattNode converter(meter, wattnode, rtu);

// How thr RS485 port is connected to pins
#define BOARD_485_TX 33
#define BOARD_485_RX 32
#define Serial485 Serial2


// Keep list of transactions, to retrieve the block related to the transaction
struct Transaction
{
    modbus::BlockValues *_block;
    uint16_t _transaction;
};
std::vector<Transaction> transactionList;

// Room for 3 timed events
unsigned long prevTime1;
unsigned long prevTime2;
unsigned long prevTime3;

void handleRoot()
{
    String r = "";
    for (auto i = meter._blockValues.begin(); i < meter._blockValues.end(); i++)
        r += i->to_string();

    server.send(200, "text/plain", r.c_str());
}

void handleNotFound()
{
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++)
    {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

void WiFiEvent(arduino_event_id_t event)
{
    switch (event)
    {
    case ARDUINO_EVENT_ETH_START:
        Serial.println("ETH Started");
        // set eth hostname here
        ETH.setHostname("esp32-ethernet");
        break;
    case ARDUINO_EVENT_ETH_CONNECTED:
        Serial.println("ETH Connected");
        break;
    case ARDUINO_EVENT_ETH_GOT_IP:
        Serial.print("ETH MAC: ");
        Serial.print(ETH.macAddress());
        Serial.print(", IPv4: ");
        Serial.print(ETH.localIP());
        if (ETH.fullDuplex())
        {
            Serial.print(", FULL_DUPLEX");
        }
        Serial.print(", ");
        Serial.print(ETH.linkSpeed());
        Serial.println("Mbps");
        eth_connected = true;
        break;
    case ARDUINO_EVENT_ETH_DISCONNECTED:
        Serial.println("ETH Disconnected");
        eth_connected = false;
        break;
    case ARDUINO_EVENT_ETH_STOP:
        Serial.println("ETH Stopped");
        eth_connected = false;
        break;
    default:
        break;
    }
}



Modbus::ResultCode myOnRequest(Modbus::FunctionCode fc, const Modbus::RequestData data)
{
    //Serial.printf("myOnRequest %i %i %i %i\n\r", fc, data.reg.type, data.reg.address, data.regCount);
    return Modbus::EX_SUCCESS;
}

void addreg(const modbus::RegisterBlock &ib)
{
    for (auto i = ib._registers.begin(); i < ib._registers.end(); i++)
    {
        switch (i->_r_type)
        {
        case modbus::Register::data_type_e::int16:
            rtu.addHreg(i->_offset, i->_default.w);
            Serial.printf("int16 reg %i count=%i val=%i\r\n", i->_offset, 1, i->_default.w);
            break;
        case modbus::Register::data_type_e::uint16:
            rtu.addHreg(i->_offset, i->_default.w);
            Serial.printf("uint16 reg %i count=%i val=%i\r\n", i->_offset, 1, i->_default.w);
            break;
        case modbus::Register::data_type_e::int32:
            rtu.addHreg(i->_offset, i->_default.w1);
            rtu.addHreg(i->_offset + 1, i->_default.w2);
            Serial.printf("int32 reg %i count=%i val1=%i val2=%i\r\n", i->_offset, 2, i->_default.w1, i->_default.w2);
            break;
        case modbus::Register::data_type_e::uint32:
            rtu.addHreg(i->_offset, i->_default.w1);
            rtu.addHreg(i->_offset + 1, i->_default.w2);
            Serial.printf("uint32 reg %i count=%i val1=%i val2=%i\r\n", i->_offset, 2, i->_default.w1, i->_default.w2);
        break;
        case modbus::Register::data_type_e::float32:
            rtu.addHreg(i->_offset, i->_default.w1);
            rtu.addHreg(i->_offset + 1, i->_default.w2);
            Serial.printf("uint32 reg %i count=%i val1=%i val2=%i float=%f\r\n", i->_offset, 2, i->_default.w1, i->_default.w2, i->_default.f32);
        break;
                default:
            Serial.printf("error\r\n");
        }
    }
}

void setup()
{
    Serial.begin(115200);

    WiFi.onEvent(WiFiEvent);

#ifdef ETH_POWER_PIN
    pinMode(ETH_POWER_PIN, OUTPUT);
    digitalWrite(ETH_POWER_PIN, HIGH);
#endif

    // Use static ip address config
    // IPAddress local_ip(192, 168, 3, 235);
    // IPAddress gateway(192, 168, 3, 1);
    // IPAddress subnet(255, 255, 255, 0);
    // IPAddress dns (192, 168, 3, 1);

    /*ETH.config( local_ip,
                gateway,
                subnet,
                dns
                // IPAddress dns1 = (uint32_t)0x00000000,
                // IPAddress dns2 = (uint32_t)0x00000000
              );*/

    ETH.setHostname("esp32-ethernet");
#if CONFIG_IDF_TARGET_ESP32
    if (!ETH.begin(ETH_TYPE, ETH_ADDR, ETH_MDC_PIN,
                   ETH_MDIO_PIN, ETH_RESET_PIN, ETH_CLK_MODE))
    {
        Serial.println("ETH start Failed!");
    }
#else
    if (!ETH.begin(ETH_PHY_W5500, 1, ETH_CS_PIN, ETH_INT_PIN, ETH_RST_PIN,
                   SPI3_HOST,
                   ETH_SCLK_PIN, ETH_MISO_PIN, ETH_MOSI_PIN))
    {
        Serial.println("ETH start Failed!");
    }
#endif

    while (!eth_connected)
    {
        Serial.println("Wait for network connect ...");
        delay(500);
        ETH.printInfo(Serial);
    }

    if (MDNS.begin("esp32"))
    {
        Serial.println("MDNS responder started");
    }

    server.on("/", handleRoot);
    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("HTTP server started");
    tcp.client();
    bool val = tcp.connect(remote, 502);
    Serial.print("tcp.connect=");
    Serial.println(val);

    prevTime1 = millis();
    prevTime2 = prevTime1;
    prevTime3 = prevTime1;

    Serial485.begin(9600, SERIAL_8N1, BOARD_485_RX, BOARD_485_TX);

#if defined(ESP32) || defined(ESP8266)
    rtu.begin(&Serial485);
#else
    rtu.begin(&Serial485);
    // rtu.begin(&Serial, RXTX_PIN);  //or use RX/TX direction control pin (if required)
    rtu.setBaudrate(9600);
#endif

    rtu.slave(SLAVE_ID);
    // Add registers
    for (auto i = wattnode._blocks.begin(); i < wattnode._blocks.end(); i++)
    {
        addreg(*i);
    }
    rtu.onRequest(myOnRequest);

    //modbus::Register::value_t t = modbus::Register::value_t::_float32_t(3000.0);
    //Serial.printf("BYTE: %x %x %x %x\r\n", t.b1, t.b2, t.b3, t.b4);
    //Serial.printf("WORD: %x %x\r\n", t.w1, t.w2);

    //modbus::Register::value_t t1 = modbus::Register::value_t::_uint32_t(3000);
    //Serial.printf("BYTE: %x %x %x %x\r\n", t1.b1, t1.b2, t1.b3, t1.b4);
    //Serial.printf("WORD: %x %x\r\n", t1.w1, t1.w2);
    //BYTE: 0 80 3b 45
    //WORD: 8000 453b
    //BYTE: b8 b 0 0
    //WORD: bb8 0
}



bool cbReadIreg(Modbus::ResultCode event, uint16_t transaction, void *data)
{
    static bool hasAlreadyTimedOut = false;
    if (event != Modbus::EX_SUCCESS)                     // If transaction got an error
        Serial.printf("Modbus result: %02X\n\r", event); // Display Modbus error code
    else
        hasAlreadyTimedOut = false;

    if (event == Modbus::EX_TIMEOUT)
    {   // If Transaction timeout took place
        if (hasAlreadyTimedOut) {
           Serial.printf("Reset Modbus RTU connection"); 
           tcp.disconnect(remote); // Close connection to slave and
           tcp.dropTransactions(); // Cancel all waiting transactions
           hasAlreadyTimedOut = false;
        }
        else {
            hasAlreadyTimedOut = true;
        }
    }

    modbus::BlockValues *b = 0;
    for (auto i = transactionList.begin(); i < transactionList.end(); i++)
    {
        if (i->_transaction == transaction)
        {
            b = i->_block;
            transactionList.erase(i);
            break;
        }
    }
    if (b)
    {
        if (event == Modbus::EX_SUCCESS)
        {
            b->_transaction = transaction;
            converter.Copy();
        }
        /*else
        {
            Serial.print("ERROR: ");
        }
        Serial.print("cbReadIreg block=");
        Serial.print(b->_block._name);
        Serial.print(" event=");
        Serial.print(event);
        Serial.print(" values_block=");
        Serial.print(uint32_t(b->_values.data()), HEX);
        Serial.print(" data=");
        Serial.print(uint32_t(data), HEX);
        Serial.print(" transaction=");
        Serial.print(transaction);
        Serial.print(" transactionlistsize=");
        Serial.println(transactionList.size());*/
    }
    else
    {
        Serial.print("ERROR: Block for transaction ");
        Serial.print(transaction);
        Serial.println(" not found=");
    }

    return true;
}

bool readBlock(modbus::BlockValues *b)
{
    bool result = false;
    // Avoid growing of transaction list. Allow maximum 50 entries
    if (transactionList.size() > 50)
        transactionList.erase(transactionList.begin(), transactionList.begin() + (transactionList.size() - 50));

    if (tcp.isConnected(remote))
    {
        if (b->_block._number_reg > 0)
        {
            uint16_t t = tcp.readIreg(remote, b->_block._offset, b->_values.data(), b->_block._number_reg, &cbReadIreg);
            if (t > 0)
            {
                result = true;
                transactionList.push_back({b, t});
            }
        }
    }
    else
    {
        bool val = tcp.connect(remote, 502);
        Serial.print("tcp.connect=");
        Serial.println(val);
    }

    return result;
}

void loop()
{
    static std::vector<modbus::BlockValues*> _joblist;
    server.handleClient();
    unsigned long currTime = millis();
    if (currTime - prevTime1 >= 500)
    {
        _joblist.push_back(meter.get_block("dynamic"));
        prevTime1 = currTime;
    }
    if (currTime - prevTime2 >= 1000)
    {
        _joblist.push_back(meter.get_block("energy"));
        _joblist.push_back(meter.get_block("time"));
        _joblist.push_back(meter.get_block("tariff"));
        prevTime2 = currTime;
    }    
    // process a job
    if (_joblist.size() > 0)
    {
        modbus::BlockValues* b = _joblist[0];
        _joblist.erase(_joblist.begin());
        readBlock(b);    
    }
    tcp.task();
    rtu.task();
    yield();
    delay(20); // allow the cpu to switch to other tasks
}