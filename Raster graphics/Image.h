#pragma once
#include <vector>
#include <string>
#include "Transformation.h"
#include <fstream>
#include <iostream>
const size_t M = 70;


class Image {
	string name;
	string P;
	size_t transformationNumber = 0;
	size_t width;
	size_t height;
protected:
	vector <size_t> numb;
public:
	Image() = default;
	Image(const string& name, size_t transformationNumber);
	virtual ~Image() = default;

	const string& getName() const { return name; }
	const string& getP() const { return P; }
	const size_t getTNumber() const { return transformationNumber; }
	const size_t getWidth() const { return width; }
	const size_t getHeight() const { return height; }
	const size_t getNum(size_t i)const { if (numb.size() != 0) return numb[i]; }

	void setTransfNumb(size_t t);
	void setWidth(size_t width);
	void setHeight(size_t height);
	void setName(const string& name);
	void setP(const string& P);
	void setNumb(const vector<size_t>& matr);

	void runTransf(const string& name, const vector<Transformation>& transformations);

	virtual Image* clone() const = 0;
	virtual void setFistRows(std::ofstream& file) = 0;
	virtual void printMatr(std::ofstream& file);
	virtual void grayscale() = 0;
	virtual void monochrome() = 0;
	virtual void negative() = 0;

	void rotate(size_t lORr);
	virtual void rotateRight();
	virtual void rotateLeft();

	const bool isValidNameOfPhoto(const string& name);
	const vector<size_t> tekeIntsFromChar(const char* str);
};

