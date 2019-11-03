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

struct Lista{
    nodoLista *primero;
    nodoLista *ultimo;
};

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

struct nodoSlack{
    int ultimo;
    Lista elems;
};

typedef nodo_texto* texto;

void procesar_palabra(texto &fuente, texto &cursor, char *palabra);

void borrar_texto(texto &fuente);

void agrPrincipio(Lista &l, int elem);

void agrFinal(Lista &l, int elem);

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
        nodoSlack s[cantidad_de_palabras];
        for(int i = 0; i < cantidad_de_palabras; i++){
            s[i].elems.primero = s[i].elems.ultimo = NULL;
            s[i].ultimo = cantidad_de_palabras - 1;
        }

        cursor = fuente;
        texto cursorAd;
        

        //Cargamos los valores de S, desperdiciamos mucha memoria, en el futuro deberia usar otra estructura que no sea una matriz
        for(int i=0; i<cantidad_de_palabras; i++){ //tenia un -1 cantidad de palabras, I dont know why
            int Ci = cursor -> largo;
            agrPrincipio(s[i].elems, L - Ci);
            s[i].ultimo = i;
            cursorAd = cursor->siguiente;
            int j = 1;
            while(j < cantidad_de_palabras - i){
                Ci = Ci + 1 + cursorAd -> largo; //el +1 es el espacio entre las palabras
                if(L >= Ci){
                    agrFinal(s[i].elems, L - Ci);
                    s[i].ultimo = j + i;
                } else {
                    s[i].ultimo = i + j-1; //en realidad seria j-1 pero como estan corridos
                    break; //no queremos seguir cuando encontremos a uno que no sirve
                }
                cursorAd = cursorAd -> siguiente;
                j++;
            }

            /* for(int j = 1; j < cantidad_de_palabras - i && j < L/2; j++){ //CAMBIAR POR EL WHILE QUE TENGA COMO CONDICION QUE ULTIMO SEA DISTINTO DEL I
                Ci = Ci + 1 + cursorAd ->largo; //el +1 es el espacio entre las palabras
                if(L >= Ci){
                    agrFinal(s[i].elems, L - Ci);
                } else {
                    s[i].ultimo = j; //en realidad seria j-1 pero como estan corridos
                }
                cursorAd = cursorAd -> siguiente;
            } */
            cursor = cursor -> siguiente;
        }

        
        int opt[cantidad_de_palabras + 1];
        int indice_opt[cantidad_de_palabras + 1];
        opt[0] = 0;
        indice_opt[0] = 0;
        for(int i = 1; i <= cantidad_de_palabras; i++){ 
            int min = ( primeroLista(s[i - 1].elems) * primeroLista(s[i - 1].elems) ) + opt[i-1]; //tenemos que incializar con algo min, no es el primero, seria el ultimo valor calculado del for
            borrarPrimeroLista(s[i-1].elems);
            indice_opt[i] = i - 1;
            for(int j = 1; j < i; j++){
                if( s[j - 1].ultimo >= i - 1  && ( primeroLista(s[j - 1].elems) * primeroLista(s[j - 1].elems) ) + opt[j-1] <= min){
                    min = ( primeroLista(s[j - 1].elems) * primeroLista(s[j - 1].elems) ) + opt[j-1];
                    indice_opt[i] = j - 1; //Este es el j que nos sirve para i
                    borrarPrimeroLista(s[j - 1].elems);
                } else if(s[j - 1].ultimo >= i) { //Si no se cumple esta condicion entonces el j t que tamos mirando no esta en la lista del i
                    borrarPrimeroLista(s[j - 1].elems);
                }
            }
            opt[i] = min;
        }

        Lista optimos;
        optimos.primero = optimos.ultimo = NULL;
        agrPrincipio(optimos, cantidad_de_palabras);
        int i = indice_opt[cantidad_de_palabras]; //Arranca por el ultimo, queremos saber hasta donde imprimir en cada linea
        
        while(i > 0){ //Vamos hacia atras hasta llegar a 0
            agrPrincipio(optimos, i);
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
            destruirLista(s[i].elems);
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

void agrPrincipio(Lista &l, int elem){
    if(l.primero == NULL){
        l.primero = new nodoLista;
        l.primero -> dato = elem;
        l.primero -> sig =  NULL;
        l.ultimo = l.primero;
    } else {
        nodoLista *nuevo = new nodoLista;
        nuevo -> dato = elem;
        nuevo -> sig = l.primero;
        l.primero = nuevo;
    }
}

void agrFinal(Lista &l, int elem){
    if(l.primero == NULL){
        l.primero = new nodoLista;
        l.primero -> dato = elem;
        l.primero -> sig =  NULL;
        l.ultimo = l.primero;
    } else {
        nodoLista *nuevo = new nodoLista;
        nuevo -> dato = elem;
        nuevo -> sig = NULL;
        l.ultimo -> sig = nuevo;
        l.ultimo = nuevo;
    }
}

int primeroLista(Lista l){ //Se asume lista no vacia
    return l.primero -> dato;
}

void borrarPrimeroLista(Lista &l){
    if(l.primero != NULL){
        
        if(l.primero == l.ultimo){
            delete l.primero;
            l.primero = NULL;
            l.ultimo = NULL;
        } else {
            nodoLista *temp = l.primero ->sig;
            delete l.primero;
            l.primero = temp;        
        }
    }
}

void destruirNodo(nodoLista *l){
    if(l != NULL){
        if(l -> sig != NULL){
            destruirNodo(l->sig);
        }
        delete l;
    }
}

void destruirLista(Lista &l){
    destruirNodo(l.primero);
}

