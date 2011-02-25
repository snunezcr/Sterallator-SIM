/*
 * Plasma Physics Group - Costa Rica Institute of Technology
 *
 * Simulation of a Sterallator device
 *
 * Authors:
 *	Hugo Peraza Rodriguez, School of Physics, UCR
 * 	Santiago Nunez Corrales, School of Computer Science, ITCR
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
#include <stdlib.h>
#include <errors.h>
#include <field.h>
#include <math.h>
#include <log.h>

#define FN_SIZE	256

void usage(const char *);

int main(int argc, char *argv[]) {
	/* Error handler */
	int error;

	/* Parameter conversion variables */
	double r_maj;
	double r_min;
	double j;
	double pol;
	double tor;
	double rho;
	int n;
	double modulus;

	/* Structure that represents the machine */
	struct machine sterallator;

	/* Coil points */
	struct coil_point **coils;

	/* Amount of coil points */
	int *coil_count;

	/* Generator for coil filenames */
	char **coil_files;

	/* Counters */
	int i;

	/* Structures for the position and magnetic field of one location */
	struct coil_point point;
	double point_rho;
	struct vector magnet_field;

	/* Modules structures */
	extern struct module field_module;
	extern struct module log_module;

	/* Log structure */
	extern struct log history;

	/* Initialize the field module */
	field_module_init(&field_module);

	/* Initialize the log module */
	log_module_init(&log_module);

	/* Open log file */
	log_open(&history, &field_module, LOG_FILE);

	/* Create start log entry */
	log_entry(DEBUG_INFO, &log_module, &log_module,
					"Log module initialized", ENOERR, &history);

	/* Check for correct number of parameters */
	if (argc != 9) {
		usage(argv[0]);
		log_entry(DEBUG_ERROR, &field_module, &field_module,
				"Incomplete parameters", EINVOPTION, &history);
		log_close(&history);
		return -1;
	}

	/* Obtain and check all parameters */
	r_maj = atof(argv[1]);
	r_min = atof(argv[2]);
	n = atoi(argv[3]);
	j = atof(argv[4]);
	pol = atof(argv[5]);
	tor = atof(argv[6]);
	rho = atof(argv[7]);

	/* Scale to radians */
	pol *= TORADS;
	tor *= TORADS;

	/* Check for R > r */
	if (r_min >= r_maj) {
		usage(argv[0]);
		log_entry(DEBUG_ERROR, &field_module, &field_module,
				"Major radius smaller than minor radius",
							EINVVALUE, &history);
		log_close(&history);
		return -1;
	}

	/* Set local point data */
	point.poloidal = pol;
	point.toroidal = tor;
	point_rho = rho;

	/* Set parameters of the sterallator */
	machine_set_params(&sterallator, r_maj, r_min, n, j);
	log_entry(DEBUG_INFO, &field_module, &sterallator,
						"Machine initialized", ENOERR, &history);

	/* Set initial data of magnetic field */
	magnet_field.x = 0;
	magnet_field.y = 0;
	magnet_field.z = 0;

	/* Initialize coil filenames */
	coil_files = (char **) malloc (n * sizeof(char *));

	for (i = 0; i < n; i++)
		coil_files[i] = (char *) malloc(FN_SIZE);

	/* Initialize coil counts */
	coil_count = (int *) malloc(n * sizeof(int));

	/* Generate coil file names */
	for (i = 0; i < n; i++)
		sprintf(coil_files[i], "%s/coil_%d.txt", argv[8], i);

	/* Generate coil points arrays */
	coils = (struct coil_point **) malloc(n * sizeof(struct coil_point *));

	for (i = 0; i < n; i++) {
		/* Read the file with coil coordinates */
		coils[i] = field_load_file(coil_files[i], coils[i], 
								&coil_count[i]);

		if (coil_count[i] > 0) {
			log_entry(DEBUG_INFO, &field_module, &coils[i],
					"Coil data loaded", ENOERR, &history);
		} else {
		log_entry(DEBUG_ERROR, &field_module, &field_module,
				"Coil data not loaded", EINVFILE, &history);
		}

		/* Compute magnetic field vector at desired location */
		if (coils[i] == NULL)
			return;

		field_compute_coil(&sterallator, coil_count[i], coils[i], 
					&magnet_field, point.poloidal,
					point.toroidal, point_rho);
	}

	/* Print the value of the magnetic field at the point */
	printf("(%lf, %lf, %lf) B[x]: %lf\tB[y]: %lf\tB[z]: %lf\t", point.poloidal, point.toroidal,
						point_rho, magnet_field.x, 
						magnet_field.y, magnet_field.z);
	
	/* Calculate modulus of magnetic field */
	modulus += magnet_field.x * magnet_field.x;
	modulus += magnet_field.y * magnet_field.y;
	modulus += magnet_field.z * magnet_field.z;
	modulus = sqrt(modulus);
	printf("|B| = %lf\n", modulus);

	/* Clean memory */
	if (coils != NULL) {
		for (i = 0; i < n; i++)
			free(coils[i]);
		free(coils);
	}
	
	if (coil_files != NULL) {
		for (i = 0; i < n; i++)
			free(coil_files[i]);
		free(coil_files);
	}

	if (coil_count != NULL)
		free(coil_count);

	/* Create start log entry */
	log_entry(DEBUG_INFO, &log_module, &log_module, "Log module closed",
							ENOERR, &history);

	/* Close log */
	log_close(&history);

	return 0;
}

void usage(const char *arg) {
	printf("%s: R r n J pol tor rho coord-dir\n", arg);
}
