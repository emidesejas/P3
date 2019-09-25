/*50884288*/

#include <stdio.h>
#include "include/utils.h"
#include "include/grafo.h"
#include "include/lista_pares.h"
#include "include/lista.h"
#include "include/cola.h"
#include "include/pila.h"

/* struct butterfly{
    nat id;
    butterfly *prev;
    butterfly *next;
};

typedef butterfly *ButterfliesList;

typedef struct edge_t{
    nat e1;
    nat e2;
    int value;
} Edge; */

bool consistenteMaximal(Grafo G);

int main(){
    nat n, m, e1, e2;
    char juicio;
    scanf("%d", &n);
    Grafo mariposas = crear_grafo(n);
    // Aqui darle calor a n
    scanf("%d", &m);
    // Aqui darle calor a m
    for(nat i = 0; i < m; i++){
        scanf("%d %d %c", &e1, &e2, &juicio);
        agregar_arista(e1, e2, int(juicio), mariposas);
    }

    printf("%s", consistenteMaximal(mariposas)?"Consistente":"No consistente"); //Esta linea consiste en decir si es consistente o no es consistente, porque sino, de que consistiria la tarea verdad?, es una inconsistencia maximal que esta tarea no consista en preguntar acerca de la consitencia de las mariposas. Espero que sus vidas sean consistentes y que el señor consistente los consista
    destruir_grafo(mariposas); //A.K.A. matar mariposas :(
}

void siguiente(bool explored[], nat max, nat &current);

bool consistenteMaximal(Grafo G) { // Quién dice que perder lógica no deja secuelas?
    //bool discovered[cantidad_vertices(G)];
    //nat aristas = cantidad_aristas(G);
    nat vertices = cantidad_vertices(G);
    //Edge Edges[aristas];
    bool label[vertices];
    bool explored[vertices];
    
    for(nat i = 0; i < vertices; i++){
        explored[i] = false;
    }

    nat current = 1;
    Cola elements = crear_cola();
    bool todoBien = true; //Lo usamos de flag para detectar cuando detener todos los juails

    while (current != 0 && todoBien) { //jeje current != 0
        encolar(current, elements);
        label[current - 1] = true;
        while(!es_vacia_cola(elements) && todoBien){
            nat verticeA = frente(elements);
            desencolar(elements);
            if (!explored[verticeA - 1]) {
                explored[verticeA - 1] = true;
                Lista_pares incidents = adyacentes(verticeA, G);
                while(!es_vacia_lista_pares(incidents) && todoBien){
                    Par_nat_int vertexB = primer_par(incidents);
                    if(explored[vertexB.id - 1]){
                        if(vertexB.valor == int('=')){
                            if(label[vertexB.id - 1] != label[verticeA - 1]){
                                todoBien = false;
                            }
                        } else {
                            if(label[vertexB.id - 1] == label[verticeA - 1]){
                                todoBien = false;
                            }
                        }
                    } else {
                        encolar(vertexB.id, elements);
                        if(vertexB.valor == int('=')){
                            label[vertexB.id - 1] = label[verticeA - 1];
                        } else {
                            label[vertexB.id - 1] = !label[verticeA - 1];
                        }
                    }
                    incidents = resto_pares(incidents);
                }
                //Esto es para que solo se actualice el valor de current cuando el while no hizo break
                /* if(!es_vacia_lista_pares(incidents)){
                    break; //Para que salga del while principal
                } */
            }
        }
        if (todoBien){
            siguiente(explored,vertices,current);
        }
    }
    destruir_cola(elements);
    //printf("%d\n", current);
    return !current;
}

/*
    Se fija si queda algun nodo sin explorar (basicamente buscar componentes conexas), si no queda nadie devuelve 0.
    El nat current se utiliza para empezar a buscar desde ese y asi no recorrer todos cada vez, se modifica el valor de current para seguir buscando desde ese en otra llamada de la funcion.
    Max debe ser el largo del array, si es n entonces el array es 0..n-1
*/
void siguiente(bool explored[], nat max, nat &current){ //repensar lo de usar current como parametro, arreglame los indices
    while(current <= max){
        if(!explored[current - 1]){
            break;
        } else {
            current++;
        }
    }

    if (current > max){
        current = 0;
    }
}