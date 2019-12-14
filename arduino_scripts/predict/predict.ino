boolean measure = false;
const short duration = 2000;
const short pause = 25;
const short steps = 80;
const short smoothing = 0;

const short size_inPins = 7;
short inPins[size_inPins] = {A1, A2, A3, A4, A5, A6, A7};
const short n_classes = 2;
const short target[n_classes] = {1, 2};
const short centroid_1[][steps] = {{-89, 39, -28, 10, 17, 17, 19, 35, 24, 23, 25, -11, 38, 27, 46, 63, 66, 78, 99, 65, 44, 31, 72, 63, 47, 32, 50, 42, 66, 21, 3, -28, -34, -68, -94, -90, -85, -91, -106, -115, -114, -120, -131, -128, -142, -154, -194, -178, -140, -140, -141, -120, -108, -69, -56, -19, 18, 30, 33, 30, 49, 49, 56, 53, 107, 148, 83, 90, 95, 91, 87, 115, 110, 126, 103, 84, 78, 78, 83, 83}, {-53, 53, 44, 40, 43, 42, 43, 25, 41, 48, 53, 56, 49, 81, 101, 107, 111, 105, 102, 95, 88, 60, 18, 1, -9, -24, -50, -35, -56, -32, -21, -25, -54, -77, -99, -123, -147, -149, -144, -129, -124, -132, -143, -166, -159, -158, -162, -177, -165, -166, -163, -137, -107, -69, -23, -17, -3, 24, 39, 33, 38, 38, 43, 63, 76, 98, 96, 101, 102, 98, 108, 110, 111, 115, 109, 114, 115, 114, 119, 123}, {-50, 60, 75, 44, 40, 39, 40, 30, 43, 40, 40, 13, 68, 38, 56, 74, 79, 92, 120, 108, 99, 78, 89, 56, 52, 53, 39, 42, 44, 20, -14, -45, -70, -103, -112, -113, -122, -126, -137, -145, -119, -138, -140, -154, -159, -169, -186, -165, -158, -158, -155, -130, -112, -83, -55, -49, -25, -10, 25, 53, 63, 63, 64, 71, 75, 79, 112, 112, 112, 112, 105, 98, 87, 82, 76, 77, 74, 77, 87, 94}, {-13, 55, 6, 31, 34, 34, 35, 31, 36, 36, 37, 56, 56, 28, 45, 45, 44, 48, 62, 62, 60, 50, 68, 45, 31, 14, -5, -40, -50, -67, -90, -92, -115, -115, -135, -139, -139, -140, -139, -140, -139, -142, -145, -149, -149, -147, -144, -138, -133, -132, -128, -120, -112, -86, -47, 17, 41, 60, 86, 107, 126, 126, 128, 121, 136, 110, 134, 136, 143, 147, 145, 143, 145, 146, 147, 136, 133, 131, 126, 123}, {-44, 49, -46, 35, 40, 39, 38, 25, 37, 36, 35, 56, 68, 57, 39, 50, 53, 64, 76, 65, 64, 33, 38, 24, 19, -2, -12, -27, -42, -57, -71, -92, -107, -106, -112, -113, -117, -119, -122, -124, -131, -131, -132, -140, -137, -137, -145, -143, -130, -126, -124, -118, -107, -86, -60, -15, 22, 31, 48, 60, 64, 64, 63, 77, 92, 153, 120, 122, 128, 125, 137, 141, 134, 127, 121, 124, 133, 127, 119, 113}, {4, 102, 102, 104, 99, 99, 99, 98, 101, 102, 105, 122, 123, 128, 110, 92, 88, 73, 48, 28, 4, -19, -36, -51, -62, -73, -79, -86, -89, -84, -81, -90, -90, -97, -100, -102, -104, -106, -107, -107, -108, -108, -109, -106, -111, -113, -120, -118, -121, -121, -119, -112, -108, -101, -97, -93, -81, -63, -46, -24, 3, 3, 13, 28, 55, 83, 59, 60, 60, 60, 60, 64, 68, 76, 89, 97, 102, 106, 113, 113}, {-16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, 112, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, 624, -16, -16, -16, -16, 496, -16}};
const short centroid_2[][steps] = {{48, -28, -119, -40, -36, -30, -25, 14, 118, 12, 12, 13, 5, 13, 15, 39, 32, 85, 60, 67, 64, 56, 52, 108, 18, -25, -38, -106, -53, -45, -32, -51, -41, -28, -63, -99, -102, -101, -89, -67, -24, -57, -90, -108, -103, -126, -103, -39, -14, 49, 33, 13, 46, 114, 79, 59, 61, 129, 70, 69, 59, 50, -3, -14, -6, 4, -7, -18, 2, -5, 42, -16, 82, 0, -1, -13, -2, 12, 15, -2}, {140, 52, 39, 3, 1, 6, 5, -34, -12, -18, -18, -16, -11, 3, 18, 24, 23, 16, 17, 18, 20, 20, 20, 17, -8, -13, -39, -22, -72, -87, -92, -105, -127, -146, -152, -166, -167, -165, -165, -164, -188, -157, -145, -119, -107, -100, -82, -91, -79, -74, -12, 10, 56, 61, 59, 67, 70, 55, 84, 94, 105, 110, 113, 123, 129, 134, 141, 141, 149, 145, 122, 109, 84, 102, 97, 90, 86, 77, 80, 89}, {-83, -141, -166, -151, -154, -155, -149, -151, -146, -119, -119, -106, -86, -57, -28, 3, 37, 63, 79, 80, 64, 56, 56, 86, 88, 94, 86, 36, 96, 108, 127, 136, 145, 141, 106, 91, 62, 28, 23, 32, 36, 33, 48, 65, 85, 99, 75, 94, 77, 98, 94, 126, 112, 96, 53, 48, 46, 51, 43, 50, 86, 50, 7, -23, -44, -56, -79, -88, -79, -70, -67, -62, -55, -57, -55, -55, -55, -56, -64, -66}, {-73, -113, -120, -118, -118, -119, -118, -131, -112, -94, -94, -81, -65, -38, -9, 12, 25, 30, 37, 40, 45, 50, 51, 90, 81, 93, 129, 140, 147, 143, 145, 137, 137, 140, 139, 142, 139, 133, 122, 118, 105, 104, 109, 104, 96, 86, 84, 103, 85, 74, 37, 23, 17, 9, 1, -5, -11, -31, -34, -40, -43, -56, -62, -68, -72, -78, -79, -76, -74, -76, -77, -96, -108, -101, -103, -109, -109, -106, -100, -97}, {-80, -122, -139, -115, -114, -112, -101, -110, -107, -69, -69, -38, -28, -11, 16, 23, 45, 67, 95, 99, 105, 97, 96, 109, 139, 137, 135, 145, 125, 121, 117, 119, 114, 107, 110, 100, 105, 105, 107, 106, 80, 95, 89, 88, 92, 98, 100, 93, 75, 74, 23, 11, 10, -10, -3, -16, -27, -44, -41, -44, -44, -50, -55, -69, -73, -72, -67, -72, -75, -74, -91, -88, -107, -105, -107, -106, -106, -111, -115, -119}, {-41, -94, -105, -103, -104, -104, -102, -109, -94, -94, -94, -92, -91, -83, -73, -61, -42, -10, 11, 20, 24, 26, 28, 91, 96, 115, 133, 139, 139, 139, 135, 135, 130, 130, 124, 124, 120, 115, 112, 112, 110, 110, 113, 115, 119, 119, 118, 124, 115, 92, 51, 28, 7, -22, -30, -43, -47, -73, -60, -62, -67, -70, -79, -85, -85, -81, -82, -81, -79, -79, -97, -89, -83, -86, -87, -88, -89, -90, -91, -91}, {-16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, 624, -16, -16, -16, -16, 625, -16}};

