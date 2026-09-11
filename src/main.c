#include <stdio.h>
#include <kv.h>

int main()
{
    kv_t* table = kv_init(3);

    printf("%p\n", table);
    printf("%ld\n", table->count);
    printf("%ld\n", table->capacity);

    kv_put(table, "hehe", "haha");
    kv_put(table, "color", "blue");
    kv_put(table, "colour", "red");

    for(size_t i = 0; i < table->capacity; i++)
    {
        if(table->entries[i].key)
        {
            printf("[%ld] %s: %s\n",
                i,
                table->entries[i].key,
                table->entries[i].value);
            printf("size: %ld\n", table->count);
        }
    }

    return 0;
}
