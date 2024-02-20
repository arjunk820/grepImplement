/*
* unit_tests.h
* By: Arjun Kantamsetty
* November 6, 2022
*
* Unit testing for the phaseOne functions of zap.
*/

#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

// tests the unit_test framework for corret compilating and linking
void test_framework()
{

}

// tests if counting and printing frequency of different characters correctly
void test_freqcount()
{
    std::stringstream ss("!!9jf");
    count_freqs(ss);
}

// tests by creating a 4 node Huffman Tree and checking the output
void test_serializetree()
{
    HuffmanTreeNode *root = new HuffmanTreeNode('\0', 0);
    HuffmanTreeNode *c1 = new HuffmanTreeNode('\0', 0);
    HuffmanTreeNode *c2 = new HuffmanTreeNode('b', 0);
    HuffmanTreeNode *c3 = new HuffmanTreeNode('c', 0);
    root->set_left(c1);
    root->set_right(c2);
    c1->set_left(c3);

    std::string test = serialize_tree(root);
    assert(test == "IILcLb");
    delete_tree(root);
}

// tests by calling deserialize and then serialize and then checking output
void test_deserializetree()
{
    std::string test = "ILaLb";
    HuffmanTreeNode *root = deserialize_tree("ILaLb");
    std::string temp = serialize_tree(root);
    delete_tree(root);
    assert(temp == test);
}
