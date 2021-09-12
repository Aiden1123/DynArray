#include <stdio.h>
#include <stdlib.h>
#include "dynarray.h"
#define sep "\n/////////////////\n\n"

    //program to test dynarray.h library

int main() {            
    
    //dynarray library test

    dyn_array *array = new_array();
    
    for(int i=0;i<12;i++)
        add(array,rand()%21);
    
    //delete_index test
    print_array(array);
    delete_index(array,4);
    print_array(array);
    delete_index(array,10);
    print_array(array);
    delete_index(array,0);
    print_array(array);
    delete_index(array,420);
    print_array(array);
    delete_index(array,-420);
    print_array(array);
    printf(sep);

    //array_pop_last test
    printf("%d\n",array_pop_last(array));
    print_array(array);
    printf(sep);

    //find_in_array test
    printf("%d\n",find_in_array(array,8));
    printf("%d\n",find_in_array(array,27));
    printf(sep);
    
    //array_value test
    printf("%d\n",array_value(array,3));
    printf("%d\n",array_value(array,27));
    printf(sep);
    
    //delete_value test
    print_array(array);
    delete_value(array,12);
    print_array(array);
    printf(sep);
    
    //get_array_size test
    print_array(array);
    printf("%d \n",get_array_size(array));
    printf(sep);
    
    //delete_all_value test
    print_array(array);
    delete_all_value(array,19);
    print_array(array);
    printf(sep);

    //array_element_count test
    printf("%d\n", array_element_count(array,14));
    printf(sep);
    
    //copy_array and array_extend test
    dyn_array *other = copy_array(array);
    print_array(array);
    print_array(other);
    array_extend(array,other);
    print_array(array);
    print_array(other);
    delete_array(other);
    printf(sep); 
    
    //array_insert test
    print_array(array);
    array_insert(array,-4,69);
    array_insert(array,0,420);
    array_insert(array,3,324);
    array_insert(array,7,43);
    array_insert(array,15,1);
    print_array(array);
    printf(sep);

    //array_sort test
    array_sort(array);
    print_array(array);
    printf(sep);

    //array_reverse test
    array_reverse(array);
    print_array(array);
    printf(sep);

    //clear_array test
    clear_array(array);
    print_array(array);

    delete_array(array);
    
    
    return 0;

}
