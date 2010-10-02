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
#include <string.h>
#include <stdlib.h>
#include <module.h>

void module_set_debug(struct module *mod, enum debug_level level) {
	mod->debug = level;

	return;
}

void module_describe(const struct module *mod, char *str) {
	str = (char *) malloc(MODULE_DESC_LENGTH * sizeof(char));
	str = memset(str, '\0', MODULE_DESC_LENGTH);

	sprintf(str, "\nModule: %s\nVersion: %d.%d\nDescription: %s\n", mod->name,
					mod->version_major, mod->version_minor, mod->description);

	return;
}
