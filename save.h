// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#pragma once

#include "image.h"
#include <stdio.h>

/**
 * @brief Saves the image to the file specified in param
 */
int save(char *param, img image);

/**
 * @brief Writes image data as text
 */
void write_text(FILE *out, img image);

/**
 * @brief Writes image data as binary information
 */
void write_binary(FILE *out, img image);
