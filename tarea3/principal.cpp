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

struct nodoLista{
    int dato;
    nodoLista *sig;
};

typedef nodoLista *Lista;

struct nodo_texto{
    int largo;
    nodo_texto *siguiente;
    char palabra[MAX_LONG_PALABRA]; //[MAX_LONG_PALABRA]
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

void agregarNodoLista(Lista &l, int elem);

void destruirLista(Lista &l);

int primeroLista(Lista l);

void borrarPrimeroLista(Lista &l);

void imprimir(char *s);

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
        int *s[cantidad_de_palabras];
        for(int i = 0; i < cantidad_de_palabras; i++){
            s[i] = new int[cantidad_de_palabras - i];
        }

        cursor = fuente;
        texto cursorAd;
        

        //Cargamos los valores de S, desperdiciamos mucha memoria, en el futuro deberia usar otra estructura que no sea una matriz
        for(int i=0; i<cantidad_de_palabras; i++){ //tenia un -1 cantidad de palabras, I dont know why
            int Ci = cursor->largo;
            s[i][0] = L - Ci;
            cursorAd = cursor->siguiente;
            for(int j = 1; j < cantidad_de_palabras - i; j++){
                Ci = Ci + 1 + cursorAd ->largo; //el +1 es el espacio entre las palabras
                if(L >= Ci){
                    s[i][j] = L - Ci;
                } else {
                    s[i][j] = -1;
                }
                cursorAd = cursorAd -> siguiente;
            }
            cursor = cursor -> siguiente;
        }

        
        int opt[cantidad_de_palabras + 1];
        int indice_opt[cantidad_de_palabras + 1];
        opt[0] = 0;
        indice_opt[0] = 0;
        for(int i = 1; i <= cantidad_de_palabras; i++){
            int min = ( s[i-1][0] * s[i-1][0] ) + opt[i-1]; //tenemos que inciaizar con algo min, no es el primero, seria el ultimo valor calculado del for
            indice_opt[i] = i - 1;
            for(int j = 1; j < i; j++){
                if(s[j-1][i-j] != -1 && (s[j-1][i-j]*s[j-1][i-j]) + opt[j-1] <= min){
                    min = ( s[j-1][i-j] * s[j-1][i-j] ) + opt[j-1];
                    indice_opt[i] = j - 1; //Este es el j que nos sirve para i
                }
            }
            opt[i] = min;
        }


        
        Lista optimos = NULL;
        agregarNodoLista(optimos, cantidad_de_palabras);
        int i = indice_opt[cantidad_de_palabras]; //Arranca por el ultimo, queremos saber hasta donde imprimir en cada linea
        
        while(i > 0){ //Vamos hacia atras hasta llegar a 0
            agregarNodoLista(optimos, i);
            i = indice_opt[i];
            //printf("%d\n",i);
        }

        int actual = 0;
        cursor = fuente;
        
        while(actual < cantidad_de_palabras){
            int renglonActual = primeroLista(optimos);
            borrarPrimeroLista(optimos);
            while(actual < renglonActual - 1){
                printf("%s ", cursor -> palabra);
                cursor = cursor -> siguiente;
                actual++;
            }
            
            printf("%s\n", cursor -> palabra); //Necesitamos diferenciar el ultimo caso por el espacio y el enter
            cursor = cursor -> siguiente;
            actual++;
        }
        
        for(int i = 0; i < cantidad_de_palabras; i++){ //borrar la matriz
            delete[] s[i];
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

    cursor -> palabra[n] = '\0';
    cursor -> largo = n;
    cursor -> siguiente = NULL;
}

void agregarNodoLista(Lista &l, int elem){
    if(l == NULL){
        l = new nodoLista;
        l -> dato = elem;
        l -> sig =  NULL;
    } else {
        nodoLista *nuevo = new nodoLista;
        nuevo -> dato = elem;
        nuevo -> sig = l;
        l = nuevo;
    }
}

int primeroLista(Lista l){ //Se asume lista no vacia
    return l -> dato;
}

void borrarPrimeroLista(Lista &l){
    if(l != NULL){
        nodoLista *temp = l ->sig;
        delete l;
        l = temp;
    }
}

void destruirLista(Lista &l){
    if(l != NULL){
        if(l -> sig != NULL){
            destruirLista(l->sig);
        }
        delete l;
    }
}