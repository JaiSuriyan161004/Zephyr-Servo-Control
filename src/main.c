#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/sys/printk.h>

/* Standard hobby servo pulse widths (nanoseconds) */
#define SERVO_MIN_PULSE_NS  1000000   /* 1.0 ms -> 0 degrees   */
#define SERVO_MAX_PULSE_NS  2000000   /* 2.0 ms -> 180 degrees */
#define SERVO_MID_PULSE_NS  1500000   /* 1.5 ms -> 90 degrees  */

static const struct pwm_dt_spec servo = PWM_DT_SPEC_GET(DT_PATH(zephyr_user));

static int set_angle(const struct pwm_dt_spec *pwm, int angle_deg)
{
	if (angle_deg < 0)   angle_deg = 0;
	if (angle_deg > 180) angle_deg = 180;

	uint32_t pulse_ns = SERVO_MIN_PULSE_NS +
		((SERVO_MAX_PULSE_NS - SERVO_MIN_PULSE_NS) * angle_deg) / 180;

	return pwm_set_pulse_dt(pwm, pulse_ns);
}

int main(void)
{
	if (!pwm_is_ready_dt(&servo)) {
		printk("Error: PWM device is not ready\n");
		return 0;
	}

	printk("Servo sweep starting...\n");

	while (1) {
		printk("Moving to 0 degrees\n");
		set_angle(&servo, 0);
		k_sleep(K_SECONDS(1));

		printk("Moving to 90 degrees\n");
		set_angle(&servo, 90);
		k_sleep(K_SECONDS(1));

		printk("Moving to 180 degrees\n");
		set_angle(&servo, 180);
		k_sleep(K_SECONDS(1));
	}

	return 0;
}