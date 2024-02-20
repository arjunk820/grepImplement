/*
* phaseOne.cpp
* By: Arjun Kantamsetty
* November 6, 2022
*
* Definitions of the phaseOne functions.
*/

#include <iostream>
#include <sstream>
#include <vector>
#include "HuffmanTreeNode.h"
#include "phaseOne.h"

/*
 * name:      count_freqs()
 * purpose:   count frequency of characters in istream
 * arguments: input stream
 * returns:   none
 * effects:   prints out the frequency
 */
void count_freqs(std::istream &text)
{
    std::vector<int> char_counts(256); // represents freq of each ASCII val
    for (int i = 0; i < 256; i++) // sets vector to 0 at each index
    {
        char_counts[i] = 0;
    }

    char a = '0';
    while (text.get(a)) { // increments frequency at specified index
        char_counts[a]++;
    }
    
    for (int j = 0; j < 256; j++) {
        if (char_counts[j] > 0) { // prints out char and freq if more than 0
            std::cout << char(j) << ": " << char_counts[j] << std::endl;
        }
    }
}

/*
 * name:      serialize_tree()
 * purpose:   convert tree to string form
 * arguments: root of the Huffman Tree
 * returns:   string form of Huffman Tree
 * effects:   none
 */
std::string serialize_tree(HuffmanTreeNode *root)
{
    std::string result = "";
    if (root == nullptr) { // base case
        return result;
    } else if (root->isLeaf()) { // leaf case
        result = result + "L" + root->get_val();
    } else { // pre-order traversal recursive (internode) case
        result = result + "I" + serialize_tree(root->get_left()) 
            + serialize_tree(root->get_right());
    }
    return result;
}

/*
 * name:      deserialize_tree()
 * purpose:   create a Huffman Tree
 * arguments: string form of the Huffman Tree
 * returns:   root of the Huffman Tree
 * effects:   calls deserialize_helper()
 */
HuffmanTreeNode *deserialize_tree(std::string serial_tree)
{
    std::stringstream ss(serial_tree);
    HuffmanTreeNode *result = deserialize_helper(&ss); // calls helper
    return result;
}

/*
 * name:      deserialize_helper()
 * purpose:   create a Huffman Tree
 * arguments: stringstream of the Huffman string
 * returns:   root of the Huffman Tree
 * effects:   creates the Huffman Tree nodes
 */
HuffmanTreeNode *deserialize_helper(std::stringstream *ss)
{
    HuffmanTreeNode *result = nullptr;
    char a = '0';
    ss->get(a);
    if (a == 'L') { // leaf case
        char b = '0';
        ss->get(b);
        result = new HuffmanTreeNode(b, 0);
    } else if (a == 'I') { // internode case
       result = new HuffmanTreeNode('\0', 0);
       result->set_left(deserialize_helper(ss)); // calls helper on left
       result->set_right(deserialize_helper(ss)); // calls helper on right
    }
    return result;
}

/*
 * name:      delete_tree()
 * purpose:   deallocates memory taken by the created nodes
 * arguments: root of the Huffman Tree
 * returns:   none
 * effects:   deletes the Huffman Tree
 */
void delete_tree(HuffmanTreeNode *root)
{
    if (root == nullptr) { // base case
        return;
    } else if (root->isLeaf()) { // one node case
        delete root;
    } else { // post-order traversal recursive case
        delete_tree(root->get_left()); 
        delete_tree(root->get_right());
        delete root;
    }
}