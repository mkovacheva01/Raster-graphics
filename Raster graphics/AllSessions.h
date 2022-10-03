#pragma once
#include "Session.h"

class AllSessions {
	vector<Session> sessions;
	size_t indexOfCurentSession = 0;
public:
	Session* switchS(size_t ID);
	void help();
	void open(vector<string> files);
	void exit();
	void close();
	void conzol();
};

