# GPCB
General purpose control boards based off Arduino nano Every

### test_board
pio project to help test the boards. To use, just uncomment the right function in loop()

### Feeder
basic feeder script. Activates the stepper motor when :
- The arduino recieves "FDR" from com
- The button is pressed
- A1 is activated

Dripper support will be implemented