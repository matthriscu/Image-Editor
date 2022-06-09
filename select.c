// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#include "select.h"
#include "image.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int select_area(char *param, img *image)
{
	/* Return values:
		0 - Executed successfully
		1 - Invalid number of arguments
		2 - Invalid arguments
		3 - Invalid set of coordinates
	*/

	char *arg = strtok(param, "\n ");

	if (arg && strcmp(arg, "ALL") == 0) {
		image->x1 = 0;
		image->y1 = 0;
		image->x2 = image->width;
		image->y2 = image->height;
		printf("Selected ALL\n");
		return 0;
	}

	int coords[4] = {0};

	for (int i = 0; i < 4; ++i) {
		if (!arg) {
			printf("Invalid command\n");
			return 1;
		}

		coords[i] = atoi(arg);

		/* If atoi returned 0, but the argument is not 0 that means atoi
		   wasn't able to convert the string into a number and therefore the
		   parameter that was provided is invalid */
		if (coords[i] == 0 && strcmp(arg, "0") != 0) {
			printf("Invalid command\n");
			return 2;
		}

		arg = strtok(NULL, "\n ");
	}

	if (coords[0] > coords[2])
		swap(&coords[0], &coords[2], sizeof(int));
	if (coords[1] > coords[3])
		swap(&coords[1], &coords[3], sizeof(int));

	if (coords[0] < 0 || coords[1] < 0 ||
		coords[2] > image->width || coords[3] > image->height ||
		coords[0] == coords[2] || coords[1] == coords[3]) {
		printf("Invalid set of coordinates\n");
		return 3;
	}

	image->x1 = coords[0];
	image->y1 = coords[1];
	image->x2 = coords[2];
	image->y2 = coords[3];

	printf("Selected %d %d %d %d\n", image->x1,
		   image->y1, image->x2, image->y2);

	return 0;
}
