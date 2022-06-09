// Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_alloc(void *p)
{
	if (!p) {
		fprintf(stderr, "Memory allocation error\n");
		exit(-1);
	}
}

void swap(void *a, void *b, size_t size)
{
	void *temp = malloc(size);
	check_alloc(temp);

	memcpy(temp, a, size);
	memcpy(a, b, size);
	memcpy(b, temp, size);

	free(temp);
}

float clamp(float x, int lower_bound, int upper_bound)
{
	if (x < lower_bound)
		return lower_bound;
	else if (x > upper_bound)
		return upper_bound;
	return x;
}
