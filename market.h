#ifndef MARKET_H
#define MARKET_H
#define MAX 100

#include "list1.h"

typedef struct produk
{
	int kodeTrans;
    List barang;
}transaksi;

typedef struct{
	transaksi Produk[MAX];
    int numOfProduk;
}basket;

void generateProduk(int X);

void createBasket(basket *bkt);
void createTransaksi(transaksi *tra, int kodeTrans);
void printBasket(basket bkt);
void addJmlProduk(basket *bkt, transaksi tra);
void addProduk(transaksi *tra, char namaProduk[50]);
void removeProduk(transaksi *tra);

#endif