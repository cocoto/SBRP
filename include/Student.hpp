/**
 * \class Student
 *
 * This class models a student (or a group of students) in the SBRP
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#ifndef STUDENT_HPP_
#define STUDENT_HPP_

#include "Vertex.hpp"
#include "Utils.hpp"

class Student:public Vertex {
public:
	/**
	 * Constructor of the class.
	 * \param i the identifier of the student
	 */
	Student(int i);

};

#endif /* STUDENT_HPP_ */
