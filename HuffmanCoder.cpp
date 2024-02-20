/*
* HuffmanCoder.cpp
* By: Arjun Kantamsetty
* November 13, 2022
* 
* HuffmanCoder.cpp has functions which are designed to allow one to compress
* (zap) and decompress (unzap) any text file. Notable functions include
* encoder() and decoder() which are responsible for compression and 
* decompression respectively. This class is best for someone who wants to
* compress a file to create more space for more files.
*/

#include "HuffmanCoder.h"
#include "HuffmanTreeNode.h"
#include "BinaryIO.h"
#include <queue>
#include <vector>
#include <istream>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

/*
 * name:      HuffmanCoder()
 * purpose:   instantiates object of class and initializes priv member vars
 * arguments: none
 * returns:   none
 * effects:   places null char value in every spot of char_codes vector
 */
HuffmanCoder::HuffmanCoder()
{
    for (int i = 0; i < 256; i++) // sets vectors to null at each index
    {
        char_codes.push_back("\0");
        real_values.push_back("\0");
    }
}

/*
 * name:      open_or_die()
 * purpose:   opens input_file and exits if file can't open
 * arguments: file stream obj and string obj holding name of file
 * returns:   none
 * effects:   opens the input file, allows for class to read in chars.
 */
void HuffmanCoder::open_or_die(std::fstream &stream, std::string fileInput)
{
    stream.open(fileInput);
    if (not stream.is_open())
    {
        std::cerr << "Unable to open file " << fileInput; // error output
        exit(EXIT_FAILURE);
    }
}

/*
 * name:      open_or_die_writemode()
 * purpose:   opens input_file and exits if file can't open
 * arguments: file stream obj and string obj holding name of file
 * returns:   none
 * effects:   opens the input file, allows for class to write to a file.
 */
void HuffmanCoder::open_or_die_writemode(std::ofstream &stream, 
    std::string fileInput)
{
    stream.open(fileInput);
    if (not stream.is_open())
    {
        std::cerr << "Unable to open file " << fileInput; // error output
        exit(EXIT_FAILURE);
    }
}

/*
 * name:      encoder()
 * purpose:   encodes the file into a string of bits.
 * arguments: string objs holding the names of the input and output files
 * returns:   none
 * effects:   calls functions to encode the given input file and save it to 
 *            output.
 */
void HuffmanCoder::encoder(std::string input_file, std::string output_file)
{
    std::fstream inStream;
    open_or_die(inStream, input_file);
    count_freqs(inStream);
    buildHuffmanTree();
    create_codes(my_pq.top(), "");
    inStream.clear();
    inStream.seekg(0); // sets back to start of file
    std::string bitString = convert_chars(inStream);
    std::string serial = serialize_tree(my_pq.top());
    BinaryIO encoding;
    encoding.writeFile(output_file, serial, bitString);
    std::cout << "Success! Encoded given text using " << bitString.size() <<
        " bits." << std::endl;
    delete_tree(my_pq.top()); // recycles nodes on heap
    inStream.close(); // done with inStream here
}

/*
 * name:      count_freqs()
 * purpose:   count frequency of characters in istream
 * arguments: input stream
 * returns:   none
 * effects:   prints out the frequency
 */
void HuffmanCoder::count_freqs(std::istream &text)
{
    for (int i = 0; i < 256; i++) // sets vector to 0 at each index
    {
        char_counts[i] = 0;
    }

    char a = '\0';
    while (text.get(a)) { // increments frequency at specified index
        char_counts[(unsigned char) a]++;
    }
}

/*
 * name:      buildHuffmanTree()
 * purpose:   creates leaf nodes, adds to priority queue, and keeps adding
 *            to priority queue until only 1 node is left.
 * arguments: none
 * returns:   none
 * effects:   gets the root node of the newly built Huffman tree
 */
void HuffmanCoder::buildHuffmanTree()
{
    // for each non zero freq, create a leaf and add to priority queue
    for (int i = 0; i < 256; i++)
    {
        if (char_counts[i] > 0)
        {
            HuffmanTreeNode *n1 = new HuffmanTreeNode(char(i), char_counts[i]);
            my_pq.push(n1);
        }
    }

    while (my_pq.size() > 1) { // until root is left
        HuffmanTreeNode *c1 = my_pq.top();
        my_pq.pop();
        HuffmanTreeNode *c2 = my_pq.top();
        my_pq.pop();
        HuffmanTreeNode *parent = new HuffmanTreeNode('\0', c1->get_freq() 
            + c2->get_freq(),c1, c2);
        my_pq.push(parent);
    }
}

