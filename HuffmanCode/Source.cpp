#include<iostream>
#include <string>
#include <fstream>
#include "MinHeap.h"
#include "MinHeap.cpp"
using namespace std;

template <class T>
struct node {
	T key;
	int frequency;
	node<T>* left_child = 0;
	node<T>* right_child = 0;
};

// function prototypes
void printHuffmanCodes(node<char>* head_node, int code_array[], int top = 0);
void decryptHuffmanCode(node<char>* head_node, int code_array[], int length);
void checkFrequency(node<char> nodes[], int total_numbers_of_nodes);

int main() {
	try {
		// create a node to hold data to be placed onto heap
		node <char>* node_1;

		// variable to hold number of keys
		int number_of_elements;

		ifstream inputStream;
		//attempt to open file stream for input
		inputStream.open("data.txt");
		
		if (inputStream.is_open() != true) {
			throw 15;
		}

		// get number of keys from file
		inputStream >> number_of_elements;

		// output number of elements from file
		cout << "Number of Elements: " << number_of_elements << endl;

		// instantiate MinHeap and node to hold and organize data
		MinHeap<node <char> > heap(number_of_elements + 1);
		node_1 = new node<char>[number_of_elements];

		// get input of keys and frequencies
		// place this data into a node
		// insert node into heap
		for (int i = 0; i < number_of_elements; i++) {
			// get key from file
			inputStream >> node_1[i].key;

			// check whether the file ends early for stated 
			// number of elements
			if (node_1[i].key == -51) {
				throw 16;
			}
			// get frequency of key
			inputStream >> node_1[i].frequency;

			// insert node into MinHeap
			heap.Insert(node_1[i]);
		}

		// close file stream
		inputStream.close();

		checkFrequency(node_1, number_of_elements);

		// Build Huffman Tree
		// delete first 2 nodes
		// create new node where frequency = sum of frequencies of deleted nodes
		// set child  of first deleted node = 'L'
		// set child of second deleted node = 'R'
		// repeat until heap only contains the head of Huffman Tree
		node<char>* new_node = 0;
		node<char>* deleted_node_1, * deleted_node_2;
		while (heap.Size > 1) {
			deleted_node_1 = new node<char>();
			deleted_node_2 = new node<char>();
			// delete first node
			heap.Delete(*deleted_node_1);

			// delete second node
			heap.Delete(*deleted_node_2);

			// create new node to hold data
			new_node = new node<char>();

			// populate data fields of new node
			new_node->left_child = deleted_node_1;
			new_node->right_child = deleted_node_2;
			new_node->frequency = deleted_node_1->frequency + deleted_node_2->frequency;

			// add huffman subtree to MinHeap
			heap.Insert(*new_node);
		}

		// get head node for Huffman Tree
		heap.Delete(*new_node);

		//print all code for Huffman Code
		int *code_array = new int[256];
		printHuffmanCodes(new_node, code_array, 0);


		// get an encrypted code and decrypt it
		char encrypted_code[256];

		// have user input an encrypted code to be decrypted
		cout << "\nEnter encrypted code below:" << endl;
		// clear cin buffer
		cin.clear();
		// get encrytped code
		cin.getline(encrypted_code, 256);
		// convert character encrypted code into integer
		for (int i = 0; i < 256; i++) {
			code_array[i] = (int)encrypted_code[i] - (int)'0';
		}

		// decrypt encrypted code
		decryptHuffmanCode(new_node, code_array, 256);

		// delete dynamic memory
		delete new_node;
		delete[] node_1;
		delete[] code_array;
	}
	catch(int e){
		// output errors (if any)
		if (e == 15)
			cerr << "File 'data.txt' not found." << endl;
		else if (e == 16)
			cerr << "File ended prematurely for stated number of elements." << endl;
		else if (e == 17)
			cerr << "Total number of keys is greater than 100." << endl;
	}

	return 0;
}


void printHuffmanCodes(node<char>* head_node, int code_array[], int top)
{
	/*
		Function that goes through Huffman Tree recursively and output code
		when a leaf is reached
	*/
	// go to left node
	// assign 0 to code array
	if (head_node->left_child != NULL) {
		code_array[top] = 0;
		printHuffmanCodes(head_node->left_child, code_array, top + 1);
	}


	// go to right node
	// assign 1 to code array
	if (head_node->right_child != NULL) {
		code_array[top] = 1;
		printHuffmanCodes(head_node->right_child, code_array, top + 1);
	}

	// check if this is a leaf node, 
	// if not then don't output code
	if ((head_node->left_child == NULL) && (head_node->right_child == NULL)) {
		cout << head_node->key << ": ";
		for (int i = 0; i < top; i++) {
			cout << code_array[i];
		}
		cout << endl;
	}
}

void decryptHuffmanCode(node<char>* head_node, int code_array[], int length) {
	/*
		Function that recursively goes through Huffman Tree based on code
		in code_array
	*/
	cout << "\nDecrypting" << endl;
	node<char> node_copy = *head_node;

	for (int i = 0; i < length; i++) {
		// stop when code finishes
		if ((code_array[i] != 0) && (code_array[i] != 1))
			break;

		if (code_array[i] == 0) {
			node_copy = *node_copy.left_child;
		}

		else {
			node_copy = *node_copy.right_child;
		}

		if ((node_copy.left_child == NULL) && (node_copy.right_child == NULL)) {
			cout << node_copy.key << ", ";
			node_copy = *head_node;
		}
	}
}

void checkFrequency(node<char> nodes[], int total_number_of_nodes) {
	int total = 0;
	for (int i = 0; i < total_number_of_nodes; i++) {
		total += nodes[i].frequency;
	}
	if (total > 100) {
		throw 17;
	}
}