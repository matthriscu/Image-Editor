// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#include "load.h"
#include "image.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

int load(char *param, img *image)
{
	/* Return values:
		0 - Executed successfully
		1 - Failed to load the provided file
		2 - Unsupported image type
	*/

	// If an image is already loaded it will be freed
	if (image->matrix)
		free_image(*image);
	image->matrix = NULL;

	char *file_name = strtok(param, "\n ");

	FILE *in = fopen(file_name, "rt");
	if (!in) {
		fprintf(stdout, "Failed to load %s\n", file_name);
		return 1;
	}

	char input_line[MAX_LINE_LENGTH];
	fpos_t beginning;

	// Skipping any comments that may be present at the beginning of the file
	do {
		fgetpos(in, &beginning);
		fgets(input_line, MAX_LINE_LENGTH, in);
	} while (input_line[0] == '#');

	fsetpos(in, &beginning);

	// Skipping the 'P' character
	fseek(in, 1, SEEK_CUR);

	fscanf(in, "%d%d%d%d", &image->type, &image->width,
		   &image->height, &image->max_value);

	if (image->type % 3 == 2) {
		image->colors = 1;
	} else if (image->type % 3 == 0) {
		image->colors = 3;
	} else {
		fprintf(stderr, "Unsupported image type\n");
		return 2;
	}

	alloc_image(image, image->width, image->height, image->colors,
				image->max_value, image->type);

	if (image->type == 2 || image->type == 3) {
		read_text(in, image);
	} else {
		image->type -= 3;

		/* Skipping the new line character from the last line
		   that was read as otherwise it may be mistaken as
		   part of the image when read from a binary file */
		freopen(file_name, "rb", in);
		fseek(in, ftell(in) + 1, SEEK_SET);

		read_binary(in, image);
	}

	fclose(in);

	printf("Loaded %s\n", file_name);
	return 0;
}

void read_text(FILE *in, img *image)
{
	for (int i = 0; i < image->height; ++i)
		for (int j = 0; j < image->width; ++j)
			for (int k = 0; k < image->colors; ++k)
				fscanf(in, "%f", &image->matrix[i][j][k]);
}

void read_binary(FILE *in, img *image)
{
	/* A temporary variable must be used when reading from a binary file
	   as the image is stored using the float data type but the pixel
	   information is encoded using a single byte per subpixel */
	unsigned char temp;
	for (int i = 0; i < image->height; ++i)
		for (int j = 0; j < image->width; ++j)
			for (int k = 0; k < image->colors; ++k) {
				fread(&temp, sizeof(unsigned char), 1, in);
				image->matrix[i][j][k] = temp;
			}
}
