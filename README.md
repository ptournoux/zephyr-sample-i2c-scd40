# I2C SCD40

Should work for all the boards with I2C. You just have to specify which I2C port should be used in your overlay file.

On ST nucleo 64 boards, the arduino r3 shield's I2C port is accessible through I2C2. This code sample uses I2C2.

## Where are the I2C2 pins ?

As seen in the STM32WL55 documentation, SCL and SDA of I2C2 are respectively available on pins PA12 and PA11. The Arduino header of the NUCLEO_WL55, these pin are D15 and D14.

![mbed](https://os.mbed.com/media/uploads/jeanmarcr/nucleo_wl55jc_arduino_right_2021_2_1.png)

If you are using [the SCD40 from M5 Stack](https://docs.m5stack.com/en/unit/co2) :
* pin IIC_SCL (grey) should be connected to D15 of the nucleo,
* pin IIC_SDA (yellow) should be connected to D14 of the nucleo,
* pin VCC (red) should be connected to 5v of the nucleo
* pin GND (black) should be connected to one of the GND pin of the nucleo

Note that the M5 Stack SCD40 module already integrate I2C pullup resistor.

## How to use this sample

### Clone the repo to your workspace

git clone https://github.com/ptournoux/zephyr-sample-i2c-scd40.git

### Build

```bash
# go to your zephyr workspace (likely ~/zephyrproject/zephyr)
cd ~/zephyrproject/zephyr
west build --board=nucleo_wl55jc -p always zephyr-sample-i2c-scd40
````

```bash
west flash
```

The sensor data should be printed on the UART. If you are using a nucleo board, the stlink allow you to access the UART (which are also available on D0 and D1). Use picocom, teraterm (...) to monitor the serial port.


```bash
picocom -b 115200 /dev/ttyACM0

CO2: 539 ppm
Temperature: 26.85 °C
Humidity: 90.21 %
--------------------------------------
CO2: 539 ppm
Temperature: 26.85 °C
Humidity: 90.24 %
--------------------------------------
CO2: 539 ppm
Temperature: 26.85 °C
Humidity: 90.23 %
--------------------------------------
CO2: 540 ppm
Temperature: 26.86 °C
Humidity: 90.24 %
--------------------------------------
CO2: 541 ppm
Temperature: 26.95 °C
Humidity: 90.44 %
--------------------------------------
CO2: 2466 ppm
Temperature: 27.65 °C
Humidity: 93.46 %
--------------------------------------
CO2: 6735 ppm
Temperature: 28.84 °C
Humidity: 98.64 %
--------------------------------------
CO2: 9470 ppm
Temperature: 29.33 °C
Humidity: 100.00 %
--------------------------------------
CO2: 11758 ppm
Temperature: 29.80 °C
Humidity: 100.00 %
--------------------------------------
CO2: 13934 ppm
Temperature: 30.22 °C
Humidity: 100.00 %
--------------------------------------
CO2: 15729 ppm
Temperature: 30.47 °C
Humidity: 100.00 %
--------------------------------------
CO2: 17042 ppm
Temperature: 30.67 °C
Humidity: 100.00 %
--------------------------------------
CO2: 17693 ppm
Temperature: 30.78 °C
Humidity: 100.00 %
```


# Troubleshooting

What if the code fails to initialize the I2C2 device ? In this case, it probably prints nothing and hang forever

* Is the connexion correct ?
  * Have I provided GND and +5v to the module ? If in doubt use your voltmeter
  * Have I connected SCL and SDA to the right pin ? Use an oscilloscope.
* Is there a pullup resistor on SCL and SDA lines ? (if using the M5 Stack SCD40 module, the answer is yes).
* Have I the right I2C address ?
  * Use an I2C scanner to scan devices e.g. https://github.com/ptournoux/zephyr-sample-i2c-scanner
