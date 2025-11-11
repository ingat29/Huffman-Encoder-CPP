#ifndef HEADER_H
#define HEADER_H
#define MAGIC 0xDEADEAEF // 32-bit magic number.
#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>
#include "BitPath.h"
#include "Node.h"
#include <stack>

class Header {
private:
	uint32_t signature = MAGIC;//4 bytes
	uint16_t treeSize;//2 bytes
	std::uintmax_t fileSize; //8 bytes
public:
	Header(const std::string& infileName , BitPath* bitPathArray);//path to the original infile so we can get the size//bitPath array of 256 elements
	void WriteHeader(std::ofstream &out)const;
};

#endif //HEADER_H
//love scheme scorpion grocery valley wet prize spare joke boost drum quarter