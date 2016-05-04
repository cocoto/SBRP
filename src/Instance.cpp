/*
 * Implementation of the class Instance
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#include "Instance.hpp"

Instance::Instance(int n_stop, int n_stud, int c_bus, double m_d_s) {
	num_stops = n_stop;
	num_students = n_stud;
	cap_buses = c_bus;

	travel_info = new Travel_info(1 + num_stops + num_students); /* The 1 corresponds to the school*/
	max_dist_stop = m_d_s;

	/* Initialize the list of students that can reach a stop */
	students_stop = new std::vector<int>*[num_stops];
	for (int i = 0; i < num_stops; i++) {
		students_stop[i] = new std::vector<int>();
	}

	/* Initialize the list of stops that a student can reach */
	stops_student = new std::vector<int>*[num_students];
	for (int i = 0; i < num_students; i++) {
		stops_student[i] = new std::vector<int>();
	}

	school = new School(0); /* It is assumed that the first vertex is the school*/

	/* Initialize the array with the stops*/
	stops = new Stop*[num_stops];
	for (int i = 0; i < n_stop; i++) {
		stops[i] = new Stop(i + 1); /* The plus one accounts for the school already created*/
	}

	/* Initialize the array with the students*/
	student = new Student*[num_students];
	for (int i = 0; i < n_stud; i++) {
		/* The plus accounts for the school and the stops already created*/
		student[i] = new Student(i + num_stops + 1);
	}
}

Instance::~Instance() {

	/* Delete the array of students*/
	for (int i = 0; i < num_students; i++){
		delete student[i];
	}
	delete [] student;

	/* Delete the array of stops*/
	for (int i = 0; i < num_stops; i++) {
		delete stops[i];
	}
	delete [] stops;

	/* Delete the school */
	delete school;

	/* Delete the list of stops that a student can reach */
	for (int i = 0; i < num_students; i++) {
		delete stops_student[i];
	}
	delete [] stops_student;

	/* Delete the list of students that can reach a stop */
	for (int i = 0; i < num_stops; i++) {
		delete students_stop[i];
	}
	delete [] students_stop;

	/* Delete the travel information*/
	delete travel_info;
}

int Instance::get_num_stops() {
	return num_stops;
}

int Instance::get_num_students() {
	return num_students;
}

int Instance::get_cap_buses() {
	return cap_buses;
}

double Instance::get_max_dist_stop() {
	return max_dist_stop;
}

School* Instance::get_school() {
	return school;
}

Stop* Instance::get_stop(int s_i) {
	/* Check the input parameters */
	assert_index_stop(s_i);

	return stops[s_i];
}

Student* Instance::get_student(int stu_i) {
	/* Check the input parameters */
	assert_index_student(stu_i);

	return student[stu_i];
}

double Instance::get_dist_stop_school(int s_i) {
	/* Check the input parameters */
	assert_index_stop(s_i);

	/* Use the ids of the vertices as indexes in travel_info*/
	return travel_info->get_distance(stops[s_i]->get_id(), school->get_id());
}

double Instance::get_time_stop_school(int s_i) {
	/* Check the input parameters */
	assert_index_stop(s_i);

	/* Use the ids of the vertices as indexes in travel_info*/
	return travel_info->get_time(stops[s_i]->get_id(), school->get_id());
}

double Instance::get_dist_school_stop(int s_i) {
	/* Check the input parameters */
	assert_index_stop(s_i);

	/* Use the ids of the vertices as indexes in travel_info*/
	return travel_info->get_distance(school->get_id(), stops[s_i]->get_id());
}

double Instance::get_time_school_stop(int s_i) {
	/* Check the input parameters */
	assert_index_stop(s_i);

	/* Use the ids of the vertices as indexes in travel_info*/
	return travel_info->get_time(school->get_id(), stops[s_i]->get_id());
}

double Instance::get_dist_stops(int s_i_1, int s_i_2) {
	/* Check the input parameters */
	assert_index_stop(s_i_1);
	assert_index_stop(s_i_2);

	/* Use the ids of the vertices as indexes in travel_info*/
	return travel_info->get_distance(stops[s_i_1]->get_id(), stops[s_i_2]->get_id());
}

