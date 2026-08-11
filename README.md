# Automated Servo Actuator Node (Zephyr OS)

An embedded application leveraging the Zephyr RTOS framework to control a standard hobby servo motor via PWM on an ESP32 microcontroller. The project utilizes hardware abstraction layers via DeviceTree to execute non-blocking angle sweeps.

##  Features
- **Hardware Abstraction:** Configured via DeviceTree overlays (`app.overlay`) to separate hardware pin-mapping from application logic.
- **Non-Blocking Control:** Uses Zephyr kernel scheduling (`k_sleep`) to yield CPU execution during timing intervals, avoiding busy-waiting.
- **Precision Sweeps:** Maps rotational requirements ($0^\circ$, $90^\circ$, $180^\circ$) directly to raw nanosecond pulse-widths required by standard servo controllers.

##  Hardware & Pin Configuration
- **Microcontroller:** ESP32
- **Actuator:** Standard Hobby Servo (SG90 or equivalent)
- **PWM Pin:** GPIO 13 (configured via LEDC peripheral driver)

##  How to Build and Flash

1. Initialize your Zephyr workspace and ensure the toolchain is set up.
2. Clone this repository into your workspace.
3. Build the application for the ESP32:
   ```bash
   west build -b esp32 --pristine
