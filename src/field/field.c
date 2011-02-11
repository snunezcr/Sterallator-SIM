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
#include <math.h>
#include <errors.h>
#include <machine.h>
#include <field.h>
#include <log.h>

struct module field_module;

void field_module_init(struct module *mod) {
	mod->name = "Field calculation";
	mod->debug = DEBUG_INFO;
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

	if (file == NULL)
		goto terminate;

	in = fopen(file, "r");

	if (in == NULL)
		goto terminate;

	while (fscanf(in, "%lf\t%lf\n", &poloidal, &toroidal) == 2)
		count++;

terminate:
	fclose(in);
	return count;
}

struct coil_point * field_load_file(const char *file,
										struct coil_point *point, int *count) {
	struct coil_point *curr;
	FILE *in;
	int error;
	int i;

	error = -1;
	*count = field_count_lines(file);

	if (*count <= 0) {
		return NULL;
	}

	if (point != NULL) {
		return NULL;
	}

	point = (struct coil_point *) malloc(*count * sizeof(struct coil_point));

	if (point == NULL) {
		return NULL;
	}

	for (curr = point; curr < point + *count; curr++)
		field_init_coil_point(curr);

	in = fopen(file, "r");

	for (curr = point; curr < point + *count; curr++) {
		fscanf(in, "%lf\t%lf\n", &(curr->poloidal), &(curr->toroidal));
		curr->poloidal *= TORADS;
		curr->toroidal *= TORADS;
		printf("\n\n%lf...\n\n", curr->poloidal);
	}

	fclose(in);

	return point;
}

void field_init_coil_point(struct coil_point *point) {
	point->poloidal = 0;
	point->toroidal = 0;

	return;
}

int field_compute_point(const struct machine *mach, struct coil_point *point,
								int count, int i, struct vector *field,
								double poloidal, double toroidal, double rh) {
	/* Arithmetic pre-calculations:
	 *
	 * In order to avoid loss in execution time, the main problem is divided
	 * into subexpressions thus reducing the number of calls to FPU functions.
	 */
	double cos_pol_a, cos_tor_a, sin_pol_a, sin_tor_a;
	double cos_pol_b, cos_tor_b, sin_pol_b, sin_tor_b;
	double cos_pol_m, cos_tor_m, sin_pol_m, sin_tor_m;

	double exp_a, exp_b, exp_c, exp_d, exp_e;
	double exp_f, exp_g, exp_h, exp_i, exp_j;
	double exp_k, exp_l, exp_m, exp_n, exp_o;

	double rj, rn, j, rho;
	double rn_sq, rj_rn, rho_rn;
	int n;

	double denom, num_x, num_y, num_z;

	/* Setup the base data for sines and cosines */
	cos_pol_a = cos(point[i].poloidal);
	cos_tor_a = cos(point[i].toroidal);
	sin_pol_a = sin(point[i].poloidal);
	sin_tor_a = sin(point[i].toroidal);
	cos_pol_b = cos(point[(i + 1) % count].poloidal);
	cos_tor_b = cos(point[(i + 1) % count].toroidal);
	sin_pol_b = sin(point[(i + 1) % count].poloidal);
	sin_tor_b = sin(point[(i + 1) % count].toroidal);
	cos_pol_m = cos(poloidal);
	cos_tor_m = cos(toroidal);
	sin_pol_m = sin(poloidal);
	sin_tor_m = sin(toroidal);

	/* Obtain data from the machine description */
	rj = mach->r_maj;
	rn = mach->r_min;
	j = mach->j;
	rho = rh;
	n = mach->n;

	/* Precompute constant products */
	rn_sq = rn * rn;
	rj_rn = rj * rn;
	rho_rn = rho * rn;

	/* Precompute common factors */
	exp_a = rj + rn * cos_pol_a;
	exp_b = rj + rn * cos_pol_b;
	exp_c = rj + rn * cos_pol_b;
	exp_d = sin_tor_b * sin_pol_a;
	exp_e = sin_pol_b * sin_tor_a;
	exp_f = sin_tor_a * sin_pol_m;
	exp_g = sin_tor_m * sin_pol_a;
	exp_h = sin_pol_m * sin_tor_b;
	exp_i = sin_pol_b * sin_tor_m;
	exp_j = cos_tor_b * sin_pol_a;
	exp_k = sin_pol_b * cos_tor_a;
	exp_l = cos_tor_a * sin_pol_m;
	exp_m = cos_tor_m * sin_pol_a;
	exp_n = cos_tor_b * sin_pol_m;
	exp_o = sin_pol_b * cos_tor_m;

	/* Initialize components */
	denom = 0;
	num_x = 0;
	num_y = 0;
	num_z = 0;

	/* Calculate the denominator */
	denom += 0.5*rn_sq*(1 + sin_pol_a*sin_pol_b);
	denom += rho*rho;
	denom += 0.5*exp_a*exp_b*(cos_tor_a*cos_tor_b + sin_tor_a*sin_tor_b);
	denom -= rj_rn*sin_pol_m*(sin_pol_a + sin_pol_b);
	denom -= exp_c*exp_a*(cos_tor_a*cos_tor_m + sin_tor_a*sin_tor_m);
	denom -= exp_b*exp_c*(cos_tor_b*cos_tor_m + sin_tor_b*sin_tor_m);
	denom *= 1.5;

	if (denom == 0.0) {
		return -EINVVALUE;
	}

	/* Calculate the x component for the magnetic field */
	num_x += rj_rn*(exp_d - exp_e);
	num_x += rn_sq*cos_pol_b*(exp_d - exp_e);
	/* TODO: The following case seems odd with respect to symmetry below */
	num_x += rj*(rho*exp_f - rn*exp_g);
	num_x += rho_rn*(cos_pol_a*exp_f - cos_pol_m*exp_g);
	num_x -= rj*(rho*exp_h - rn*exp_i);
	num_x += rho_rn*cos_pol_b*(exp_h - exp_i);
	num_x *= MU0_4PI;
	num_x *= j;
	num_x *= n;

	/* Calculate the y component for the magnetic field */
	num_y -= rj_rn*(exp_j - exp_k);
	num_y -= rn_sq*(cos_pol_b*exp_j - cos_pol_a*exp_k);
	num_y -= rj*(rho*exp_l - rn*exp_m);
	num_y -= rho_rn*(cos_pol_a*exp_l - cos_pol_m*exp_m);
	num_y -= rj*(rho*exp_n - rn*exp_o);
	num_y -= rho_rn*(cos_pol_b*exp_n - cos_pol_m*exp_o);

	/* Calculate the z component for the magnetic field */
	num_z += exp_a*exp_b*(sin_tor_a*cos_tor_b - cos_tor_b*sin_tor_a);
	num_z += exp_b*exp_c*(sin_tor_m*cos_tor_b - cos_tor_m*sin_tor_a);
	num_z += exp_a*exp_c*(sin_tor_a*cos_tor_m - cos_tor_m*sin_tor_a);

	/* Set the appropriate vector value */
	field->x = num_x/denom;
	field->y = num_y/denom;
	field->z = num_z/denom;

	return ENOERR;
}

int field_compute_coil(const struct machine *mach, int count,
							struct coil_point *point, struct vector *field,
							double poloidal, double toroidal, double rh) {
	int i;

	for (i = 0; i < count; i++)
		if (field_compute_point(mach, point, i, count, field,
										poloidal, toroidal, rh)
															== -EPOINTCOMP) {
			return -ECOILCOMP;
		}

	return ENOERR;
}