//bluetooth communication library
#include <ArduinoBLE.h>
//set up service and characteristic for BLE communication
BLEService classificationService("f36aa955-0c78-43b6-bcb6-1b4d37b2c80b");
BLEShortCharacteristic classificationInt("62855a59-0dcf-4fc3-8417-89f93f334222", BLERead | BLENotify);


//use pin D5 for starting measurement
const int button_pin = 5;
int button_state = 0;

#include "MegunoLink.h"
#include "Filter.h"
const int filterIntensity = 1;
ExponentialFilter<long> A1Filter(filterIntensity, 0);
ExponentialFilter<long> A2Filter(filterIntensity, 0);
ExponentialFilter<long> A3Filter(filterIntensity, 0);
ExponentialFilter<long> A4Filter(filterIntensity, 0);
ExponentialFilter<long> A5Filter(filterIntensity, 0);
ExponentialFilter<long> A6Filter(filterIntensity, 0);
ExponentialFilter<long> A7Filter(filterIntensity, 0);
long currentMillis = 0;
long lastMeasurement = 0;

void setup() {

  Serial.begin(9600);

  //check BLE connection
  if(!BLE.begin()) {

    Serial.println("starting BLE failed!");
    while(1);
  }

  //further set up of service and characteristic
  BLE.setLocalName("GestureClassification");
  BLE.setAdvertisedService(classificationService);
  classificationService.addCharacteristic(classificationInt);
  BLE.addService(classificationService);

  BLE.advertise();

}

