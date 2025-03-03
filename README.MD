<h1 align = "center">🌟LilyGO T-POE-PRO Modbus Gateway</h1>

This is a gateway to connect a SolarEdge inverter to your own evergy meter. 
The SolarEdge inverter connects to the LilyGO ETH-POE-PRO through Modbus-RTU
The LilyGO-POE-PRO connects to a Carlo Gavazzi EM24 through Modbus-TCP
The gateway translates the registers and values as needed.

## 1️⃣ PlatformIO Quick Start <Recommended>

1. Install [Visual Studio Code](https://code.visualstudio.com/) and [Python](https://www.python.org/)
2. Search for the `PlatformIO` plugin in the `VisualStudioCode` extension and install it.
3. After the installation is complete, you need to restart `VisualStudioCode`
4. After restarting `VisualStudioCode`, select `File` in the upper left corner of `VisualStudioCode` -> `Open Folder` -> select the `LilyGO T-ETH-Series` directory
5. Wait for the installation of third-party dependent libraries to complete
6. Click on the `platformio.ini` file, and in the `platformio` column
7. First change the default_envs to the board used
8. Uncomment one of the lines src_dir = xxxx to make sure only one line works
9. Click the (✔) symbol in the lower left corner to compile
10. Connect the board to the computer USB (If there is no onboard downloader, USB2TTL must be connected)
11. Click (→) to upload firmware
12. Click (plug symbol) to monitor serial output
13. Since **T-LITE-ESP32** uses **IO0** as the clock input, the default working level of **DTR** is high level, so after the download is completed, you need to remove the connection between **DTR** and **IO0**, so that ETH will work, otherwise the initialization will fail
14. For **T-LITE-ESP32**, when uploading a sketch, you need to press and hold the *BOOT* button to run the upload


## 2️⃣ Arduino IDE Quick Start
* It is recommended to use platformio without cumbersome steps
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Install [Arduino ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
3. Copy everything from this repository [lib folder](./lib/)  to Arduino library folder (e.g. C:\Users\YourName\Documents\Arduino\libraries)
4. Open ArduinoIDE -> Tools
   ![ArduinoIDE](image/ArduinoIDE.jpg)
5. `T-ETH-Elite` options are the same as `T-ETH-Lite`, but you need to adjust `USB CDC On Boot` to `Enabled`
5. Open the [examples](./examples/),such as [examples/UnitTestExample](./examples/UnitTestExample)
6. Switch to the [utilities.h](./examples/UnitTestExample/utilities.h) file, at the top of the sketch, uncomment the definition of the board name you use , such as **LILYGO_T_INTERNET_POE**
7. Connect external [USB2TTL](https://www.amazon.com/usb-ttl-adapter/s?k=usb+to+ttl+adapter)，such as **CP2102,CP2104,CH340X**
      * Has an onboard downloader(**T-POE-Pro**)
          If the board has a USB-C, plug it directly into the USB-C, select the corresponding port, and upload.
      * no onboard downloader(**T-ETH-Lite-ESP32/T-ETH-Lite-ESP32S3/T-Internet-POE**)
          Additional USB2TTL is required to connect the board with USB2TTL
      * Connection example:


        | USB2TTL(Has DTR,RTS) | USB2TTL(NO DTR,RTS) | T-ETH-Series |
        | -------------------- | ------------------- | ------------ |
        | 5V                   | 5V                  | 5V IN        |
        | GND                  | GND                 | GND          |
        | RX                   | RX                  | TXD          |
        | TX                   | TX                  | RXD          |
        | RTS                  |                     | RST          |
        | DTR                  |                     | IO0          |

     * Connection diagram
  
        ![connect](./image/connect.jpg)

     *  **Note that for boards that are not connected to DTR or RTS, the board must be put into download mode before uploading the sketch, otherwise the sketch cannot be uploaded.How to enter download mode, please see FAQ**
     *  **注意，对于没有连接到DTR,RTS 的板子，上传程序之前，必须先将板子置入下载模式,否则无法上传程序，如何进入下载模式，请看FAQ**


8. Select the corresponding port and click Upload <If the upload fails, View the FAQ below>
9. Since **T-LITE-ESP32** uses **IO0** as the clock input, the default working level of **DTR** is high level, so after the download is completed, you need to remove the connection between **DTR** and **IO0**, so that ETH will work, otherwise the initialization will fail
10. **T-LITE-ESP32** Since the `PHYAD` address is selected as 0, the yellow LINK light will not light up, which does not affect the use.

<h2 align = "left">5️⃣ ESP32 basic examples </h2>

* [BLE Examples](https://github.com/espressif/arduino-esp32/tree/master/libraries/BLE)
* [WiFi Examples](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi)
* [SPIFFS Examples](https://github.com/espressif/arduino-esp32/tree/master/libraries/SPIFFS)
* [FFat Examples](https://github.com/espressif/arduino-esp32/tree/master/libraries/FFat)
* For more examples of esp32 chip functions, please refer to [arduino-esp32-libraries](https://github.com/espressif/arduino-esp32/tree/master/libraries)

<h2 align = "left">6️⃣ FAQ </h2>

1. Unable to upload sketch,Please enter the upload mode manually.
    1. Connect the board via the USB cable or connect USB2TTL
    2. Press and hold the BOOT button , While still pressing the BOOT button, press RST
    3. Release the RST
    4. Finally release the BOOT Button(The BOOT button must be released last)
    5. Upload sketch

2. Unable to verify flash chip connection
    1. Please refer to this [issue #45](https://github.com/Xinyuan-LilyGO/LilyGO-T-ETH-Series/issues/45)

## 7️⃣ RESOURCE

* [T-ETH-ELite/Lite POE Module datasheet](./datasheet/ETH-POE-DP9900M-5V.pdf)
* [T-ETH-POR POE Module datasheet](./datasheet/ETH-PRO-POE-DP5300-12V.pdf)

