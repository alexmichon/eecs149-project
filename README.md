# Wearable LEDs

## INNOVATIONS
> Hand signals are given by cyclists and some motorists to indicate their intentions to other traffic. Under the terms of the Vienna Convention on Traffic, bicycles are considered to be vehicles and cyclists are considered to be drivers. The traffic codes of most countries reflect this.<br>
In some countries (such as in the Czech Republic, Canada, and the United States), hand signals are designated not only for cyclists, but for every vehicle that does not have signal lights or has damaged signal lights. For example, drivers of older cars and mopeds may be required to make hand signals.

Similar to automobile signaling, there are three primary signals: Left turn/overtaking, Right turn, and Stopping/braking.<br>
From [Wiki Page Hand Signals](https://en.wikipedia.org/wiki/Hand_signals)

Although these hand signals will probably work fine during daytime, they may be very hard to be recognized by car drivers during night, which is our innovation to create a LEDs system that can effectively protect cyclists' night safety. In addition, the LED matrix can also react to the music playing in its vicinity, from which "Wearable Dance Party" derives.

## HARDWARES

For this project, we used the following hardwares:

1. [Arduino Nano](https://store.arduino.cc/usa/arduino-nano) as the microcontroller, for it has nice library support and it's open source, but finally we chose [Feather M0](https://learn.adafruit.com/adafruit-feather-m0-basic-proto) for it's more portable(it also supports Arduino's library). It has **256KB of FLASH** and **32KB of RAM**. And it's based on a ATSAMD21G18 **[ARM Cortex M0](https://developer.arm.com/products/processors/cortex-m/cortex-m0)** processor(**32bits**), which is clocked at **48MHz** and at **3.3V** logic.

2. The LEDs have to be sewable and addressable for we won't have enough pins to control those LEDs separately. [Neopixel](https://www.adafruit.com/product/1460) might be a good choice, which also has a reasonable price.

3. We used [Adafruit 9-DOF Accel/Mag/Gyro+Temp Breakout Board](https://www.adafruit.com/product/3387). 5 of them might be enough, for a IMU has every thing we need - 3-axes accelerometers, a gyroscope and even a magnetometer. Its accelerometers has **±2/±4/±8/±16 g ranges**. Its gyros have the same **±245/±500/±2000 dps** ranges.

4. Our sample rate must be twice the maximum frequency of interest, according to [Nyquist–Shannon sampling theorem](https://en.wikipedia.org/wiki/Nyquist%E2%80%93Shannon_sampling_theorem). So in this case, maybe 7000Hz is enough, for telephone networks work up to about 3400Hz(Although human can hear sounds up to 20kHz). Finally, we chose [Adafruit I2S MEMS Microphone](https://www.adafruit.com/product/3421), which has a range of about **50Hz - 15KHz**.

5. We will probably mount those LEDs on a Velcro. [VELCRO Brand Thin Fasteners Tape](https://www.amazon.com/VELCRO-Brand-Thin-Fasteners-Tape/dp/B0013AIAQ2/ref=pd_sim_229_13?_encoding=UTF8&psc=1&refRID=JYEME8QBZMPKE4HW1DJZ) is our choice.

## Software implementation

One way to handle transferring the high dimensional signal into simple categories is Machine Learning. [`LDA`](https://en.wikipedia.org/wiki/Linear_discriminant_analysis) plus [`Gaussian naive Bayes`](https://en.wikipedia.org/wiki/Naive_Bayes_classifier) will probably work for us, and **which is indeed the final version**. Alternatively, raw data window plus [`KNN`](https://en.wikipedia.org/wiki/K-nearest_neighbors_algorithm) using a [`dynamic time warping`](https://en.wikipedia.org/wiki/Dynamic_time_warping) should work, too.

The ability to take inputs from a serial port connected to a laptop will really help us to test/debug without really riding a bike. Also, if we wish to send back state/sensor information over the serial port, [protobufs](koti.kapsi.fi/jpa/nanopb/) is recommended by Marcel, one of our GSIs.

And we will use a state machine model to construct this whole system. The high level overview is in the `Docs` folder under the root directory.