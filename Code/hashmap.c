#include "hashmap.h"

int initHashmap(hashmap* hm, size_t size)
{   int error;
    
    hashElement* hm_elements;

    hm_elements = (hashElement*) malloc(size * sizeof(hashElement));
    if(!hm_elements){
            error = HASHMAP_CREATE_ERROR;
    } else error = HASHMAP_SUCCESS;

    hm->current_size = 0;
    hm->max_size = size;
    hm->hash_element = hm_elements;

    return error;
}

hashmap* resizeHashmap(size_t size, hashmap* hm)
{
    int error = HASHMAP_SUCCESS;

    //counter for insertions into the buffer
    int insertionCounter = 0;
    size_t oldsize;

    int* keybuffer;
    keybuffer = (int*)malloc(hm->current_size * sizeof(int));
    
    int* databuffer;
    databuffer = (int*)malloc(hm->current_size * sizeof(int));
    
    //extract all keys and values of hashmap and store in buffer
    
    for (size_t i = 0; i < hm->max_size; i++) {
        
        if (hm->hash_element[i].entryUsed == HASHMAP_BOOL_TRUE){
            
            keybuffer[insertionCounter] = hm->hash_element[i].key;
            databuffer[insertionCounter] = hm->hash_element[i].data;

            //reset hashmap entries
            hm->hash_element[i].key = 0;
            hm->hash_element[i].data = 0;
            hm->hash_element[i].entryUsed = HASHMAP_BOOL_FALSE;

            insertionCounter++;
        }
    }

    //realloc hashmap to new size
    hm->hash_element = realloc(hm->hash_element, size * sizeof(hashElement));
    if(!hm) 
    {
        error = HASHMAP_RESIZE_ERROR;
        goto ResizeErr;

    } else error = HASHMAP_SUCCESS;

    //saving old size for reinsert
    oldsize = hm->current_size;

    hm->max_size = size;
    hm->current_size = 0;

    //rehash all keys and insert data to resized hashmap
    for (size_t i = 0; i < oldsize; i++) {
        error = insertData(keybuffer[i], databuffer[i], hm); 
        if(error != HASHMAP_SUCCESS) goto ResizeErr;
    }

    free(keybuffer);
    free(databuffer);
    return hm;

    ResizeErr: 
        errorHandling(error);
        free(keybuffer);
        free(databuffer);
        
}

int getHashValue(int key, size_t hm_size)
{   
    int hash;
    //diffrent hash functions
    
    //devisional methode
    hash = key % hm_size;

    //absolut value to prevent negativ outcome of modulo
    return abs(hash);
}

int insertData(int key, int data, hashmap* hm)
{   

    int hash;
    int error = HASHMAP_SUCCESS;
    
    if (hm->max_size == hm->current_size)
    {
        hm = resizeHashmap(hm->max_size *2, hm);
    }

    //getting hash value for given key
    hash = getHashValue(key, hm->max_size);

    //inserting data into hashmap
    //searching for free cell if hash is colliding
    if (hm->hash_element[hash].entryUsed == HASHMAP_BOOL_TRUE || (size_t)hash > hm->max_size){

        //hash collision happened; inserting at first free position

        //double key to do
        int newHash = 0;
        for (size_t i = 0; i < hm->max_size; i++){
            if (hm->hash_element[i].entryUsed == HASHMAP_BOOL_FALSE) newHash = i;
        }
        hm->hash_element[newHash].key = key;
        hm->hash_element[newHash].data = data;
        hm->hash_element[newHash].entryUsed = HASHMAP_BOOL_TRUE;
        hm->current_size++;

    } else {

        //no collision
        hm->hash_element[hash].key = key;
        hm->hash_element[hash].data = data;
        hm->hash_element[hash].entryUsed = HASHMAP_BOOL_TRUE;
        hm->current_size++;

    }
    
    return error;

}

int getData(int key, hashmap* hm)
{

    int error;
    int data = -1;
    
    int hash = getHashValue(key, hm->max_size);

    if (hm->hash_element[hash].key == key) {

        return hm->hash_element[hash].data;

    } else {
        
         //searching towards end of hashmap 
        for (size_t i = 0; i < hm->max_size; i++){
            
            if (hm->hash_element[i].key == key) {

                data = hm->hash_element[i].data;
                
            }
            
        }
        if (data != -1) return data;
            else {
                error = HASHMAP_OUTPUT_ERROR;
                goto OutputErr;
            }
    }

OutputErr:
    errorHandling(error);
    return -1;
}



void deleteElement(int key, hashmap* hm)
{
    int hash;

    hash = getHashValue(key, hm->max_size);

    if (hm->hash_element[hash].key != key){

        //searching towards end of hashmap 
        for (size_t i = 0; i < hm->max_size; i++){
            
            if (hm->hash_element[i].key == key) {

                hm->hash_element[i].key = 0;
                hm->hash_element[i].data = 0;
                hm->hash_element[i].entryUsed = HASHMAP_BOOL_FALSE;
                hm->current_size--;
            }
        }

    } else {

        //no collision
        hm->hash_element[hash].key = 0;
        hm->hash_element[hash].data = 0;
        hm->hash_element[hash].entryUsed = HASHMAP_BOOL_FALSE;
        hm->current_size--;

    }
    
    if (hm->current_size < hm->max_size / 4) hm = resizeHashmap(hm->max_size / 4, hm);
        
}

void destroyHashmap(hashmap* hm)
{   
    free(hm->hash_element);
}

void errorHandling(int error)
{
    switch (error)
    {
        case HASHMAP_SUCCESS: 
            printf("No errors occured!\n");
            break;
        case HASHMAP_OVERLOAD:
            printf("Error! Hashmap is full!\n"); 
            break;     
        case HASHMAP_INPUT_ERROR:  
            printf("Error! Could not insert element.\n"); 
            break;
         case HASHMAP_OUTPUT_ERROR: 
            printf("Error! Could not find or extract element.\n");
            break;
        case HASHMAP_CREATE_ERROR:
            printf("Error! Could not create hashmap.\n");
            break;
        case HASHMAP_RESIZE_ERROR: 
            printf("Error! Could not resize hashmap.\n");
            break;
    }
}

    