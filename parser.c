#include "parser.h"

/*********************************/

void sintaxis(){
	int c_siguiente[] = {COMA, R_CORCHETE, R_LLAVE, '\0'};
	element(c_siguiente);
}


void element(int synchset[]){
    int c_primero[] = {L_CORCHETE,L_LLAVE,'\0'};
    int c_siguiente[] = {COMA,R_CORCHETE,R_LLAVE, '\0'};

    checkeo_entrada(c_primero, synchset);

    if(t.compLex == L_LLAVE)
        objeto(c_siguiente);
    else if(t.compLex == L_CORCHETE)
        array(c_siguiente);

    checkeo_entrada(c_siguiente, c_primero);
}

void array(int synchset[]){
	int c_primero[] = {L_CORCHETE, '\0'};
	int c_siguiente[] = {COMA, R_CORCHETE, R_LLAVE, '\0'};

	checkeo_entrada(c_primero, synchset);

	if (t.compLex == L_CORCHETE){
		matcheo(L_CORCHETE);
		array_(c_siguiente);
	}

	checkeo_entrada(c_siguiente, c_primero);

}

void array_(int synchset[]){
	int c_primero[] = {L_LLAVE, L_CORCHETE, R_CORCHETE, '\0'};

	int c_siguiente[] = {COMA, R_CORCHETE, R_LLAVE, L_CORCHETE, '\0'};

	checkeo_entrada(c_primero, synchset);

	if ((t.compLex == L_LLAVE) || (t.compLex == L_CORCHETE)){
		
		element_list(c_siguiente);
		matcheo(R_CORCHETE);
	}
	else if(t.compLex == R_CORCHETE){
		matcheo(R_CORCHETE);
		
	}

	checkeo_entrada(c_siguiente, c_primero);
}

void element_list(int synchset[]){
	int c_primero[] = {L_LLAVE, L_CORCHETE, '\0'};
	int c_siguiente[] = {R_CORCHETE, '\0'};

	checkeo_entrada(c_primero, synchset);

	if((t.compLex == L_LLAVE) || (t.compLex == L_CORCHETE)){
		element(c_siguiente);
		element_list_(c_siguiente);
	}

	checkeo_entrada(c_siguiente, c_primero);
}

void element_list_(int synchset[]){

	if(t.compLex == R_CORCHETE)
       return;

	int c_primero[] = {COMA,'\0'};
	int c_siguiente[] = {R_CORCHETE, '\0'};

	checkeo_entrada(c_primero, synchset);

	

	if (t.compLex == COMA){
		matcheo(COMA);
		element(c_siguiente);
		element_list_(c_siguiente);
	}

	checkeo_entrada(c_siguiente, c_primero);
}

void objeto(int synchset[]){
	int c_primero[] = {L_LLAVE, '\0'};
	int c_siguiente[] = {COMA, R_CORCHETE, R_LLAVE, '\0'};
	
	checkeo_entrada(c_primero, synchset);

	if (t.compLex == L_LLAVE) {
		matcheo(L_LLAVE);
		objeto_(c_siguiente);
	}
	
	checkeo_entrada(c_siguiente, c_primero);
}

void objeto_(int synchset[]){
	int c_primero[] = {STRING, R_LLAVE, '\0'};

	int c_siguiente[] = {COMA, R_CORCHETE, R_LLAVE, STRING, '\0'};

	checkeo_entrada(c_primero, synchset);

	if (t.compLex == STRING){
		atribut_list(synchset);
		matcheo(R_LLAVE);
	} else if (t.compLex == R_LLAVE){
		matcheo(R_LLAVE);
	}

	checkeo_entrada(c_siguiente, c_primero);
}

void atribut_list(int synchset[]){
	int c_primero[] = {STRING, '\0'};
	int c_siguiente[] = {R_LLAVE, '\0'};

	checkeo_entrada(c_primero, synchset);

	if (t.compLex == STRING){
		atributes(c_siguiente);
		atribut_list_(c_siguiente);
	}

	checkeo_entrada(c_siguiente, c_primero);

}

