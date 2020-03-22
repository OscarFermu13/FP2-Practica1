#ifndef EDITAR_LISTA_H
#define EDITAR_LISTA_H

#include "afegir_alumne.h"

node_t *search_dni(node_t *list, int dni);
node_t *search_nombre(node_t *list, char *nombre);

void see_last_search(node_t *last);
void del_last_search(node_t *lista_total, node_t **last);

#endif // EDITAR_LISTA_H