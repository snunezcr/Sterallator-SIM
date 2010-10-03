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

#import <machine.h>

#ifndef FIELD_H_
#define FIELD_H_

struct vector {
	double x;
	double y;
	double z;
};

struct coil_point {
	double poloidal;
	double toroidal;
};

void field_module_init(struct module *);

int field_count_lines(const char *);
int field_load_file(const char *, struct coil_point *);

void field_init_coil_point(struct coil_point *);
int field_compute_point(const struct machine *, struct coil_point *, int, int,
															struct vector *);
int field_compute_coil(const struct machine *, int, struct coil_point *,
															struct vector *);

#endif /* FIELD_H_ */
