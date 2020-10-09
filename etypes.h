/*
 * @file   etypes.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Library type definitions.
 */

#ifndef ETYPES_H
#define ETYPES_H

#include <stdint.h>
#include <stdlib.h>


#define UNUSED(arg) (void)arg;

#define countof(x) (sizeof(x)/sizeof(x[0]))

#define __IO volatile
#define __attr_flash __attribute__((section(".USER_FLASH")))
#ifndef __packed
#define __packed __attribute__((__packed__))
#endif
#define __deprecated __attribute__((__deprecated__))
#define __weak __attribute__((weak))
#ifndef __always_inline
#define __always_inline __attribute__((always_inline))
#endif
#ifndef __unused
#define __unused __attribute__((unused))
#endif

#ifndef NULL
#define NULL 0
#endif

#if (__ARMCOMPILER_VERSION < 6000000)
#define nullptr ((void*)NULL);
#endif

#define null NULL

#endif  // ETYPES_H
