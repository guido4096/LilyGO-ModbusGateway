<h1 align = "center">🌟LilyGO T-POE-PRO Modbus Gateway</h1>

This is a gateway to connect a SolarEdge inverter to your own evergy meter. 
The SolarEdge inverter connects to the LilyGO ETH-POE-PRO through Modbus-RTU.
The LilyGO-POE-PRO connects to a Carlo Gavazzi EM24 through Modbus-TCP.
The gateway translates the registers and values as needed.

## 1️⃣ PlatformIO Quick Start <Recommended>

1. Install [Visual Studio Code](https://code.visualstudio.com/) and [Python](https://www.python.org/)
2. Search for the `PlatformIO` plugin in the `VisualStudioCode` extension and install it.
3. After the installation is complete, you need to restart `VisualStudioCode`
4. After restarting `VisualStudioCode`, select `File` in the upper left corner of `VisualStudioCode` -> `Open Folder` -> select the `LilyGO T-ETH-Series` directory
5. Wait for the installation of third-party dependent libraries to complete
7. Click the (✔) symbol in the lower left corner to compile
8. Connect the board to the computer USB (If there is no onboard downloader, USB2TTL must be connected)
9. Click (→) to upload firmware
10. Click (plug symbol) to monitor serial output
11. Since **T-LITE-ESP32** uses **IO0** as the clock input, the default working level of **DTR** is high level, so after the download is completed, you need to remove the connection between **DTR** and **IO0**, so that ETH will work, otherwise the initialization will fail
12. For **T-LITE-ESP32**, when uploading a sketch, you need to press and hold the *BOOT* button to run the upload

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

