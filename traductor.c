#include "traductor.h"


void sintaxis_trad(){
    element_trad();
}


void element_trad(){
    if(t.compLex == L_LLAVE){
        objeto_trad();
    }
    else if(t.compLex == L_CORCHETE){
        array_trad();
    }
}


void array_trad(){  
    if(t.compLex == L_CORCHETE){
        matcheo(L_CORCHETE);
        arrayP_trad();
    }
}


void arrayP_trad(){
    if(t.compLex == L_CORCHETE || t.compLex == L_LLAVE){
		fputs("\n",salida);
        imprimir_espacios();
		fputs("<item>\n",salida);
		espacios+=1;
        element_list_trad();
        matcheo(R_CORCHETE);
        imprimir_espacios();
		fputs("</item>\n",salida);
    }
    else if(t.compLex == R_CORCHETE){
		espacios-=1;
        matcheo(R_CORCHETE);
    }
}


void element_list_trad(){
    if(t.compLex == L_CORCHETE || t.compLex == L_LLAVE){
        element_trad();
        element_listP_trad();
        
    }
}


void element_listP_trad(){
    if(t.compLex == COMA){  
        matcheo(COMA);
		imprimir_espacios();
		fputs("</item>\n",salida);
		imprimir_espacios();
		fputs("<item>\n",salida);
		espacios+=1;
        element_trad();
        element_listP_trad();     
    }
}


void objeto_trad(){
    if(t.compLex == L_LLAVE){
        matcheo(L_LLAVE);
        objetoP_trad();
    }
}


void objetoP_trad(){
    if(t.compLex == STRING){
        atribute_list_trad();
        matcheo(R_LLAVE);

    }
    else if(t.compLex == R_LLAVE){
        matcheo(R_LLAVE);
    }
}


void atribute_list_trad(){
    if(t.compLex == STRING){
        atributes_trad();
        atribute_listP_trad();
    }
}


void atribute_listP_trad(){
    if (t.compLex == R_LLAVE){
        espacios-=1;
		return;
    }
    if(t.compLex == COMA){
        matcheo(COMA);
        atributes_trad();
        atribute_listP_trad();
    }
}


void atributes_trad(){
    if(t.compLex == STRING){
		imprimir_espacios();
        char lexema[TAMLEX];
        strcpy(lexema,t.lexema);
		fputs("<",salida);
        atribute_name_trad();
		fputs(">",salida);
        matcheo(DOS_PUNTOS);
        atribute_value_trad();
		fputs("</",salida);
        string_sin_comillas(lexema);
		fputs(">\n",salida);		
    }
}


void atribute_name_trad(){
    if(t.compLex == STRING){    
        string_sin_comillas(t.lexema);
        matcheo(STRING);
    }
}



void atribute_value_trad(){
    if(t.compLex == L_CORCHETE || t.compLex == L_LLAVE){
		espacios += 1;
        element_trad();
    }
    else if(t.compLex == STRING){
		fputs(t.lexema, salida);
        matcheo(STRING);
    }
    else if(t.compLex == NUMBER){
		fputs(t.lexema, salida);
        matcheo(NUMBER);
    }
    else if(t.compLex == PR_TRUE){
		fputs(t.lexema, salida);
        matcheo(PR_TRUE);
    }
    else if(t.compLex == PR_FALSE){
		fputs(t.lexema, salida);
        matcheo(PR_FALSE);
    }
    else if(t.compLex == PR_NULL){
		fputs(t.lexema, salida);
        matcheo(PR_NULL);
    }
}

void string_sin_comillas(char* cadena){
    char string[TAMLEX];
	char cad[TAMLEX] = "";
    strcpy(string,cadena);
    int i=1;
    while(string[i] != '"'){
		cad[i-1] = string[i];
        i++;
    }
	fputs(cad, salida);
}

void imprimir_espacios(){
    int i;
    for (i=1;i<=espacios;i++){
        fputs("\t", salida);
    }
}


int main (int argc,char* args[]){
    if(argc > 1)
    {
        if (!(entrada=fopen(args[1],"rt")))
        {
            printf("Fuente no encontrada.\n");
            exit(1);
        }
        lexema();
        sintaxis();
        if(aceptado){
            fclose(entrada);
            entrada=fopen(args[1],"rt");
			salida=(fopen("output.xml","w"));
            lexema();
            sintaxis_trad();
        }
		fclose(salida);
    }else{
        printf("Debe pasar como parametro el path al archivo fuente.\n");
        exit(1);
    }

    return 0;
}
