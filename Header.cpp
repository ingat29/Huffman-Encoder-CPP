#include "Header.h"

Header::Header(const std::string& infileName, BitPath *bitPathArray) {
	this->signature = MAGIC;
	this->fileSize = std::filesystem::file_size(infileName);
	int counter = 0;
	for (int i =0 ; i < 256 ; i++) {
		if ((bitPathArray+i)->GetLength() != 0) counter++;
	}
	this->treeSize = (counter*3) - 1;
}

void Header::WriteHeader(std::ofstream& out) const {
	out.write(reinterpret_cast<const char*>(&signature), sizeof(signature));
	out.write(reinterpret_cast<const char*>(&treeSize), sizeof(treeSize));
	out.write(reinterpret_cast<const char*>(&fileSize), sizeof(fileSize));
}


