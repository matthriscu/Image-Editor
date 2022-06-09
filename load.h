// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#pragma once

#include "image.h"
#include <stdio.h>

/**
 * @brief Loads a new image from the file specified in param
 */
int load(char *param, img * image);

/**
 * @brief Reads image data as text
 */
void read_text(FILE *in, img *image);

/**
 * @brief Reads image data as binary information
 */
void read_binary(FILE *in, img *image);
