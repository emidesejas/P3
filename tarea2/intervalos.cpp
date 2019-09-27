/*50884288*/

#include "intervalos.h"

struct intervalo{
    nat indice;
    intervalo_t elem;
};


/* Chequea si i,j son compatibles*/
bool compatibles(intervalo_t i, intervalo_t j) {
    return i.fin <= j.inicio || j.fin <= i.inicio;
}

intervalo *ordenar_rec(intervalo_t *intervalos, nat inicio, nat fin){
    if (fin-inicio == 0) {
        intervalo *resultado = new intervalo[1];
        resultado [0].indice = inicio;
        resultado [0].elem = intervalos[inicio];
        return resultado;
    } else if (fin - inicio == 1) {
        intervalo *resultado = new intervalo[2];
        if(intervalos[inicio].fin <= intervalos[fin].fin) {
            resultado[0].elem = intervalos[inicio];
            resultado[0].indice = inicio;
            resultado[1].elem = intervalos[fin];
            resultado[1].indice = fin;
        } else {
            resultado[1].elem = intervalos[inicio];
            resultado[1].indice = inicio;
            resultado[0].elem = intervalos[fin];
            resultado[0].indice = fin;
        }
        return resultado;
    } else {
        nat mitadIzq = inicio+((fin-inicio)/2);
        intervalo *izq = ordenar_rec(intervalos, inicio, mitadIzq);
        intervalo *der = ordenar_rec(intervalos, mitadIzq+1, fin);
        intervalo *resultado = new intervalo[(fin-inicio)+1];
        nat i = 0;
        nat j = 0;
        nat cursor = 0;
        nat fin1 = mitadIzq-inicio;
        nat fin2 = fin - mitadIzq;
        while (i <= fin1 && j < fin2 && cursor <= (fin-inicio)+1) {
            if (izq[i].elem.fin < der[j].elem.fin) {
                resultado[cursor].indice = izq[i].indice;
                resultado[cursor].elem = izq[i].elem;
                i++;
            } else {
                resultado[cursor].indice = der[j].indice;
                resultado[cursor].elem = der[j].elem;
                j++;
            }
            cursor++;
        }

        while(i<=fin1 && cursor <= (fin-inicio)){
            resultado[cursor].indice = izq[i].indice;
            resultado[cursor].elem = izq[i].elem;
            i++;
            cursor++;
        }

        while(j < fin2 && cursor <= (fin-inicio)){
            resultado[cursor].indice = der[j].indice;
            resultado[cursor].elem = der[j].elem;
            j++;
            cursor++;
        }
        delete[] izq;
        delete[] der;
        return resultado;
    }

    
}

bool *max_cantidad(intervalo_t *intervalos, nat n) {
    intervalo *ordenados = ordenar_rec(intervalos, 0, n-1);
    nat i = 0;
    bool *resultado = new bool[n];
    resultado[ordenados[i].indice] = true;
    intervalo_t anterior = ordenados[i].elem;
    i++;
    while (i < n) {
        if (compatibles(ordenados[i].elem, anterior)){
            anterior = ordenados[i].elem;
            resultado[ordenados[i].indice] = true;
        } else {
            resultado [ordenados[i].indice] = false;
        }
        i++;
    }
    delete[] ordenados;
    return resultado;
}