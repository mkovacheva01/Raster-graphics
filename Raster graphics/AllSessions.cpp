#include "AllSessions.h"


Session* AllSessions::switchS(size_t ID) {
	for (size_t i = 0; i < sessions.size(); i++) {
		if (sessions[i].getID() == ID) {
			cout << "You switched to session with ID: " << ID << endl;
			sessions[i].sessionInfo();
			indexOfCurentSession = sessions[i].getID();
			return &sessions[i];
		}
	}
	std::cout << "A session with such an ID does not exist!";
	return nullptr;
}

void AllSessions::help() {
	std::cout << "The following commands are supported :" << std::endl
		<< "open <file>  -  opens <file>" << std::endl
		<< "close  -  closes currently opened file" << std::endl
		<< "save  -  saves the currently open file" << std::endl
		<< "saveas <file>  -  saves the currently open file in <file>" << std::endl
		<< "help  -  prints this information" << std::endl
		<< "exit  -  exists the program" << std::endl
		<< "info  -  information for curent session" << endl;
}

void AllSessions::open(vector<string> files) {
	Session sess(sessions.size());
	std::cout << "Session with ID : " << sessions.size() << " started" << std::endl;
	sessions.push_back(sess);
	indexOfCurentSession = sess.getID();
	sessions[sessions.size() - 1].load(files);
}

void AllSessions::exit() {
	for (size_t i = 0; i < sessions.size(); i++) {
		if (!sessions[i].IsSave()) {
			std::cout << "Do you want to save all files from session " << i << " ? (type: save / save as / no)" << std::endl;
			string n;
			std::cin >> n;
			if (n == "save") sessions[i].save();
			else if (n == "no") return;
			else if (n == "save as") {
				std::cout << "Write name of file: ";
				std::cin >> n;
				sessions[i].saveAs(n);
			}
		}
	}
}

void AllSessions::close() { return; }

void AllSessions::conzol() {
	string anser;
	if (indexOfCurentSession == 0) {
		cout << "You do not have an open session. Do you want to open a session?";
		cin >> anser;
		if (anser == "Yes" || anser == "yes") {
			vector<string> files;
			cout << "Open file/s (stop - to stop): ";
			while (anser != "stop") {
				cin >> anser;
				if (anser != "stop")
					files.push_back(anser);
			}
			open(files);
		}
		else if (anser == "close") close();
		else help();
	}
	while (anser != "close") {
		cout << "Enter a command";
		cin >> anser;
		if (anser == "open") {
			vector<string> files;
			cout << "Open file/s (stop - to stop): ";
			while (anser != "stop") {
				cin >> anser;
				if (anser != "stop")
					files.push_back(anser);
			}
			open(files);
		}
		else if (anser == "switch") {
			cout << "Enter new session's ID: ";
			size_t id;
			cin >> id;
			switchS(id);
		}
		else if (anser == "help")help();
		else if (anser == "exit")exit();
		else if (anser == "close") {
			if (!sessions[indexOfCurentSession].IsSave()) {
				cout << "Do you want to save this sassion? ";
				cin >> anser;
				if (anser == "Yes" || anser == "yes") sessions[indexOfCurentSession].save();
				else close();
			}
			else close();
		}
		else if (anser == "undo")sessions[indexOfCurentSession].undo();
		else if (anser == "add") {
			cout << "Enter name of image: ";
			cin >> anser;
			vector <string> name;
			name.push_back(anser);
			sessions[indexOfCurentSession].load(name);
		}
		else if (anser == "transformation") {
			cout << "Enter name of transformation: ";
			cin >> anser;

			sessions[indexOfCurentSession].addTransf(anser);
		}
		else if (anser == "info")sessions[indexOfCurentSession].sessionInfo();
		else if (anser == "collage") {
			cout << "Enter derection: ";
			cin >> anser;
			string im1, im2, outim;
			cout << "Enter first image: ";
			cin >> im1;
			cout << "Enter second image: ";
			cin >> im2;
			cout << "Enter out image: ";
			cin >> outim;

			if (im1[im1.size() - 2] == 'p' && im2[im2.size() - 2] == 'p') {
				PPM image1(im1, sessions[indexOfCurentSession].getTransCount());
				PPM image2(im2, sessions[indexOfCurentSession].getTransCount());
				sessions[indexOfCurentSession].collage(anser, image1, image2, outim);
			}
			else if (im1[im1.size() - 2] == 'g' && im2[im2.size() - 2] == 'g') {
				PGM image1(im1, sessions[indexOfCurentSession].getTransCount());
				PGM image2(im2, sessions[indexOfCurentSession].getTransCount());
				sessions[indexOfCurentSession].collage(anser, image1, image2, outim);
			}
			else if (im1[im1.size() - 2] == 'b' && im2[im2.size() - 2] == 'b') {
				PBM image1(im1, sessions[indexOfCurentSession].getTransCount());
				PBM image2(im2, sessions[indexOfCurentSession].getTransCount());
				sessions[indexOfCurentSession].collage(anser, image1, image2, outim);
			}
		}
		else if (anser == "save") sessions[indexOfCurentSession].save();
		else if (anser == "save as") {
			cout << "Enter name of new file: ";
			cin >> anser;
			sessions[indexOfCurentSession].saveAs(anser);
		}
		else close();
	}
	close();
}
