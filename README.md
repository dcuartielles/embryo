# embryo

## Description

Step by step construction of a state machine for EIT Manufacturing's EMBRYO educational metal press machine.

## Installation

### First Method

1. Navigate to the Releases page.
2. Download the latest release.
3. Extract the zip file in your Arduino's Sketchbook
4. In the Arduino IDE, navigate to File > Sketchbook > EMBRYO-X.Y.Z

## Features

- ### Official dependencies

    Code examples depend on the official EduIntro library.

- ### Easy to use

    It is simple, basic and very easy to understand. Just import the code collection in your Sketchbook and try out the different examples.

- ### Complete package for the EMBRYO machine

    Learn how to use the machine from scratch and step by step build a reliable state machine that will give you access to all of its capabilities.

- ### Intuitive syntax

    The code has a simple and intuitive syntax to handle variables and functions.

- ### Give back

    EMBRYO is free for everyone. Everyone can download and use it in their projects, assignments or anywhere for free.

## Components and functions

This is an example of how code can be built iteratively around a certain machine but slowly adding improvements to the core software. Here a list of components of the code

  - ### Architecture
    Includes information about the system itself, the pinouts to the connected sensors and actuators, and constructs to navigate through them

  - ### Comm Functions
    Functions dedicated to send and receive informaiton via Serial port

  - ### Data Functions
    Handling of the information from sensors, arranging into easy to compare arrays, etc

  - ### States
    Definitions of names of states to make the code easier to read
        
## General code structure

There are many examples implemented in this repository. Below are shown some of the examples.

  - ### 03 Machine Status Serial Control
    In this example, the machine offers a bi-directional communication port to the computer for you to send commands to it and collect information in real time. The main loop responds to the structure:

``` C++
void loop() {
  // Check the inputs
  readInputs();

  // Serial terminal
  serialCheck();

  // Print out the inputs if there is an event
  if (inputEvent()) {
    printInputs();
  }

  // Copy arrays of inputs to check state changes
  copyInputs();
}
```

## Versions

### v0.0.1 (Current Stable version)

#### April, 2021

* Initial release of examples

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell others about this code
- Contribute new protocols

Please read [CONTRIBUTING.md](https://github.com/AghaSaad04/EduIntro/blob/master/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Credits

Created and maintained by D. Cuartielles, Malmo, 2021

Based on previous work by:

- F. Troya, Malmo, 2020
- [Arduino community](https://www.arduino.cc)

## Current stable version

**number:** v0.0.1

**codename:** Jokkmokk

## License

This library is licensed under [GPLv3](https://www.gnu.org/licenses/quick-guide-gplv3.html).
