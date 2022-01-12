#ifndef STL_FLEX_SENSOR_H
#define STL_FLEX_SENSOR_H

#include "defaults.h"

/*  structure to encapsulate parameters related to flex sensor  */
struct flex_sensor {
  /* analog pin no */
  int pin_no;
  /* power supply voltage */
  float vcc;
  /* resistance of the resistor of voltage divider */
  float r_div;
  /* resistance of the flex sensor when it is flat (0 degrees) */
  float flat_resistance;
  /* resistance of the flex sensor when it is bent (90 degrees) */
  float bend_resistance;
  /* reading from analog pin from 0 to 1023 */
  int reading;
  /* voltage across the flex sensor */
  float flex_voltage;
  /* resistance accross from flex sensor */
  float flex_resistance;
  /* the angle at which the flex_sensor is bent */
  float angle;
};

/*  initialized all the constant parameters of the flex_sensor  */
void flex_sensor_init(
  struct flex_sensor* sensor,
  int _pin_no,
  float _vcc,
  float _r_div,
  float _flat_resistance,
  float _bend_resistance
) {
  sensor->pin_no = _pin_no;
  sensor->vcc = _vcc;
  sensor->r_div = _r_div;
  sensor->flat_resistance = _flat_resistance;
  sensor->bend_resistance = _bend_resistance;
  sensor->reading = 0.0;
  sensor->flex_voltage = 0.0;
  sensor->flex_resistance = 0.0;
  sensor->angle = 0.0;
}

/*  initialize the pin_no of the flex_sensor with the given value
 *  and other constant parameters will be initialized with default
 *  values
 */
void flex_sensor_init_with_pin_no(
  struct flex_sensor* sensor,
  int _pin_no
) {
  flex_sensor_init(
    sensor,
    _pin_no,
    DEFAULT_VCC,
    DEFAULT_R_DIV,
    DEFAULT_FLAT_RESISTANCE,
    DEFAULT_BEND_RESISTANCE
  );
}

/*  calculate all the variable parameters of the flex sensors
 *  1. reading from the analog pin
 *  2. voltage across the flex sensor
 *  3. resistance across the flex sensor
 *  4. angle at which the flex sensor is bent
 */
void calculate_flex_sensor_parameters(
  struct flex_sensor* sensor
) {
  /* the reading of the sensor can be taken from the pin using analogRead */
  sensor->reading = analogRead( sensor->pin_no );

  /* the voltage across the flex sensor is a fraction of vcc
   * this fraction is (reading) / 1023.0
   */
  sensor->flex_voltage = (float) sensor->reading * sensor->vcc / 1023.0;
  
  /* using the voltage divider formula and the flex_voltage
   * we calculate the flex_resistance
   */
  sensor->flex_resistance = sensor->r_div * ( sensor->vcc / sensor->flex_voltage - 1.0 );

  /* the flex_resistance will be mapped from the range [FLAT_RESISTANCE, BEND_RESISTANCE] 
   * to [0,90] 
   */
  sensor->angle = map( 
    sensor->flex_resistance,
    sensor->flat_resistance,
    sensor->bend_resistance,
    0.0,
    90.0
  );
}

/*  print the values of the variable parameters of all the flex sensors in deployment  */
void print_flex_sensors_info(
  struct flex_sensor* sensors,
  int n_sensors
) {
  Serial.println("Slno\tADC\tResistance\tVoltage\t\tAngle");
  for( int i=0; i<n_sensors; i++ ) {
    Serial.println(
      String(i) + "\t" +
      String(sensors[i].reading) + "\t" + 
      String(sensors[i].flex_resistance) + "ohm\t" + 
      String(sensors[i].flex_voltage) + "V\t\t" + 
      String(sensors[i].angle) + "degrees"
    );
  }
  Serial.println();
}

void print_flex_angles(
  struct flex_sensor* sensors,
  int n_sensors
) {
  for( int i=0; i<n_sensors; i++ ) {
    Serial.print(sensors->angle + "\t");
  }
  Serial.print("\n");
}

#endif
