//=========================================================================================
// Program 			: Trie.c
// Deskripsi 		: Body dari ADT Trie
// Tanggal			: 11 Juli 2020
// Author/Modifier	: Aldy Akbarrizky
// Versi			: 1.0
// IDE				: Dev C++ 5.13
// Original Author	: Vijaykrishna Ram
// Sumber			: https://www.journaldev.com/36507/trie-data-structure-in-c-plus-plus
// Compiler			: TDM-GCC 9.2.0 32-bit Debug
//=========================================================================================

#ifndef TRIE_C
#define TRIE_C

#include <stdio.h>
#include <stdlib.h>
#include "Trie.h"

//-------------
//CONSTRUCTOR
//-------------

trie_address make_trienode(int data)
{
	// Allocate memory for a TrieNode
    trie_address node = (trie_address) calloc (1, sizeof(TrieNode));
    for (int i=0; i<N; i++)
        node->children[i] = NULL;
    Support(node) = 0;
    Data(node) = data;
    return node;
}


//-------------
//DESTRUCTOR
//-------------

void free_trienode(trie_address node)
{
	// Free the trienode sequence
    for(int i=0; i<N; i++) {
        if (node->children[i] != NULL) {
            free_trienode(node->children[i]);
        }
        else {
            continue;
        }
    }
    free(node);
}


//-------------
//OPERATOR
//-------------

trie_address insert_trie(trie_address root, int* data_array, int length)
{
	// Inserts the data onto the Trie
    trie_address temp = root;
 
    for (int i=0; i<length; i++) {
        int idx = data_array[i];
        if (temp->children[idx] == NULL) {
            // If the corresponding child doesn't exist,
            // simply create that child!
            temp->children[idx] = make_trienode(data_array[i]);
        }
        else {
            // Do nothing. The node already exists
        }
        // Go down a level, to the child referenced by idx
        // since we have a prefix match
        temp = temp->children[idx];
    }
    return root;
}

boolean search_trie(trie_address root, int* data_array, int length)
{
	// Searches for word in the Trie
    trie_address temp = root;
 
    for(int i=0; i<length; i++)
    {
        int position = data_array[i];
        if (temp->children[position] == NULL)
            return false;
        temp = temp->children[position];
    }
    if (temp != NULL)
        return true;
    return false;
}

trie_address search_trie_node(trie_address root, int* data_array, int length)
{
	// Searches for word in the Trie
    trie_address temp = root;
 
    for(int i=0; i<length; i++)
    {
        int position = data_array[i];
        if (temp->children[position] == Nil)
        {
 			return Nil;
		}
        temp = temp->children[position];
    }
    if (temp != Nil)
        return temp;
    return Nil;
}

void print_trie(trie_address root)
{
	// Prints the nodes of the trie
    if (!root)
        return;
    trie_address temp = root;
    printf("%d -> ", Data(temp));
    for (int i=0; i<N; i++) {
        print_trie(temp->children[i]); 
    }
}

#endif