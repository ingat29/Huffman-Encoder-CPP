#include "Utils.h"

#include "Header.h"

void Utils::ComputeHistogram(std::string text, uint64_t* C) {//C has to be a double[256]={0} array
    for (int i = 0 ; i < 256 ; i++) {
        uint8_t symbol = 0 + static_cast<uint8_t>(i);
        int nrOfAppearence = 0;
        for (int j = 0 ; j < text.length() ; j++) {
            if (text[j] == symbol) {
                nrOfAppearence++;
            }
        }
        if (nrOfAppearence > 0) *(C +i) = nrOfAppearence;
    }
}


std::string Utils::ReadFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary); // Read in binary mode
    return std::string{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
}

BitPath* Utils::ConstructPathTable(Node* root, BitPath* pathTable, BitPath& currentPath) {
    if (root == nullptr) return pathTable;  // Base case

    // Recur left first
    currentPath.PushBit(false);
    Utils::ConstructPathTable(root->left, pathTable, currentPath);
    currentPath.PopBit();

    // Then recur right
    currentPath.PushBit(true);
    Utils::ConstructPathTable(root->right, pathTable, currentPath);
    currentPath.PopBit();

    // Process node only after both children are visited
    if (root->left == nullptr && root->right == nullptr) {
        *(pathTable + static_cast<int>(root->symbol)) = currentPath;
    }

    return pathTable;
}

void Utils::WriteTreeToBinFile(Node *root, std::ostream &out){
    if (!root) return;

    // Post-order traversal: left, right, node
    WriteTreeToBinFile(root->left, out);
    WriteTreeToBinFile(root->right, out);

    if (!root->left && !root->right) {
        // Leaf node
        out.put('L'); // Write 'L' as a byte
        out.put(static_cast<char>(root->symbol)); // Write symbol as a byte
    } else {
        // Internal node
        out.put('I'); // Write 'I' as a byte
    }
}

void Utils::WriteEncodedFile(std::istream& inFile, std::ostream& outFile, const BitPath table[256]) {
    uint8_t bitBuffer = 0;
    uint8_t bitCount = 0;

    char ch;
    while (inFile.get(ch)) {
        const BitPath& path = table[static_cast<uint8_t>(ch)];

        for (int i = 0; i < path.GetLength(); ++i) {
            bool bit = path.bits[i];

            // shift left, then OR the new bit into LSB
            bitBuffer <<= 1;
            bitBuffer |= bit;
            bitCount++;

            // Flush full byte
            if (bitCount == 8) {
                outFile.put(static_cast<char>(bitBuffer));
                bitBuffer = 0;
                bitCount = 0;
            }
        }
    }

    // Flush last partially filled byte (pad with zeros)
    if (bitCount > 0) {
        bitBuffer <<= (8 - bitCount); // shift remaining bits to MSB
        outFile.put(static_cast<char>(bitBuffer));
    }
}

void Utils::PrintCompressionStats(const std::string& inputPath, const std::string& outputPath) {
    namespace fs = std::filesystem;

    if (!fs::exists(inputPath) || !fs::exists(outputPath)) {
        std::cerr << "Error: One or both files do not exist.\n";
        return;
    }

    auto uncompressedSize = fs::file_size(inputPath);
    auto compressedSize = fs::file_size(outputPath);

    std::cout << "Uncompressed size: " << uncompressedSize << " bytes\n";
    std::cout << "Compressed size: " << compressedSize << " bytes\n";

    if (uncompressedSize == 0) {
        std::cout << "Cannot calculate space saving: uncompressed file is empty.\n";
        return;
    }

    double saving = 100.0 * (1.0 - static_cast<double>(compressedSize) / uncompressedSize);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Space saving: " << saving << "%\n";
}

Node* Utils::ReadHeader(std::string inputFileName ,uintmax_t* fileSize ) {
    std::ifstream input(inputFileName , std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "Error opening file " << inputFileName << std::endl;
        return nullptr;
    }
    uint32_t signature;
    input.read(reinterpret_cast<char*>(&signature), sizeof(signature));
    if (signature != MAGIC) {
        std::cerr << "Error opening file : " << inputFileName << "Not an identifiable file , misses header."<<std::endl;
    }

    uint16_t treeSize;
    std::stack<Node*> NodeStack;
    input.read(reinterpret_cast<char*>(&treeSize), sizeof(treeSize));
    input.read(reinterpret_cast<char*>(fileSize), sizeof(fileSize));
    uint8_t treeDump[treeSize];
    input.read(reinterpret_cast<char*>(treeDump), sizeof(treeDump));
    for (int i = 0; i < treeSize; i++) {
        if (static_cast<unsigned char>(treeDump[i]) == 'L') {
            Node* tempNode =new Node{0,treeDump[++i],nullptr,nullptr};
            NodeStack.push(tempNode);
        }
        else if (static_cast<unsigned char>(treeDump[i]) == 'I') {
            Node* right = NodeStack.top();
            NodeStack.pop();
            Node* left = NodeStack.top();
            NodeStack.pop();
            Node* interiorNode =new Node {0,'\0',left,right};
            NodeStack.push(interiorNode);
        }
    }
    input.close();
    Node* root = NodeStack.top();
    return root;
}
void Utils::ReadEncodedFile(std::string inFileName, std::string outFileName , Node* root ,uintmax_t& fileSize) {
    std::ifstream input(inFileName , std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "Error opening file " << inFileName << std::endl;
    }
    uint32_t signature1;
    uint16_t treeSize1;
    uintmax_t fileSize1;
    input.read(reinterpret_cast<char*>(&signature1), sizeof(signature1));
    input.read(reinterpret_cast<char*>(&treeSize1), sizeof(treeSize1));
    input.read(reinterpret_cast<char*>(&fileSize1), sizeof(fileSize1));
    uint8_t treeDump1[treeSize1];
    input.read(reinterpret_cast<char*>(treeDump1), sizeof(treeDump1));

    uint16_t treeSize;
    std::ofstream output(outFileName);
    uint8_t bitBuffer;
    Node* currentNode = root;
    uintmax_t currentFileSize = 0;
    while (currentFileSize < fileSize && input) {
        input.read(reinterpret_cast<char*>(&bitBuffer), sizeof(bitBuffer));
        for (int i = 7; i >= 0; i--) {
            bool bit = (bitBuffer >> i) & 1;
            if (currentNode != nullptr) {
                if (bit == true) {
                    currentNode = currentNode->right;
                    if (currentNode != nullptr && (currentNode->left == nullptr && currentNode->right == nullptr)) {//is a leaf
                        output.put(static_cast<unsigned char>(currentNode->symbol));
                        currentNode = root;
                        currentFileSize++;
                    }
                }
                else if (bit == false) {
                    currentNode = currentNode->left;
                    if (currentNode != nullptr && (currentNode->left == nullptr && currentNode->right == nullptr)) {//is a leaf
                        output.put(static_cast<unsigned char>(currentNode->symbol));
                        currentNode = root;
                        currentFileSize++;
                    }
                }
            }

        }
    }
    input.close();
    output.close();
}
