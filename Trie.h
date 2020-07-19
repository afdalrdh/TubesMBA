//=========================================================================================
// Program 			: Trie.h
// Deskripsi 		: Spesifikasi ADT Trie
// Tanggal			: 11 Juli 2020
// Author/Modifier	: Aldy Akbarrizky
// Versi			: 1.0
// IDE				: Dev C++ 5.13
// Original Author	: Vijaykrishna Ram
// Sumber			: https://www.journaldev.com/36507/trie-data-structure-in-c-plus-plus
// Compiler			: TDM-GCC 9.2.0 32-bit Debug
//=========================================================================================

#ifndef TRIE_H
#define TRIE_H

#include "boolean.h"

#define Nil NULL
#define Data(T) (T)->data
#define Support(T) (T)->support
#define N 30

//===============================
// DATA TYPE
//===============================
typedef int datatype;
typedef struct tTrieNode* trie_address;
 
typedef struct tTrieNode {
    int data;
    trie_address children[N];
    int support;
}TrieNode;


//===============================
// PROTOTYPE
//===============================

//-------------
//CONSTRUCTOR
//-------------

trie_address make_trienode(int data);
// Author			: Vijaykrishna Ram
// Modified by		: Aldy Akbarrizky
// English
// Input Parameter	: 1. data: An integer value that will be inserted into the trie
// Output Parameter	: Address of the new node for the trie
// Description		: Function used to do memory allocation for new nodes in the trie
// Indonesian
// Parameter Input	: 1. data: Sebuah nilai integer yang akan diinsertkan ke dalam trie
// Parameter Output	: Alamat dari node baru untuk trie
// Deskripsi		: Function yang digunakan untuk melakukan alokasi memori untuk node baru pada trie


//-------------
//DESTRUCTOR
//-------------

void free_trienode(trie_address node);
// Author			: Vijaykrishna Ram
// English
// Initial State	: A node allocated in the memory
// Final State		: The node are freed from memory
// Description		: Procedure used to free a node in a trie
// Indonesian
// Kondisi Awal		: Sebuah node teralokasi di memori
// Kondisi Akhir	: Node dibebaskan dari memori, sehingga memori tersebut dapat digunakan lagi
// Deskripsi		: Procedure yang digunakan untuk melepaskan alokasi suatu node


//-------------
//OPERATOR
//-------------

trie_address insert_trie(trie_address root, int* data_array, int length);
// Author			: Vijaykrishna Ram
// Modified by		: Aldy Akbarrizky
// English
// Input Parameter	: 1. root		: Root of a trie
//					  2. data_array	: A collection data of array of integers
//					  3. length		: The number of elements in that array
// Output Parameter	: Address of the root node will be returned
// Description		: Function used to insert a new data to the trie
// Indonesian
// Parameter Input	: 1. root		: Sebuah node yang merupakan root dari trie
//					  2. data_array	: Sekumpulan data array of integer
//					  3. length		: Jumlah elemen pada array tersebut
// Parameter Output	: Alamat dari node root akan dikembalikan
// Deskripsi		: Function yang digunakan untuk menginsertkan suatu data baru kepada trie

boolean search_trie(trie_address root, int* data_array, int length);
// Author			: Vijaykrishna Ram
// Modified by		: Aldy Akbarrizky
// English
// Input Parameter	: 1. root		: Root of a trie
//					  2. data_array	: A collection data of array of integers
//					  3. length		: The number of elements in that array
// Output Parameter	: Returns True if the data sought is found on the trie, and returns false if not found
// Description		: Function used to check whether a data is in a trie or not
// Indonesian
// Parameter Input	: 1. root		: Sebuah node yang merupakan root dari trie
//					  2. data_array	: Sekumpulan data array of integer
//					  3. length		: Jumlah elemen pada array tersebut
// Parameter Output	: Mengembalikan True jika data yang dicari ditemukan pada trie, dan mengembalikan false apabila tidak ditemukan
// Deskripsi		: Function yang digunakan untuk mengecek apakah suatu data berada pada suatu trie

trie_address search_trie_node(trie_address root, int* data_array, int length);
// Author			: Vijaykrishna Ram
// Modified by		: Aldy Akbarrizky
// English
// Input Parameter	: 1. root		: Root of a trie
//					  2. data_array	: A collection data of array of integers
//					  3. length		: The number of elements in that array
// Output Parameter	: The address of the node will be returned if data is found. If not, then returns NULL
// Description		: Function is used to check whether a data is in a trie, then returns the node address of that data if found
// Indonesian
// Parameter Input	: 1. root		: Sebuah node yang merupakan root dari trie
//					  2. data_array	: Sekumpulan data array of integer
//					  3. length		: Jumlah elemen pada array tersebut
// Parameter Output	: Alamat dari node akan dikembalikan jika data ditemukan. Jika tidak, maka mengembalikan NULL
// Deskripsi		: Function yang digunakan untuk mengecek apakah suatu data berada pada suatu trie, kemudian mengembalikan alamat node dari data tersebut jika ditemukan

void print_trie(trie_address root);
// Author			: Vijaykrishna Ram
// English
// Initial State	: A trie that has been defined (Not empty)
// Final State		: The contents of the trie will be displayed to the screen
// Description		: Procedure used to display the contents of the trie
// Indonesian
// Kondisi Awal		: Sebuah trie yang sudah terdefinisi
// Kondisi Akhir	: Isi dari trie akan ditampilkan ke layar
// Deskripsi		: Procedure yang digunakan untuk menampilkan isi dari trie

#endif