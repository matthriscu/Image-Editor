// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#include "rotate.h"
#include "image.h"
#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int rotate(char *param, img *image)
{
	/* Return values:
		0 - Executed successfully
		1 - Invalid parameter
		2 - Invalid selection
		3 - Rotation wasn't performed successfully
	*/

	char *angle_string = strtok(param, "\n ");
	int angle = atoi(angle_string);

	/* If atoi returned 0, but the rotation angle is not 0 that means atoi
	   wasn't able to convert the string into a number and therefore the
	   parameter that was provided is invalid */
	if (angle == 0 && (!angle_string || strcmp(angle_string, "0") != 0)) {
		fprintf(stdout, "Invalid command\n");
		return 1;
	}

	if (!((image->y2 - image->y1 == image->x2 - image->x1) ||
		  (image->x1 == 0 && image->y1 == 0 &&
		   image->x2 == image->width && image->y2 == image->height))) {
		fprintf(stdout, "The selection must be square\n");
		return 2;
	}

	// Reducing the angle to the range [0, 360)
	angle = (angle + 360) % 360;

	if (rotate_image(image, angle))
		return 3;

	printf("Rotated %s\n", angle_string);
	return 0;
}

int rotate_image(img *image, int angle)
{
	
	/// TODO: Incorporate Octave functions for rotating at angles which aren't
	/// multiples of 90.

	/* Return values:
		0 - Executed successfully
		1 - Unsupported rotation angle
	*/
	if (angle % 90 != 0) {
		fprintf(stdout, "Unsupported rotation angle\n");
		return 1;
	}

	if (angle == 0)
		return 0;

	img temp;

	/* If rotating a rectangular image by an angle other
	   than 180 degrees the dimensions will be swapped */
	if (angle == 180) {
		temp.width = image->x2 - image->x1;
		temp.height = image->y2 - image->y1;
	} else {
		temp.height = image->x2 - image->x1;
		temp.width = image->y2 - image->y1;
	}

	alloc_image(&temp, temp.width, temp.height, image->colors,
				image->max_value, image->type);

	for (int i = 0; i < temp.height; ++i)
		for (int j = 0; j < temp.width; ++j)
			for (int k = 0; k < temp.colors; ++k)
				if (angle == 90)
					temp.matrix[i][j][k] =
					image->matrix[image->y2 - j - 1][i + image->x1][k];
				else if (angle == 180)
					temp.matrix[i][j][k] =
					image->matrix[image->y2 - i - 1][image->x2 - j - 1][k];
				else if (angle == 270)
					temp.matrix[i][j][k] =
					image->matrix[j + image->y1][image->x2 - i - 1][k];

	/* The temporary image is now the new image) */
	swap(&temp, image, sizeof(img));

	free_image(temp);

	return 0;
}
