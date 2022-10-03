#pragma once
#include "Image.h"
class PGM :public Image {
	size_t maxPixNumber;

public:
	PGM(const string& name, size_t transformationNumber);
	const size_t getMaxPixNumb()const { return maxPixNumber; }
	void setMaxNumber(size_t max) { maxPixNumber = max; }

	void setFistRows(std::ofstream& file) override;
	void grayscale() override {}
	void monochrome() override;
	void negative() override;
	Image* clone() const override;
};