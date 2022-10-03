#pragma once
#include "Image.h"
#include "Pixel.h"

class PPM :public Image {
	size_t maxPixNumber;
	vector<Pixel> pixels;

public:
	PPM() = default;
	PPM(const string& name, size_t transformationNumber);

	void setMaxNumber(size_t maxPixNumber);
	void setPixels(const vector<size_t>& pixels);
	const size_t getMaxPixNumb()const { return maxPixNumber; }
	const Pixel getPix(size_t i)const { return pixels[i]; }

	void setFistRows(std::ofstream& file) override;
	void printMatr(std::ofstream& file) override;
	void grayscale() override;
	void monochrome() override;
	void negative() override;
	Image* clone() const override;

	void rotateRight() override;
	void rotateLeft() override;
};

