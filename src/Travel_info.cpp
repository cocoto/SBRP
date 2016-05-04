/*
 * Implementation of the class Travel_info
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#include "Travel_info.hpp"

Travel_info::Travel_info(int n_v) {
	num_vert = n_v;

	/* Initialize the distance matrix */
	distance = new double*[num_vert];
	for (int i = 0; i < num_vert; i ++) {
		distance[i] = new double[num_vert];
	}

	/* Initialize the travel time matrix */
	travel_time = new double*[num_vert];
	for (int i = 0; i < num_vert; i ++) {
		travel_time[i] = new double[num_vert];
	}
}

Travel_info::~Travel_info() {
	/* Delete the travel time matrix*/
	for (int i = 0; i < num_vert; i++) {
		delete [] travel_time[i];
	}
	delete [] travel_time;

	/* Delete the distance matrix*/
	for (int i = 0; i < num_vert; i++) {
		delete [] distance[i];
	}
	delete [] distance;
}

double Travel_info::get_distance(int v1, int v2) {
	/* Check the input parameters */
	assert_index_vertex(v1);
	assert_index_vertex(v2);

	return distance[v1][v2];
}

void Travel_info::set_distance(int v1, int v2, double d) {
	/* Check the input parameters */
	assert_index_vertex(v1);
	assert_index_vertex(v2);
	assert_non_negative(d);

	distance[v1][v2] = d;
}

double Travel_info::get_time(int v1, int v2) {
	/* Check the input parameters */
	assert_index_vertex(v1);
	assert_index_vertex(v2);

	return travel_time[v1][v2];
}

void Travel_info::set_time(int v1, int v2, double t) {
	/* Check the input parameters */
	assert_index_vertex(v1);
	assert_index_vertex(v2);
	assert_non_negative(t);

	travel_time[v1][v2] = t;
}

bool Travel_info::read_distances_file(const char* f_p) {
	FILE *file; /*File*/
	int n_v; /* Number of vertices in the file */
	double dist; /* Distance read from the file*/

	file = fopen(f_p, "r");

	/* Check if the file could be read or not.*/
	if (file == NULL) {
		printf("   ERROR! The file that contains the distances between the vertices"
				" could not be read. (Class Travel_info).\n");
		return false;
	}

	/* Read the number of vertices in the file*/
	fscanf(file, "%d", &n_v);

	/* Check if the number of vertices in the file is the same as that used to
	 * create the object*/
	if (n_v != num_vert) {
		printf("   ERROR! The number of vertices in the file that contains the distances"
				" does not match that used to create the object. (Class Travel_info).\n");
		fclose(file);
		return false;
	}

	/* Read the distances */
	for (int i = 0; i < num_vert; i++) {
		for (int j = 0; j < num_vert; j++) {
			fscanf(file, "%lf", &dist);
			set_distance(i, j, dist);
		}
	}

	fclose(file);
	return true;
}

void Travel_info::print_distances(){
	for (int i = 0; i < num_vert; i++) {
		for (int j = 0; j < num_vert; j++) {
			printf("%9.2lf ", get_distance(i,j));
		}
		printf("\n");
	}
}

bool Travel_info::read_times_file(const char* f_p) {
	FILE *file; /*File*/
	int n_v; /* Number of vertices in the file */
	double time; /* Time read from the file*/

	file = fopen(f_p, "r");

	/* Check if the file could be read or not.*/
	if (file == NULL) {
		printf("   ERROR! The file that contains the times between the vertices"
				" could not be read. (Class Travel_info).\n");
		return false;
	}

	/* Read the number of vertices in the file*/
	fscanf(file, "%d", &n_v);

	/* Check if the number of vertices in the file is the same as that used to
	 * create the object*/
	if (n_v != num_vert) {
		printf("   ERROR! The number of vertices in the file that contains the times"
				" does not match that used to create the object. (Class Travel_info).\n");
		fclose(file);
		return false;
	}

	/* Read the distances */
	for (int i = 0; i < num_vert; i++) {
		for (int j = 0; j < num_vert; j++) {
			fscanf(file, "%lf", &time);
			set_time(i, j, time);
		}
	}

	fclose(file);
	return true;
}

void Travel_info::print_times(){
	for (int i = 0; i < num_vert; i++) {
		for (int j = 0; j < num_vert; j++) {
			printf("%9.2lf ", get_time(i,j));
		}
		printf("\n");
	}
}

void Travel_info::assert_index_vertex(int v) {
	assert(v >= 0 && v < num_vert);
}

void Travel_info::assert_non_negative(double i) {
	assert(i >=0);
}

