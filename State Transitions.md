State Machine Layout\
**Data Rates:**\
  	High = 35hz\
  	Medium = 10hz\
 	Low = 1Hz\
**Startup / State-Switcher**\
	Trigger: Power-on\
	Connect sensors\
	Accels\
	Barometer & Temperature Sensor\
	Zero altitude until State 3\
	Gyros\
	Select state given condition\
**Manual State-Switcher**\
	If signal received from ground, select state based on signal\
**State 1: Ground Idle**\
	Trigger: Selection by State 0\
	Connect telemetry radio\
	Low-hertz refresh rate on telemetry\
**State 2: Launch Ready**\
	Trigger: Manual\
	GPS Connection\
	High transmit rate on telemetry (all the way till State 9)\
	Reading from both accelerometers\
	SD card datalogging; very low rate 1hz\
	Camera manual enable\
	GS Signal Tests\
	Gyroscope Bias Calculations\
**State 3: Powered Ascent**\
	Trigger: Accelerometer > 13G || Manual\
	Logging High-G accelerometer and low G,  reading and transmitting only chosen accel\
	High SD card log rate\
	Gyroscopes connected and begin to be logged and transmitted\
**State 4: Unpowered Ascent**\
	Trigger: Accelerometer < 2G\
	Switch to low-G accelerometer reading\
	Check for under 16g\
	Medium SD card log rate\
**State 5: Separation**\
	Trigger: Accelerometer Body Axis X axis > 4G\
	Separation Confirmation\
**State 6: Parachute Descent**\
	Trigger: Barometer Δalt < 0 more than 1 second\
	Timer to allow stabilization, as well as waiting for manual confirmation\
	High speed SD card logging\
**State 7: Roll Control**\
	Trigger: Timer or Manual\
	DC Motor is digitally connected\
	Control is given to PID algorithm, to stabilize the camera\
	If PWM signal is at +- 255 for more than 5 seconds, shut down the servo\
**Manual Roll Control**\
	Trigger: Manual\
	Telemetry will send a new PID setpoint\
	Note that inputs wll be constantly sent until it is confirmed by an output, or a new input is sent\
**State 8: Landing**\
	Trigger: Barometer < 50m\
	Camera manual disable, or automatically disabled when switched to State 9\
	DC Motor disabled\
	Telemetry transmit rate is medium\
	SD logging rate is medium\
**State 9: Mission Complete**\
	Trigger: <2.5° degrees of movement, barometer < 20m, for 5 seconds, time since flight greater than 1 minute || manual\
	Sensors disconnected after 10 seconds in this state\
	GPS sends location much more slowly now\
	Telemetry transmit rate is low\
	SD logging rate is 0\
