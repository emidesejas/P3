/*
    Programa principal.

    Lee desde la entrada estándar el largo máximo de linea y el nombre del archivo (incluye la ruta).
    Lee el contenido del archivo .
    Imprime en la salida estándar el texto del archivo de acuerdo a la especificación. 
    Se puede asumir :
        - La longitud del nombre del archivo no es mayor a 80. El archivo existe.
        - El largo máximo de linea no es mayor a 80.
        - La longitud de cada palabra del archivo no es mayor al largo máximo de línea
        - Los caracteres del archivo son ASCII estándar (no incluye tildes, 'ñ' , 'Ñ', '¡' , '¿')

    Laboratorio de Programación 3
    InCo-Fing-Udelar
*/

#include <stdio.h>

#define MAX_LONG_PALABRA 80
#define MAX_NOMBRE_ARCHIVO 80

struct nodo_texto{
    char palabra[MAX_LONG_PALABRA];
    int largo;
    nodo_texto *siguiente;
};

struct mejor_palabra{
    int indice;
    int valor;
};

struct info_palabra{
    int largo;
    char *palabra;
};

typedef nodo_texto* texto;

void procesar_palabra(texto &fuente, texto &cursor, char *palabra);

void borrar_texto(texto &fuente);

int main () {
    int L; // largo de la linea
    char nom_archivo[MAX_NOMBRE_ARCHIVO];
    scanf("%d  %s", &L,  nom_archivo) ;
    
    // Se debe  abrir el archivo en modo  lectura  ("r")
    // Las  referencias  al archivo  se  hacen  mediante  el descriptor 
    FILE  *descriptor  = fopen(nom_archivo, "r");
    char palabra[MAX_LONG_PALABRA];
    // leer las palabras

    // int res_ lectura;
    // c  permite comparar con el resultado de una asignación
    // while (( res_ lectura  = fscanf{descriptor, "%s",  palabra))   != EOF)  {
    
    texto fuente = NULL;
    texto cursor = fuente;
    int cantidad_de_palabras = 0;
    int  res_lectura  = fscanf(descriptor, "%s",  palabra);
    /* if(res_lectura != EOF){
        cantidad_de_palabras++;
    } */
    //printf("%s ",palabra);
    //procesar_palabra(fuente, cursor, palabra);
    
    while (res_lectura  != EOF) {
        // procesar palabra
        
        
        //printf("%s\n", palabra);
        procesar_palabra(fuente, cursor, palabra);
        cantidad_de_palabras++;
        res_lectura = fscanf(descriptor, "%s", palabra);
        //printf("%s \n", palabra);
        
    }

    //printf("%d\n", cantidad_de_palabras);
    if(cantidad_de_palabras){
        int i = 0;
        /* info_palabra info_palabras[cantidad_de_palabras];
        cursor = fuente;
        
        while(cursor != NULL){
            info_palabras[i].largo = cursor -> largo;

            info_palabras[i].palabra = cursor -> palabra; //NOT SURE, quiero el puntero del array palabra peeeero
            cursor = cursor -> siguiente;
        } */

        /* int opt[cantidad_de_palabras];
        opt[0] = 0; */

        mejor_palabra S[cantidad_de_palabras];
        cursor = fuente;
        i = 0;
        for(int i = 0; i<cantidad_de_palabras; i++){
            S[i].indice = i;
            S[i].valor = (L - (cursor -> largo))*(L - (cursor -> largo));
            cursor = cursor -> siguiente;
        }
        
        /* for(int i = 0; i < cantidad_de_palabras; i++){
            S[i].indice = i;
            S[i].valor = L - (info_palabras[i].largo);
        } */

        cursor = fuente;
        i = 0;
        int j = 0;
        while(cursor != NULL){
            int Ci = cursor -> largo;
            texto cursorAd = cursor -> siguiente;
            j = i + 1;
            while(cursorAd != NULL){
                Ci = Ci + 1 + cursorAd -> largo;
                if(L >= Ci){
                    if(S[i].valor > (L - Ci)*(L - Ci)){
                        S[i].valor = (L - Ci)*(L - Ci);
                        S[i].indice = j;
                    }
                } else {
                    break; //TURBINA, lo cambio despues, quiero que funcione
                }
                cursorAd = cursorAd -> siguiente;
                j++;
            }
            cursor = cursor -> siguiente;
            i++;
        }

        /* for(int i = 0; i < cantidad_de_palabras; i++){
            int Ci = info_palabras[i].largo; //Ci es el costo total de todas las palabras juntas, con los espacios
            for(int j = i + 1; j < cantidad_de_palabras; j++){ //La palabra i ya fue computada en el for anterior
                Ci = Ci + 1 + info_palabras[j].largo; //El +1 es el espacio en medio de las palabras, no se agrefa el espacio del final
                if(L >= Ci){
                    if(S[i].valor > L - Ci){
                        S[i].valor = L - Ci;
                        S[i].indice = j;
                    }
                } else {
                    break; //TURBINA, lo cambio despues, quiero que funcione
                }
                
            }
        } */

        cursor = fuente;
        i = 0;
        j = 0;
        while(cursor != NULL){
            printf("%s", cursor -> palabra);
            if(S[i].indice == j){
                printf("\n");
                i = j + 1;
                j = i;
            } else if(cursor -> siguiente != NULL) {
                printf(" ");
                j++;
            }
            cursor = cursor -> siguiente;
        }


    }

    borrar_texto(fuente);
    
    // Se debe cerrar el arhivo
    fclose(descriptor);
    // procesar palabras leidas e imprimir
}

void borrar_texto(texto &fuente){
    if(fuente != NULL){
        texto cursor = fuente -> siguiente;
        while (fuente != NULL){
            delete fuente;
            fuente = cursor;
            if (cursor != NULL){
                cursor = cursor -> siguiente;
            }
            
        }
    }
}

void procesar_palabra(texto &fuente, texto &cursor, char *palabra) {
    if(fuente == NULL){
        fuente = new nodo_texto;
        cursor = fuente;
    } else {
        cursor -> siguiente = new nodo_texto;
        cursor = cursor -> siguiente;
    }
    int n = 0;
    while (palabra[n] != '\0'){ //Medimos el largo de la palabra, en C todas las palabras terminan con el caracter especial \0
        cursor -> palabra[n] = palabra[n];
        n++;
    }
    cursor -> palabra[n + 1] = '\0';
    cursor -> largo = n;
    cursor -> siguiente = NULL;
}