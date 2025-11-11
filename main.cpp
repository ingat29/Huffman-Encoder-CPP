#include <filesystem>
#include <fstream>
#include <iostream>
#include "Utils.h"
#include "Node.h"
#include "PriorityQueue.h"
#include "Header.h"


int main(/*int argc, char *argv[]*/) {
    std::string inputFileName;
    std::string outputFileName;
    std::string inputOption;
    bool hasBeenExecuted = false;
    std::cout <<"Type '-h' for help" <<std::endl;
    while (inputOption != "-q") {
        std::cout << "Enter command : ";
        std::cin >> inputOption;
        if (inputOption == "-h") {
            std::cout <<"-i : Specify the input file to encode using Huffman coding" <<std::endl;
            std::cout <<"-o : Specify the output file to write the comprfessed input to " <<std::endl;
            std::cout <<"-s : Prints compression statistics. These statistics include the uncompressed file size, the compressed file size, and space saving" << std::endl;
            std::cout <<"-e : Execute the huffman encoding - requires both input and output"<<std::endl;
            std::cout <<"-q : Quit" <<std::endl;
        }
        else if (inputOption == "-i") {
            if (!hasBeenExecuted) {
                std::cout << "Write the name of the input file : "<<std::endl;
                std::cin >> inputFileName;
            }
            else {
                std::cout << "You have already executed the program once" << std::endl;
            }
        }
        else if (inputOption == "-o") {
            if (!hasBeenExecuted) {
                std::cout << "Write the name of the output file (should be a '.bin' file) : "<<std::endl;
                std::cin>> outputFileName;
            }
            else {
                std::cout << "You have already executed the program once" << std::endl;
            }
        }
        else if (inputOption == "-s") {
            if (hasBeenExecuted) {
                Utils::PrintCompressionStats(inputFileName, outputFileName);
            }
            else {
                std::cout << "You have not executed the program-" << std::endl;
            }
        }
        else if(inputOption == "-e" && (inputFileName !="" && outputFileName !="")) {
            std::string text = Utils::ReadFile(inputFileName);
            if (text.empty()){
                std::cerr<<"File is empty"<<std::endl;
                return 1;
            }
            uint64_t C[256] = {0};
            Utils::ComputeHistogram(text, C);
            C[0]++;
            C[255]++;
            PriorityQueue prioQ;
            for (int i = 0; i < 256; i++) {
                if (C[i] > 0) {
                    Node tempNode = {C[i] , static_cast<uint8_t>(i) ,nullptr,nullptr};
                    prioQ.Enqueue(tempNode);
                }
            }
            Node* root = prioQ.ComputeHuffmanTree() ;
            BitPath bitPathTable[256];BitPath currentPath;
            Utils::ConstructPathTable(root , bitPathTable , currentPath);
            Header header = {inputFileName, bitPathTable};
            std::ofstream outFile(outputFileName, std::ios::binary);
            std::ifstream inFile(inputFileName , std::ios::binary);
            header.WriteHeader(outFile);
            Utils::WriteTreeToBinFile(root, outFile);
            Utils::WriteEncodedFile(inFile , outFile, bitPathTable);
            inFile.close();
            outFile.close();
            hasBeenExecuted = true;
            std::cout<<"Executed huffman encoding" << std::endl;
        }
    }
    return 0;
}
//command line