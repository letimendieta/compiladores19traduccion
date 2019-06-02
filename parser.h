/*********** Inclusión de cabecera **************/

#include "lexer.c"
#define CANT_COMP_LEX 10

/**********************************

sintaxis -> element EOF
element -> objeto | array
array -> [ a'
a'-> element_list ] | ]

object -> { o'
o'-> atribute_list} | }

elemento_list -> element e'
e'->  ,element e' | epsilon

atribut_list -> atributes at'
at' -> ,atributes at' | epsilon

atributes -> atribute_name : atribute_value
atribute_name -> string
atribute_value -> element | string | number | true | false | null

***********************************/

/**Prototipos de funciones**/

void sintaxis();
void element(int []);
void array(int []);
void array_(int []);//corresponde al a' de la gramatica
void element_list(int []);
void element_list_(int []);//corresponde al e' de la gramatica
void objeto(int []);
void objeto_(int []);
void atributes(int []);
void atribut_list(int []);//corresponde al at' de la gramatica
void atribut_list_(int []);
void atribute_name(int []);
void atribute_value(int []);
int aceptado=1;

/**Funciones de control**/

void matcheo(int);
void checkeo_entrada(int [], int []);
void escaneo(int []);
void errorSintactico();
