#include <kv.h>
#include <stdlib.h>
#include <string.h>

#define TOMBSTONE 0x1

kv_t *kv_init(size_t capacity) 
{
    if(capacity == 0) return NULL;

    kv_t* table = malloc(sizeof(kv_t));
    if(table == NULL)
    {
        return NULL;
    }

    table->capacity = capacity;
    table->count = 0;

    table->entries = calloc(sizeof(kv_entry_t), capacity);
    if(table->entries == NULL)
    {
        return NULL;
    }

    return table;
}

size_t hash(char *val, int capacity)
{
    size_t hash = 0x13371337deadbeef;

    while(*val)
    {
        hash ^= *val;
        hash = hash << 8;
        hash += *val;

        val++;
    }

    return hash % capacity;
}

// fn kv+put
// params:
//  - db: a pointer to the db
//  - key: a pointer to the key value
//  - value: a pointer to the value itself
// returns:
//    returns -1: the index of the key, otherwise on error   
//    returns -2: on not found
int kv_put(kv_t *db, char *key, char *value)
{
    if(!db || !key || !value) return -1;

    size_t hsh = hash(key, db->capacity);
    for(int i = 0; i < db->capacity - 1; i++)
    {
        size_t real_idx = (hsh + i) % db->capacity;
        kv_entry_t *entry = &db->entries[real_idx];

        // The key is already set, updating
        if(entry->key &&
            entry->key != (void*)TOMBSTONE &&
            !strcmp(entry->key, key))
        {
            char *newVal = strdup(value);
            if(!newVal) return -1;
            entry->value = newVal;

            return real_idx;
        }

        // land in a slot that is "empty"
        // null or tombstone
        if(!entry->key || entry->key == (void*)TOMBSTONE)
        {
            char *newVal = strdup(value);
            char *newKey = strdup(key);
            if(!newVal | !newKey)
            {
                free(newKey);
                free(newVal);
                return -1;
            }
            entry->value = newVal;
            entry->key = newKey;
            db->count++;

            return real_idx;
        }

    }

    return -1;
}

char *kv_get(kv_t *db, const char *key)
{

}

