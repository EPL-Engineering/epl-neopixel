# Neopixel Controller

![alt text](https://github.com/EPL-Engineering/epl-neopixel/blob/main/Images/front-panel.png?)

[Windows installer](https://github.com/EPL-Engineering/epl-neopixel/releases/download/v1.0/Neopixel_Controller_1-0.exe)

[Changelog](CHANGELOG.md)

## NI Prerequisites
The software requires the following installations from National Instruments. All are free downloads, but registration may be required.
1. [NI DAQmx 20.1](https://www.ni.com/en/support/downloads/drivers/download.ni-daq-mx.html#348669) or greater
2. [LabVIEW 2020 32-bit Runtime Engine](https://www.ni.com/en/support/downloads/software-products/download.labview-runtime.html?srsltid=AfmBOorCUv3V_56cdQDMn3BNF-vT57k48-523YsmQve1thLfrV5-ecnW#369481)
3. [NI-VISA](https://www.ni.com/en/support/downloads/drivers/download.ni-visa.html?srsltid=AfmBOopZtnEMzVJhmXjvn7esJthgh9vWX_lWwgG6HzHGwRQR9I_imjlV#442805)

## Installation
1. Download and install the Arduino IDE (https://www.arduino.cc/en/software)
2. Download and install the Adafruit Neopixel Library (https://github.com/adafruit/Adafruit_NeoPixel)
3. Download and install the [Neopixel Controller](https://github.com/EPL-Engineering/epl-neopixel/releases/download/v1.0/Neopixel_Controller_1-0.exe)

## Programming Arduino
1. Open Arduino IDE
2. The Neopixel Controller installer should install an Arduino sketch in the folder `Documents\Arduino\neopixel-controller`.
3. Compile and upload

Note: programming the Arduino should only need to be done once. Whenever it is powered up thereafter, it should automatically begin executing the Neopixel program.

