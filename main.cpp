#include <iostream>
#include <thread>
#include <fstream>
#include <windows.h>
#include <string>
HANDLE rSemaphore = NULL;
HANDLE wSemaphore = NULL;



void readf() {
	while (true) {

		WaitForSingleObject(rSemaphore, INFINITE);
		std::string line;
		std::ifstream in("C:\\Users\\vbifn\\source\\repos\\зрђ\\зрђ\\file.txt");
		std::getline(in, line);
		if (line != "") {
			std::cout << "chat1: " << line << std::endl;
		}
		in.clear();
		in.close();
		ReleaseSemaphore(rSemaphore, 1, NULL);
	}

}

void writef() {
	while (true) {
		WaitForSingleObject(wSemaphore, INFINITE);
		std::string line;
		std::ofstream in("C:\\Users\\vbifn\\source\\repos\\зрђ\\зрђ\\file.txt");
		std::getline(std::cin, line);
		in << line << std::endl;
		in.close();
		ReleaseSemaphore(wSemaphore, 1, NULL);
	}
}



void main() {
	wSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"readSemaphore");
	rSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"writeMySemaphore");

	std::thread Thread1(readf);
	std::thread Thread2(writef);

	Thread1.join();
	Thread2.join();

	std::cout << "hui";
}