/*
* phaseOne.h
* By: Arjun Kantamsetty
* November 6, 2022
*
* Declarations of the phaseOne functions.
*/

#ifndef __PHASEONE_H__
#define __PHASEONE_H__

#include <iostream>
#include "HuffmanTreeNode.h"

void count_freqs(std::istream &text);
std::string serialize_tree(HuffmanTreeNode *root);
HuffmanTreeNode *deserialize_tree(std::string serial_tree);
HuffmanTreeNode *deserialize_helper(std::stringstream *ss);
void delete_tree(HuffmanTreeNode *root);

#endif