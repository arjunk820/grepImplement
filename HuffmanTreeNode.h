#ifndef __HUFFMANTREENODE_H__
#define __HUFFMANTREENODE_H__

class HuffmanTreeNode {
public:
    /* 
     * Constructor #1: sets val to c, freq to f, and
     * sets left and right to nullptr by default.
     */
    HuffmanTreeNode(char c, int f);

    /*
     * Constructor #2: sets val to c, freq to f, left to l, and right to r.
     */
    HuffmanTreeNode(char c, int f, HuffmanTreeNode *l, HuffmanTreeNode *r);

    /* 
     * Helper function for determining if this node is a leaf.
     */
    bool isLeaf() const;

    /*
     * getters for the private member variables
     */
    char get_val() const;
    int get_freq() const;
    HuffmanTreeNode *get_left() const;
    HuffmanTreeNode *get_right() const;

    /*
     * setters for left and right
     */
    void set_left(HuffmanTreeNode*);
    void set_right(HuffmanTreeNode*);

private:
    /* 
     * The character stored within this node. 
     * Should be '\0' for internal nodes.
     */
    char val;
    
    /* 
     * The frequency of this character,
     * or the frequency for all descendant characters for internal nodes.
     */
    int freq;
    
    /* 
     * Left and right children.
     */
    HuffmanTreeNode *left;
    HuffmanTreeNode *right;
};

/* A comparator class: defines a comparison function so that nodes can
 * be used in a minheap.
 * The comparison function compares two nodes based on their frequencies.
 * Returns n1->get_freq() > n2->get_freq().
 */
class NodeComparator {
public:
    bool operator()(const HuffmanTreeNode *n1, const HuffmanTreeNode *n2);
};

#endif
