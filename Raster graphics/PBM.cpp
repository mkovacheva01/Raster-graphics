#include "PBM.h"

PBM::PBM(const string& name, size_t transformationNumber) :Image(name, transformationNumber) {
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

	if (nums.size() == 2) setHeight(nums[1]);
	else {
		file.getline(buff, M);
		while (buff[0] == '#') file.getline(buff, M);
		setHeight(tekeIntsFromChar(buff)[0]);
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

void PBM::setFistRows(std::ofstream& file) {
	file << getP() << std::endl
		<< getWidth() << " " << getHeight() << std::endl;
}

void PBM::negative() {
	for (size_t i = 0; i < numb.size(); i++) {
		if (numb[i] == 1)numb[i] = 0;
		else if (numb[i] == 0)numb[i] = 1;
	}
}

Image* PBM::clone() const {
	return new PBM(*this);
}
