/*
 * File: helper.c
 *
 * General helper functions
 */

#ifdef STLINK_HAVE_SYS_TIME_H
#include <sys/time.h>
#else
#include <sys_time.h>
#endif // STLINK_HAVE_SYS_TIME_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "helper.h"

uint32_t time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint32_t) (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int32_t arg_parse_freq(const char *str) {
    if(str == NULL) {
        return -1;                    // faulty input
    }
    
    char* tail = NULL;
    int32_t value = (uint32_t) strtol(str, &tail, 10);

    /* == Input value interpretation ==
     *
     * These decimal values represent kHz.
     * The prefix "k" may be added for better understanding, but has no effect.
     * In addition, values can be interpreted as thousands of kHz thus representing MHz.
     * This is achieved by using the prefix "M".
     */

    if(tail == NULL) {
        return -1;                    // faulty integer conversion
    } else if(tail[0] == '\0') {
        return value;                 // no prefix: kHz
    } else if((tail[0] == 'k' || tail[0] == 'K') && tail[1] == '\0') {
        return value;                 // k prefix: kHz
    } else if(tail[0] == 'M' && tail[1] == '\0') {
        return (value * 1000);        // M prefix: MHz
    }
    return -1;                        // invalid prefix
}
