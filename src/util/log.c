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

#include <stdlib.h>
#include <string.h>
#include <errors.h>
#include <time.h>
#include <log.h>

void log_module_init(struct module *mod) {
	mod->name = "History log";
	mod->debug = DEBUG_INFO;
	mod->version_major = 1;
	mod->version_minor = 0;
	mod->description = "Stores execution history";
}

int log_open(struct log *history, struct module *mod, int option) {
	switch (option) {
	case LOG_FILE:
		if (history->file_ptr != NULL)
			return -EOPEN;

		history->file_ptr = fopen(history->file_name, "a");
		if (history->file_ptr == NULL) {
			history->file_ptr = stdout;
			log_entry(DEBUG_ERROR, mod, history->file_ptr, NULL,
															-ENOTOPEN, history);
			log_entry(DEBUG_WARN, mod, history->file_ptr,
										"falling back to stdout", 0, history);
		}
		else {
			log_entry(DEBUG_INFO, mod, history->file_ptr,
										"log initialized to file", 0, history);
		}
		break;
	case LOG_STDOUT:
		if (history->file_ptr != NULL)
			if (history->file_ptr != stdout)
				fclose(history->file_ptr);
			else
				log_entry(DEBUG_ERROR, mod, history->file_ptr, NULL, -EOPEN,
																	history);
		else
			history->file_ptr = stdout;
		break;
	default:
		break;
	}

	return ENOERR;
}

void log_close(struct log *history) {
	if (history->file_ptr != NULL)
		if (history->file_ptr != stdout)
			fclose(history->file_ptr);

	return;
}

void log_entry(int dbg, struct module *mod, void *addr, char *msg, int err,
														struct log *history) {
	struct tm *lt_info;
	time_t local_time;
	char *message;
	char *local_error;

	if (mod->debug == DEBUG_NONE)
		return;

	if (dbg > mod->debug)
		return;

	message = (char *) malloc(LOG_MAX_SIZE * sizeof(char));
	message = memset(message, '\0', LOG_MAX_SIZE);

	local_time = time(NULL);
	lt_info = localtime(&local_time);

	local_error = NULL;

	switch (dbg) {
	case DEBUG_INFO:
		sprintf(message, "[%c - %s] address: %p module: %s message: %s\n",
			debug_acronym[DEBUG_INFO], asctime(lt_info), addr, mod->name, msg);
		fprintf(history->file_ptr, message);
		break;
	case DEBUG_WARN:
		sprintf(message, "[%c - %s] address: %p module: %s message: %s\n",
			debug_acronym[DEBUG_WARN], asctime(lt_info), addr, mod->name, msg);
		fprintf(history->file_ptr, message);
		break;
	case DEBUG_ERROR:
		error_describe(mod, err, local_error);
		sprintf(message, "[%c - %s] address: %p %s\n",
			debug_acronym[DEBUG_ERROR], asctime(lt_info), addr, local_error);
		fprintf(history->file_ptr, message);
		break;
	default:
		break;
	}

	return;
}
