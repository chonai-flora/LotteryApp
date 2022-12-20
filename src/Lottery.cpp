#include "Lottery.hpp"

// 抽選会クラス(全学生のデータ)
Lottery::Lottery(int32 a1, int32 b1, int32 c1,
			int32 a2, int32 b2, int32 c2,
			int32 a3, int32 b3, int32 c3,
			int32 a4, int32 b4, int32 c4,
			int32 a5, int32 b5, int32 c5,
			int32 d1, int32 d2) {
	m_students = {
		{
			Course::A, {
				{ 1, this->range(1, a1) },
				{ 2, this->range(1, a2) },
				{ 3, this->range(1, a3) },
				{ 4, this->range(1, a4) },
				{ 5, this->range(1, a5) },
			},
		},
		{
			Course::B, {
				{ 1, this->range(1, b1) },
				{ 2, this->range(1, b2) },
				{ 3, this->range(1, b3) },
				{ 4, this->range(1, b4) },
				{ 5, this->range(1, b5) },
			},
		},
		{
			Course::C, {
				{ 1, this->range(1, c1) },
				{ 2, this->range(1, c2) },
				{ 3, this->range(1, c3) },
				{ 4, this->range(1, c4) },
				{ 5, this->range(1, c5) },
			},
		},
		{
			Course::D, {
				{ 1, this->range(1, d1) },
				{ 2, this->range(1, d2) },
			},
		}
	};
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
		int32 grade = Random(1, (course == Course::D ? 2 : 5));
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
	String courseName = courseNames.at(static_cast<int32>(course));

	return U"{}{}{:0>2}"_fmt(grade, courseName, id);
}
