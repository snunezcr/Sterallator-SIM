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

#ifndef ERRORS_H_
#define ERRORS_H_

#include <module.h>

#define ENOERR		(0)
#define EINVFILE	(1)
#define ENOTNULL	(2)
#define ENULL		(3)
#define ECOILCOMP	(4)
#define EPOINTCOMP	(5)
#define EOPEN		(6)
#define EINVOPTION	(7)
#define ENOTOPEN	(8)
#define EINVVALUE	(9)

#define ERROR_MAX_LENGTH	200

void error_describe(const struct module *, int, char *);

#endif /* ERRORS_H_ */
