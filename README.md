# Embedded Systems - Project2: Car Parking System

This project is done for the Embedded Systems Course at the American University in Cairo in Spring 2021.<br/>
Instructor: Dr. Mohamed Shalan <br/>

Done By:
- Dareen Hussein 
- Marwa Sulaiman 
- Zahraa Shehabeldin <br/>

## Project Idea
We propose an embedded based car parking system that presents a solution to better organize and monitor the free and occupied parking spaces and reduce the parking traffics and time wastages.

The car parking system proposes booking to parking slots at the entrance. To clarify, the available, occupied, and booked parking slots are shown on a screen in the entrance, and the driver gets to choose one of the available slots to book through a message sent by his/her phone. The MCU is connected to a Bluetooth module that receives this booking and changes the chosen slot from ‘Empty’ to ‘reserved’ on the screen, and once the driver parks the car, the slot will be displayed as ‘Full.’ All the parking slots are provided with IR sensors that detect whether each slot is occupied or not and sends this information to the MCU on a real-time basis, so it always displays accurate data. 

## Objective

The main objective of this project is to implement a smart parking system in order to reduce the problems such as traffic congestion in parking spaces.
The prime objectives of this project are:
* Provide a new and more organized method to park a vehicle.
* Provide information about the vacant slot where the vehicle has to be parked.
* Provide proper management with context to traffic management in parking areas, thus saving time for the driver.

## Components
### Software components:
* Keil uVision 5
* STM32CubeMX
* Android Studio

### Hardware components:
* STM32 Nucleo-32: STM32L432KC
* Bluetooth Module: HC-06
* 6x IR Infrared Object Detection Sensors FC-51
* SSD1306 0.96 inch I2C OLED
* L293D chip (h bridge)
* DC Motor
* 8x LEDs


## Architecture

#### Large scale architecture:

It is be implemented using a WiFi TCP connection between a centralized master of an ESP 8226 microcontroller with a built-in wifi module that is connected to many slaves of STM32 microcontrollers through an external WiFi module.

<img src="https://github.com/ZahraaShehabeldin/Embedded-Project-2/blob/main/WiKi-Images/large%20scsle%20system.PNG"/>
<br/>

#### Current system architecture: 

<img src="https://github.com/ZahraaShehabeldin/Embedded-Project-2/blob/main/WiKi-Images/parking%20diagram.PNG"/>

### Example of how the parking area looks like: 

<img src="https://github.com/ZahraaShehabeldin/Embedded-Project-2/blob/main/WiKi-Images/parking.jpg" width="350" height="250"/>

### Example scenario:
* A car driver enters the parking area and chooses slot no.6 out of the displayed available slots. 
* Slot 6 is then marked "Booked", so it can’t be chosen by the next driver in line.
* When the driver parks his car in slot 6, the IR sensor will detect that the slot is occupied and send this data to the MCU to mark the parking status as "Full".
* However if the driver didn't reach his parking slot within a duration of 10 mins, the parking status is then changed into "Empty".
* Once the park becomes free again, the IR will detect it, and it will be marked as "Empty" in the display.
<br/>

<img src="https://github.com/ZahraaShehabeldin/Embedded-Project-2/blob/main/WiKi-Images/fc.jpeg" width="400" height="550"/>


#### Circuitry Connections: 
Top View

<img src="https://github.com/ZahraaShehabeldin/Embedded-Project-2/blob/main/WiKi-Images/WhatsApp Image 2021-05-06 at 5.40.18 AM.jpeg" width="350" height="250"/>

Front View

<img src="https://github.com/ZahraaShehabeldin/Embedded-Project-2/blob/main/WiKi-Images/WhatsApp Image 2021-05-06 at 5.40.18 AM (1).jpeg" width="350" height="250"/>

## Implementations

### Code Structure:

* FreeRTOS
   * Achieves a Real-time based system
   * Used to implement synchronization between multiple tasks

* Main Functions
   * Reading sensors
   * Displaying on OLED
   * Handling booking through BT
   * Controlling DC Motor

* Libraries
   * OLED
   * DC Motor

### Technical challenges:
1. OLED configuration and integration to the system.
2. Booking system implementation.
3. Researching system large scale.
4. Microcontroller malfunctioning.
5. Integrating system modules.

## Potential improvements

- The driver can get a password via Bluetooth at the main parking entrance that will be used while entering the chosen parking slot.
-  A keypad and a boom barrier will be provided at every slot. The password is entered in a keypad, and if it’s correct, a boom barrier will open, and the driver gets access to enter the parking. Otherwise, it generates an alarm for security and alerts the administrator for unauthenticated exit/theft.

- Another thing is, implementing this application on a larger scale, as due to time and materials availability restriction, we are implementing over one lane, but further improvements include integrating larger scale with more lanes according to the parking availability and requirements. 

## Milestones
- Phase 1: Set on the Project Idea and design the Proposal.
- Phase 2: Implement the system connections then test & tune the sensors with the MCU
- Final Phase: Fix the errors faced in implementation in phase 2. Also, work on the automatic gate using a DC motor and a sensor detecting the cars at entry. Finally, do a whole system testing and tuning and finalize the project.


## Slides link
For Phase 1, kindly check [this link](https://docs.google.com/presentation/d/16VzrCFKKfvxo0mosMrF5KoRkvmuDUxT5BY3MVo3UGPo/edit?usp=sharing).

For Phase 2, kindly check [this link](https://docs.google.com/presentation/d/1XmCyIk8GSd0yji6glnmEbfAMFlizP-_yew1aWbW0Km8/edit?usp=sharing).

## Video presentation link
For Phase 1, find the proposal video [here](https://drive.google.com/file/d/1PLYriexlz2okmX9REb7Ax7ZrwN9vtZ5j/view?usp=sharingv).

For Phase 2, find the demo video [here](https://drive.google.com/file/d/1g6oaHcHdrlzaMgjIEIEJfCR8ly4W4v2O/view?usp=sharing).

While for the Final Phase, find its demo video [here]().
 
## References
* Bachani, Mamta, et al. “Performance Analysis of Proximity and Light Sensors for Smart Parking.” Procedia Computer Science, vol. 83, 2016, pp. 385–392., doi:10.1016/j.procs.2016.04.200.
* Esp8266. (n.d.). Retrieved April 28, 2021, from https://www.espressif.com/en/products/socs/esp8266
* Lad , Hitesh, and Vibhuti Joshi. “Vehicle Parking Management Using Embedded System.” International Journal of Engineering Science and Innovative Technology (IJESIT), July 2013.
* NUCLEO-F446RE. (n.d.). Retrieved April 29, 2021, from https://www.st.com/en/evaluation-tools/nucleo-f446re.html
* Reve, Satish, and Sonal Choudhri. “Management of Car Parking System Using Wireless Sensor Network.” International Journal of Emerging Technology and Advanced Engineering, July 2012. 
