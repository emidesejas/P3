/*50884288*/

#include <stdio.h>
#include "include/utils.h"
#include "include/grafo.h"
#include "include/lista_pares.h"
#include "include/lista.h"
#include "include/cola.h"
#include "include/pila.h"

struct butterfly{
    nat id;
    butterfly *prev;
    butterfly *next;
};

typedef butterfly *ButterfliesList;

struct Edges{ //How to make a useful structure out of useless structures Part I
    Pila first;
    Lista_pares second;
};

bool consistenteMaximal(Grafo G);

void killButterfly(nat id, ButterfliesList *Array, ButterfliesList &List);

bool alreadyChecked(nat node, ButterfliesList *Array);

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
        // Aqui darle calor a e1, e2 y juicio, juira cucha
    }

    //bool resultado;

    //resultado = algo jejejejejeje

    printf("%s", consistenteMaximal(mariposas)?"Consitente":"No consistente"); //Esta linea consiste en decir si es consistente o no es consistente, porque sino, de que consistiria la tarea verdad?, es una inconsistencia maximal que esta tarea no consista en preguntar acerca de la consitencia de las mariposas. Espero que sus vidas sean consistentes y que el señor consistente los consista
    destruir_grafo(mariposas); //A.K.A. matar mariposas :(
}

bool consistenteMaximal(Grafo G) { // Quién dice que perder lógica no deja secuelas?
    //bool discovered[cantidad_vertices(G)];
    bool label[cantidad_vertices(G)];
    ButterfliesList Butterflies[cantidad_vertices(G)];
    ButterfliesList auxList = new butterfly();
    auxList -> id = 1;
    auxList -> next = NULL;
    auxList -> prev = NULL;
    //discovered[0] = false;

    Butterflies[0] = auxList;
    ButterfliesList cursor = auxList;
    for(nat i = 2; i <= cantidad_vertices(G); i++) { //ATENTO ACAAAA
        //discovered[i] = false;
        cursor -> next = new butterfly();
        cursor -> next -> prev = cursor;
        cursor = cursor -> next;
        cursor -> id = i;
        Butterflies[i - 1] = cursor;
    }
    cursor -> next = NULL;

    //JMMM DUDOSO TODO ESTO ^^^^^^^


    //bfsLevels levels = new level;
    //levels -> id = 0; // No es necesario, se borrará en futuras versiones (es el numero del nivel)
    //levels -> elements = crear_cola();
    //encolar(0, levels -> elements);
    Cola elements = crear_cola();
    //encolar(0, elements);
    //killButterfly(0, Butterflies, auxList);

    Edges graph;
    graph.first = crear_pila();
    graph.second = crear_lista_pares();


    while(auxList != NULL){
        encolar(auxList -> id, elements);
        label[auxList -> id - 1] = true;
        while(!es_vacia_cola(elements)){
            nat vertexA = frente(elements);
            Lista_pares incidents = adyacentes(vertexA, G);
            
            /* while(!es_vacia_lista_pares(incidents)){
                printf("%d %d\n", vertexA, primer_par(incidents).id);
                incidents = resto_pares(incidents); //Por alguna razon hay guardado un 0 y un 2 aca
            } */

            //discovered[vertexA] = true;
            killButterfly(vertexA, Butterflies, auxList); //I'm in love with Visual Studio Code

            while(!es_vacia_lista_pares(incidents)){
                Par_nat_int vertexB = primer_par(incidents);
                //printf("%d %d", vertexA, vertexB.id);
                if (vertexB.valor == int('=')){
                    label[vertexB.id - 1] = label[vertexA - 1];
                } else {
                    label[vertexB.id - 1] = !label[vertexA - 1];
                }

                if(!alreadyChecked(vertexB.id, Butterflies)){ // if we already checked B we don't care about registering its link with A
                    apilar(vertexA, graph.first); // YOU SHOULD CREATE A FUNCTION CALLED STACK TO INSERT SOMETHING
                    insertar_par(vertexB, graph.second); //HERE WE'RE GONNA TO HAVE A MEMORY LEAK, TRUST ME
                    
                    encolar(vertexB.id, elements);
                    killButterfly(vertexB.id, Butterflies, auxList);
                }
                incidents = resto_pares(incidents);
            }
            destruir_lista_pares(incidents);
            desencolar(elements);

        // Basicamente crear nuevo nodo de bfs levels con los nodos que son incidentes a v en el grafo (usar pila para ir haciendo pop de cada nodo y poder irlos agregando)

        }
    }

    destruir_cola(elements);

    while(!es_vacia_pila(graph.first)) { //PUT THIS IN ANOTHER FUNCTION Should be implemented in match function
        if (primer_par(graph.second).valor == int('=')) {
            if (label[cima(graph.first) - 1] != label[primer_par(graph.second).id- 1]){
                break;
            }
        } else {
            if (label[cima(graph.first) - 1] == label[primer_par(graph.second).id - 1]){
                break;
            }
        }
        desapilar(graph.first);
        graph.second = resto_pares(graph.second);
    }

    if (!es_vacia_pila(graph.first)){
        destruir_pila(graph.first);
        destruir_lista_pares(graph.second);
        return false;
    } else {
        destruir_pila(graph.first);
        destruir_lista_pares(graph.second);
        return true;
    }
}
/* 
void bfs(nat node, Grafo G, bool *discovered){
    discovered[node] = true;

} */

bool alreadyChecked(nat node, ButterfliesList *Array){ //Return true when we already checked node
    return Array[node - 1] == NULL;
}

/* bool match(){

} */

void killButterfly(nat id, ButterfliesList *Array, ButterfliesList &List){ //Se me fue de las manos esto pero sino no me aseguro el O(1)
    id = id - 1;
    if(Array[id] != NULL){
        if(Array[id] -> prev != NULL){
            Array[id] -> prev -> next = Array[id] -> next;
        } else {
            List = Array[id] -> next;
        }
        if(Array[id] -> next != NULL){
            Array[id] -> next -> prev = Array[id] -> prev;
        }
        delete Array[id];
        Array[id] = NULL;
    }
}
// HACER FUNCIONES PARA MANIPULAR BFSLEVELS, DESTRUIR MOVERSE ETC.
