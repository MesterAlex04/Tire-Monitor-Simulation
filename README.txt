This project is a simulation of a tire monitoring sysyem. This project was made using C++ in Arduino IDE. The components used are: 
-1 DHT11;
-1 KY-40 Rotary Encoder;
-1 KY-024 Hal Effect Sensor Module;
-1 led, 1 330 ohm resistor;
-1 Arduino UNO R3 microcontroller;
-jumpwires.
One big improvement I made to this project was that at first, I used two buttons for the "LOW TIRE PRESSURE" and "HIGH TIRE PRESSURE", but then decided to instead use the rotary encoder, since I can actually give values to the microcontroller.
During the project I met some problems with the sensors, because I had to make adjustments to the code. For example, after I implemented the DHT11, I had to remove the delay at the end of the code since in the serial monitor it kept printing "Failed to read from the DHT sensor!". I quickly found out how to fix this problem, by implementing a non-blocking delay.
This project helped me understand how to implement multiple sensors and make it functional, how a Hal Effect Sensor works and how I can use it to calculate the RPM of a wheel, and most importantly it taught me that careful planning and understanding of component limitations are crucial for a successful project.