void atribut_list_(int synchset[]){

	if (t.compLex == R_LLAVE)
        return;

	int c_primero[] = {COMA, '\0'};
	int c_siguiente[] = {R_LLAVE, '\0'};

	checkeo_entrada(c_primero, synchset);


	if (t.compLex == COMA){
		matcheo(COMA);
		atributes(c_siguiente);
		atribut_list_(c_siguiente);
	}

	checkeo_entrada(c_siguiente, c_primero);
}

void atributes(int synchset[]){
	int c_primero[] = {STRING, '\0'};
	int c_siguiente[] = {COMA, R_LLAVE, '\0'};

	checkeo_entrada(c_primero, synchset);

	if (t.compLex == STRING){
		atribute_name(c_siguiente);
		matcheo(DOS_PUNTOS);
		atribute_value(c_siguiente);
	}

	checkeo_entrada(c_siguiente, c_primero);
}

void atribute_name(int synchset[]){
	int c_primero[] = {STRING, '\0'};
	int c_siguiente[] = {DOS_PUNTOS, '\0'};

	checkeo_entrada(c_primero, synchset);

	if (t.compLex == STRING)
		matcheo(STRING);

	checkeo_entrada(c_siguiente, c_primero);
}

void atribute_value(int synchset[]){
	int c_primero[] = {L_LLAVE, L_CORCHETE, STRING,
		NUMBER, PR_TRUE, PR_FALSE, PR_NULL, '\0'};
	int c_siguiente[] = {COMA, R_LLAVE, '\0'};

	checkeo_entrada(c_primero, synchset);

	if (t.compLex == L_LLAVE){
		element(c_siguiente);
	}
	else if (t.compLex == L_CORCHETE) {
		element(c_siguiente);
	}
	else if (t.compLex == STRING){
		matcheo(STRING);
	}
	else if (t.compLex == NUMBER){
		matcheo(NUMBER);
	}
	else if (t.compLex == PR_TRUE){
		matcheo(PR_TRUE);
	}
	else if (t.compLex == PR_FALSE){
		matcheo(PR_FALSE);
	}
	else if (t.compLex == PR_NULL){
		matcheo(PR_NULL);
	}

	checkeo_entrada(c_siguiente, c_primero);

}

void matcheo(int expectedToken){
    if(t.compLex == expectedToken)
        lexema();
}


void checkeo_entrada(int c_primero[], int c_siguiente[]){

    int indice1=0;
    if(t.compLex == EOF)
    	return;

    //entra cuando no hay errores
    while(c_primero[indice1] != '\0') 
    {
        if(t.compLex == c_primero[indice1])
            return;
        indice1++;
    }
 
 	indice1=0;    
    
    int synchset[]={1}; 
    
    while(c_primero[indice1] != '\0'){ 
        synchset[indice1] = c_primero[indice1];
        indice1++;
    }
    int indice2=0;

    while(c_siguiente[indice2] != '\0'){
        synchset[indice1] = c_siguiente[indice2];
        indice1++; 
        indice2++; 
    }

    escaneo(synchset);

}



void escaneo(int synch[]){
    errorSintactico();
	int indice1 = 0;
    while(t.compLex != synch[indice1] && t.compLex != EOF){   
        if (synch[indice1] == '\0'){
            lexema();
            indice1=0;        
        }
        indice1++;
    }
    
    lexema();
    return;    	   
}


void errorSintactico(){
	aceptado=0;
   	printf("\nError sintactico: Linea %d. Se encontro %s.\n", numLinea, t.lexema);
}


/*int main (int argc,char* args[]){
    if(argc > 1)
    {
        if (!(entrada=fopen(args[1],"rt")))
        {
            printf("Fuente no encontrada.\n");
            exit(1);
        }
        lexema();
        sintaxis();
        if(aceptado) printf("Analisis sintactico correcto de la fuente.\n");
        fclose(entrada);
    }else{
        printf("Debe pasar como parametro el path al archivo fuente.\n");
        exit(1);
    }

    return 0;
}*/
