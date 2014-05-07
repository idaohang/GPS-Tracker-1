/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#ifndef GLOBAL_H__
#define GLOBAL_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

/**
 * FOR DEBUG
 */

#define printlog(msg, args...)    printf(msg, ##args)

/**
 * FOR RELEASE
 */

//#define printlog(msg, args...)

#endif  /* GLOBAL_H__ */
