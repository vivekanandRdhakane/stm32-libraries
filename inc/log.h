#ifndef LOG_H
#define LOG_H

#include "stm32G0xx_hal.h"  // Replace with your specific HAL header file
#include <stdarg.h>
#include <stdio.h>

// Initialize the logger with a specific UART handle
void dlog_init(UART_HandleTypeDef *uart_handle);

// Log a formatted string over UART
void dlog(const char *format, ...);

#endif // LOG_H
