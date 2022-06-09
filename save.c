// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#include "save.h"
#include "image.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int save(char *param, img image)
{
	/* Return values:
		0 - Executed successfully
		1 - Failed to load the provided file
	*/

	char *file_name = strtok(param, "\n "), *ascii = strtok(NULL, "\n ");

	FILE *out = fopen(file_name, "wt");

	if (!out) {
		fprintf(stderr, "Failed to open %s\n", file_name);
		return 1;
	}

	int save_type = image.type;

	if (!ascii || strcmp(ascii, "ascii"))
		save_type += 3;

	fprintf(out, "P%d\n%d %d\n%d\n", save_type, image.width,
			image.height, image.max_value);

	if (save_type == 2 || save_type == 3) {
		write_text(out, image);
	} else if (save_type == 5 || save_type == 6) {
		freopen(file_name, "ab", out);
		write_binary(out, image);
	}

	fclose(out);

	printf("Saved %s\n", file_name);
	return 0;
}

void write_text(FILE *out, img image)
{
	for (int i = 0; i < image.height; ++i) {
		for (int j = 0; j < image.width; ++j)
			for (int k = 0; k < image.colors; ++k)
				fprintf(out, "%0.f ", round(image.matrix[i][j][k]));
		fprintf(out, "\n");
	}
}

void write_binary(FILE *out, img image)
{
	/* A temporary variable must be used when writing to a binary file
	   as the image is stored using the float data type but the pixel
	   information is encoded using a single byte per subpixel */
	   
	unsigned char temp;
	for (int i = 0; i < image.height; ++i)
		for (int j = 0; j < image.width; ++j)
			for (int k = 0; k < image.colors; ++k) {
				temp = round(image.matrix[i][j][k]);
				fwrite(&temp, sizeof(unsigned char), 1, out);
			}
}
