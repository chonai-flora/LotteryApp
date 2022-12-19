#pragma once
#include "Common.hpp"

class Lottery {
public:
	Lottery(int32 mi1, int32 ac1, int32 bc1,
			int32 mi2, int32 ac2, int32 bc2,
			int32 mi3, int32 ac3, int32 bc3,
			int32 mi4, int32 ac4, int32 bc4,
			int32 mi5, int32 ac5, int32 bc5,
			int32 ap1, int32 ap2);
	void removeStudents(int32 grade, Course course, Array<int32> ids);
	Array<String> chooseStudents(int32 n, String title, TextWriter& writer, bool insertLineFeed = true);

private:
	HashTable<Course, HashTable<int32, Array<int32>>> m_students;
	Array<String> m_courseNames;

	Array<int32> range(int32 start, int32 end) const;
	String toString(int32 grade, Course course, int32 id) const;
};
