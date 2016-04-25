/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <stdint.h>
#include <asf.h>
#include "defs.h"

void dhry(void);
void linpack (void);
void coreMark(void);


static void configure_console(void);

volatile uint32_t msCounter = 0;	/* Milliseconds counter */ 

void SysTick_Handler    ( void ) {
	msCounter++;
}

int main (void) {
	sysclk_init();
	board_init();
	SysTick_Config(SystemCoreClock / 1000); // ms
	configure_console();

	puts("\n\n");
	puts(  "=== Atmel ARM MCUs benchmarks. V.1.0 ===");
	puts(  "Autor:            Andrei Kurnits (kurnits@gmail.com)");	
	puts(  "====================================================");	
	printf("Microcontroller:  %s\n", DEVICE);
	printf("CPU clock:        %d Hz\n", sysclk_get_cpu_hz());
	printf("Peripheral clock: %d Hz\n", sysclk_get_peripheral_hz());
	printf("Cache:            %s\n", USING_CACHE_STR);
	printf("Program location: %s\n", PROGRAM_LOCATION_NAME);
	printf("Compiler:         %s\n", COMPILER);
	printf("Opt. flags:       %s\n", OPTIMIZATIONS_FLAGS);
	printf("Benchmark:        %s\n", BENCHMARK_NAME);
	puts(  "--------------");
	puts(  "----START!----");
	puts(  "--------------");
	
	#if ((BENCHMARK == DHRYSTONE) || (BENCHMARK == ALL))
	dhry();
	#endif
	#if ((BENCHMARK == LINPACK) || (BENCHMARK == ALL))
	linpack();
	#endif
	#if ((BENCHMARK == COREMARK) || (BENCHMARK == ALL))
	coreMark();
	#endif
	
	for (;;) ;
}


/**
 *  \brief Configure UART console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#if (defined CONF_UART_CHAR_LENGTH)
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_UART_PARITY,
#if (defined CONF_UART_STOP_BITS)
		.stopbits = CONF_UART_STOP_BITS,
#endif
	};

	/* Configure UART console. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
#if defined(__GNUC__)
	setbuf(stdout, NULL);
#endif
}