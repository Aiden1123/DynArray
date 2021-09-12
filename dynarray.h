#ifndef DYNARRAY
#define DYNARRAY
#endif

typedef struct array_info {                      //structure containing dynamic array
    int size;
    int* data;
} dyn_array;

dyn_array *new_array();                         //function that creates new array

void add(dyn_array *array,int num);            //function that adds int to the end of dynamic array

dyn_array *copy_array(dyn_array *array);            //function that creates a copy of an array
                                                    //new array doesn't refernece the old one

int array_element_count(dyn_array *array, int num);     //function that returns number of elements in the array equal to num

void array_extend(dyn_array *dest, dyn_array *src);     //function concatenates src array at the end of dest array

void array_insert(dyn_array *array, int index, int num);    //function that inserts num at specified index in array
                                                            //if index doesn't exist yet then all empty spaces are filled with 0
                                                            //and num is still placed at the desired index

void array_reverse(dyn_array *array);           //function that reverses array

int int_compare(const void *aa, const void *bb);    //auxilairy cmp function for sorting array

void array_sort(dyn_array* array);      //function that sorts array in ascending order

void print_array(dyn_array *array);     //function that prints array to console

void clear_array(dyn_array *array);         //function that removes all elements from array

void delete_array(dyn_array *array);        //function that deletes entire array structure

int find_in_array(dyn_array *array,int num);    //function that searches array for num

void delete_index(dyn_array *array, int index);         //function that deletes element with specified index

int array_pop_last(dyn_array *array);       //function that deletes last element and returns its value

int array_value(dyn_array *array, int index);           //function that returns value of element at desired index

void delete_value(dyn_array *array, int num);       //function that deletes first appearance of num in array

void delete_all_value(dyn_array *array, int num);       //function that deletes all appearances of num in array

int get_array_size(dyn_array *array);       //function that returns number of elements in array                                                   