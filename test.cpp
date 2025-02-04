#include "ortho-hall.h"

#include "hall-effect-sensor-definitions.h"

#include <iostream>

#include <chrono>

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

void time_test(int runs);

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

    time_test(100000000);

    return 0;
}

void time_test(int runs) {
    adc_dummy_x = 2419;
    adc_dummy_y = 2419;

    unsigned long start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    for (int i = 0; i < runs; i++) {
        test_sensor.read_angle_degrees();
    }

    std::cout << runs << " runs took " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - start << " ms" << std::endl;
}
