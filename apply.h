// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#pragma once

#include "image.h"

#define K_SIZE 3

/**
 * @brief Updates ker to the appropriate kernel, according to the provided name
 */
int set_kernel(float ker[][K_SIZE], char *kernel_name);

/**
 * @brief Applies a filter over the current selection of the image
 */
int apply(char *param, img *image);

/**
 * @return The new value of a specific pixel
 *		   after applying the image kernel
 */
float apply_kernel(img image, float ker[][K_SIZE],
				   int line, int col, int color);
