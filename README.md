# GPS Display Replacement for Audi 80/100/V8 Multi-function display

## Overview
This project is a versatile GPS information display system that uses an Arduino platform. It demonstrates capabilities such as showing speed, direction, precise coordinates, altitude, and distances to predefined locations using a 7-segment display. The system also provides maximum speed tracking since the last device reset. 7-segment display can be fit into a broken multi-function display of classic Audi car -- and that was its main purpose; however it can be used for various multiple applications.

## Hardware Requirements
- Arduino board (preferably 'nano' board)
- TinyGPS++ module
- SoftwareSerial library compatible GPS device
- SevenSegmentTM1637 display module
- Standard pushbuttons (3x)
- Miscellaneous: connecting wires, breadboard

## Software Dependencies
- [TinyGPS++](http://arduiniana.org/libraries/tinygpsplus/): A library for parsing NMEA data streams provided by GPS modules.
- [SoftwareSerial](https://www.arduino.cc/en/Reference/softwareSerial): Allows serial communication on other digital pins of the Arduino.
- [SevenSegment](https://github.com/bremme/arduino-tm1637): A library for the 7-segment display using the TM1637 driver.

## Installation
1. **Install Arduino IDE**:
   Download and install the Arduino IDE from the official [Arduino website](https://www.arduino.cc/en/software).

2. **Library Installation**:
   Install the required libraries using the Library Manager in Arduino IDE:
   - Open Arduino IDE, go to `Sketch` > `Include Library` > `Manage Libraries...`
   - Search for `TinyGPS++`, `SoftwareSerial`, and `SevenSegmentTM1637`.
   - Click `Install` for each library.

3. **Hardware Setup**:
   - Connect the GPS module to the Arduino:
     - RX pin of GPS to TXPin (Digital 3) on Arduino.
     - TX pin of GPS to RXPin (Digital 4) on Arduino.
   - Connect the TM1637 display:
     - CLK pin to Digital 11 on Arduino.
     - DIO pin to Digital 12 on Arduino.
   - Setup the buttons:
     - Connect each button to a digital pin on the Arduino (pins 6, 7, and 8) and the other side of the button to ground. Three buttons are used because build-in controls of Audi's multifunction display have three buttons ('up', 'down' and 'reset').

4. **Load the Code**:
   - Copy the provided source code into a new sketch in Arduino IDE.
   - Verify and upload the sketch to your Arduino board using a USB cable.

## Configuration
Modify the following constants in the code to suit your environment or preferences:
- `RXPin` and `TXPin`: Pins used for GPS module connection.
- `PIN_CLK` and `PIN_DIO`: Pins for the 7-segment display module.
- `buttonPinUp`, `buttonPinDown`, `buttonPinReset`: Pins for the buttons.

## Usage
After setting up the hardware and uploading the code, perform the following:
- Power the Arduino system.
- Use buttons to navigate through different modes displaying various GPS data:
  - **Button Up**: Increment mode.
  - **Button Down**: Decrement mode.
  - **Button Reset**: Reset the stored coordinates or maximum speed.

The display will show information based on the selected mode:
1. Speed (Current speed in km/h)
2. Direction of travel
3. Coarse coordinates
4. Precise coordinates
5. Altitude
6. Direction to a predefined "Home" location
7. Distance to a predefined "Home" location
8. Distance to a specific landmark (e.g., University)
9. Distance to a saved set of coordinates
10. Direction to the saved coordinates
11. Maximum speed recorded since last reset

## Troubleshooting
- **No GPS Data**: Check the wiring of the GPS module. Ensure that the TX and RX pins are correctly connected and that the module is powered.
- **Display Not Updating**: Verify that the TM1637 display is correctly wired and receiving power.
- **Button Issues**: Ensure buttons are connected correctly and debounced in software to prevent multiple detections. Useful upgrade can be a capacitor connected in parallel to each button, to prevent multiple detections due to bad contacts in more than 30-year old cars.

## Contributing
Contributions to the project are welcome. Please fork the repository and submit a pull request with your enhancements.

## License
This project is released under the MIT License.
