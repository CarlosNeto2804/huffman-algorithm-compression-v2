#ifndef HUFFMAN
#define HUFFMAN
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <math.h>
#include "./list.h"

#define ASCII 256
#define BYTE_SIZE 5

using namespace std;

class Huff
{
public:
    // Constructors.
    Huff();

    // Methods.
    void compress(std::string filename, std::string outfile);
    void decompress(std::string filename, std::string outfile);

private:
    // Attributes.
    List *list;

    // Methods.
    string build_bytes(string bitflow);
    string *build_code(Node *root);
    void build_code(string *codes, Node *node, string code);
    List *build_list(string text);
    Node *build_trie(List *list);
    string bytes_to_bit_flow(string bytes);
    int find(string text, char charact);
    string get_file_extension(string filename, int dotPos);
    string get_file_without_extension(string filename, int dotPos);
    string get_output_filename(string filename);
    void print_code(string *codes);
    void print_trie(Node *root);
    string read(string filename);
    string read_file_extension(string *text);
    int read_size(string *text);
    Node *read_trie(string *text);
    Node *read_trie(string text, int *index);
    string translate(string bitflow, int size, Node *root);
    string transform(Node *node, string trie);
    string transform(Node *node);
    string transform(string text, string *table);
    void write(string text, string filename);
    void write(string fileext, string trie, int size, string bitflow, string filename);
};
#endif