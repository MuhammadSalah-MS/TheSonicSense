# TheSonicSense

This project implements a distance measurement system using an ATmega32 microcontroller, an HC-SR04 ultrasSonic sensor, and 4x16 LCD interface. The system calculates and displays the distance of an object in real-time.

## Introduction

The project follows the MCAL (Microcontroller Abstraction Layer) and HAL (Hardware Abstraction Layer) approach to ensure modularity and reusability of the code. The MCAL provides low-level access to the microcontroller's hardware peripherals, while the HAL abstracts higher-level functionalities, allowing easy porting of the code to different microcontroller platforms.

MCAL: Includes low-level drivers for GPIO (General Purpose Input/Output) and input capture unit of the ATmega32 microcontroller.

HAL: Provides high-level drivers for the ultrasonic sensor (HC-SR04) and LCD interface, enabling seamless interaction with these hardware components.


## Integration of ICU and HC-SR04 Ultrasonic Sensor

1. **ICU Connection:**
   - The Input Capture Unit (ICU) of the ATmega32 microcontroller is configured to capture the time interval between the transmission and reception of the ultrasonic signal.
   - Connect the Echo pin of the HC-SR04 sensor to the Input Capture pin (ICP1) of the ATmega32 microcontroller. 
   - Configure the ICU to capture rising edges of the Echo signal. ( depending on HCS04 specifications. )
   - When the ultrasonic signal is transmitted, the Echo pin of the sensor will generate a pulse, and the ICU captures the time it takes for the signal to travel to the object and back.

2. **Trigger Connection:**
   - Connect the Trigger pin of the HC-SR04 sensor to any digital output pin of the ATmega32 microcontroller. This pin will be used to trigger the ultrasonic signal transmission.
   - To measure the distance, send a short pulse (typically 10 microseconds) to the Trigger pin. This will initiate the ultrasonic signal transmission.

3. **Calculation of Distance:**
   - Once the ICU captures the time interval (in microseconds) between the transmission and reception of the ultrasonic signal, you can use this time to calculate the distance.
   - Using the formula: **Distance = (Time × Speed of Sound) / 2**.
   - Speed of Sound is approximately 343 meters per second in air at room temperature. Divide the result by 2 because this time is for  the signal traveling to the object and back.

```
HC-SR04 Sensor      ATmega32 Microcontroller
-------------------------------------------------
   VCC                    VCC
   GND                    GND
   Trigger                PORTB, Pin 5 as in Simulation
   Echo                   ICP1 (Input Capture Pin)
```

## Hardware Used

1. ATmega32 Microcontroller
2. HC-SR04 Ultrasonic Sensor
3. LCD Display (compatible with ATmega32)
4. Breadboard and Jumper Wires
5. External Power Supply (if required)

## Contributing

Contributions are welcome!
If you have any suggestions, bug reports, or feature requests, please open an issue or submit a pull request on the project's GitHub repository.
