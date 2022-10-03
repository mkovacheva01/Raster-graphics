#include "PGM.h"

PGM::PGM(const string& name, size_t transformationNumber) :Image(name, transformationNumber) {
	if (!isValidNameOfPhoto(name)) {
		std::cout << "Invalid name of image" << std::endl;
		return;
	}
	std::ifstream file(name.c_str());
	if (!file.is_open()) {
		std::cout << "File is not open!";
		return;
	}
	char buf[M];
	file.getline(buf, M);
	buf[2] = '\0';
	if (buf[0] != 'P') return;
	setP(buf);

	char buff[M];
	file.getline(buff, M);
	while (buff[0] == '#') file.getline(buff, M);

	vector<size_t> nums = tekeIntsFromChar(buff);
	setWidth(nums[0]);

	if (nums.size() >= 2) {
		setHeight(nums[1]);
		if (nums.size() == 3) setMaxNumber(nums[2]);
		else if (nums.size() == 2) {
			file.getline(buff, M);
			while (buff[0] == '#') file.getline(buff, M);
			setMaxNumber(tekeIntsFromChar(buff)[0]);
		}
	}
	else {
		file.getline(buff, M);
		while (buff[0] == '#') file.getline(buff, M);
		setHeight(tekeIntsFromChar(buff)[0]);
		if (nums.size() == 2) setMaxNumber(nums[1]);
		else if (nums.size() == 1) {
			file.getline(buff, M);
			while (buff[0] == '#') file.getline(buff, M);
			setMaxNumber(tekeIntsFromChar(buff)[0]);
		}
	}

	for (size_t i = 0; i < getHeight(); i++) {
		file.getline(buff, M);
		while (buff[0] == '#') file.getline(buff, M);
		nums = tekeIntsFromChar(buff);
		for (size_t j = 0; j < getWidth(); j++)
			numb.push_back(nums[j]);
	}
	file.close();
}

void PGM::setFistRows(std::ofstream& file) {
	file << getP() << std::endl
		<< getWidth() << " " << getHeight() << std::endl
		<< maxPixNumber << std::endl;
}

void PGM::monochrome() {
	for (size_t i = 0; i < numb.size(); i++) {
		if (numb[i] != 0) numb[i] = 1;
	}
}

void PGM::negative() {
	for (size_t i = 0; i < numb.size(); i++) {
		numb[i] = maxPixNumber - numb[i];
	}
}

Image* PGM::clone() const {
	return new PGM(*this);
}
