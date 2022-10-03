#pragma once
#include "Image.h"

class PBM :public Image {
public:
	PBM(const string& name, size_t transformationNumber);

	void setFistRows(std::ofstream& file) override;
	void grayscale() override {}
	void monochrome() override {}
	void negative() override;
	Image* clone() const override;
};

