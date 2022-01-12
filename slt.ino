#include "flex_sensor.h"
#include "imu.h"

const int n_sensors = 5;
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
  imu_setup()
}

void loop() {
  // put your main code here, to run repeatedly:
  for( int i=0; i<n_sensors; i++ ) {
    calculate_flex_sensor_parameters( &flex_sensors[i] );
  }
  print_flex_angles( flex_sensors, n_sensors );
  imu_loop();
  delay( 1000 );
}
