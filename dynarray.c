#include <stdio.h>
#include <stdlib.h>
#include "dynarray.h"

dyn_array *new_array() {                        //function that creates new array
    dyn_array* temp=malloc(sizeof(dyn_array));  //memory allocation for structure

    if(temp==NULL) {                            //handle mem errors
        printf("ERROR: cannot allocate memory\n");
        return NULL;
    }

    temp->size=0;                               //initialise variables
    temp->data=NULL;
    return temp;
}

void add(dyn_array *array,int num) {            //function that adds int to the end of dynamic array
    
    //case 1 - array is empty:
    if (array->data==NULL) {        
        
        array->data=malloc(sizeof(int));        //memory allocation for array
        
        if(array->data==NULL) {                 //handle mem errors
            printf("ERROR: cannot allocate memory\n");
            return;
        }

        *(array->data)=num;                     //add num
        array->size=1;
        return;
    }

    //case 2 - array is not emoty:
    int* aux;
    array->size+=1;                             //increase size
    aux=realloc(array->data,array->size*sizeof(int));   //reallocate mem fo rarray

    if(aux==NULL) {                             //handle mem errors
        printf("ERROR: cannot allocate memory\n");
        return;
    }

    array->data=aux;                            //add num
    array->data[array->size-1]=num;
    return;
}

void array_update_value(dyn_array *array, int index,int new_value) {
    
    if (array->size <= index || index < 0) {
        printf("ERROR: index out of bounds\n");
        return;
    }

    array->data[index] = new_value;
    return;
}

dyn_array *copy_array(dyn_array *array) {           //function that creates a copy of an array
                                                    //new array doesn't refernece the old one
    dyn_array* temp=malloc(sizeof(dyn_array));      //allocate memory for structure

    if(temp==NULL) {                                //handle mem errors
        printf("ERROR: cannot allocate memory\n");
        return NULL;
    }

    temp->size=array->size;                         //copy size
    
    if (array->size) {                              //if there are numbers to copy then:
        
        temp->data=malloc(array->size*sizeof(int));     //allocate memory for array
        
        if(temp->data==NULL) {                          //handle mem errors
            printf("ERROR: cannot allocate memory\n");
            return NULL;
        }
        
        for(int i=0;i<array->size;i++) {                //copy the array
            temp->data[i]=array->data[i];
        }
    }

    else {                                          //else initialise data as NULL
        temp->data=NULL;
    }

    return temp;
}

int array_element_count(dyn_array *array, int num) {    //function that returns number of elements in the array equal to num
    
    int count = 0;

    for(int i=0;i<array->size;i++) {
        if (array->data[i]==num) {
            count++;
        }
    }

    return count;
}

void array_extend(dyn_array *dest, dyn_array *src) {    //function concatenates src array at the end of dest array
    
    int* aux;

    //case 1 - dest already contains some ints:
    if (dest->data) {
        aux = realloc(dest->data, sizeof(int)*(dest->size+src->size));  //reallocate memory
        
        if(aux==NULL) {                                                 //handle mem errors
            printf("ERROR: cannot allocate memory\n");
            return;
        }

        dest->data=aux;                                         

        for(int i=dest->size;i<dest->size+src->size;i++) {              //add ints
            dest->data[i]=src->data[i-dest->size];
        }

        dest->size=dest->size+src->size;                                //increase size
        return;
    }

    //case 2 - only src contains data:
    if (src->data) {
        dest->size=src->size;                   //copy the size

        for(int i=0;i<dest->size;i++) {         //copy the data
            dest->data[i]=src->data[i];
        }
        return;
    }

    //case 3 - both dest and src are empty:
    return;
}

void array_insert(dyn_array *array, int index, int num) {   //function that inserts num at specified index in array
                                                            //if index doesn't exist yet then all empty spaces are filled with 0
                                                            //and num is still placed at the desired index
    int* aux;
    
    if (index<0) {                                          //make sure index is valid
        printf("ERROR: invalid index : %d\n", index);
        return;
    }

    if (index==array->size) {                               //if num is to be placed at the end then simply add it
        add(array,num);
        return;
    }
    if (index<array->size) {                                //if num is to be placed somewhere in the middle then
        array->size+=1;                                         //increase size
        aux = realloc(array->data, sizeof(int)*array->size);    //reallocate memory
        
        if(aux==NULL) {                                         //handle mem errors
            printf("ERROR: cannot allocate memory\n");
            return;
        }

        array->data=aux;

        for(int i=array->size-2;i>=index;i--)                   //move ints one place higher
            array->data[i+1]=array->data[i];

        array->data[index]=num;                                 //place num in desired index
        return;
    }

    while(array->size<index)    //if index doesn't exist yet
        add(array,0);               //filled missing spaces with 0
    add(array,num);             //add num at index
    return;
}

