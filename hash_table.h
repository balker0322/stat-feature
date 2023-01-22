
#define HT_SIZE 1000

typedef struct HashTable {
    int max_count;
    int max_key;
} HashTable;


void ht_init_table(HashTable*);
void ht_append(HashTable*, int);
int ht_get_max_key(HashTable*);
void ht_free_table(HashTable*);