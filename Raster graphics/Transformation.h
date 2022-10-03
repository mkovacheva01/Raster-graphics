#pragma once
#include <string>
using namespace std;

class Transformation {
	string name;
	size_t number;
	size_t leftORight = 0; // 0 - grayscale, monochrome, negative
						  // 1 - rotate right  2 - rotate left
public:
	Transformation() = default;
	Transformation(const string& name, size_t num, size_t lORr) {
		setName(name);
		setleftORright(lORr);
		number = num;
	}
	const string& getName() const { return name; }
	size_t getNumber() const { return number; }
	size_t getleftORright() const { return leftORight; }
	void setleftORright(size_t lOR) {
		if (name == "rotate") leftORight = lOR;
		else leftORight = 0;
	}

	void setName(const string& name) { this->name = name; }
};

