# fftArduinoAccelerator

Fast fourier transform of acceleration data with Arduino

## Implementation

Arduino has a package `arduinoFFT` which I use to calculate the fft and `FaBo9Axis_MPU9250` which I use to read the accelaration data from `MPU-9250` chip.

For every `loop` I read acceleration data, set it to the rolling list, set `IMG_ARR` to zeros, compute array from `RollingList` and calculates the short time energy.

## calculateNormalizedShortTimeEnergy

It first sets new `float*` for the `FFT` object, computest the fft, sums the absolute values of all data points and divides it with length of the return array.

## Rolling List

`RollingList` is a object that can be store `n` last data points and insert new data point in O(1) time. Unfortunately the `arduinoFFT` need a array so I need to convert `RollingList` to array which is O(n) operation so I didn't save any time after all.

Due bad naming habits `RollingList` is named `Rolling"List"` even tho it uses Arrays everywhere (list -> Linked list, Array -> Memory block)

## Unfortunate mistakes in my implementation

_Currently, there are only 75 samples (not 100). If I try to add it to 100, the arduino crashes._ I assume it is due to running out of memory. Arduino Uno R3 has 2KiB /(Kiki Bytes) of SRAM and size of float is 4B (Bytes). This program has two 128 float arrays and one 75 float array. Let's assume we had an array of 100 floats instead of 75 floats.

$2\text{KiB} - (2 \cdot 128 \cdot 4\text{B} + 100 \cdot 4 \text{B}) = 624 \text{B}$

624 Bytes of memory for everything else we need to store which I assume is not enougth for `FaBo9Axis_MPU9250`, `arduinoFFT` and all my variables.

- [Size of float](https://www.arduino.cc/reference/en/language/variables/data-types/float/)
- [Size of memory](https://wiki-content.arduino.cc/en/Tutorial/Foundations/Memory)

## Picture of my Arduino setup

!(Picture of my Arduino setup)[https://raw.githubusercontent.com/ileskanRepot/fftArduinoAccelerator/main/setup.jpg]
