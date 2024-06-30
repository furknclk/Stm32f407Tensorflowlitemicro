Stm32f407Tensorflowlitemicro
TensorFlow Lite Micro HelloWorld application on STM32F407VG Discovery board

It is sufficient to place the downloaded libraries in the same directory as the source code. The address definitions have been made in the project file. The example tflite model that is run is the HelloWorld application from the tinyML book written by Pete Warden. The debug console has been modified to work on the STM32F407.

About the model::
The model is trained to predict the sine function value of angle inputs given in radians. The predictions obtained from the model are applied as a PWM signal to the D4 pin on the board. A different model you train will also work without any problems.
