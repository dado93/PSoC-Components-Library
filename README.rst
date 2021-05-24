# PSoC Sensors Library
This is a PSoC Creator library project containing code to be used to interface a PSoC 5LP MCU to several sensors with drag-and-drop components.

## Sensors
This is a list of sensors contained in the library:
- :construction: [ST LIS3DH](https://www.st.com/en/mems-and-sensors/lis3dh.html)
- :construction: [InvenSense ICM-20948](https://product.tdk.com/en/search/sensor/mortion-inertial/imu/info?part_no=ICM-20948&gclid=EAIaIQobChMIvNTek8zb8AIVjLHtCh2roADtEAAYASAAEgKdl_D_BwE)

This is a list of sensors that will be included in the library in the near future:
- [Sensirion SHT85](https://www.sensirion.com/en/environmental-sensors/humidity-sensors/sht85-pin-type-humidity-sensor-enabling-easy-replaceability/)
- [Maxim Integrated DS2438](https://www.maximintegrated.com/en/products/power/battery-management/DS2438.html?intcid=para)
- [Bosch BME280](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/)
- [InvenSense MPU9250](https://invensense.tdk.com/products/motion-tracking/9-axis/mpu-9250/)

## Setup
1. Clone the repository: `git clone https://github.com/dado93/PSoC-Sensors-Library`
2. Add the `Sensors` project as a dependency for your project in PSoC Creator. Go to `Project` > `Dependencies` > `Add User Depencency`
3. Use the provided components