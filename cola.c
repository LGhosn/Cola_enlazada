#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo{
    void *dato;
    struct nodo *siguiente;
} nodo_t;

struct cola{
    nodo_t *primero;
    nodo_t *ultimo;
};

nodo_t *nodo_crear(void *valor){
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (!nodo){
        return NULL;
    }

    nodo->dato = valor;
    nodo->siguiente = NULL;
    return nodo;
}

cola_t *cola_crear(void){
    cola_t *cola = malloc(sizeof(cola_t));
    if (!cola){
        return NULL;
    }

    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}

bool cola_esta_vacia(const cola_t *cola){
    return !cola->primero;
}

bool cola_encolar(cola_t *cola, void *valor){
    nodo_t *nuevo_nodo = nodo_crear(valor);
    if (!nuevo_nodo){
        return false;
    }

    if (cola_esta_vacia(cola)){
        cola->primero = nuevo_nodo;
    }
    else{
        cola->ultimo->siguiente = nuevo_nodo;
    }

    cola->ultimo = nuevo_nodo;
    return true;
}

void *cola_ver_primero(const cola_t *cola){
    if (cola_esta_vacia(cola)){
        return NULL;
    }
    return cola->primero->dato;
}

void *cola_desencolar(cola_t *cola){
    if (cola_esta_vacia(cola)){
        return NULL;
    }

    nodo_t *viejo_primero = cola->primero;
    void *viejo_dato_primero = viejo_primero->dato;

    cola->primero = cola->primero->siguiente;
    if (cola_esta_vacia(cola)){
        cola->ultimo = NULL;
    }

    free(viejo_primero);
    return viejo_dato_primero;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)){
    while (!cola_esta_vacia(cola)){
        void *dato = cola_desencolar(cola);
        if (destruir_dato){
            destruir_dato(dato);
        }
    }
    free(cola);
}
