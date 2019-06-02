#include "parser.c"

/*************
sintaxis_trad -> element.trad
element.trad -> object.trad | array.trad

array.trad -> a'.trad 
a'.trad -> <item> element_list.trad </item> | ε

element_list.trad -> element.trad e'.trad 
e'.trad -> </item> <item> element.trad e'.trad | ε

object.trad -> o'.trad 
o'.trad -> atribute_list.trad | ε

atribute_list.trad -> atributes.trad 
at'.trad ->atributes.trad at'.trad | ε

atributes.trad -> <atribute_name.trad> atribute_value.trad </atribute_name.trad>
atribute_name.trad -> string.trad_sin_comilla
atribute_value.trad -> element.trad | string | number | true | false | null
************/


/*Prototipos de funciones**/

void sintaxis_trad();
void element_trad();
void array_trad();
void arrayP_trad();//Corresponder al a' de la gramatica
void element_list_trad();
void element_listP_trad();//Corresponder al e' de la gramatica
void objeto_trad();
void objetoP_trad();//Corresponder al o' de la gramatica
void atributes_trad();
void atribute_list_trad();
void atribute_listP_trad();//Corresponder al at' de la gramatica
void atribute_name_trad();
void atribute_value_trad();
int espacios=0;

/**Funcion auxiliar**/

void string_sin_comillas(char* );
void imprimir_espacios();
