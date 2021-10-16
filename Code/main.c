#include "hashmap.h"
#include <time.h>
#include <stdlib.h>

#define TEST_MAP_SIZE 100
#define TEST_ITER_SIZE 2000
#define UPPER_KEY 10000
#define LOWER_KEY -100

void printHM(hashmap* hm)
{   size_t hm_size = hm->max_size;
    printf("| Hash \t| Key\t| Data\t| Used\t|\n");
    printf("-------------------------------\n");
    for (size_t i = 0; i < hm_size; i++)
    {
        printf("| %ld \t| %d\t| %d\t| %d\t|\n", i, hm->hash_element[i].key, hm->hash_element[i].data, hm->hash_element[i].entryUsed);
        printf("-------------------------------\n");
    }
}

void fillHM(hashmap* hm, size_t iter, size_t number)
{
    srand(time(0));
    clock_t insertTime = clock();
    clock_t readTime;
    float totalreadtime = 0;
    for(size_t j = 0; j < iter; j++){
    for (size_t i = 0; i < number-1; i++)
    {
        int key = (rand() %
           (UPPER_KEY - LOWER_KEY + 1)) + LOWER_KEY;
        int data = rand();
        insertData(key, data, hm);
    }
    insertData(42, 42, hm);
    readTime = clock();
    getData(42, hm);
    totalreadtime = (clock() - readTime) /  CLOCKS_PER_SEC;
    destroyHashmap(hm);
    initHashmap(hm, 8);
    }
    float insertTimerTotal = (clock() - insertTime) /  CLOCKS_PER_SEC;
    
    printf("Anzahl Eingefügte Elemente: %ld, Anzahl Wiederholugen: %ld\n", number, iter);
    printf("Gesamte Einfügezeit: %f sec.\n", insertTimerTotal);
    printf("Gesamte Einfügezeit pro Wiederholung: %f sec.\n", insertTimerTotal/(float)iter);
    printf("Durchschnittliche Einfügezeit pro Element: %f sec.\n", (insertTimerTotal/(((float)iter)*(float)number)));
    printf("Durchschnittliche Lesezeit für ein Element: %f sec.\n", (totalreadtime/(((float)iter)*(float)number)));


}


int main(void)
{
    hashmap map;
    //init a hashmap of size 8
    initHashmap(&map , 8);

    fillHM(&map, TEST_ITER_SIZE, TEST_MAP_SIZE);

    //destroy hashmap
    destroyHashmap(&map);

    return 0;
}
