/*
* HuffmanCoder.h
* By: Arjun Kantamsetty
* November 13, 2022
*
* Below are the declarations of the functions of the HuffmanCoder class which
* either run compression or decompression or help with specific functionality
* for compression and decompression. Also included are the data structures used
* to store information read in and manipulated in the .cpp file. Read on if 
* interested in the HuffmanCoder class and compression/decompression 
* functionality.
*/

#ifndef __HUFFMANCODER_H__
#define __HUFFMANCODER_H__

#include "BinaryIO.h"
#include "HuffmanTreeNode.h"
#include <queue>
#include <vector>
#include <istream>
#include <map>

class HuffmanCoder {

public:
    HuffmanCoder();
    void encoder(std::string input_file, std::string output_file);
    void decoder(std::string input_file, std::string output_file);

private:
    void open_or_die(std::fstream &stream, std::string fileInput);
    void count_freqs(std::istream &text); // change to priv later
    void buildHuffmanTree(); // change to priv later
    void create_codes(HuffmanTreeNode *root, std::string code); // priv
    std::string convert_chars(std::fstream &inStream);
    std::string serialize_tree(HuffmanTreeNode *root);
    std::priority_queue<HuffmanTreeNode*,std::vector<HuffmanTreeNode*>, 
        NodeComparator>my_pq; // change to priv later
    std::vector<std::string> char_codes; // for encoder
    std::vector<std::string> real_values; // for decoder
    std::string revert(std::string bitString, HuffmanTreeNode *root);
    void delete_tree(HuffmanTreeNode *root);
    HuffmanTreeNode *deserialize_tree(std::string serial_tree);
    HuffmanTreeNode *deserialize_helper(std::stringstream *ss);
    void print_tree(HuffmanTreeNode *root);
    int char_counts[256];
    void open_or_die_writemode(std::ofstream &stream, std::string fileInput);
};

#endif
