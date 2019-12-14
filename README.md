# fingerspelling-gesture-glove
 Nearest Centroid IMplementation for recognizing Fingerspelling Gestures from Sensor Glove
 -- Fork from https://gitlab.com/linev8k/in-hand-gesture-glove

Thanks again to Jocelyn Ziegler for letting me use her code!!!

# Original README:

## Hand-In Gesture Glove Code
This repository contains code for training and classification of sensor data with Arduino. It is currently used and tested (only) for a self-built hand-in gesture glove.

## Getting Started
Everything runs via python scripts (Python 3).

## Prerequisites
The following (non-standard) python packages need to be installed:
numpy
pyserial
scipy
matplotlib
For managing the upload of Arduino scripts
arduino-cli
needs to be installed.

## Installing
Clone the repository and go into the respective directory in your terminal.

# Use

## Run it
Make sure your Arduino is connected to the computer via USB.
Run the training script like this (with default settings):
python3 trainArduino.py
To see default settings and options to change them, run
python3 trainArduino.py -h
An example using multiple options:
python3 trainArduino.py -m false -n some_data -p A2 A4 -s 0 -usb COM5 -ent true

## Training
The training script will be uploaded automatically to your Arduino.
Follow the instructions appearing in your terminal for training.
Training data will be saved in a txt file with the name specified for potential later use.
Note: By default this version relies on having a button connected to digital pin 5 to start measuring training instances. The option to not use a button can be specified when running the training script.

## Classification
The classification script will also be created and uploaded automatically after training.
It is possible to do this without training if a txt file with training data is specified.
Note: This version includes seeing classification results via bluetooth (BLE). To see classification results without USB connection, your Arduino has to be able to connect via BLE. You can use an app (e.g., LightBlue) or some BLE browser on your computer (e.g., Bluetility for Mac). The Arduino should appear as a device called GestureClassification. Subscribe for instant result updates.
This works only if the data is measured with a connected button. If no button is used, input 's' into the Arduino serial monitor to start measuring. Classification results will be outputted there.

## Methods used
This is a Nearest centroid classifier. For each class the average over the measured time series is calculated and stored. The centroid with the least distance to newly measured data determines the predicted class. As measure of distance as well as for calculation of the centroids DTW (Dynamic Time Warping) is used.

# Other Sources
Links to other code this repository makes use of:
https://github.com/fpetitjean/DBA/blob/master/DBA_multivariate.py

https://github.com/ncanac/dtw/blob/master/dtw.c
