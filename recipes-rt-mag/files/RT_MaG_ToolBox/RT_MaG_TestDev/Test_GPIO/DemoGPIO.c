/*
  Simple GPIO toggle. 
*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

#define IRQ_PIN 146
#define TOGGLE_PIN 147 

void irq_handler(int irq, void *dev_id)
{
	gpio_set_value(IRQ_PIN, 0);
	printf("IRQ occured!\n");
}

int main(int argc, char **argv)
{
	int GpioNum;
	int result;
	unsigned int IrqNum;
	
	if (argc!=2)
	{
		printf("SYNTAX: %s <gpio num>\n",argv[0]);
		printf("         e.g., '%s 146' (for gpio146) \n\n",argv[0]);
		
		return(0);
	}	
	else
	{
		if (!strcmp(argv[1],"-help")||!strcmp(argv[1],"-h"))
		{
			printf("SYNTAX: %s <gpio num>\n",argv[0]);
			printf("         e.g., '%s 146' (for gpio146) \n\n",argv[0]);
			return(0);
		}
		else
		{
			GpioNum = (int)strtol(argv[1],NULL, 10);
			printf("GPIO: %d\n", GpioNum);
		}
	}
	
	// reserve the gpio
	gpio_request(IRQ_PIN, "IrqPin");
	gpio_request(TOGGLE_PIN, "TogglePin");
	
	// set the direction of gpio
	gpio_direction_output(TOGGLE_PIN, 0);
	gpio_direction_input(IRQ_PIN);
	
	// create the irq
		// define the GPIO as IRQ source
	IrqNum = gpio_to_irq(IRQ_PIN);	
		// create the irq and associate to it a function's handler
	result = request_irq(IrqNum,
						irq_handler,
						IRQF_TRIGGER_RISING,
						"IRQ_GPIO_146",	//	name of the interrupt which will appear in /proc/interrupts
						&IrqNum);
	
	// turn on the gpio to arm the interrupt
	gpio_set_value(TOGGLE_PIN, 1);
	
	// sleep 1 second to let irq to be done
	sleep(1);
	
	// free the interrupt
	free_irq(IrqNum, &IrqNum);  
	
	// free the gpio
	gpio_free(IRQ_PIN);
	
	/*
	gpio_request(unsigned gpio, const char *label)
	gpio_direction_output(unsigned gpio, int value)
	gpio_direction_input(unsigned gpio)
	gpio_get_value(unsigned gpio)
	gpio_set_value(unsigned gpio, int value)
	gpio_free(unsigned gpio)
	
	gpio_to_irq(unsigned gpio)
	request_irq(unsigned int irq, void (*gest)(int, void *, struct pt_regs *), unsigned long drap_interrupt, const char *devname, void *dev_id);
	void free_irq(unsigned int irq, void *dev_id);  
	IRQF_TRIGGER_RISING     0x00000001
	IRQF_TRIGGER_FALLING    0x00000002
	IRQF_TRIGGER_HIGH       0x00000004
	IRQF_TRIGGER_LOW        0x00000008
	*/
	
	return(0);
}