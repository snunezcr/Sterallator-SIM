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

#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <module.h>

#define LOG_STDOUT			0
#define LOG_FILE			1
#define LOG_MAX_SIZE		300

struct log {
	FILE *file_ptr;
	char *file_name;
};

void log_module_init(struct module *);
void log_init(struct log *);
int log_open(struct log *, struct module *, int);
void log_close(struct log *);
void log_error_describe(const struct module *, int, char *);
void log_entry(int, struct module *, void *, char *, int, struct log *);

#endif /* LOG_H_ */
