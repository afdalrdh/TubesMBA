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
	transaksi Produk[MAX];
    int numOfProduk;
}basket;

//ALDY
trie_address generate_itemset_trie();
void combination_to_generate_trie(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_number);
void insert_basket_into_trie(trie_address root, basket bkt, int transaction_total_choice);
void insert_transaction_into_trie(trie_address root, List transaksi);
void sortIntArray(int *a, int length);
void combination_to_add_support(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_number);
void combination_for_showing_support(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_number, int threshold, int *length);
void print_support_min_threshold(trie_address root, int* data_array, int length, int threshold, int *supp_per_length);
void show_support_list_from_basket(trie_address root, basket bkt, int min_support);
void show_support_list_from_transaction(trie_address root, List transaksi, int min_support);

//AFDAL
void generateProduk(int X, int min_support, int min_confidence);
void createBasket(basket *bkt);
void createTransaksi(transaksi *tra, int kodeTrans);
void printBasket(basket bkt);
void addJmlProduk(basket *bkt, transaksi tra);
void addProduk(transaksi *tra, int kodeProduk);
void removeProduk(transaksi *tra);
void PrintTransaksi(List L);
void mainMenu(int min_support, int min_confidence);

#endif