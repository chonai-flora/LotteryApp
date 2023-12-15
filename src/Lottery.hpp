#pragma once
#include "Common.hpp"

class Lottery {
public:
	Lottery(int32 a1, int32 b1, int32 c1,
			int32 a2, int32 b2, int32 c2,
			int32 a3, int32 b3, int32 c3,
			int32 a4, int32 b4, int32 c4,
			int32 a5, int32 b5, int32 c5,
			int32 d1, int32 d2);
	void removeStudents(int32 grade, Course course, Array<int32> ids);
	Array<String> chooseStudents(int32 n, String title, TextWriter& writer, bool insertLineFeed = true);

private:
	HashTable<Course, HashTable<int32, Array<int32>>> m_students;

	String toString(int32 grade, Course course, int32 id) const;
};
