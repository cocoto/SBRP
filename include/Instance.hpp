/**
 * \class Instance
 *
 * This class models an instance of the SBRP and the information it requires
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#ifndef INSTANCE_HPP_
#define INSTANCE_HPP_

#include "assert.h"
#include <vector>
#include <stdio.h>

#include "School.hpp"
#include "Student.hpp"
#include "Stop.hpp"
#include "Vertex.hpp"
#include "Travel_info.hpp"
#include "Utils.hpp"

class Instance {
private:
	/** Number of bus stops*/
	int num_stops;
	/** Number of students*/
	int num_students;
	/** Capacity of the buses*/
	int cap_buses;

	/** Travel information between each pair of vertices*/
	Travel_info* travel_info;
	/** Maximum distance that a student is allowed to walk to a stop*/
	double max_dist_stop;

	/** School */
	School* school;
	/** Array of stops */
	Stop** stop;
	/** Array of students*/
	Student** student;

	/* Pre-processed information*/
	/** Vector of students that can reach a stop*/
	std::vector<int>** students_stop;
	/** Vector of stops that a student can reach */
	std::vector<int>** stops_student;

public:

	/**
	 * Constructor of the class. This constructor does not initialize the travel
	 * information of the instance.
	 *
	 * \param n_stop number of stops
	 * \param n_stud number of students
	 * \param c_bus capacity of the buses
	 * \param m_d_s maximum distance that a student is allowed to walk
	 */
	Instance(int n_stop, int n_stud, int c_bus, double m_d_s);

	/**
	 * Destructor of the class.
	 */
	~Instance();

	/**
	 * Get the number of stops in the instance.
	 *
	 *\return the number of stops
	 */
	int get_num_stops();

	/**
	 * Get the number of students in the instance.
	 *
	 * \return the number of students
	 */
	int get_num_students();

	/**
	 * Get the capacity of the buses.
	 * \return the capacity of the buses
	 */
	int get_cap_buses();

	/**
	 * Get the maximum distance that a student is allowed to walk to a stop.
	 *
	 * \return the maximum distance
	 */
	double get_max_dist_stop();

	/**
	 * Get a pointer to the object school in the instance.
	 *
	 * \return a pointer to the school object
	 */
	School* get_school();

	/**
	 * Get a pointer to an object stop in the instance.
	 *
	 * \param s_i the index of the stop
	 * \return a pointer to the stop object
	 */
	Stop* get_stop(int s_i);

	/**
	 * Get a pointer to an object student in the instance.
	 *
	 * \param stu_i the index of the student
	 * \return a pointer to the student object
	 */
	Student* get_student(int stu_i);

	/**
	 * Get the distance between a bus stop and the school.
	 *
	 * \param s_i the index of the stop
	 * \return the distance between the stop and the school
	 */
	double get_dist_stop_school(int s_i);

	/**
	 * Get the travel time between a bus stop and the school.
	 *
	 * \param s_i the index of the stop
	 * \return the travel time between the stop and the school
	 */
	double get_time_stop_school(int s_i);

	/**
	 * Get the distance between the school and a bus stop.
	 *
	 * \param s_i the index of the stop
	 * \return the distance between the school and the stop
	 */
	double get_dist_school_stop(int s_i);

	/**
	 * Get the travel time between the school and a bus stop.
	 *
	 * \param s_i the index of the stop
	 * \return the travel time between the school and the stop
	 */
	double get_time_school_stop(int s_i);


	/**
	 * Get the distance between two bus stops.
	 *
	 * \param s_i_1 index of the first stop
	 * \param s_i_2 index of the second stop
	 * \return the distance between the stops
	 */
	double get_dist_stops(int s_i_1, int s_i_2);

	/**
	 * Get the travel time between two bus stops.
	 * \param s_i_1 index of the fist stop
	 * \param s_i_2 index of the second stop
	 * \return the travel time between the two stops
	 */
	double get_time_stops(int s_i_1, int s_i_2);

	/**
	 * Get the distance between a student and a stop.
	 *
	 * \param stu_i index of the student
	 * \param sto_i index of the stop
	 * \return the distance between the student and the stop
	 */
	double get_dist_student_stop(int stu_i, int sto_i);

	/**
	 * Get the travel time between a student and a stop.
	 *
	 * \param stu_i index of the student
	 * \param sto_i index of the stop
	 * \return the travel time between the student and the stop
	 */
	double get_time_student_stop(int stu_i, int sto_i);

	/**
	 * Check if a student can be assigned to a stop.
	 *
	 * \param stu_i index of the student
	 * \param sto_i index of the stop
	 * \return true if the student can be assigned to that stop, false otherwise
	 */
	bool can_student_assigned_stop(int stu_i, int sto_i);


	/************* Assertion functions *************/

	/**
	 * Assert that an index of a stop is valid.
	 *
	 * \param s_i index of a stop
	 */
	void assert_index_stop(int s_i);

	/**
	 * Assert that an index of a student is valid.
	 *
	 * \param s_i index of a student
	 */
	void assert_index_student(int s_i);

	/**
	 * Assert that an index of a bus is valid.
	 *
	 * \param b_i index of a bus
	 */
	void assert_index_bus(int b_i);


	/************* Input/Output (reading and printing) functions *************/

	/**
	 * Create a new instance with the information stored in the files specified.
	 *
	 * \param f_inst path of the file that contains the information about
	 *               the instance
	 * \param f_dist path of the file that contains the distance matrix
	 * \param f_times path of the file that contains the travel time matrix
	 * \return a pointer to the new instance object
	 */
	static Instance* read_from_files(const char* f_inst, const char* f_dist, const char* f_times);

	/**
	 * Print the information of the instance on the console.
	 */
	void print();

};



#endif /* INSTANCE_HPP_ */
