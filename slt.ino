#include "flex_sensor.h"

const int n_sensors = 2;
struct flex_sensor flex_sensors[n_sensors];

void init_flex_sensors() {
  flex_sensor_init_with_pin_no(&flex_sensors[0], A0);
  flex_sensor_init_with_pin_no(&flex_sensors[1], A1);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 9600 );
  init_flex_sensors();
  for( int i=0; i<n_sensors; i++ ) 
    pinMode( flex_sensors[i].pin_no, INPUT );
}

void loop() {
  // put your main code here, to run repeatedly:
  for( int i=0; i<n_sensors; i++ ) {
    calculate_flex_sensor_parameters( &flex_sensors[i] );
  }

  print_flex_sensors_info( flex_sensors, n_sensors );
  delay( 1000 );
}
