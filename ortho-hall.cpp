#include "ortho-hall.h"

#include "hall-effect-sensor-definitions.h"

#include <math.h>

void angle_sensor::init(int pin_x, int pin_y, sensor_variables sensor, int (*reading_function)(int), int adc_resolution) {
    this->pin_x = pin_x;
    this->pin_y = pin_y;
    this->sensor = sensor;
    this->reading_function = reading_function;
    this->adc_bits = adc_resolution;
    
}

angle_sensor::angle_sensor(int pin_x, int pin_y, sensor_variables sensor, int (*reading_function)(int)) {   
    this->init(pin_x, pin_y, sensor, reading_function, 12);
}

angle_sensor::angle_sensor(int pin_x, int pin_y, sensor_variables sensor, int (*reading_function)(int), int adc_resolution = 12) {
    this->init(pin_x, pin_y, sensor, reading_function, adc_resolution);
}

float angle_sensor::read_angle() {
    int zero_offset = (this->sensor.zero_voltage / this->sensor.driving_voltage) / this->adc_max(this->adc_bits);
    int y_component= (reading_function(this->pin_y) - zero_offset);
    int x_component = (reading_function(this->pin_x) - zero_offset);

    float normalized_x = normalize_values(x_component, x_component, y_component);
    float normalized_y = normalize_values(y_component, x_component, y_component);

    return atan2(normalized_y, normalized_x);
}

float angle_sensor::read_angle_degrees() {
    return this->read_angle() * 180 / M_PI;
}

float angle_sensor::normalize_values(float normal_targ, float x, float y) const {
    return (normal_targ)/sqrt(pow(x, 2) + pow(y, 2));
}

int angle_sensor::adc_max(int adc_bits) {
    return pow(2, adc_bits) - 1;
}
