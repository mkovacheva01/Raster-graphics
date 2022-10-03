#include "PPM.h"

PPM::PPM(const string& name, size_t transformationNumber) : Image(name, transformationNumber) {
	std::ifstream file(name.c_str());
	if (!file.is_open()) {
		std::cout << "File is not open!";
		return;
	}

	char buf[M];
	file.getline(buf, M);
	buf[2] = '\0';
	if (buf[0] != 'P') return;
	setP(buf); //cpy

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

	Pixel p;
	for (size_t i = 0; i < getHeight() * getWidth(); i++) {
		file.getline(buff, M);
		while (buff[0] == '#') file.getline(buff, M);
		nums = tekeIntsFromChar(buff);
		p.setR(nums[0]);
		p.setG(nums[1]);
		p.setB(nums[2]);
		this->pixels.push_back(p);
	}
	file.close();
}

void PPM::setMaxNumber(size_t maxPixNumber) { this->maxPixNumber = maxPixNumber; }

void PPM::setPixels(const vector<size_t>& matr) {
	Pixel p;
	for (size_t i = 0, j = 0; i < matr.size() / 3; i++, j++) {
		p.setR(matr[j]);
		p.setG(matr[++j]);
		p.setB(matr[++j]);
		this->pixels.push_back(p);
	}
}

void PPM::setFistRows(std::ofstream& file) {
	file << getP() << std::endl
		<< getWidth() << " " << getHeight() << std::endl
		<< maxPixNumber << std::endl;
}

void PPM::printMatr(std::ofstream& file) {
	size_t k = 0;
	for (size_t j = 0; j < getHeight(); j++) {
		for (size_t i = 0; i < getWidth(); i++) {
			file << pixels[k].getR() << " " << pixels[k].getG() << " " << pixels[k].getB() << "   ";
			k++;
		}
		file << std::endl;
	}
}

void PPM::grayscale() {
	for (size_t i = 0; i < pixels.size(); i++) {
		size_t newColor = (pixels[i].getR() * 0.299) + (pixels[i].getG() * 0.587) + (pixels[i].getB() * 0.114);

		pixels[i].setR(newColor);
		pixels[i].setG(newColor);
		pixels[i].setB(newColor);
		//numb[i] = ((pixels[i].r * 30 + pixels[i].g * 59 + pixels[i].b * 11) * 255) / (100 * maxPixNumber);
	}
}

void PPM::monochrome() {
	setMaxNumber(1);
	for (size_t i = 0; i < pixels.size(); i++) {
		if ((pixels[i].getR() + pixels[i].getG() + pixels[i].getB()) != 0) {
			pixels[i].setR(maxPixNumber);
			pixels[i].setG(maxPixNumber);
			pixels[i].setB(maxPixNumber);
		}
	}
}

void PPM::negative() {
	for (size_t i = 0; i < numb.size(); i++) {
		pixels[i].setR(maxPixNumber - pixels[i].getR());
		pixels[i].setG(maxPixNumber - pixels[i].getG());
		pixels[i].setB(maxPixNumber - pixels[i].getB());
	}
}

Image* PPM::clone() const {
	// return new PPM(*this);
	Image* newObj = new PPM(*this);
	return newObj;
}

void PPM::rotateLeft() {
	vector<Pixel> newIm;
	size_t k = 0;
	for (size_t j = 0; j < getWidth(); j++) {
		for (size_t i = 0; i < getHeight(); i++) {
			size_t m = getWidth() - 1 + getWidth() * i - j;
			Pixel p = pixels[m];
			newIm.push_back(p);
			k++;
		}
	}
	for (size_t i = 0; i < getHeight() * getWidth(); i++)
		pixels[i] = newIm[i];
	size_t temp = getWidth();
	setWidth(getHeight());
	setHeight(temp);
}

void PPM::rotateRight() {
	vector<Pixel> newIm;
	size_t k = 0;
	for (size_t j = 0; j < getWidth(); j++) {
		for (size_t i = 0; i < getHeight(); i++) {
			size_t m = getHeight() * getWidth() - getWidth() - getWidth() * i + j;
			Pixel p = pixels[m];
			newIm.push_back(p);
			k++;
		}
	}
	for (size_t i = 0; i < getHeight() * getWidth(); i++)
		pixels[i] = newIm[i];

	size_t temp = getWidth();
	setWidth(getHeight());
	setHeight(temp);
}

