// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#include "apply.h"
#include "image.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

int set_kernel(float ker[][K_SIZE], char *kernel_name)
{
	/* Return values:
		0 - Executed successfully
		1 - Invalid kernel name
	*/

	if (strcmp(kernel_name, "EDGE") == 0) {
		ker[0][0] = -1;	ker[0][1] = -1;	ker[0][2] = -1;
		ker[1][0] = -1;	ker[1][1] =  8;	ker[1][2] = -1;
		ker[2][0] = -1;	ker[2][1] = -1;	ker[2][2] = -1;
	} else if (strcmp(kernel_name, "SHARPEN") == 0) {
		ker[0][0] = 0;	ker[0][1] = -1;	ker[0][2] = 0;
		ker[1][0] = -1;	ker[1][1] =  5;	ker[1][2] = -1;
		ker[2][0] = 0;	ker[2][1] = -1;	ker[2][2] = 0;
	} else if (strcmp(kernel_name, "BLUR") == 0) {
		ker[0][0] = 1.F / 9;	ker[0][1] = 1.F / 9;	ker[0][2] = 1.F / 9;
		ker[1][0] = 1.F / 9;	ker[1][1] = 1.F / 9;	ker[1][2] = 1.F / 9;
		ker[2][0] = 1.F / 9;	ker[2][1] = 1.F / 9;	ker[2][2] = 1.F / 9;
	} else if (strcmp(kernel_name, "GAUSSIAN_BLUR") == 0) {
		ker[0][0] = 1.F / 16;	ker[0][1] = 1.F / 8;	ker[0][2] = 1.F / 16;
		ker[1][0] = 1.F /  8;	ker[1][1] = 1.F / 4;	ker[1][2] = 1.F /  8;
		ker[2][0] = 1.F / 16;	ker[2][1] = 1.F / 8;	ker[2][2] = 1.F / 16;
	} else {
		fprintf(stdout, "APPLY parameter invalid\n");
		return 1;
	}

	return 0;
}

int apply(char *param, img *image)
{
	/* Return values:
		0 - Executed successfully
		1 - No filter name provided
		2 - The image is greyscale and cannot have a filter applied
		3 - The filter name provided is invalid
	*/

	char *kernel_name = strtok(param, "\n ");

	if (!kernel_name) {
		fprintf(stdout, "Invalid command\n");
		return 1;
	}

	if (image->type != 3) {
		fprintf(stdout, "Easy, Charlie Chaplin\n");
		return 2;
	}

	float ker[K_SIZE][K_SIZE];

	if (set_kernel(ker, param) != 0)
		return 3;

	/* Creating a new image in which the new values are temporarily stored
	   as the old values are stil required for computing the new values of
	   other pixels */
	img temp;

	alloc_image(&temp, image->x2 - image->x1, image->y2 - image->y1,
				image->colors, image->max_value, image->type);

	for (int i = image->y1; i < image->y2; ++i)
		for (int j = image->x1; j < image->x2; ++j)
			for (int k = 0; k < image->colors; ++k)
				temp.matrix[i - image->y1][j - image->x1][k] =
				apply_kernel(*image, ker, i, j, k);

	for (int i = image->y1; i < image->y2; ++i)
		for (int j = image->x1; j < image->x2; ++j)
			for (int k = 0; k < image->colors; ++k)
				image->matrix[i][j][k] =
				temp.matrix[i - image->y1][j - image->x1][k];

	free_image(temp);

	printf("APPLY %s done\n", kernel_name);
	return 0;
}

float apply_kernel(img image, float kernel[][K_SIZE],
				   int line, int col, int color)
{
	/* If the provided pixel doesn't have enough
	   neighbours its value won't change */
	if (line < K_SIZE / 2 || col < K_SIZE / 2 ||
		line >= image.height - K_SIZE / 2 ||
		col >= image.width - K_SIZE / 2)
		return image.matrix[line][col][color];

	float value = 0;
	for (int i = 0; i < K_SIZE; ++i)
		for (int j = 0; j < K_SIZE; ++j)
			value += kernel[i][j] *
			image.matrix[line - K_SIZE / 2 + i][col - K_SIZE / 2 + j][color];

	return clamp(value, 0, image.max_value);
}
