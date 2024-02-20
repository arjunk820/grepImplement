/*
* zap.cpp
* Arjun Kantamsetty
* November 13, 2022
*
* Driver of the HuffmanCoder.cpp class. Checks the command line to ensure
* correct usage and calls specified function. Prints out to error output if 
* command line is incorrect.
*/

#include <iostream>
#include "HuffmanTreeNode.h"
#include "HuffmanCoder.h"
#include "BinaryIO.h"

int main(int argc, char *argv[]) {
    HuffmanCoder compressAlgo;
    if (argc > 1) {
        std::string cmd = argv[1];
        if ((argc != 4) or ((cmd != "zap") and (cmd != "unzap"))) {
            std::cerr << "Usage: ./zap [zap | unzap] inputFile outputFile"
                << std::endl;
            exit(EXIT_FAILURE);
        }
        if (cmd == "zap") {
            compressAlgo.encoder(argv[2], argv[3]);
        } else if (cmd == "unzap") {
            compressAlgo.decoder(argv[2], argv[3]);
        }
    } else {
        std::cerr << "Usage: ./zap [zap | unzap] inputFile outputFile"
             << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}