void loop() {

    //initialize input pins
  //run once

  if(!measure) {

    for (short i = 0; i< size_inPins; i++){

          //Serial.println(inPins[i]);
          pinMode(inPins[i], INPUT);
    }
    pinMode(button_pin, INPUT_PULLUP);

    measure = true;


   //end initializing


   //start actual loop
  while (measure) {

     //connect to BLE central device
     BLEDevice central = BLE.central();

     button_state = digitalRead(button_pin);

     //start measuring if button is pressed
     if (button_state == LOW) {


      int sensor_data[steps][size_inPins];
      int startMillis = millis();
      int currentStep = 0;

      while (currentMillis < (startMillis+duration)){
        currentMillis = millis();

          delay(1);
          int RawValueA1 = analogRead(A1);
          A1Filter.Filter(RawValueA1);
          int RawValueA2 = analogRead(A2);
          A2Filter.Filter(RawValueA2);
          int RawValueA3 = analogRead(A3);
          A3Filter.Filter(RawValueA3);
          int RawValueA4 = analogRead(A4);
          A4Filter.Filter(RawValueA4);
          int RawValueA5 = analogRead(A5);
          A5Filter.Filter(RawValueA5);
          int RawValueA6 = analogRead(A6);
          A6Filter.Filter(RawValueA6);
//          int RawValueA7 = analogRead(A7);
//          A7Filter.Filter(RawValueA7);

         if (currentMillis >= lastMeasurement + pause) {  //
            lastMeasurement = millis();

        //    for (int i = 0; i < steps; i++) {
            sensor_data[currentStep][0] = A1Filter.Current();
            sensor_data[currentStep][1] = A2Filter.Current();
            sensor_data[currentStep][2] = A3Filter.Current();
            sensor_data[currentStep][3] = A4Filter.Current();
            sensor_data[currentStep][4] = A5Filter.Current();
            sensor_data[currentStep][5] = A6Filter.Current();
//            sensor_data[currentStep][6] = A7Filter.Current();
            currentStep++;

      /*    for (int j = 0; j < size_inPins; j++) {


            sensor_data[i][j] = analogRead(inPins[j]);

            }
            */
        // delay(pause);
    //    }
      }
    } //end while
       //write out sensor data for Anschaulichkeit
	Serial.println();
        for(short i=0; i<steps;i++){
          if(i>0){
            Serial.print(F(";"));
           }

          for (short j = 0; j<size_inPins; j++) {
           if(j>0){
             Serial.print(F(","));
           }
            Serial.print(sensor_data[i][j]);
          }
        }
      Serial.println();

     // compute distance with dtw
		int distance_1 = 0;
		int distance_2 = 0;
	
	//compute distance per dimension and add them for multidimensional DTW (simple approach)
     	short sensor_data_dim[steps];
    
     	for (short i=0; i<size_inPins; i++) {
          	for (short j=0; j<steps; j++) {
              	sensor_data_dim[j] = sensor_data[j][i];
            
          	}

		//smooth out measurement errors
   		smooth((short*)sensor_data_dim);

		//normalize with z-transformation
		normalize((short*)sensor_data_dim);

 		Serial.println();
       
          	for (short j = 0; j<steps; j++) {
           	 if(j>0){
             	  Serial.print(F(","));
           	}
            	 Serial.print(sensor_data_dim[j]);
          	}
        
      		Serial.println();

		distance_1 = distance_1 + dtw((short*)sensor_data_dim, (short*)centroid_1[i], steps, steps, 0.25);
		distance_2 = distance_2 + dtw((short*)sensor_data_dim, (short*)centroid_2[i], steps, steps, 0.25);

		//get class during last iteration

		if(i==size_inPins-1){

		Serial.println(distance_1);
		Serial.println(distance_2);
				int all_distances[n_classes] = {distance_1, distance_2};
	//get class of smallest distance

        short predict_class_index = 0;
        for(short i = 1; i<n_classes;i++) {
            if (all_distances[i] < all_distances[predict_class_index]) {
                 predict_class_index = i;
                 }
            }
            short predict_class = target[predict_class_index];
	    Serial.print(F("Class: "));
            Serial.print(predict_class);

	    //send class via BLE
	    classificationInt.writeValue(predict_class);


            }

      }
       //set button back to low
       //digitalWrite(button_pin, LOW);
     }
    }
   }
}
