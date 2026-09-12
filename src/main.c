#include <stdio.h>
#include <kv.h>

int main()
{
    kv_t* table = kv_init(3);

    printf("%p\n", table);
    printf("%ld\n", table->count);
    printf("%ld\n", table->capacity);

    kv_put(table, "hehe", "haha");
    kv_put(table, "hehe", "hoho");
    kv_put(table, "lala", "baba");

    char *val = kv_get(table, "hehe");
    char *val2 = kv_get(table, "lala");
    char *val3 = kv_get(table, "this_doesn't_exist");

    printf("%s %s %s\n",
        val,
        val2,
        val3
    );

    return 0;
}
