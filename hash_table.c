


#define HT_SIZE 1000

typedef struct HashTable {
    int max_count;
    int max_key;
    int** data;
} HashTable;


void ht_init_table(HashTable* ht) {
    int i;
    ht->data = (int**)malloc(HT_SIZE*sizeof(int*));

    for (i=0; i<HT_SIZE; i++) {
        ht->data[i] = (int*)malloc(sizeof(int))
    }
}

void ht_append(HashTable*, int) {

}

int ht_get_max_key(HashTable*) {

}

void ht_free_table(HashTable*) {

}
