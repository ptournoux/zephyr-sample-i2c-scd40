 #include <zephyr/kernel.h>
 #include <zephyr/device.h>
 #include <zephyr/devicetree.h>
 #include <zephyr/drivers/sensor.h>
 #include <zephyr/sys/printk.h> // For printk
 #include <stdio.h> 

 static const struct device *const scd4x_dev = DEVICE_DT_GET(DT_ALIAS(scd40));
 
 int main(void)
 {
	 struct sensor_value co2, temp, humidity;
 
	 printk("SCD40 Sensor Example Application\n");
 
	 /* Check if the device is ready */
	 if (!device_is_ready(scd4x_dev)) {
		 printk("Error: SCD40 sensor device not ready.\n");
		 return 1; // Return an error code
	 } else {
		 printk("SCD40 sensor device is ready.\n");
	 }
 
	 /* Main loop to periodically fetch and print sensor data */
	 while (1) {
		 /* Fetch all samples from the sensor */
		 if (sensor_sample_fetch(scd4x_dev) != 0) {
			 printk("Error: Failed to fetch sample from SCD40.\n");
		 } else {
			 /* Get CO2 concentration */
			 if (sensor_channel_get(scd4x_dev, SENSOR_CHAN_CO2, &co2) != 0) {
				 printk("Error: Failed to get CO2 data.\n");
			 } else {
				 printk("CO2: %.0f ppm\n", sensor_value_to_double(&co2));
			 }
 
			 /* Get temperature */
			 if (sensor_channel_get(scd4x_dev, SENSOR_CHAN_AMBIENT_TEMP, &temp) != 0) {
				 printk("Error: Failed to get temperature data.\n");
			 } else {
				 printk("Temperature: %.2f °C\n", sensor_value_to_double(&temp));
			 }
 
			 /* Get relative humidity */
			 if (sensor_channel_get(scd4x_dev, SENSOR_CHAN_HUMIDITY, &humidity) != 0) {
				 printk("Error: Failed to get humidity data.\n");
			 } else {
				 printk("Humidity: %.2f %%\n", sensor_value_to_double(&humidity));
			 }
			 printk("--------------------------------------\n");
		 }
 
		 /* Wait before taking the next measurement */
		 k_sleep(K_SECONDS(5)); // Read every 5 seconds
	 }
	 return 0; // Should not be reached in this example
 }
 