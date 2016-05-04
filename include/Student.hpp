/**
 * \class Student
 *
 * This class models a student (or a group of students) in the SBRP
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#ifndef SBRP_INCLUDE_STUDENT_HPP_
#define SBRP_INCLUDE_STUDENT_HPP_

#include "Vertex.hpp"
#include "Utils.hpp"

class Student:public Vertex {
public:
	/**
	 * Constructor of the class.
	 * \param i the identifier of the student
	 */
	Student(int i);

	int getWeight() const {
		return weight;
	}

	void setWeight(int weight) {
		this->weight = weight;
	}

private:
	int weight;

};

#endif /* SBRP_INCLUDE_STUDENT_HPP_ */
