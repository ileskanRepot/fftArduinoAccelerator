/**
  @file read9axis.ino
  @brief This is an Example for the FaBo 9Axis I2C Brick.

   http://fabo.io/202.html

   Released under APACHE LICENSE, VERSION 2.0

   http://www.apache.org/licenses/

  @author FaBo<info@fabo.io>
*/

// Due bad naming habits rollingList is named rolling list even tho it uses Array everywhere (list -> Linked list, Array -> Memory block)
#include "rollingList.h"
#include <Wire.h>
#include <arduinoFFT.h>
#include <FaBo9Axis_MPU9250.h>

FaBo9Axis fabo_9axis;


const int PADDED_ARR_LEN = 128;
float IMG_ARR[PADDED_ARR_LEN];

RollingList DATA_LIST = RollingList(75, PADDED_ARR_LEN);
float *DATA_LIST_POINTER = DATA_LIST.toPaddedArray();
const int FREQ = 10;

// Initialize Arduino FFT object. Set pointer to real data list, imaginary data list, data length and data frequency
ArduinoFFT<float> FFT = ArduinoFFT<float>(DATA_LIST_POINTER, IMG_ARR, PADDED_ARR_LEN, FREQ);

void setup() {
  Serial.begin(115200);
  Serial.println("RESET");
  Serial.println();

  Serial.println("configuring device.");

  // Set imaginary array to be zero
  for (int ii = 1; ii < PADDED_ARR_LEN; ii++) {
    IMG_ARR[ii] = 0;
  }

  if (fabo_9axis.begin()) {
    Serial.println("configured FaBo 9Axis I2C Brick");
  } else {
    Serial.println("device error");
    while (1);
  }
  Serial.println("Energy, Az");
}

float pow2(float num){
  return num * num;
}

/**
   Calculate the normalized short-time energy of frames
   https://github.com/kosme/arduinoFFT/wiki

   @return the short time "energy"
*/
float calculateNormalizedShortTimeEnergy() {
  // Compute Fast Fourier Transform
  FFT.compute(FFTDirection::Forward);

  float energy = 0;

  // Sum the "energy" across frequency bins
  for (int ii = 0; ii < PADDED_ARR_LEN / 2; ii++) {
    // Absolute value
    float absoluteValue = pow2(DATA_LIST_POINTER[ii]) + pow2(IMG_ARR[ii]);
    energy += absoluteValue;
  }

  // Normalize the energy
  float normalizedEnergy = energy / pow2(PADDED_ARR_LEN / 2);
  
  return normalizedEnergy;
}

void loop() {

  // Initialize three axis acceleration variables
  float ax, ay, az;
  
  // Read to the three axis acceleration variables
  fabo_9axis.readAccelXYZ(&ax,&ay,&az);

  // Set z-axis acceleration to rolling Array
  DATA_LIST.set(az);

  // Set Imaginary array to zero
  for (int ii = 0; ii < PADDED_ARR_LEN; ii++) {
    IMG_ARR[ii] = 0;
  }

  // Compute the padded array from the rolling Array
  DATA_LIST.toPaddedArray();

  // Calculate the short time energy
  float shortTimeEnergy = calculateNormalizedShortTimeEnergy();

  // Print short time energy and velocity
  Serial.print(shortTimeEnergy);
  Serial.print(", ");
  Serial.println(pow2(az));
  
  delay(FREQ);
}
