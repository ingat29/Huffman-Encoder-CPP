#ifndef UTILS_H
#define UTILS_H
#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Node.h"
#include "BitPath.h"
#include <filesystem>
#include <stack>

class Utils {
public:
    static void ComputeHistogram(std::string text = "" , uint64_t * C = nullptr);
    static std::string ReadFile(const std::string& filename);
    static BitPath* ConstructPathTable(Node* root, BitPath* pathTable , BitPath& currentPath);
    static void WriteTreeToBinFile(Node* root, std::ostream& out);
    static void WriteEncodedFile(std::istream& inFile, std::ostream& outFile, const BitPath table[256]);
    static void PrintCompressionStats(const std::string& inputPath, const std::string& outputPath);
    static Node* ReadHeader(std::string inputFileName , uintmax_t* fileSize);//Decoder
    static void ReadEncodedFile(std::string inFileName, std::string outFileName,Node* root,uintmax_t& fileSize);

};
#endif //UTILS_H
