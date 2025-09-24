# Arduino-Scale
Code to measure and display weight in pounds, including tare feature.

System Components:            
3 Load cells                
1 Load cell summing board     
1 HX711                
1 Arduino             
1 Push button            



Block Description:
A metal base-frame supports 3 load cells. Mounted to the load cells is another metal frame to create a weighing surface. On this upper frame, a standard agricultural use "Pro-box" is meant to be placed containing seed or fertilizer. The weight of the seed causes deformation in the load cells. As the load cells deform, the internal resistance changes, and results in a proportionally varied output voltage in milli-volts. The individual milli-volt signals from each load cell are fed into the load cell summing board. The output from this summing board is a milli-volt signal which is equal to the sum of all input voltages, effectively adding the weight from each individual load cell into a total weight. The voltage is then fed into the HX711 board, which recieves the signal and relays it onto the Arduino via a data a clock pin. The ardunio reads the value from the HX711, and converts it to pounds based on a hard-coded calibration factor and offset value. The arduino then prints the calculated weight value to the LCD display. A push button is also connected to the arduino. When the button is pressed, the ardunio looks at its current weight, and subtracts that value from the weight it is printing to the LCD. This effectively "tares" the scale. Functionally speaking, if 500lbs is sitting on the scale and displayed on the LCD, once you press the "tare" button, 0lbs will now be displayed on the LCD, despite 500lbs remaining on the scale.
