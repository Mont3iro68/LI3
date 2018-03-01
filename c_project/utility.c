#include <stdio.h>
#include "./headers/utility.h"

int word_byte_count(char* text, int *i){
    int w_b = 0;
    if(!text) return 0;
    char prevChar = text[0];

    while(text[*i]){
        if(text[*i] == ' ' || text[*i] == '\n' || text[*i] == '\t' || text[*i] == '\0'){
            if(prevChar != ' '){
                w_b++;
            }
        }
        prevChar = text[*i];
        (*i)++;
    }
    return w_b;
}

long get_first_digit(long id){

    while(id >= 10){
        id = id/10;
    }
    return id;
}

long max(long a, long b){
	return (a>b)? a : b;
}
