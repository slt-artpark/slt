#include "flex_sensor.h"
#include "imu.h"

const int n_sensors = 5;
struct flex_sensor flex_sensors[n_sensors];

void init_flex_sensors() {
  flex_sensor_init(&flex_sensors[0], A0, R_DIV_0, FLAT_RESISTANCE_0, BEND_RESISTANCE_0);
  flex_sensor_init(&flex_sensors[0], A1, R_DIV_1, FLAT_RESISTANCE_1, BEND_RESISTANCE_1);
  flex_sensor_init(&flex_sensors[0], A2, R_DIV_2, FLAT_RESISTANCE_2, BEND_RESISTANCE_2);
  flex_sensor_init(&flex_sensors[0], A3, R_DIV_3, FLAT_RESISTANCE_3, BEND_RESISTANCE_3);
  flex_sensor_init(&flex_sensors[0], A4, R_DIV_4, FLAT_RESISTANCE_4, BEND_RESISTANCE_4);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 9600 );
  init_flex_sensors();
  for( int i=0; i<n_sensors; i++ ) 
    pinMode( flex_sensors[i].pin_no, INPUT );
  imu_setup();
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