/*
 * name:      create_codes()
 * purpose:   traverses the tree and creates the code based on the traversal.
 * arguments: root node of the tree and a string which updates with each call
 * returns:   none
 * effects:   adds the string for each node to respective spot in char_codes
 *            vector.
 */
void HuffmanCoder::create_codes(HuffmanTreeNode *root, std::string code)
{
    if (root->isLeaf()) { // base case
        char_codes[(int) root->get_val()] = code;
        return;
    } else { // pre-order traversal recursive (internode) case
        create_codes(root->get_left(), code + "0"); 
        create_codes(root->get_right(), code + "1");
    }
}

/*
 * name:      convert_chars()
 * purpose:   given a char, convert the char into specified encoding
 * arguments: file stream object of given input file
 * returns:   string of bits
 * effects:   none
 */
std::string HuffmanCoder::convert_chars(std::fstream &inStream)
{
    char a = '\0';
    std::string finalString = "";
    while (inStream.get(a)) { // if i change this loop, bitstring changes
        finalString += char_codes[(int) a];
    }
    return finalString;
}

/*
 * name:      serialize_tree()
 * purpose:   convert tree to string form
 * arguments: root of the Huffman Tree
 * returns:   string form of Huffman Tree
 * effects:   none
 */
std::string HuffmanCoder::serialize_tree(HuffmanTreeNode *root)
{
    std::string result = "";
    if (root == nullptr) { // base case
        return result;
    } else if (root->isLeaf()) { // leaf case
        result += "L";
        result += root->get_val();
    } else { // pre-order traversal recursive (internode) case
        result += "I" + serialize_tree(root->get_left()) 
            + serialize_tree(root->get_right());
    }
    return result;
}

/*
 * name:      decoder()
 * purpose:   decodes a binary file into a text file
 * arguments: strings holding the names of the input and output files
 * returns:   none
 * effects:   calls helper functions to do different parts to decode
 */
void HuffmanCoder::decoder(std::string input_file, std::string output_file)
{
    BinaryIO decoding;
    std::fstream inStream; 
    std::ofstream outStream;
    open_or_die(inStream, input_file); // opens input stream
    open_or_die_writemode(outStream, output_file); // opens output stream
    real_values = decoding.readFile(input_file); // reads zapped file
    std::string result = revert(real_values[1], 
        deserialize_tree(real_values[0]));
    outStream << result;
    delete_tree(deserialize_tree(real_values[0])); // recycles nodes on heap
    outStream.close();
    
}

/*
 * name:      deserialize_tree()
 * purpose:   create a Huffman Tree
 * arguments: string form of the Huffman Tree
 * returns:   root of the Huffman Tree
 * effects:   calls deserialize_helper()
 */
HuffmanTreeNode *HuffmanCoder::deserialize_tree(std::string serial_tree)
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
HuffmanTreeNode *HuffmanCoder::deserialize_helper(std::stringstream *ss)
{
    HuffmanTreeNode *result = nullptr;
    char a;
    ss->get(a);
    if (a == 'L') { // leaf case
        char b;
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
void HuffmanCoder::delete_tree(HuffmanTreeNode *root)
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

/*
 * name:      revert()
 * purpose:   given a string of bits and the root, this function goes through
 *            the tree and constructs the text.
 * arguments: root of the Huffman Tree and a string of bits
 * returns:   translated string of text
 * effects:   none
 */
std::string HuffmanCoder::revert(std::string bitString, 
    HuffmanTreeNode *root)
{
    std::string result = "";
    HuffmanTreeNode *temp = root;
    std::stringstream ss(bitString);
    char a;
    while (ss.get(a)) {
        if (a == '0') { // go left
            temp = temp->get_left();
            if (temp->isLeaf()) { // adds char to return value
                result += temp->get_val();
                temp = root;
            }
        }
        if (a == '1') { // go right
            temp = temp->get_right();
            if (temp->isLeaf()) { // adds char to return value
                result += temp->get_val();
                temp = root;
            }
        }
    }
    if (temp != root) { // edge case of decoding stopping in middle
        throw std::runtime_error("Encoding did not match Huffman tree.");
    }
    return result;
}

/*
 * name:      print_tree()
 * purpose:   print out the nodes of the tree
 * arguments: root of the Huffman Tree
 * returns:   none
 * effects:   prints the tree
 */
void HuffmanCoder::print_tree(HuffmanTreeNode *root)
{
    if (root == nullptr) { // base case
        return;
    } else if (root->isLeaf()) { // one node case
        std::cout << "L" << std::endl;
        std::cout << root->get_val() << std::endl;
    } else { // post-order traversal recursive case
        std::cout << "I" << std::endl;
        print_tree(root->get_left()); 
        print_tree(root->get_right());
    }
}