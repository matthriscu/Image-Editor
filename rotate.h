// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#pragma once

#include "image.h"

/**
 * @brief Rotates an image according to the angle specified in param
 */
int rotate(char *param, img * image);

/**
 * @brief Executes the actual rotation based on the angle provided
 */
int rotate_image(img *image, int angle);
