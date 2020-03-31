#ifndef EDITAR_LISTA_H
#define EDITAR_LISTA_H

#include "afegir_alumne.h"

/* Prototipos */
void load_list(node_t *list);
void save_list(node_t *list);

node_t *search_dni(node_t *list, int dni);
node_t *search_nombre(node_t *list, char *nombre);

void see_last_search(node_t *last);
void del_last_search(node_t *lista_total, node_t **last);

void see_list(node_t *list);
void del_list(node_t **list);

void num_suspensos(node_t *list);
void num_aprobados(node_t *list);
void num_hombres(node_t *list);
void num_mujeres(node_t *list);
void nota_alta(node_t *list);

bool comprovaDNI(data_t *list);

#endif // EDITAR_LISTA_H