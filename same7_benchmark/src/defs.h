/*
 * defs.h
 *
 * Created: 10.04.2016 3:42:09
 *  Author: Andrei Kurnits
 */ 


#ifndef DEFS_H_
#define DEFS_H_

#include <stdlib.h>
#include <stdint.h>

/* Compiler and optimization */
#define OPTIMIZATIONS_FLAGS	"-o3"

/* Benchmark */
#define DHRYSTONE 1
#define LINPACK   2
#define COREMARK  3
#define ALL       4
#define BENCHMARK COREMARK

/* Program location */
#define FLASH_MEMORY			1
#define INTERNAL_SRAM_MEMORY	2
#define TCM_MEMORY				3
#ifndef PROGRAM_LOCATION
#define PROGRAM_LOCATION	FLASH_MEMORY
#endif

/* Internal I and D caches */
#define USE_CACHE 1

/* Floating point precision */
#define SINGLE_PRECISION	1
#define DOUBLE_PRECISION	2
#define FLOATING_POINT	SINGLE_PRECISION





#if (BENCHMARK == DHRYSTONE)
#define BENCHMARK_NAME "Dhrystone"
#elif (BENCHMARK == LINPACK)
#define BENCHMARK_NAME   "Linpack"
#elif (BENCHMARK == COREMARK)
#define BENCHMARK_NAME  "Coremark"
#elif (BENCHMARK == ALL)
#define BENCHMARK_NAME "Dhrystone Linpack Coremark"
#else
#define BENCHMARK_NAME  "not defined"
#endif


/* Compiler and optimization */
#ifdef __GNUC__
#define COMPILER "GCC "__VERSION__
#else
#define COMPILER "not defined"
#endif

/* Model of microcontroller */
#ifdef __SAME70Q21__
#define DEVICE "SAME70Q21"
#else
#define DEVICE "not defined"
#endif

#if (PROGRAM_LOCATION == FLASH_MEMORY)
#define PROGRAM_LOCATION_NAME	"Internal Flash"
#elif (PROGRAM_LOCATION == INTERNAL_SRAM_MEMORY)
#define PROGRAM_LOCATION_NAME	"Internal SRAM"
#elif (PROGRAM_LOCATION == TCM_MEMORY)
#define PROGRAM_LOCATION_NAME	"Internal Tightly Coupled Memory"
#else
#define PROGRAM_LOCATION_NAME	"not defined"
#endif

#if (PROGRAM_LOCATION == INTERNAL_SRAM_MEMORY)
#define MEMORY_SECTION __attribute__( (section(".data") ) )
#else
#define MEMORY_SECTION
#endif

#if (PROGRAM_LOCATION == TCM_MEMORY)
#define CONF_BOARD_CONFIG_MPU_AT_INIT
#endif

#if (FLOATING_POINT == DOUBLE_PRECISION)
#define real_t double
#define FLOATING_POINT_PRECISION_NAME	"Double precision"
#else	/* #if (FLOATING_POINT == DOUBLE_PRECISION) */
#define real_t float
#define FLOATING_POINT_PRECISION_NAME	"Single precision"
#endif	/* #if (FLOATING_POINT == DOUBLE_PRECISION) */

#if (USE_CACHE)
#define USING_CACHE_STR	"I and D caches are USED"
#else
#define USING_CACHE_STR	"I and D caches are NOT used"
#endif

#endif /* DEFS_H_ */