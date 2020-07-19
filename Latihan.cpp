#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// The number of children for each node
// We will construct a N-ary tree and make it
// a Trie
// Since we have 26 english letters, we need
// 26 children per node
#define N 100
 
typedef struct TrieNode TrieNode;
 
struct TrieNode {
    // The Trie Node Structure
    // Each node has N children, starting from the root
    // and a flag to check if it's a leaf node
    int data; // Storing for printing purposes only
    TrieNode* children[N];
    int support;
};
 
TrieNode* make_trienode(int data) {
    // Allocate memory for a TrieNode
    TrieNode* node = (TrieNode*) calloc (1, sizeof(TrieNode));
    for (int i=0; i<N; i++)
        node->children[i] = NULL;
    node->support = 0;
    node->data = data;
    return node;
}
 
void free_trienode(TrieNode* node) {
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
 
TrieNode* insert_trie(TrieNode* root, int* word, int length) {
    // Inserts the word onto the Trie
    // ASSUMPTION: The word only has lower case characters
    TrieNode* temp = root;
 
    for (int i=0; i<length; i++) {
        // Get the relative position in the alphabet list
        int idx = word[i];
        if (temp->children[idx] == NULL) {
            // If the corresponding child doesn't exist,
            // simply create that child!
            temp->children[idx] = make_trienode(word[i]);
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
 
int search_trie(TrieNode* root, int* word, int length)
{
    // Searches for word in the Trie
    TrieNode* temp = root;
 
    for(int i=0; i<length; i++)
    {
        int position = word[i];
        if (temp->children[position] == NULL)
            return 0;
        temp = temp->children[position];
    }
    if (temp != NULL)
        return 1;
    return 0;
}

TrieNode* search_trie_node(TrieNode* root, int* word, int length)
{
    // Searches for word in the Trie
    TrieNode* temp = root;
 
    for(int i=0; i<length; i++)
    {
        int position = word[i];
        if (temp->children[position] == NULL)
            return NULL;
        temp = temp->children[position];
    }
    if (temp != NULL)
        return temp;
    return NULL;
}
 
void print_trie(TrieNode* root) {
    // Prints the nodes of the trie
    if (!root)
        return;
    TrieNode* temp = root;
    printf("%d -> ", temp->data);
    for (int i=0; i<N; i++) {
        print_trie(temp->children[i]); 
    }
}
 
void print_search(TrieNode* root, int* word, int length) {
    int i;
    
	printf("Searching for [");
    for(i=0; i<length;i++)
    {
    	if(i!=length-1)
    		printf("%d, ", word[i]);
    	else
    		printf("%d", word[i]);
	}
	printf("] : ");
    if (search_trie(root, word, length) == 0)
        printf("Not Found\n");
    else
        printf("Found!\n");
}

void print_support(TrieNode* root, int* word, int length) {
	TrieNode* temp;
	int i;
	
	printf("|");
	for(i=0; i<length;i++)
    {
    	if(i!=length-1)
    		printf("%d ", word[i]);
    	else
    		printf("%d", word[i]);
	}
	
	temp = search_trie_node(root, word, length);
	if(length < 4)
		printf("\t\t\t");
	else if(length < 6)
		printf("\t\t");
		
	printf("|%d\t|\n", temp->support);
}

void print_support_min_threshold(TrieNode* root, int* word, int length, int threshold, int *supp_per_length) {
	TrieNode* temp;
	int i;
	
	printf("|");
	for(i=0; i<length;i++)
    {
    	if(i!=length-1)
    		printf("%d ", word[i]);
    	else
    		printf("%d", word[i]);
	}
	
	temp = search_trie_node(root, word, length);
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

void print_support_min_threshold_eliminated(TrieNode* root, int* word, int length, int threshold) {
	TrieNode* temp;
	int i;
	temp = search_trie_node(root, word, length);
	
	if(temp->support>=threshold) {
		printf("|");
		
		for(i=0; i<length;i++)
	    {
	    	if(i!=length-1)
	    		printf("%d ", word[i]);
	    	else
	    		printf("%d", word[i]);
		}
		
		if(length < 4)
			printf("\t\t\t");
		else if(length < 6)
			printf("\t\t");
			
		printf("|%d\t|\n", temp->support);
	}
}

void print_confidence(TrieNode* root, int subset[], int itemset[], int sub_length, int item_length, int min_confidence)
{
	TrieNode *itemset_temp, *subset_temp;
	int i;
	float confidence;
	
	itemset_temp = search_trie_node(root, itemset, item_length);
	subset_temp = search_trie_node(root, subset, sub_length);
	confidence = ((float)itemset_temp->support/(float)subset_temp->support)*100;
	
	printf("Confidence = support{");
	for(i=0;i<item_length;i++)
	{
		if(i!=item_length-1)
			printf("%d, ", itemset[i]);
		else
			printf("%d", itemset[i]);
	}
	printf("}/support{");
	for(i=0;i<sub_length;i++)
	{
		if(i!=sub_length-1)
			printf("%d, ", subset[i]);
		else
			printf("%d", subset[i]);
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

void print_subset(TrieNode* root, int arr[], int data[], int start, int end, int index, int r, int length, int min_confidence)
{
	bool ketemu;
	if (index == r) 
    { 
    	printf("Rule {");
        for (int j=0; j<r; j++) 
        {
        	if(j!=r-1)
        		printf("%d ", data[j]);
        	else
        		printf("%d", data[j]);
		}
        printf("} -> {{");
        for (int j=0; j<length; j++) 
        {
        	if(j!=length-1)
        		printf("%d ", arr[j]);
        	else
        		printf("%d", arr[j]);
		}
		printf("} - {");
		for (int j=0; j<r; j++) 
        {
        	if(j!=r-1)
        		printf("%d ", data[j]);
        	else
        		printf("%d", data[j]);
		}
		printf("}} berarti jika seseorang membeli ");
		for (int j=0; j<r; j++) 
        {
        	if (j<r-2)
        		printf("%d, ", data[j]);
        	else if(j==r-2)
        		printf("%d dan ", data[j]);
        	else if(j==r-1)
        		printf("%d", data[j]);
		}
		printf(", maka dia akan membeli ");
		for (int j=0; j<length; j++) 
        {
        	ketemu = false;
        	for (int k=0; k<r; k++)
        	{
        		if(arr[j]==data[k])
	        	{
	        		ketemu = true;
				}
			}
			if(!ketemu)
			{
				printf("%d ", arr[j]);
			}
		}
		printf("juga\n");
		print_confidence(root, data, arr, r, length, min_confidence);
        return; 
    } 
    for (int i=start; i<=end && end-i+1 >= r-index; i++) 
    { 
        data[index] = arr[i]; 
        print_subset(root, arr, data, i+1, end, index+1, r, length, min_confidence); 
    } 
}

void print_last_for_assoc_rule(TrieNode* root, int* word, int length, int threshold, int min_confidence) {
	TrieNode* temp;
	int array[length];
	int temporary[5];
	int i;
	temp = search_trie_node(root, word, length);
	
	if(temp->support>=threshold) {
		printf("Subset untuk itemset {");
		for(i=0; i<length;i++)
	    {
	    	if(i!=length-1)
	    		printf("%d ", word[i]);
	    	else
	    		printf("%d", word[i]);
	    	array[i] = word[i];
		}
		printf("}: \n");
		for(i=0; i<length-1;i++)
			print_subset(root, array, temporary, 0, length-1, 0, i+1, length, min_confidence);
		printf("\n");
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

void doCombination(TrieNode* root, int arr[], int data[], int start, int end, int index, int r) 
{ 
    if (index == r) 
    { 
        //for (int j=0; j<r; j++) 
        //    printf("%d ", data[j]);
        root = insert_trie(root, data, r);
        return; 
    } 
    for (int i=start; i<=end && end-i+1 >= r-index; i++) 
    { 
        data[index] = arr[i]; 
        doCombination(root, arr, data, i+1, end, index+1, r); 
    } 
}

void doPrintCombination(TrieNode* root, int arr[], int data[], int start, int end, int index, int r) 
{ 
    if (index == r) 
    {
    	if (search_trie(root, data, r) == 1)
    	{
    		print_support(root, data, r);
		}
        return; 
    } 
    for (int i=start; i<=end && end-i+1 >= r-index; i++) 
    { 
        data[index] = arr[i]; 
        doPrintCombination(root, arr, data, i+1, end, index+1, r); 
    } 
}

void doFinalPrintCombination(TrieNode* root, int arr[], int data[], int start, int end, int index, int r, int threshold) 
{ 
    if (index == r) 
    {
    	if (search_trie(root, data, r) == 1)
    	{
    		print_support_min_threshold_eliminated(root, data, r, threshold);
		}
        return; 
    } 
    for (int i=start; i<=end && end-i+1 >= r-index; i++) 
    { 
        data[index] = arr[i]; 
        doFinalPrintCombination(root, arr, data, i+1, end, index+1, r, threshold); 
    } 
}

void doThresholdCombination(TrieNode* root, int arr[], int data[], int start, int end, int index, int r, int threshold, int *length) 
{ 
    if (index == r) 
    {
    	if (search_trie(root, data, r) == 1)
    	{
    		print_support_min_threshold(root, data, r, threshold, length);
		}
        return; 
    } 
    for (int i=start; i<=end && end-i+1 >= r-index; i++) 
    { 
        data[index] = arr[i]; 
        doThresholdCombination(root, arr, data, i+1, end, index+1, r, threshold, length); 
    } 
}

void doSupportCombination(TrieNode* root, int arr[], int data[], int start, int end, int index, int r) 
{
	TrieNode *temp;
    if (index == r) 
    {
    	temp = search_trie_node(root, data, r);
    	if (temp != NULL)
    	{
    		temp->support++;
		}
        return; 
    } 
    for (int i=start; i<=end && end-i+1 >= r-index; i++) 
    { 
        data[index] = arr[i]; 
        doSupportCombination(root, arr, data, i+1, end, index+1, r); 
    } 
}

void findAssociationRule(TrieNode* root, int arr[], int data[], int start, int end, int index, int r, int threshold, int min_confidence) 
{ 
    if (index == r) 
    {
    	if (search_trie(root, data, r) == 1)
    	{
    		print_last_for_assoc_rule(root, data, r, threshold, min_confidence);
		}
        return; 
    } 
    for (int i=start; i<=end && end-i+1 >= r-index; i++) 
    { 
        data[index] = arr[i]; 
        findAssociationRule(root, arr, data, i+1, end, index+1, r, threshold, min_confidence); 
    } 
}
 
int main() {
	//min support
	int min_support = 2;
	int association_itemset_length;
	int min_confidence = 60;
	
    // Driver program for the Trie Data Structure Operations
    int a[5];
    int support_per_length[5] = {0};
    
    //Simulasi Transaksi
    int a1[3] = {1,3,4};
    int a2[3] = {2,3,5};
    int a3[4] = {1,2,3,5};
    int a4[1] = {2};
    int a5[3] = {1,3,5};
    
    int temp[5];
    int b[2] = {2, 4};
    int c[2] = {2, 5};
    int i;
    for(i=0;i<5;i++)
    	a[i] = i+1;
    TrieNode* root = make_trienode('\0');
    for(i=0; i<5; i++)
    {
    	doCombination(root, a, temp, 0, 4, 0, i+1);
	}
	
	for(i=0; i<3; i++)
	{
		doSupportCombination(root, a1, temp, 0, 2, 0, i+1);
	}
	for(i=0; i<3; i++)
	{
		doSupportCombination(root, a2, temp, 0, 2, 0, i+1);
	}
	for(i=0; i<4; i++)
	{
		doSupportCombination(root, a3, temp, 0, 3, 0, i+1);
	}
	for(i=0; i<1; i++)
	{
		doSupportCombination(root, a4, temp, 0, 0, 0, i+1);
	}
	for(i=0; i<3; i++)
	{
		doSupportCombination(root, a5, temp, 0, 2, 0, i+1);
	}
		
	printf("---------------------------------\n");
	printf("| Itemset\t\t| Supp\t|\n");
	printf("---------------------------------\n");
	for(i=0; i<5; i++)
    {
    	doPrintCombination(root, a, temp, 0, 4, 0, i+1);
	}
	printf("---------------------------------\n");
	
	printf("---------------------------------\n");
	printf("| Itemset\t\t| Supp\t|\n");
	printf("---------------------------------\n");
	for(i=0; i<5; i++)
    {
    	doThresholdCombination(root, a, temp, 0, 4, 0, i+1, min_support, support_per_length);
	}
	printf("---------------------------------\n");
	for(i=0; i<5; i++)
		printf("Total passed on length %d: %d\n", i+1, support_per_length[i]);
	for(i=0; i<5; i++)
	{
		if(support_per_length[i] > 0)
			association_itemset_length = i+1;
	}
	printf("Panjang subset yang dijadikan association rules: %d\n", association_itemset_length);
	printf("\nFinal Subset for Association Rules:\n");
	printf("---------------------------------\n");
	printf("| Itemset\t\t| Supp\t|\n");
	printf("---------------------------------\n");
	doFinalPrintCombination(root, a, temp, 0, 4, 0, association_itemset_length, min_support);
	printf("---------------------------------\n");
	printf("\n");
	printf("Pencarian Association Rules: \n");
	printf("----------------------------\n");
	findAssociationRule(root, a, temp, 0, 4, 0, association_itemset_length, min_support, min_confidence);
    //free_trienode(root);
    return 0;
}