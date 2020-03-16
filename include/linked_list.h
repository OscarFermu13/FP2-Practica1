#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdio.h>

/* Data type */

typedef struct fecha_t
{
	int dia;
	int mes;
	int any;
} fecha_t;

typedef struct data_t
{
	char nomAlumne[100];
	int dniNum;
	char dniLetra;
	char correu[100];
	float nota;
	fecha_t fecha;
	char sexe;
} data_t;

typedef data_t Alumne;

/* Node type */

typedef struct Node
{
	data_t data;
	struct Node *next;
} node_t;

/* Prototypes */

void list_init(node_t **p_list);

bool list_empty(node_t *list);
size_t list_size(node_t *list);

void list_to_string(node_t *list);

node_t *list_new_node(data_t data, node_t *next);

void list_add_first(node_t **p_list, data_t data);
void list_add_search(node_t **p_list, data_t data, int dni);
void list_add_last(node_t **p_list, data_t data);

data_t list_remove_first(node_t **p_list);
data_t list_remove_last(node_t **p_list);

void addAlumne(data_t *data);

#endif // LINKED_LIST_H
