#ifndef MARKET_H
#define MARKET_H
#define MAX 100

#include "list1.h"
#include "Trie.h"

typedef struct produk
{
	int kodeTrans;
    List barang;
}transaksi;

typedef struct{
	transaksi Produk[100];
    int numOfProduk;
}basket;

// **** ALDY **** //

//UNTUK TRIE// 
//untuk mengenerate sebuah trie baru yang berisikan list baru
trie_address generate_itemset_trie();

//prcedure untuk melakukan kombinasi yang ditujukan untuk menginsertkan semua item set dari produk ke dalam trie
void combination_to_generate_trie(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_number);

//menambahkan nilai support pada suatu trie berdasarkan suatu isi dari basket
void insert_basket_into_trie(trie_address root, basket bkt, int transaction_total_choice);

//menambahkan nilai support pada suatu trie berdasarkan suatu transaksi
void insert_transaction_into_trie(trie_address root, List transaksi);

//procedure untuk mensorting array of integer
void sortIntArray(int *a, int length);

//procedure untuk melakukan kombinasi yang ditujukan untuk menambah nilai support itemset pada trie sesuai dengan hasil kombinasi itemset dari suatu transaksi
void combination_to_add_support(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_number);

//procedure untuk melakukan kombinasi yang ditujukan untuk menampilkan nilai support seluruh itemset pada trie
void combination_for_showing_support(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_number, int threshold, int *length);

//procedure yang digunakan untuk menampilkan list itemset suatu trie dan nilai supportnya beserta statusnya apakah itemset tersebut pass (nilai support > nilai treshold) atau fail (nilai support < nilai treshold)
void print_support_min_threshold(trie_address root, int* data_array, int length, int threshold, int *supp_per_length);

//procedure yang digunakan untuk menampilkan list itemset dari suatu trie berdasarkan nilai supportnya
void show_support_list_from_trie(trie_address root, int min_support, int *support_per_length);

//procedure yang digunakan untuk mencari list item set yang nantinya akan digunakan untuk mencari association rule nya
void show_final_item_subset(trie_address root, int assoc_item_length, int min_support);

//procedure yang digunakan untuk melakukan kombinasi untuk menghasilkan suatu itemset yang nantinya akan digunakan untuk mencari association rule
void combination_for_final_subset(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_number, int threshold);

//procedure yang digunakan untuk menampilkan list item set yang nantinya akan digunakan untuk mencari association rule nya
void print_support_min_threshold_eliminated(trie_address root, int data_array[], int length, int threshold);

//procedure yang digunakan untuk melakukan suatu proses untuk memulai proses pencarian association rule
void generate_association_rule(trie_address root, int assoc_item_length, int min_support, int min_confidence);

//procedure untuk melakukan suatu kombinasi untuk menampilkan list subset dari suatu final itemset
void combination_for_association_rules(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_number, int threshold, int min_confidence);

//procedure untuk menampilkan association rule
void print_last_for_assoc_rule(trie_address root, int data_array[], int length, int threshold, int min_confidence);

//procedure yang digunakan untuk menampilkan penjelasan dari sebuah rule
void print_subset(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_length, int max_subset_length, int min_confidence);

//procedure yang digunakan untuk menampilkan hasil confidence dari suatu rule
void print_confidence(trie_address root, int data_subset[], int data_itemset[], int sub_length, int item_length, int min_confidence);


// **** AFDAL **** //

//procedure untuk mengenerate list produk menjadi file dan array of integer
void generateProduk(int X, int min_support, int min_confidence);

//untuk menyiapkan data basket (100 produk)
void createBasket(basket *bkt);

//untuk menambah transaksi baru ke dalam basket
void createTransaksi(transaksi *tra, int kodeTrans);

//menampilkan data produk yang berada di basket
void printBasket(basket bkt);

//menambah jumlah produk di linkedlist
void addJmlProduk(basket *bkt, transaksi tra);

//procedure untuk menambah list produk baru
void addProduk(transaksi *tra, int kodeProduk);

//untuk menghapus salah satu list produk
void removeProduk(transaksi *tra);

//untuk menampilkan seluruh transaksi yang sudah di buat secara random
void PrintTransaksi(List L);

//untuk merubah warna pada output program
void setcolor(short color);

//untuk menampilkan main menu program ini
void mainMenu();

#endif