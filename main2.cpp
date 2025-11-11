#include <filesystem>
#include <fstream>
#include <iostream>
#include "Utils.h"
#include "Node.h"
#include "PriorityQueue.h"
#include "Header.h"


int main() {
    std::string inputFileName;
    std::string outputFileName;
    std::string inputOption;
    bool hasBeenExecuted = false;
    std::cout <<"Type '-h' for help" <<std::endl;
    while (inputOption != "-q") {
        std::cout << "Enter command : ";
        std::cin >> inputOption;
        if (inputOption == "-h") {
            std::cout <<"-i : Specify the input file to encode using Huffman decoding" <<std::endl;
            std::cout <<"-o : Specify the output file to write the decompressed input to " <<std::endl;
            std::cout <<"-s : Prints decompression statistics. These statistics include the uncompressed file size, the compressed file size, and space saving" << std::endl;
            std::cout <<"-e : Execute the huffman decoding - requires both input and output"<<std::endl;
            std::cout <<"-q : Quit" <<std::endl;
        }
        else if (inputOption == "-i") {
            if (!hasBeenExecuted) {
                std::cout << "Write the name of the input file (should be a '.bin' file): "<<std::endl;
                std::cin >> inputFileName;
            }
            else {
                std::cout << "You have already executed the program once" << std::endl;
            }
        }
        else if (inputOption == "-o") {
            if (!hasBeenExecuted) {
                std::cout << "Write the name of the output file : "<<std::endl;
                std::cin>> outputFileName;
            }
            else {
                std::cout << "You have already executed the program once" << std::endl;
            }
        }
        else if (inputOption == "-s") {
            if (hasBeenExecuted) {
                Utils::PrintCompressionStats(outputFileName, inputFileName);
            }
            else {
                std::cout << "You have not executed the program-" << std::endl;
            }
        }
        else if(inputOption == "-e" && (inputFileName !="" && outputFileName !="")) {
            uintmax_t* fileSize;
            Node* root = Utils::ReadHeader(inputFileName,fileSize);
            Utils::ReadEncodedFile(inputFileName,outputFileName, root , *fileSize);
            hasBeenExecuted = true;
            std::cout<<"Executed huffman decoding" << std::endl;
        }
    }
    return 0;
}