double Instance::get_time_stops(int s_i_1, int s_i_2) {
	/* Check the input parameters */
	assert_index_stop(s_i_1);
	assert_index_stop(s_i_2);

	/* Use the ids of the vertices as indexes in travel_info*/
	return travel_info->get_time(stops[s_i_1]->get_id(), stops[s_i_2]->get_id());
}

double Instance::get_dist_student_stop(int stu_i, int sto_i) {
	/* Check the input parameters */
	assert_index_student(stu_i);
	assert_index_stop(sto_i);

	/* Use the ids of the vertices as indexes in travel_info*/
	return travel_info->get_distance(student[stu_i]->get_id(), stops[sto_i]->get_id());
}

double Instance::get_time_student_stop(int stu_i, int sto_i) {
	/* Check the input parameters */
	assert_index_student(stu_i);
	assert_index_stop(sto_i);

	/* Use the ids of the vertices as indexes in travel_info*/
	return travel_info->get_time(student[stu_i]->get_id(), stops[sto_i]->get_id());
}

bool Instance::can_student_assigned_stop(int stu_i, int sto_i) {
	/* Check the input parameters */
	assert_index_student(stu_i);
	assert_index_stop(sto_i);

	return (get_dist_student_stop(stu_i, sto_i) <= get_max_dist_stop());
}

void Instance::assert_index_stop(int s_i) {
	assert(s_i >= 0 && s_i < get_num_stops());
}

void Instance::assert_index_student(int s_i) {
	assert(s_i >= 0 && s_i < get_num_students());
}

/************* Input/Output (reading and printing) functions *************/

Instance* Instance::read_from_files(const char* f_inst, const char* f_dist, const char* f_times) {
	FILE *file; /*File*/
	Instance* instance; /* Instance to be created */
	int n_stop; /* Number of stops in the instance*/
	int n_stud; /* Number of students in the instance */
	int c_bus; /* Capacity of the buses */
	double m_d_s; /* Maximum distance that a student is allowed to walk in the instance */


	/* Read the information from the instance file */

	file = fopen(f_inst, "r");

	/* Check if the file could be read or not.*/
	if (file == NULL) {
		printf("   ERROR! The file that contains the information about the instance"
				" could not be read. (Class Instance).\n");
		return NULL;
	}

	/* Read the information from the file (check the file format in the file info_format.txt)*/
	fscanf(file, "%d %d %d %lf", &n_stop, &n_stud, &c_bus, &m_d_s);


	/* Create the object with the information read */
	instance = new Instance(n_stop, n_stud, c_bus, m_d_s);
	for(int i =0 ; i< n_stud ; ++i){
		int nb=1;
		//fscanf(file,"%d",&nb);
		instance->get_student(i)->setWeight(nb);
	}
	fclose(file);

	/* Try to read the distance matrix */
	if (!instance->travel_info->read_distances_file(f_dist)) {
		printf("   ERROR! It was not possible to read the distance matrix from a file"
				" (Class Instance).\n");
		delete instance;
		return NULL;
	}

	/* Try to read the travel time matrix */
	if (!instance->travel_info->read_times_file(f_times)) {
		printf("   ERROR! It was not possible to read the travel time matrix from a file"
				" (Class Instance).\n");
		delete instance;
		return NULL;
	}

	/* Fill the vectors that contain the students that can reach a stop, and the
	 * stops that each student can reach.*/
	for (int stu = 0; stu < instance->num_students; stu++) {
		for (int stop = 0; stop < instance->num_stops; stop++) {
			if (instance->can_student_assigned_stop(stu, stop)) {
				instance->stops_student[stu]->push_back(stop);
				instance->students_stop[stop]->push_back(stu);
			}
		}
		/* If the student cannot reach any stop*/
		if (instance->stops_student[stu]->size() == 0) {
			printf("   ERROR! Student %d cannot reach any bus stop. (Class Instance).\n", stu);
			delete instance;
			return NULL;
		}
	}

	return instance;
}

void Instance::print() {
	printf("Information about the instance: \n");
	printf("  - Number of stops: %d\n", get_num_stops());
	printf("  - Number of students: %d\n", get_num_students());
	printf("  - Capacity of the buses: %d\n", get_cap_buses());
	printf("  - Maximum distance that students are allowed to walk: %.2lf\n", get_max_dist_stop());
	printf("Distance matrix:\n");
	travel_info->print_distances();
	printf("Travel time matrix: \n");
	travel_info->print_times();
}
