
//calculate mean for one dimension/channel (pin) of sensor data
float getMean(short* dimension_data){
    
    short sum = 0;
    for(short i=0; i<steps; i++) {
      sum += dimension_data[i];
   
    }
    float mean = (float)sum/(float)steps;
    //Serial.println("mean");
    //Serial.println(mean);
  
  return mean;
}

//calculate standard deviation for one dimension of sensor data
float getDeviation(short* dimension_data, const float mean){

  float sum = 0;
  
  for(short i=0; i<steps; i++) {
    
    sum += sq(dimension_data[i] - mean);
    
    }

    float deviation = sqrt( (1/(float)steps) * (float)sum);
    //Serial.println("deviation");
    //Serial.println(deviation);
    
  return deviation;
}

//normalize one dimension
void normalize(short* dimension_data) { //const float mean, const float deviation) {

  float mean = getMean(dimension_data);
  //Serial.println(F("mean"));
  //Serial.println(mean);
  float deviation = getDeviation(dimension_data, mean);
  //Serial.println(F("deviation"));
  //Serial.println(deviation);

  //make sure to only normalize if standard deviation is not 0 
  if (deviation != 0) {
 
    //transform to integer for less space
    for(short i=0; i<steps; i++) {
        dimension_data[i] = ((dimension_data[i] - mean) / deviation) * 100;
      }
    }
  }
