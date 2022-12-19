#include "Lottery.hpp"

// 抽選会クラス(全学生のデータ)
Lottery::Lottery(int32 mi1, int32 ac1, int32 bc1,
			int32 mi2, int32 ac2, int32 bc2,
			int32 mi3, int32 ac3, int32 bc3,
			int32 mi4, int32 ac4, int32 bc4,
			int32 mi5, int32 ac5, int32 bc5,
			int32 ap1, int32 ap2) {
	m_students = {
		{
			Course::MI, {
				{ 1, this->range(1, mi1) },
				{ 2, this->range(1, mi2) },
				{ 3, this->range(1, mi3) },
				{ 4, this->range(1, mi4) },
				{ 5, this->range(1, mi5) },
			},
		},
		{
			Course::AC, {
				{ 1, this->range(1, ac1) },
				{ 2, this->range(1, ac2) },
				{ 3, this->range(1, ac3) },
				{ 4, this->range(1, ac4) },
				{ 5, this->range(1, ac5) },
			},
		},
		{
			Course::BC, {
				{ 1, this->range(1, bc1) },
				{ 2, this->range(1, bc2) },
				{ 3, this->range(1, bc3) },
				{ 4, this->range(1, bc4) },
				{ 5, this->range(1, bc5) },
			},
		},
		{
			Course::AP, {
				{ 1, this->range(1, ap1) },
				{ 2, this->range(1, ap2) },
			},
		}
	};
	m_courseNames = { U"MI", U"AC", U"BC", U"AP" };
}

void Lottery::removeStudents(int32 grade, Course course, Array<int32> ids) {
	if (not m_students[course].contains(grade)) return;

	for (const auto& id : ids) {
		m_students[course][grade].remove_if([&](int32 n) { return (n == id); });
	}
}

Array<String> Lottery::chooseStudents(int32 n, String title, TextWriter& writer, bool insertLineFeed) {
	Array<String> winners;
	if (title.size()) {
		writer << U"<" << title << U">";
	}

	int32 chooseCount = 0;
	while (chooseCount < n) {
		Course course = static_cast<Course>(Random(3));
		int32 grade = Random(1, course == Course::AP ? 2 : 5);
		auto& classroom = m_students[course][grade];
		if (classroom.isEmpty()) continue;

		std::swap(classroom.at(Random(classroom.size() - 1)), classroom.back());
		String student = this->toString(grade, course, classroom.back());

		winners << student;
		writer << student;

		classroom.pop_back();
		chooseCount++;
	}

	if (insertLineFeed) {
		writer << U"";
	}
	return winners;
}

Array<int32> Lottery::range(int32 start, int32 end) const {
	Array<int32> ids;

	for (int32 id = start; id <= end; id++) {
		ids << id;
	}

	return ids;
}

String Lottery::toString(int32 grade, Course course, int32 id) const {
	String department = m_courseNames.at(static_cast<int32>(course));

	return U"{}{}{:0>2}"_fmt(grade, department, id);
}
