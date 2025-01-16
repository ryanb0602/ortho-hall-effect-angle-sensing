#ifndef ORTHO_HALL_H
#define ORTHO_HALL_H

struct sensor_variables {

    float zero_voltage;
    float driving_voltage;
    int mV_per_mT;

};

class angle_sensor {
    public:
        angle_sensor();
	angle_sensor(int pin_x, int pin_y, struct sensor_variables sensor, int (*reading_function)(int));
        angle_sensor(int pin_x, int pin_y, struct sensor_variables sensor, int (*reading_function)(int), int adc_resolution);

        void init(int pin_x, int pin_y, struct sensor_variables sensor, int (*reading_function)(int), int adc_resolution);

        float read_angle();
        float read_angle_degrees();

        private:
            int pin_x;
            int pin_y;
            struct sensor_variables sensor;
            int adc_bits;
            int adc_max(int adc_bits);

            int (*reading_function)(int);
            float normalize_values(float normal_targ, float x, float y) const;

};

#endif
