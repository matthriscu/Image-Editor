// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#include "image.h"
#include "utils.h"
#include <stdlib.h>

void alloc_image(img *image, int width, int height,
				 int colors, int max_value, int type)
{
	image->width = width;
	image->height = height;
	image->colors = colors;
	image->max_value = max_value;
	image->type = type;
	image->x1 = 0;
	image->y1 = 0;
	image->x2 = width;
	image->y2 = height;

	image->matrix = malloc(height * sizeof(float **));
	check_alloc(image->matrix);

	for (int i = 0; i < height; ++i) {
		image->matrix[i] = malloc(width * sizeof(float *));
		check_alloc(image->matrix[i]);

		for (int j = 0; j < width; ++j) {
			image->matrix[i][j] = malloc(colors * sizeof(float));
			check_alloc(image->matrix[i][j]);
		}
	}
}

void free_image(img image)
{
	for (int i = 0; i < image.height; ++i) {
		for (int j = 0; j < image.width; ++j)
			free(image.matrix[i][j]);
		free(image.matrix[i]);
	}
	free(image.matrix);
}
