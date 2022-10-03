#include "Session.h"

void Session::free() {
	for (size_t i = 0; i < imageCount; i++)
		delete images[i];
	delete[] images;
}
void Session::copyFrom(const Session& other) {
	images = new Image * [other.capacity];
	imageCount = other.imageCount;
	capacity = other.capacity;
	ID = other.ID;
	transformations = other.transformations;

	for (size_t i = 0; i < imageCount; i++)
		images[i] = other.images[i]->clone();
}
void Session::resize() {
	Image** newCollection = new Image * [capacity *= 2];
	for (size_t i = 0; i < imageCount; i++)
		newCollection[i] = images[i];
	delete[] images;
	images = newCollection;
}

Session::Session() {
	capacity = 8;
	imageCount = 0;
	images = new Image * [capacity];
}
Session::Session(size_t Id) : Session() {
	ID = Id;
}
Session::Session(const Session& other) { copyFrom(other); }
Session& Session::operator=(const Session& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}
Session::~Session() { free(); }


void Session::load(const vector<string>& names) {
	Image* img;
	for (size_t i = 0; i < names.size(); i++) {
		if (names[i][names[i].size() - 2] == 'p') {
			PPM im(names[i], transformations.size());
			add(*(static_cast<Image*> (&im)));
		}
		else if (names[i][names[i].size() - 2] == 'g') {
			PGM im(names[i], transformations.size());
			add(*(static_cast<Image*> (&im)));
		}
		else if (names[i][names[i].size() - 2] == 'b') {
			PBM im(names[i], transformations.size());
			add(*(static_cast<Image*> (&im)));
		}
		std::cout << "Image " << names[i] << " added" << std::endl;
	}
}

void Session::save(int i) {
	if (i != 0) i = 1;

	for (; i < imageCount; i++)
		images[i]->runTransf(images[i]->getName(), transformations);
	isSaved = true;
}
void Session::saveAs(const string& name) {
	images[1]->runTransf(name, transformations);
	save(1);
}


void Session::undo() {
	transformations.pop_back();
}

void Session::add(const Image& im) {
	if (imageCount == capacity)
		resize();
	//if(im != nullptr)
	images[imageCount++] = im.clone();
}

void Session::addTransf(const string& namet) {
	Transformation t;
	size_t num = transformations.size() + 1;
	if (namet == "rotate") {
		string lORr;
		std::cin >> lORr;
		if (lORr == "right") t = { namet, num, 1 };
		else if (lORr == "left") t = { namet, num, 2 };
	}
	else t = { namet, num, 0 };
	transformations.push_back(t);
}


void Session::sessionInfo()const {
	std::cout << "Number of this session is: " << ID << std::endl
		<< "Name of images in the session: ";
	for (size_t i = 0; i < imageCount; i++) {
		std::cout << images[i]->getName() << ", ";
	}
	std::cout << std::endl << "Pending transformations: ";
	for (size_t i = 0; i < transformations.size(); i++) {
		std::cout << transformations[i].getNumber() << ", ";
	}
	std::cout << std::endl;
}

void Session::collage(const string& direction, const Image& image1, const Image& image2, const string& outimage) {
	if (!(image1.getP() == image2.getP())) {
		std::cout << " Cannot make a collage from different types!\n ";
		return;
	}
	if (image1.getWidth() != image2.getWidth() || image1.getHeight() != image2.getHeight()) {
		std::cout << " Cannot make a collage from different sizes!\n ";
		return;
	}
	size_t transformationNumber = transformations.size();
	if (direction == "horizontal") {
		size_t height = image1.getHeight() + image2.getHeight();
		size_t width = image1.getWidth();
		createFile(outimage, image1, image2, height, width, transformationNumber);
	}
	else if (direction == "vertical") {
		size_t height = image1.getHeight();
		size_t width = image1.getWidth() + image2.getWidth();
		createFile(outimage, image1, image2, height, width, transformationNumber);
	}
}

void Session::createFile(const string& name, const Image& image1, const Image& image2, size_t newW, size_t newH, size_t transformationNumber) {
	size_t pix = image1.getWidth() * image1.getHeight() + image2.getWidth() * image2.getHeight();
	ofstream file(name.c_str(), ios::trunc);

	if (!file.is_open()) {
		std::cout << "Error while opening file!" << std::endl;
		return;
	}

	size_t width = image1.getWidth();
	file << image1.getP() << std::endl << newW << " " << newH << std::endl;
	Image* im1 = const_cast<Image*>(&image1);

	if (image1.getP() == "P3") {
		PPM* d1 = static_cast<PPM*>(im1);
		file << d1->getMaxPixNumb() << std::endl;
		Image* i2 = const_cast<Image*>(&image2);
		PPM* d2 = static_cast<PPM*>(i2);

		for (size_t i = 0; i < pix; i++) {
			for (size_t g = 0; g < width; g++)
				file << d1->getPix(g).getR() << " " << d1->getPix(g).getG() << " " << d1->getPix(g).getB() << " ";
			for (size_t g = 0; g < width; g++)
				file << d2->getPix(g).getR() << " " << d2->getPix(g).getG() << " " << d2->getPix(g).getB() << " ";
			file << endl;
			pix -= 2 * width;
		}
	}
	else if (image1.getP() == "P2") {
		PGM* d = static_cast<PGM*>(im1);
		file << d->getMaxPixNumb() << std::endl;
	}
	if (!(image1.getP() == "P3")) {
		for (size_t i = 0; i < pix; i++) {
			for (size_t g = 0; g < width; g++)
				file << image1.getNum(i);

			for (size_t g = 0; g < width; g++)
				file << image2.getNum(i);
			file << endl;
			pix -= 2 * width;
		}
	}
	file.close();
	//add(*read(name, transformationNumber));
}