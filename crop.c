// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#include "crop.h"
#include "image.h"
#include "utils.h"
#include <stdio.h>

void crop(img *image)
{
	img new_image;

	alloc_image(&new_image, image->x2 - image->x1, image->y2 - image->y1,
				image->colors, image->max_value, image->type);

	for (int i = 0; i < new_image.height; ++i)
		for (int j = 0; j < new_image.width; ++j)
			for (int k = 0; k < new_image.colors; ++k)
				new_image.matrix[i][j][k] =
				image->matrix[i + image->y1][j + image->x1][k];

	swap(image, &new_image, sizeof(img));
	free_image(new_image);

	printf("Image cropped\n");
}
