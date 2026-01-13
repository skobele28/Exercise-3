/*Erika Skobel
1/13/2026
code toggles LED every other time the button is pressed
one button input, one LED output*/

#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_10         // Choose your LED pin
#define BUTTON_PIN GPIO_NUM_4       // Choose your button pin

bool lstate = false;
bool bstate = false;
int button_count = 0;
bool pressed;

void app_main(void) {

    // TO-DO: Configure LED output
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_pullup_dis(LED_PIN);
    gpio_pulldown_dis(LED_PIN);
    gpio_intr_disable(LED_PIN);

    // TO-DO: Configure Button input
    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_pullup_en(BUTTON_PIN);
    gpio_pulldown_dis(BUTTON_PIN);
    gpio_intr_disable(BUTTON_PIN);

    while (1) {
    // TO-DO: Implement LED toggle and button logic here
        pressed = gpio_get_level(BUTTON_PIN) == 0;

        // Check for button press and release
        if (!bstate && pressed && (button_count == 0)) {
            bstate = true;
        }

        if (bstate && !pressed && (button_count == 0)) {
            bstate = false;
            button_count = 1;       //Count one button press
        }

        // Check for second button press and release
        if (!bstate && pressed && (button_count == 1)) {
            bstate = true;
        }

        if (bstate && !pressed && (button_count == 1)) {
            lstate = !lstate;   // Toggle LED state variable
            bstate = false;
            button_count = 0;   // Reset button count to 0
        }

        // Toggle LED state after two button presses
        if (lstate == true) {
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(25/ portTICK_PERIOD_MS); // Use appropriate loop delays
        }

        else {
            gpio_set_level(LED_PIN,0);
            vTaskDelay(25 / portTICK_PERIOD_MS); // Use appropriate loop delays
        }
        
        
    }
}

