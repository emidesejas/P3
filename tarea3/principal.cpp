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
    
    int  res_lectura  = fscanf(descriptor, "%s",  palabra);
    while (res_lectura  != EOF ) {
        // procesar palabra
        res_lectura = fscanf(descriptor, "%s", palabra);
    }

    // Se debe cerrar el arhivo
    fclose(descriptor);
    // procesar palabras leidas e imprimir
}