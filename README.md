# MP2-Midterm-Assessment

My Solution For The Advanced Microprocessor Systems Course Midterm Assessment.
The assessment consists of 4 design problems using Arduino Uno board, various sensors, and simulated using [SimuLIDE](https://www.simulide.com/p/home.html)

## Skills

- Arduino GPIO
- Interrupts
- Non-Blocking Delay with `millis()`
- Interfacing With LCD
- Interfacing With Motors
- Keyboard

## Task 1

### Requirement

It is required to connect a LED to pin 8 of Arduino uno board. Use one Tact switch connected to pin 10 to control it. This LED should be turned off at tact high and turned on at tact low.

### Results

!["s"](./Task%201/Simulation.gif)

## Task 2

### Requirement

It is required to build a light circle. It contains 12 LEDs and is controlled using a Push button. Each time the button is pressed, the system changes LED sequence direction with three seconds between each LED and the next one in the clockwise case and one second for the anticlockwise case

### Results

!["s"](./Task%202/Simulation.gif)

## Task 3

### Requirement

It is required to build an automatic kitchen ventilation fan that works also as kitchen hood. If there is smoke it works as a kitchen hood to absorb it. If there is no smoke and the temperature is more than 25 degrees, it works as a fan. Otherwise, the motor is stopped. An always on LCD is used to display the current temperature

### Results

!["s"](./Task%203/Simulation.gif)

## Task 4

### Requirement

Instead of programming Arduino uno to do certain tasks, it is required to program Arduino uno to be user programmable. You need to develop a very simple programming language. A 4 X 4 keypad is connected to 8 pins of the Arduino containing numbers from 0 to F. To start programming the user has to press 0. You allow the user
to use two internal variables Var1 and Var2. Two digital output pins connected to two LEDs Yellow and Red, All pins

### Results

!["s"](./Task%204/Simulation.gif)