void array_reverse(dyn_array *array) {          //function that reverses array
    
    int aux;
    
    for(int i=0;i<array->size/2;i++) {
        aux = array->data[i];                           //swap array->data[i] with array->data[array->size-1-i]
        array->data[i] = array->data[array->size-1-i];
        array->data[array->size-1-i] = aux;
    }

    return;
}

int int_compare(const void *aa, const void *bb) {   //auxilairy cmp function for sorting array
    int *a = (int *) aa;
    int *b = (int *) bb;

    return *a-*b;
}

void array_sort(dyn_array* array) {     //function that sorts array in ascending order
    qsort(array->data,array->size,sizeof(int),int_compare);
    return;
}


void print_array(dyn_array *array) {    //function that prints array to console
    
    if (array->size==0) {
        printf("array empty\n");
        return;
    }

    for(int i=0;i<array->size;i++)
        printf("%d ",array->data[i]);
    printf("\n");
    return;
}



void clear_array(dyn_array *array) {        //function that removes all elements from array
    free(array->data);
    array->data=NULL;
    array->size=0;
    return;
}

void delete_array(dyn_array *array) {       //function that deletes entire array structure
    clear_array(array);
    free(array);
}

int find_in_array(dyn_array *array,int num) {   //function that searches array for num
                                                //returns index of first found num on success and -1 on failure
    for(int i=0;i<array->size;i++) {
        if (array->data[i]==num)
            return i;
    }
    return -1;
}

void delete_index(dyn_array *array, int index) {        //function that deletes element with specified index
    
    int *aux;

    if (index>=array->size || index<0) {                //make sure index is correct
        printf("illegal value of index: %d\n",index);
        return;
    }
    
    //case 1 - index is at the end of the array:
    if (array->size-1==index) {                         
        array->size-=1;                                         //decrease size
        aux=realloc(array->data,array->size*sizeof(int));       //reallocate memory

        if(aux==NULL) {                                         //handle mem errors
            printf("ERROR: cannot allocate memory\n");
            return;
        }

        array->data=aux;
        return;
    }

    //case 2 - index is inside the array:
    for(int i=index;i<array->size-1;i++) {      //move everything after index one place lower
        array->data[i]=array->data[i+1];
    }

    array->size-=1;                             //decrease size
    
    aux=realloc(array->data,array->size*sizeof(int));       //reallocate memory

    if(aux==NULL) {                                         //handle mem errors
        printf("ERROR: cannot allocate memory\n");
        return;
    }

    array->data=aux;
    return;
}

int array_pop_last(dyn_array *array) {      //function that deletes last element and returns its value
    
    int *aux;

    if (array->size==0) {       //if array is empty then returns 0
        return 0;
    }

    int temp=array->data[array->size-1];    //save the last element
    array->size-=1;                         //decrease size
    aux=realloc(array->data,array->size*sizeof(int));       //reallocate memory

    if(aux==NULL) {                                         //handle mem errors
        printf("ERROR: cannot allocate memory\n");
        return temp;
    }

    array->data=aux;
    return temp;
}

int array_value(dyn_array *array, int index) {          //function that returns value of element at desired index
    
    if (index>=array->size || index<0) {                //check if index is valid
        printf("illegal value of index: %d\n",index);
        return 0;
    }
    
    return array->data[index];
}

void delete_value(dyn_array *array, int num) {      //function that deletes first appearance of num in array
    int index = find_in_array(array,num);
    
    if (index==-1)              //return if num isn't present in array
        return;

    delete_index(array,index);
    return;
}

void delete_all_value(dyn_array *array, int num) {      //function that deletes all appearances of num in array
    int index = find_in_array(array,num);
    while(index!=-1) {                      //while num is present
        delete_index(array,index);
        index = find_in_array(array,num);
    }
    return;
}

int get_array_size(dyn_array *array) {      //function that returns number of elements in array
    return array->size;
}
