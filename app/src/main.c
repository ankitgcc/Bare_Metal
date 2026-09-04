#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

//PA5 is user LED (LD2)
#define LED_PORT (GPIOA)
#define LED_PIN (GPIO5)

//setting up the clock to 84MHz using HSI
void rcc_setup(void)
{
    rcc_osc_on(RCC_HSI);
    rcc_wait_for_osc_ready(RCC_HSI);
}

//setting up GPIOA pin 5 as output
static void gpio_setup(void){
    rcc_periph_clock_enable(RCC_GPIOA); //enable GPIOA clock
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN); 
}

//delay function
static void delay_cycles(uint32_t cycles){
    for(uint32_t i = 0; i < cycles; i++){
        __asm__("nop"); //inline assembly for no operation so compiler doesn't optimize the loop away
    }
}


int main(void){
    rcc_setup();
    gpio_setup();

    while(1){
        gpio_toggle(LED_PORT, LED_PIN); //toggle PA5
        delay_cycles(1600000 / 4); //delay for a while);
    }

    return 0;
}