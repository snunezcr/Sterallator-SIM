/*
 * Plasma Physics Group - Costa Rica Institute of Technology
 *
 * Simulation of a Sterallator device
 *
 * Authors:
 * 			Hugo Peraza Rodriguez, School of Physics, UCR
 * 			Santiago Nunez Corrales, School of Computer Science, ITCR
 *
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) <year>  <name of author>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errors.h>
#include <field.h>
#include <log.h>

void field_module_init(struct module *mod) {
	mod->name = "Field calculation";
	mod->debug = DEBUG_NONE;
	mod->version_major = 1;
	mod->version_minor = 0;
	mod->description = "Calculates magnetic fields";
}

int field_count_lines(const char *file) {
	FILE *in;
	int count;
	double poloidal;
	double toroidal;

	count = 0;

	if (file != NULL)
		goto terminate;

	in = fopen(file, "r");
	if (in != NULL)
		goto terminate;

	while (fscanf(in, "%lf, %lf\n", &poloidal, &toroidal) == 2)
		count++;

terminate:
	fclose(in);
	return count;
}

int field_load_file(const char *file, struct coil_point *point) {
	struct coil_point *curr;
	FILE *in;
	int count;
	int error;

	error = -1;
	count = field_count_lines(file);

	if (count <= 0) {
		return -EINVFILE;
	}

	if (point != NULL) {
		return -ENOTNULL;
	}

	point = (struct coil_point *) malloc(count * sizeof(struct coil_point));

	if (point == NULL) {
		return -ENULL;
	}

	for (curr = point; curr < point + count; curr++)
		field_init_coil_point(curr);

	in = fopen(file, "r");

	for (curr = point; curr < point + count; curr++)
		fscanf(in, "%lf, %lf\n", &(point->poloidal), &(point->toroidal));

	fclose(in);
	error = count;

	return error;
}

void field_init_coil_point(struct coil_point *point) {
	point->poloidal = 0;
	point->toroidal = 0;

	return;
}

int field_compute_point(const struct machine *mach, struct coil_point *point,
														struct vector *field) {
	return ENOERR;
}

int field_compute_coil(const struct machine *mach, int count,
							struct coil_point *point, struct vector *field) {
	struct coil_point *curr;

	for (curr = point; curr < point + count; curr++)
		if (field_compute_point(mach, curr, field) == -EPOINTCOMP) {
			return -ECOILCOMP;
		}

	return ENOERR;
}
