#include "Image.h"
void Image::setTransfNumb(size_t t) { transformationNumber = t; }
void Image::setWidth(size_t width) { this->width = width; }
void Image::setHeight(size_t height) { this->height = height; }
void Image::setName(const string& name) { this->name = name; }
void Image::setP(const string& P) { this->P = P; }
void Image::setNumb(const vector<size_t>& matr) {
	for (size_t i = 0; i < matr.size(); i++)
		numb.push_back(matr[i]);
}

Image::Image(const string& name, size_t transformationNumber) {
	setName(name);
	setTransfNumb(transformationNumber);
	setNumb(vector<size_t>());
}

void Image::runTransf(const string& name, const vector<Transformation>& transformations) {
	std::ofstream file(name.c_str(), std::ios::trunc);
	if (!file.is_open()) {
		cout << "Error while opening file!" << std::endl;
		return;
	}

	string command;
	for (size_t i = transformationNumber; i < transformations.size(); i++) {
		command = transformations[i].getName();
		size_t lorr = transformations[i].getleftORright();
		if (command == "grayscale") grayscale();
		else if (command == "monochrome") monochrome();
		else if (command == "negative") negative();
		else if (command == "rotate") rotate(lorr);
	}

	setFistRows(file);
	printMatr(file);
	file.close();
}

void Image::printMatr(std::ofstream& file) {
	size_t k = 0;
	for (size_t j = 0; j < height; j++) {
		for (size_t i = 0; i < width; i++) {
			file << numb[k] << " ";
			k++;
		}
		file << std::endl;
	}
}

void Image::rotateLeft() {
	vector<size_t> newIm;
	size_t k = 0;
	for (size_t j = 0; j < getWidth(); j++) {
		for (size_t i = 0; i < getHeight(); i++) {
			size_t m = getWidth() - 1 + getWidth() * i - j;
			newIm.push_back(numb[m]);
			k++;
		}
	}
	for (size_t i = 0; i < getHeight() * getWidth(); i++)
		numb[i] = newIm[i];
	size_t temp = getWidth();
	setWidth(getHeight());
	setHeight(temp);
}

void Image::rotateRight() {
	vector<size_t> newIm;
	size_t k = 0;
	for (size_t j = 0; j < getWidth(); j++) {
		for (size_t i = 0; i < getHeight(); i++) {
			size_t m = getHeight() * getWidth() - getWidth() - getWidth() * i + j;
			newIm.push_back(numb[m]);
			k++;
		}
	}
	for (size_t i = 0; i < getHeight() * getWidth(); i++)
		numb[i] = newIm[i];

	size_t temp = getWidth();
	setWidth(getHeight());
	setHeight(temp);
}

void Image::rotate(size_t lORr) {
	if (lORr == 1)rotateRight();
	else if (lORr == 2)rotateLeft();
}


const char* getTail(const string& name) {
	size_t lengthstr = name.size();

	size_t i = lengthstr;
	while (name[i] != '.') i--;

	char* tail = new char[lengthstr - i];
	for (size_t j = 0; i < lengthstr; i++, j++)tail[j] = name[i + 1];

	return tail;
}

const bool Image::isValidNameOfPhoto(const string& name) {
	string tail{ getTail(name) };
	return ((tail == "pgm") || (tail == "ppm") || (tail == "pbm"));
}

const vector<size_t> Image::tekeIntsFromChar(const char* str) {
	size_t first = 0;
	size_t len = strlen(str);
	vector<size_t> nums;
	for (size_t i = 0; i < len; i++) {
		if (str[i + 1] == '#') break;
		else if (!(str[i + 1] >= '0' && str[i + 1] <= '9')) {
			first = first * 10 + str[i] - 48;
			nums.push_back(first);
			first = 0;
		}
		else if (str[i] >= '0' && str[i] <= '9')
			first = first * 10 + str[i] - 48;
	}
	return nums;
}