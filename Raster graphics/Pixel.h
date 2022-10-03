#pragma once
class Pixel {
	size_t r;
	size_t g;
	size_t b;

public:
	Pixel& operator= (Pixel& p) {
		setR(p.getR());
		setG(p.getG());
		setB(p.getB());
		return *this;
	}
	void setR(size_t m) { r = m; }
	void setG(size_t m) { g = m; }
	void setB(size_t m) { b = m; }
	size_t getR() const { return r; }
	size_t getG() const { return g; }
	size_t getB() const { return b; }
};