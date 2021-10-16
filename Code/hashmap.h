#ifndef HASHMAP_H
#define HASHMAP_H

//includes from standart libs:
#include <stdint.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <math.h>


// Error cases
#define HASHMAP_SUCCESS         0       //No error
#define HASHMAP_OVERLOAD        1       //Hashmap is full
#define HASHMAP_INPUT_ERROR     2       //Could not insert element to hashmap
#define HASHMAP_OUTPUT_ERROR    3       //Could not extract element from hashmap
#define HASHMAP_CREATE_ERROR    4       //Could not create hashmap
#define HASHMAP_RESIZE_ERROR    5       //Could not resize hashmap

#define INITIAL_SIZE 8

//Definition of booleans
typedef int HASHMAP_BOOL;
#define HASHMAP_BOOL_TRUE    1
#define HASHMAP_BOOL_FALSE   0

//Hashmap element definition
typedef struct hashElement {

int key;
int data;
HASHMAP_BOOL entryUsed;

} hashElement;

//hashmap definition
typedef struct hashmap{

size_t max_size;
size_t current_size;
hashElement* hash_element;

} hashmap;

//Init function of the hashmap
int initHashmap(hashmap* hashmapPointer, size_t hashmapSize);

//Resize function for scaling the hashmap
hashmap* resizeHashmap(size_t hashMapSize, hashmap* hashMapPointer);

//Hash function
int getHashValue(int key, size_t hashMapSize);

//Fuction to insert (key, data) into a hashmap
int insertData(int key, int data, hashmap* hashMapPointer);

//Getting the data to a key of an entry in the hashmap
int getData(int key, hashmap* hashMapPointer);

//delete function
void deleteElement(int key, hashmap* hashMapPointer);

//destroy function
void destroyHashmap(hashmap* hashMapPointer);

//error handling function
void errorHandling(int error);

#endif