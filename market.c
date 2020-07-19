#include "market.h"
#include <time.h>

trie_address generate_itemset_trie()
{
	int i;
	int produk_index[30];
	int produk_temp[30];
	
	trie_address root = make_trienode('\0');
	
	for(i=0; i<30; i++)
	{
		produk_index[i] = i;
	}
	int j;
	for(j=0; j<5; j++)
	{
		combination_to_generate_trie(root, produk_index, produk_temp, 0, 29, 0, j+1);
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
	int i=0,y,random5,random100, association_itemset_length;
	char c,produk[150][20], kode[150][5];
    basket bkt;
    createBasket(&bkt);
    transaksi temp;
    trie_address root;
    int support_per_length[5] = {0};
    
	fp = fopen("produk30.txt", "r");
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
    
    srand(time(NULL));
	for(i=0;i<X;i++){
		
		fprintf(ft,"T%d\t", i+1);
		createTransaksi(&temp, i+1);		//kode
		
		random5=rand()%5+1;
		for(random5;random5>=1;random5--){
			random100=rand()%29+1;
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
    
    int a[1];
    trie_address tempor;
    printf("Data subset 1:\n");
    
    insert_basket_into_trie(root, bkt, X);
    show_support_list_from_trie(root, min_support, support_per_length);
    for(i=0; i<5; i++)
		printf("Total passed on length %d: %d\n", i+1, support_per_length[i]);
	for(i=0; i<5; i++)
	{
		if(support_per_length[i] > 0)
			association_itemset_length = i+1;
	}
	printf("Panjang subset yang dijadikan association rules: %d\n", association_itemset_length);
	system("pause");
	printf("Final Subset yang akan digunakan untuk mencari Association Rules: \n");
	show_final_item_subset(root, association_itemset_length, min_support);
	system("pause");
	generate_association_rule(root, association_itemset_length, min_support, min_confidence);
}

void generate_association_rule(trie_address root, int assoc_item_length, int min_support, int min_confidence)
{
	int data_array[30], data_array_temp[30];
	int i;
	
	for(i=0; i<30; i++)
	{
		data_array[i] = i;
	}
	combination_for_association_rules(root, data_array, data_array_temp, 0, 29, 0, assoc_item_length, min_support, min_confidence);
}

void combination_for_association_rules(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_number, int threshold, int min_confidence)
{
	if (index == subset_element_number) 
    {
    	if (search_trie(root, data_array_temp, subset_element_number))
    	{
    		print_last_for_assoc_rule(root, data_array_temp, subset_element_number, threshold, min_confidence);
		}
        return; 
    } 
    for (int i=start; i<=end && end-i+1 >= subset_element_number-index; i++) 
    { 
        data_array_temp[index] = data_array[i]; 
        combination_for_association_rules(root, data_array, data_array_temp, i+1, end, index+1, subset_element_number, threshold, min_confidence); 
    } 
}

void print_last_for_assoc_rule(trie_address root, int data_array[], int length, int threshold, int min_confidence)
{
	FILE *fp;
	char produk[120][50];
	trie_address temp;
	int array[length];
	int temporary[5];
	int i = 0;
	
	fp = fopen("produk30.txt", "r");
	while(!feof(fp)) 		//membaca 100 produk
	{
		fscanf(fp,"%s",produk[i]);
		i++;
	}
	fclose(fp);
	
	temp = search_trie_node(root, data_array, length);
	
	if(Support(temp)>=threshold) {
		printf("Subset untuk itemset {");
		for(i=0; i<length;i++)
	    {
	    	if(i!=length-1)
	    		printf("%s ", produk[data_array[i]]);
	    	else
	    		printf("%s", produk[data_array[i]]);
	    	array[i] = data_array[i];
		}
		printf("}: \n");
		for(i=0; i<length-1;i++)
			print_subset(root, array, temporary, 0, length-1, 0, i+1, length, min_confidence);
		printf("\n");
	}
}

void print_subset(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_length, int max_subset_length, int min_confidence)
{
	FILE *fp;
	char produk[120][50];
	int i = 0;
	
	fp = fopen("produk30.txt", "r");
	while(!feof(fp)) 		//membaca 100 produk
	{
		fscanf(fp,"%s",produk[i]);
		i++;
	}
	fclose(fp);
	
	boolean ketemu;
	if (index == subset_element_length) 
    { 
    	printf("Rule {");
        for (int j=0; j<subset_element_length; j++) 
        {
        	if(j!=subset_element_length-1)
        		printf("%s ", produk[data_array_temp[j]]);
        	else
        		printf("%s", produk[data_array_temp[j]]);
		}
        printf("} -> {{");
        for (int j=0; j<max_subset_length; j++) 
        {
        	if(j!=max_subset_length-1)
        		printf("%s ", produk[data_array[j]]);
        	else
        		printf("%s", produk[data_array[j]]);
		}
		printf("} - {");
		for (int j=0; j<subset_element_length; j++) 
        {
        	if(j!=subset_element_length-1)
        		printf("%s ", produk[data_array_temp[j]]);
        	else
        		printf("%s", produk[data_array_temp[j]]);
		}
		printf("}} berarti jika seseorang membeli ");
		for (int j=0; j<subset_element_length; j++) 
        {
        	if (j<subset_element_length-2)
        		printf("%s, ", produk[data_array_temp[j]]);
        	else if(j==subset_element_length-2)
        		printf("%s dan ", produk[data_array_temp[j]]);
        	else if(j==subset_element_length-1)
        		printf("%s", produk[data_array_temp[j]]);
		}
		printf(", maka dia akan membeli ");
		for (int j=0; j<max_subset_length; j++) 
        {
        	ketemu = false;
        	for (int k=0; k<subset_element_length; k++)
        	{
        		if(data_array[j]==data_array_temp[k])
	        	{
	        		ketemu = true;
				}
			}
			if(!ketemu)
			{
				printf("%s ", produk[data_array[j]]);
			}
		}
		printf("juga\n");
		print_confidence(root, data_array_temp, data_array, subset_element_length, max_subset_length, min_confidence);
        return; 
    } 
    for (int i=start; i<=end && end-i+1 >= subset_element_length-index; i++) 
    { 
        data_array_temp[index] = data_array[i]; 
        print_subset(root, data_array, data_array_temp, i+1, end, index+1, subset_element_length, max_subset_length, min_confidence); 
    } 
}

void print_confidence(trie_address root, int data_subset[], int data_itemset[], int sub_length, int item_length, int min_confidence)
{
	FILE *fp;
	char produk[120][50];
	trie_address itemset_temp, subset_temp;
	int i = 0;
	float confidence;
	
	itemset_temp = search_trie_node(root, data_itemset, item_length);
	subset_temp = search_trie_node(root, data_subset, sub_length);
	confidence = ((float)itemset_temp->support/(float)subset_temp->support)*100;
	
	fp = fopen("produk30.txt", "r");
	while(!feof(fp)) 		//membaca 100 produk
	{
		fscanf(fp,"%s",produk[i]);
		i++;
	}
	fclose(fp);
	
	printf("Confidence = support{");
	for(i=0;i<item_length;i++)
	{
		if(i!=item_length-1)
			printf("%s, ", produk[data_itemset[i]]);
		else
			printf("%s", produk[data_itemset[i]]);
	}
	printf("}/support{");
	for(i=0;i<sub_length;i++)
	{
		if(i!=sub_length-1)
			printf("%s, ", produk[data_subset[i]]);
		else
			printf("%s", produk[data_subset[i]]);
	}
	printf("} = %d/%d = %.2f%%\n", itemset_temp->support, subset_temp->support, confidence);
	if(confidence >= min_confidence)
	{
		printf("Karena confidence nya lebih besar atau sama dengan min. confidence(%d%%), maka:\n", min_confidence);
		printf("RULES DITERIMA\n");
	} else
	{
		printf("Karena confidence nya lebih kecil dari min. confidence(%d%%), maka:\n", min_confidence);
		printf("RULES DITOLAK\n");
	}
	printf("\n");
}

void show_final_item_subset(trie_address root, int assoc_item_length, int min_support)
{
	int data_array[30], data_array_temp[30];
	int i;
	
	for(i=0; i<30; i++)
	{
		data_array[i] = i;
	}
	
	combination_for_final_subset(root, data_array, data_array_temp, 0, 29, 0, assoc_item_length, min_support);
}

void combination_for_final_subset(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_number, int threshold) 
{ 
    if (index == subset_element_number) 
    {
    	if (search_trie(root, data_array_temp, subset_element_number))
    	{
    		print_support_min_threshold_eliminated(root, data_array_temp, subset_element_number, threshold);
		}
        return; 
    } 
    for (int i=start; i<=end && end-i+1 >= subset_element_number-index; i++) 
    { 
        data_array_temp[index] = data_array[i]; 
        combination_for_final_subset(root, data_array, data_array_temp, i+1, end, index+1, subset_element_number, threshold); 
    } 
}

void print_support_min_threshold_eliminated(trie_address root, int data_array[], int length, int threshold)
{
	FILE *fp;
	trie_address temp;
	int i = 0;
	char produk[150][20];
	
	temp = search_trie_node(root, data_array, length);
	
	fp = fopen("produk30.txt", "r");
	while(!feof(fp)) 		//membaca 100 produk
	{
		fscanf(fp,"%s",produk[i]);
		i++;
	}
	fclose(fp);
	
	if(Support(temp)>=threshold) {
		printf("{");
		for(i=0; i<length;i++)
	    {
	    	if(i!=length-1)
	    		printf("%s ", produk[data_array[i]]);
	    	else
	    		printf("%s", produk[data_array[i]]);
		}			
		printf("}: Support = %d\n", Support(temp));
	}
}

void show_support_list_from_trie(trie_address root, int min_support, int *support_per_length)
{
	int data_array[30], data_array_temp[30];
	int i;
	
	for(i=0; i<30; i++)
	{
		data_array[i] = i;
	}
	
	for(i=0; i<5; i++)
	{
		combination_for_showing_support(root, data_array, data_array_temp, 0, 29, 0, i+1, min_support, support_per_length);
	}
}

void show_support_list_from_basket(trie_address root, basket bkt, int min_support, int *support_per_length)
{
	int i, j, k;
	int temp[5], temp_data[5];
	
	for(i=0; i<bkt.numOfProduk; i++)
	{
		show_support_list_from_transaction(root, bkt.Produk[i].barang, min_support, support_per_length);
	}
}

void show_support_list_from_transaction(trie_address root, List transaksi, int min_support, int *support_per_length)
{
	int count = NbElmt(transaksi); 
	int temp[count];
	int temp_data[count];
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
}

void combination_for_showing_support(trie_address root, int data_array[], int data_array_temp[], int start, int end, int index, int subset_element_number, int threshold, int *length) 
{
    if (index == subset_element_number) 
    {
    	//for(int i=0; i<subset_element_number; i++)
    	//	printf("%d ", data_array_temp[i]);
    	//printf("\n");
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
	int i = 0;
	FILE *fp;
	char produk[150][20];
	
	/*fp = fopen("produk30.txt", "r");
	while(!feof(fp)) 		//membaca 100 produk
	{
		fscanf(fp,"%s",produk[i]);
		i++;
	}
	fclose(fp);
	
	printf("{");
	for(i=0; i<length;i++)
    {
    	if(i!=length-1)
    		printf("%s, ", produk[data_array[i]]);
    	else
    		printf("%s", produk[data_array[i]]);
	}
	printf("} ");*/
	
	temp = search_trie_node(root, data_array, length);
	//printf(": Support = ");
		
	//printf("%d ", temp->support);
	if(temp->support >= threshold) {
		//printf("(PASSED) \n");
		supp_per_length[length-1] = supp_per_length[length-1] + 1;
	}
		//printf("(FAILED) \n");
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
	do
	{
		temp[i] = Info(P).index_produk;
		P = Next(P);
		i++;
	} while (P != Nil);
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
