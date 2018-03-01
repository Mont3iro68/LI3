#ifndef _utility_h_
#define _utility_h_

typedef int Boolean;
enum{false, true};

//Conta palavras
int word_byte_count(char* text, int *i);

//Obtem 1º digito para introduzir no AVL certa
long get_first_digit(long id);

//Obtem o maximo entre 2 longs
long max(long a, long b);

#endif