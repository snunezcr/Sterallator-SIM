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

#ifndef MACHINE_H_
#define MACHINE_H_

#define MU0_4PI	0.0000001
#define TORADS	0.01745329251994

struct machine {
	double r_maj;			/* Machine radius */
	double r_min;			/* Toroidal radius */
	double rho;				/* Distance from the toroidal axis to (x, y, z) */
	int n;					/* Number of turns for each coil */
	double j;				/* Machine current */
};

void machine_set_params(struct machine *, double, double, double, int, double);

#endif /* MACHINE_H_ */
