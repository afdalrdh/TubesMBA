#include "market.h"

trie_address generate_itemset_trie()
{
	int i;
	int produk_index[10];
	int produk_temp[10];
	
	trie_address root = make_trienode('\0');
	
	for(i=0; i<10; i++)
	{
		produk_index[i] = i;
	}
	for(i=0; i<5; i++);
	{
		combination_to_generate_trie(root, produk_index, produk_temp, 0, 9, 0, i+1);
	}
	
	system("pause");
	return root;
}

void combination_to_generate_trie(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_number) 
{ 
    if (index == subset_element_number) 
    { 
        root = insert_trie(root, data_array_temp, subset_element_number);
        return; 
    } 
    for (int i=start; i<=end && end-i+1 >= subset_element_number-index; i++) 
    { 
        data_array_temp[index] = data_array[i]; 
        combination_to_generate_trie(root, data_array, data_array_temp, i+1, end, index+1, subset_element_number); 
    } 
}

void generateProduk(int X, int min_support, int min_confidence)
{
	FILE *fp, *ft;
	int i=0,y,random5,random100;
	char c,produk[150][20], kode[150][5];
    basket bkt;
    createBasket(&bkt);
    transaksi temp;
    trie_address root;
    
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
			addProduk(&temp, random100);	//produk
			
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
    root = generate_itemset_trie();
    
    insert_basket_into_trie(root, bkt, X);
    show_support_list_from_basket(root, bkt, min_support);
    
   
}

void show_support_list_from_basket(trie_address root, basket bkt, int min_support)
{
	
	
	int i, j, k;
	int temp[5], temp_data[5];
	
	for(i=0; i<bkt.numOfProduk; i++)
	{
		show_support_list_from_transaction(root, bkt.Produk[i].barang, min_support);
	}
}

void show_support_list_from_transaction(trie_address root, List transaksi, int min_support)
{
	int count = NbElmt(transaksi); 
	int temp[count];
	int temp_data[count];
	int support_per_length[5] = {0};
	int i = 0;
	
	address P = First(transaksi);

	do
	{
		temp[i] = Info(P).index_produk;
		P = Next(P);
		i++;
	} while (P != Nil);

	sortIntArray(temp, count);
	for(i=0; i<count; i++)
    {
    	combination_for_showing_support(root, temp, temp_data, 0, count-1, 0, i+1, min_support, support_per_length);
	}
	printf("\n");
}

void combination_for_showing_support(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_number, int threshold, int *length) 
{ 
    if (index == subset_element_number) 
    {
    	if (search_trie(root, data_array_temp, subset_element_number))
    	{
    		print_support_min_threshold(root, data_array_temp, subset_element_number, threshold, length);
		}
        return; 
    } 
    for (int i=start; i<=end && end-i+1 >= subset_element_number-index; i++) 
    { 
        data_array_temp[index] = data_array[i]; 
        combination_for_showing_support(root, data_array, data_array_temp, i+1, end, index+1, subset_element_number, threshold, length); 
    } 
}

void print_support_min_threshold(trie_address root, int* data_array, int length, int threshold, int *supp_per_length) {
	trie_address temp;
	int i;
	
	for(i=0;i<length;i++)
	{
		printf("%d ",data_array[i]);
	}
	printf("\n");
	system("pause");
	
	printf("|");
	for(i=0; i<length;i++)
    {
    	if(i!=length-1)
    		printf("%d ", data_array[i]);
    	else
    		printf("%d", data_array[i]);
	}
	
	temp = search_trie_node(root, data_array, length);
	if(length < 4)
		printf("\t\t\t");
	else if(length < 6)
		printf("\t\t");
		
	printf("|%d\t|", temp->support);
	if(temp->support >= threshold) {
		printf(" PASSED \n");
		supp_per_length[length-1] = supp_per_length[length-1] + 1;
	} else
		printf(" FAILED \n");
}

void insert_basket_into_trie(trie_address root, basket bkt, int transaction_total_choice)
{
	int i, j, k;
	int temp[5], temp_data[5];
	
	for(i=0; i<bkt.numOfProduk; i++)
	{
		insert_transaction_into_trie(root, bkt.Produk[i].barang);
	}
}

void insert_transaction_into_trie(trie_address root, List transaksi)
{
	int count = NbElmt(transaksi); 
	int temp[count];
	int temp_data[count];
	int i = 0;
	address P = First(transaksi);
	if (P == Nil)
	{	
	}
	else
	{
		do
		{
			temp[i] = Info(P).index_produk;
			//printf("%s, ", produk[Info(P).index_produk]);
			P = Next(P);
			i++;
		} while (P != Nil);
	}
	sortIntArray(temp, count);
	for(i=0; i<count; i++)
		combination_to_add_support(root, temp, temp_data, 0, count-1, 0, i+1);
}

void combination_to_add_support(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_number)
{
	trie_address temp;
    if (index == subset_element_number) 
    {
    	temp = search_trie_node(root, data_array_temp, subset_element_number);
    	if (temp != NULL)
    	{
    		temp->support++;
		}
        return; 
    } 
    for (int i=start; i<=end && end-i+1 >= subset_element_number-index; i++) 
    { 
        data_array_temp[index] = data_array[i]; 
        combination_to_add_support(root, data_array, data_array_temp, i+1, end, index+1, subset_element_number); 
    } 
}

void sortIntArray(int *a, int length)
{
	int i, j, temp;
	for (i = 0; i < length; ++i) 
    {
        for (j = i + 1; j < length; ++j)
        {
            if (a[i] > a[j]) 
            {
	            temp =  a[i];
	            a[i] = a[j];
	            a[j] = temp;
            }
        } 
    }
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
        PrintTransaksi(bkt.Produk[i].barang);
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

void addProduk(transaksi *tra, int kodeProduk)
{
    infotype temp;
    temp.index_produk = kodeProduk;

    InsVLast(&(tra->barang), temp);
}

void PrintTransaksi(List L)
{ 
	
	int i = 0;
	char produk[150][100];
	FILE *fp = fopen("produk.txt", "r");
	while(!feof(fp)) 		//membaca 100 produk
	{
		fscanf(fp,"%s",produk[i]);
		i++;
	}
	fclose(fp);

	address P = First(L);
	if (P == Nil)
	{
		printf("[ ]");
	}
	else
	{ /* List tidak kosong */
		printf("[ ");
		do
		{
			printf("%s, ", produk[Info(P).index_produk]);
			P = Next(P);
		} while (P != Nil);
		printf("\b\b ]");
	}
}

void mainMenu(int min_support, int min_confidence)
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
				generateProduk(20, min_support, min_confidence);
			break;
			case 2 :
				generateProduk(50, min_support, min_confidence);
			break;
			case 3 :
				generateProduk(100, min_support, min_confidence);
			break;
			case 4 :
				exit(1);
			break;
			default :
				printf("Pilihan tidak ada");
			break;
		}
		fflush(stdin);
		printf("\n");
		system("pause");
	}while(1);
}
