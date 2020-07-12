#include "market.h"
#include <conio.h>
int main()
{
	int pilih;
	
	do{
		system("cls");
		printf("=================================\n");
		printf("||    MARKET BASKET ANALYSIS   ||\n");
		printf("=================================\n");
		printf("||   1.Generate 20 transaksi   ||\n");
		printf("||   2.Generate 50 transaksi   ||\n");
		printf("||   3.Generate 100 transaksi  ||\n");
		printf("||   4.Exit                    ||\n");
		printf("================================\n\n");
		printf("Pilih menu :");
		scanf("%d", &pilih);
		switch(pilih)
		{
			case 1 :
				generateProduk(20);
			break;
			case 2 :
				generateProduk(50);
			break;
			case 3 :
				generateProduk(100);
			break;
			case 4 :
				exit(1);
			break;
			default :
				printf("Pilihan tidak ada");
			break;
		}
		fflush(stdin);
		printf("\n");getch();
	}while(1);
	return 0;
}