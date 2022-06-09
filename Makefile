# Copyright 2022 Matei Hriscu (311CA) <matei.hriscu@stud.acs.upb.ro>

CC=gcc
CFLAGS=-Wall -Wextra -lm

build: image_editor

image_editor:
	$(CC) *.c -o $@ $(CFLAGS)

pack:
	zip -FSr 311CA_HriscuMatei_Tema3.zip README Makefile *.c *.h

clean:
	rm -f image_editor

.PHONY: pack clean
