#include <log.h>
#include <string.h>
#include "main.h"
static UART_HandleTypeDef *log_uart_handle = NULL; // Pointer to UART handle

void dlog_init(UART_HandleTypeDef *uart_handle) {
    log_uart_handle = uart_handle;
}

void dlog(const char *format, ...) {
	  if (log_uart_handle == NULL) {
	        return; // UART not initialized
	    }

	    char buffer[256]; // Temporary buffer for formatted string
	    va_list args;

	    va_start(args, format);
	    int len = vsnprintf(buffer, sizeof(buffer) - 2, format, args); // Reserve space for newline and null terminator
	    va_end(args);

	    // Ensure the formatted string is null-terminated and append newline
	    if (len < (int)(sizeof(buffer) - 2)) {
	        buffer[len] = '\n';
	        buffer[len + 1] = '\0';
	    } else {
	        buffer[sizeof(buffer) - 2] = '\n';
	        buffer[sizeof(buffer) - 1] = '\0';
	    }

	    HAL_UART_Transmit(log_uart_handle, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);

}
