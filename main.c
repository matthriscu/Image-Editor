// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#include <stdio.h>
#include <string.h>
#include "load.h"
#include "save.h"
#include "crop.h"
#include "image.h"
#include "apply.h"
#include "utils.h"
#include "select.h"
#include "rotate.h"

int main(void)
{
	char input_line[MAX_LINE_LENGTH], *command, *param;
	img image;

	// image.matrix is set to NULL to indicate that no image is currently loaded
	image.matrix = NULL;

	do {
		fgets(input_line, MAX_LINE_LENGTH, stdin);
		command = strtok(input_line, "\n ");
		param = strtok(NULL, "\n");

		/* If no image is currently loaded and the command
		   isn't "LOAD" the apporopriate message is shown and
		   the command is skipped as it cannot be executed */
		if (!image.matrix && strcmp(command, "LOAD") != 0) {
			fprintf(stdout, "No image loaded\n");
			continue;
		}

		if (strcmp(command, "LOAD") == 0)
			load(param, &image);
		else if (strcmp(command, "SAVE") == 0)
			save(param, image);
		else if (strcmp(command, "SELECT") == 0)
			select_area(param, &image);
		else if (strcmp(command, "CROP") == 0)
			crop(&image);
		else if (strcmp(command, "ROTATE") == 0)
			rotate(param, &image);
		else if (strcmp(command, "APPLY") == 0)
			apply(param, &image);
		else if (strcmp(command, "EXIT") != 0)
			printf("Invalid command\n");
	} while (strcmp(command, "EXIT") != 0);

	if (image.matrix)
		free_image(image);

	return 0;
}
