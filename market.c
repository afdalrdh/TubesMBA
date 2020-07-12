#include "market.h"


void generateProduk(int X)
{
	FILE *fp, *ft;
	int i=0,y,random5,random100;
	char c,produk[150][20], kode[150][5];
    basket bkt;
    createBasket(&bkt);
    transaksi temp;
    
	fp = fopen("produk.txt", "r");
	switch(X){
		case 20:
			ft =fopen("transaksi20.txt", "w+");
			break;
		case 50:
			ft =fopen("transaksi50.txt", "w+");
			break;
		case 100:
			ft =fopen("transaksi100.txt", "w+");
			break;
	}
	
	while(!feof(fp)) 		//membaca 100 produk
	{
		fscanf(fp,"%s",produk[i]);
		i++;
	}
	fclose(fp);
    
	for(i=0;i<X;i++){
		
		fprintf(ft,"T%d\t", i+1);
		createTransaksi(&temp, i+1);		//kode
		
		random5=rand()%5+1;
		for(random5;random5>=1;random5--){
			random100=rand()%100+1;
			addProduk(&temp, produk[random100]);	//produk
			
			if(random5==1){
				fprintf(ft,"%s", produk[random100]);
			}
			else{
				fprintf(ft,"%s,", produk[random100]);
			}
		}
		fprintf(ft,"\n");
		addJmlProduk(&bkt, temp);
	}
	fclose(ft);
	printf("\nList produk :\n");
    printBasket(bkt);   
    printf("\n");
}

void createBasket(basket *bkt)
{
    bkt->numOfProduk = 0;
}

void createTransaksi(transaksi *tra, int kodeTrans)
{
    CreateList(&(tra->barang));
    tra->kodeTrans = kodeTrans;
}

void printBasket(basket bkt)
{
	int i;
    for (i = 0; i < bkt.numOfProduk; i++)
    {
        printf("[ ");
        printf("%d", bkt.Produk[i].kodeTrans);
        printf(" ");
        PrintInfo(bkt.Produk[i].barang);
        printf("]\n");
    }
}

void addJmlProduk(basket *bkt, transaksi tra)
{
    if (bkt->numOfProduk + 1 > MAX)
    {
        return;
    }

    bkt->Produk[bkt->numOfProduk] = tra;
    bkt->numOfProduk++;
}

void addProduk(transaksi *tra, char namaProduk[50])
{
    infotype temp;
    strcpy(temp.nama, namaProduk);

    InsVLast(&(tra->barang), temp);
}
