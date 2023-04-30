PSoC Sensors Library
=======================
This is a PSoC Creator library project containing code to be used to
interface a PSoC 5LP MCU to several hardware devices with
PSoC Creator drag-and-drop components.

.. image:: https://readthedocs.org/projects/psoc-components-library/badge/?version=latest


Included Components
^^^^^^^^^^^^^^^^^^^^
This is a list of sensors contained in the library:

- ⚠️ `ST LIS3DH <https://www.st.com/en/mems-and-sensors/lis3dh.html>`_
- ⚠️ `InvenSense ICM-20948 <https://product.tdk.com/en/search/sensor/mortion-inertial/imu/info?part_no=ICM-20948&gclid=EAIaIQobChMIvNTek8zb8AIVjLHtCh2roADtEAAYASAAEgKdl_D_BwE>`_

This is a list of sensors that are being planned be included in the library in the near future:

- `Sensirion SHT85 <https://www.sensirion.com/en/environmental-sensors/humidity-sensors/sht85-pin-type-humidity-sensor-enabling-easy-replaceability/>`_
- `Maxim Integrated DS2438 <https://www.maximintegrated.com/en/products/power/battery-management/DS2438.html?intcid=para>`_
- `Bosch BME280 <https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/>`_
- `InvenSense MPU9250 <https://invensense.tdk.com/products/motion-tracking/9-axis/mpu-9250/>`_
- `SSD1306 Display Driver`
  
Setup
^^^^^^

1. Clone the repository: ::
   
    git clone https://github.com/dado93/PSoC-Sensors-Library

2. Add the `Library` project as a dependency for your project in PSoC Creator. Go to `Project` > `Dependencies` > `Add User Depencency`
3. Use the provided components in your projects

Documentation
^^^^^^^^^^^^^
Due to the fact that PSoC Creator require API functions to use `$INSTANCE_NAME`
in the source code, the `conf.py` file was modified to properly build the documentation 
of the library.
The official documentation is built using ReadTheDocs.

1. Install Doxygen, breathe, and sphinx
2. Do not edit the Doxygen file, as it is already configured
3. ``cd docs``
4. Run ``make html``
5. You will find the documentation in the ``docs\_build`` folder