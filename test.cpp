#include "ortho-hall.h"

#include "hall-effect-sensor-definitions.h"

#include <iostream>

int adc_dummy_x = 0;
int adc_dummy_y = 0;

int dummyRead(int pin) {
    if (pin == 1) {
        return adc_dummy_x;
    } else {
        return adc_dummy_y;
    }
}

angle_sensor test_sensor(1, 2, DRV5056A2, dummyRead);

int main() {
    

    //test for 45 degrees
    adc_dummy_x = 2419;
    adc_dummy_y = 2419;

    std::cout << "Expected: 45 degrees" << std::endl;
    std::cout << "Actual: " << test_sensor.read_angle_degrees() << " degrees" << std::endl;
    std::cout << "Radians: " << test_sensor.read_angle() << std::endl;

    //test for 90 degrees
    adc_dummy_x = 744;
    adc_dummy_y = 4095;

    std::cout << "Expected: 90 degrees" << std::endl;
    std::cout << "Actual: " << test_sensor.read_angle_degrees() << " degrees" << std::endl;
    std::cout << "Radians: " << test_sensor.read_angle() << std::endl;

    //test for 0 degrees
    adc_dummy_x = 4095;
    adc_dummy_y = 744;

    std::cout << "Expected: 0 degrees" << std::endl;
    std::cout << "Actual: " << test_sensor.read_angle_degrees() << " degrees" << std::endl;
    std::cout << "Radians: " << test_sensor.read_angle() << std::endl;

    //test with what would be a negative pole value
    adc_dummy_x = 372;
    adc_dummy_y = 2419;

    std::cout << "Expected: 135 degrees" << std::endl;
    std::cout << "Actual: " << test_sensor.read_angle_degrees() << " degrees" << std::endl;
    std::cout << "Radians: " << test_sensor.read_angle() << std::endl;

    return 0;
}
