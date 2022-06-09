// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#pragma once

typedef struct {
	int type, width, height, colors, max_value, x1, x2, y1, y2;
	float ***matrix;
} img;

/**
 * @brief Dynamically allocates memory for an image and sets all its attributes
 */
void alloc_image(img *image, int width, int height,
				 int colors, int max_value, int type);

/**
 * @brief Frees all dynamically allocated memory used by the image
 */
void free_image(img image);
