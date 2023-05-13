#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
 * HashTableItem - an item in a hashtable (also called a bucket)
 * @key: the key of that item
 * @value: the value under @key
 */
typedef struct HashTableItem {
    char *key;
    char *value;
}Ht_item;

/*
 * HashTable - our hash table data structure
 * @size: the size of the hash table
 * @count: how full the hash table is
 * @items: an array of pointers to hash table items
 */
typedef struct HashTable {
    size_t size;
    size_t count;
    Ht_item **items;
} HashTable;

static Ht_item *INITIALIZE_HASH_TABLE_ITEM(const char *key, const char *value)
{
    Ht_item *new_item = malloc(sizeof(Ht_item));
    if (new_item == NULL)
        return (NULL);
    new_item -> key = strdup(key);
    new_item -> value = strdup(value);
    return (new_item);
}

// for marking an item as deleted
static Ht_item DELETED_ITEM = {NULL, NULL};

/*
 * INITIALIZE_HASHTABLE - creates a new hash table data structure
 * Return: the created hash table or null on failure
 */
static HashTable *INITIALIZE_HASHTABLE()
{
    HashTable *new_hashtable = malloc(sizeof(HashTable));
    if (new_hashtable == NULL)
        return (NULL);
    new_hashtable -> size = 53;
    new_hashtable -> count = 0;
    new_hashtable -> items = calloc((size_t) new_hashtable->size, sizeof(Ht_item));
    return (new_hashtable);
}

/**
 * delte_ht_item - deletes a hash table item which frees the memory thus avoiding memory leaks
 * @item: the item to be deleted
*/
static void delete_ht_item(Ht_item *item)
{
    free(item -> key);
    free(item -> value);
    free(item);
}

/**
 * delte_hash_table - deletes a hash table structure which frees the memory thus avoiding leaks
 * @table: the table to be deleted
*/
static void delete_hash_table(HashTable *table)
{
    for (int i = 0; i < table->size; i++)
    {
        Ht_item *current = table->items[i];
        if (current != NULL){
            delete_ht_item(current);
        }
    }
    free(table -> items);
    free(table);
}

/**
 * hash - the hashing function
 * @a: a prime number larger than the size of the alphabet
 * We're hashing ASCII strings, which has an alphabet size of 128, so we should choose a prime larger than that.
 * @m: some upper limit, preferably the size of our hash table
 * Return: an integer value which will represent the index of an item in the hash table
 * Description: the function takes in a string input and returns a number 
 * between 0 and m (m can be our desired hash table length or bucket array length)
*/
static int hash(const char *key_string, const int a, const int m)
{
    long hash = 0;
    const int len_s = strlen(key_string);
    for (int i = 0; i < len_s; i++) {
        hash += (long)pow(a, len_s - (i+1)) * key_string[i];
        hash = hash % m;
    }
    return (int)hash;
}

/**
 * get_hash - method that tries to solve collision using double addressing
 * @key_string: the string we are getting hash value for
 * @num_buckets: fancy name for the length of our hash table
 * @attempt: number of collisions a string has run into
 * Return: the hash
 * Description: Double hashing makes use of two hash functions to 
 * calculate the index an item should be stored at after i collisions.
*/
static int get_hash(const char* key_string, const int num_buckets, const int attempt)
{
    const int hash_a = hash(key_string, 151, num_buckets);
    const int hash_b = hash(key_string, 151, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

/**
 * insert - inserts a key and a value (a bucket) to a given hash table
 * @table: the table to which we are inserting the key value pair
 * @key: the key of a bucket
 * @value: value associated to a certain bucket
*/
void insert(HashTable *table, const char *key, const char *value)
{
    // To insert a new key-value pair, we iterate through indexes until we find an empty bucket
    // We then insert the item into that bucket and increment the hash table's count attribute

    // initialize the item
    Ht_item *new_item = INITIALIZE_HASH_TABLE_ITEM(key, value);
    int index = get_hash(new_item->key, table->size, 0);
    // retrieve the item currently stored at the calculated index position
    Ht_item *current_item = table->items[index];
    // i is the number of collisions
    int i = 1;
    // loop that continues as long as there is a collision at the calculated index 
    // (i.e., an item already exists at that index)
    while(current_item != NULL && current_item != &DELETED_ITEM)
    {
        // recalculates the index by calling the ht_get_hash() function with an incremented value of i. 
        // This generates an alternative index to resolve the collision.
        index = get_hash(new_item->key, table->size, i);
        // Tries to retrieve an element to check if there is still a collision
        // if there is no collision, current_item should be NULL
        current_item = table->items[index];
        // if there is a collision, we increment i, i is the number of collisions witnessed so far
        i++;
    }
    table->items[index] = new_item;
    table->count++;
}

/**
 * search - tries to locate a value given a key
 * @table: the table from which we try to locate the value
 * @key: the key to use for searching
 * Return: the found value associated with key or NULL if no item is found
 * Description: Searching is similar to inserting, but at each iteration of the while loop, 
 * we check whether the item's key matches the key we're searching for. 
 * If it does, we return the item's value.
 *  If the while loop hits a NULL bucket, we return NULL, to indicate that no value was found.
*/
char *search(HashTable *table, const char *key)
{
    int index = get_hash(key, table->size, 0);
    Ht_item *item = table->items[index];
    int i = 1;
    while (item != NULL && item){
        if (item != &DELETED_ITEM){
            if(strcmp(item->key, key) == 0){
                return item->value;
            }
        }
        index = get_hash(key, table->size, i);
        item = table->items[index];
        i++;
    }
    return NULL;
}

// deleting logic
// Deleting from an open addressed hash table is more complicated than inserting or searching.
// The item we wish to delete may be part of a collision chain.
// Removing it from the table will break that chain, and will make finding items in the tail of the chain impossible.
// To solve this, instead of deleting the item, we simply mark it as deleted.
/*
    We mark an item as deleted by replacing it with a pointer to a 
    global sentinel item which represents that a bucket contains a deleted item.
*/

// Just set the key and the value of the item struct to NULL and NULL
// static Ht_item DELETED_ITEM = {NULL, NULL}; //moved to the top 

/**
 * delete - deletes an item from a hash table
 * @table: the table from which we are deleting from
 * @key: the key of the bucket to delete
*/
void delete(HashTable *table, const char *key)
{
    int index = get_hash(key, table->size, 0);
    Ht_item *item = table->items[index];
    int i = 1;
    while (item != NULL){
        // if the current item is not marked as deleted, then it is a valid candidate for comparison
        if (item != &DELETED_ITEM){
            if (strcmp(item->key, key) == 0){
                delete_ht_item(item);
                table->items[index] = &DELETED_ITEM;
            }
        }
        index = get_hash(key, table->size, i);
        item = table->items[index];
        i++;
    }
    table->count--;
}

int main()
{
    printf("Hash tables\n");
    HashTable *table = INITIALIZE_HASHTABLE();
    insert(table, "cat", "meows");
    insert(table, "tac", "weoms");
    insert(table, "dog", "barks");
    printf("A cat %s\n", search(table, "cat"));
    printf("A tac %s\n", search(table, "tac"));
    printf("A dog %s\n", search(table, "dog"));

    printf("cat: %d\n", hash("cat", 151, 53));
    printf("tac: %d\n", hash("cat", 151, 53));
    delete_hash_table(table);
    return (0);
}





