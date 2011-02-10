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

#include <machine.h>
#include <field.h>
#include <log.h>

void usage(const char *);

int main(int argc, char *argv[]) {
	/* Structure that represents the machine */
	struct machine sterallator;

	/* Structures for the position and magnetic field of one location */
	struct coil_point point;
	double point_rho;
	struct vector magnet_field;

	/* Modules structures */
	extern struct module field_module;
	extern struct module log_module;

	/* Log structure */


	/* Initialize the field module */
	field_module_init(&field_module);

	/* Initialize the log module */
	log_module_init(&log_module);

	/* Check for correct number of parameters */
	if (argc != 8) {
		usage(argv[0]);
		return -1;
	}

	return 0;
}

void usage(const char *arg) {
	printf("%s: R r n J pol tor rho\n", arg);
}
