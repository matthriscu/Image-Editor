// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#pragma once

#include <stddef.h>

#define MAX_LINE_LENGTH	256

/**
 * @brief Checks that a memory allocation was successful
 */
void check_alloc(void *p);

/**
 * @brief Swaps 2 variables of any data type
 */
void swap(void *a, void *b, size_t size);

/**
 * @brief Clamps x between the lower and upper bounds if it isn't already
 */
float clamp(float x, int lower_bound, int upper_bound);
