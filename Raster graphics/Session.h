#pragma once
#include "Image.h"
#include "PPM.h"
#include "PGM.h"
#include "PBM.h"

class Session {
	Image** images;
	vector <Transformation> transformations;
	size_t ID;
	size_t imageCount;
	size_t capacity;
	bool isSaved = false;

	void free();
	void copyFrom(const Session& other);
	void resize();

	void createFile(const string& name, const Image& image1, const Image& image2, size_t newW, size_t newL, size_t transformationNumber);
public:
	Session();
	Session(size_t Id);
	Session(const Session& other);
	Session& operator=(const Session& other);
	~Session();

	size_t getID()const { return ID; }
	size_t getTransCount()const { return transformations.size(); }
	bool IsSave()const { return isSaved; }

	void load(const vector<string>& names);
	void save(int i = 0);
	void saveAs(const string& name);

	void undo();
	void add(const Image& im);
	void addTransf(const string& t);
	void sessionInfo()const;
	void collage(const string& direction, const Image& image1, const Image& image2, const string& outimage);
};