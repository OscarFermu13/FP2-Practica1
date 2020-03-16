#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Type definitions */
#include "linked_list.h"

/* INITIALIZE list */

void list_init(node_t **p_list) {
	*p_list = NULL;
}

/* Check if list is EMPTY */
bool list_empty(node_t *list) {
	return list == NULL;
}

/* SIZE of list */
size_t list_size(node_t *list) {
	node_t *p;
	size_t n;

	n = 0;
	for (p = list; p != NULL; p = p->next)
		n++;

	return n-2;
}

/* DISPLAY list as a STRING */
void list_to_string(node_t *list) {
	node_t *p;

	printf("( ");
	for (p = list; p != NULL; p = p->next)
	{
		if (strcmp(p->data.nomAlumne, "Start") != 0 && strcmp(p->data.nomAlumne, "End") != 0)
		{
				printf("Nom: %s, DNI: %d, Nota: %.02f | ", p->data.nomAlumne, p->data.dniNum, p->data.nota);
		}
	}

	printf(")");
}

/* CREATE and INITIALIZE NEW NODE */
node_t *list_new_node(data_t data, node_t *next) {

	/* Create new node */
	node_t *p = (node_t *) malloc(sizeof(node_t));
	if (p == NULL) {
		printf("Can't allocate memory to create new node.\n");
		exit(EXIT_FAILURE);
	}

	/* Initialize new node */
	strcpy(p->data.nomAlumne, data.nomAlumne);
	p->data.dniNum = data.dniNum;
	p->data.dniLetra = data.dniLetra;
	strcpy(p->data.correu, data.correu);
	p->data.nota = data.nota;
	p->data.fecha = data.fecha;
	p->data.sexe = data.sexe;
	p->next = next;

	return p;
}

/* PREPEND DATA at the BEGINNING of the list */

void list_add_first(node_t **p_list, data_t data) {
	node_t *new;

	new = list_new_node(data, *p_list);

	*p_list = new;
}

/* AÑADIR nodo en la posicion deseada */

void list_add_search(node_t **p_list, data_t data, int dni)
{
	node_t *current = *p_list;
	node_t *anterior;

	while (current->data.dniNum > dni)
	{
		if (current->next->data.dniNum <= dni)
		{
			anterior = current->next;
			break;
		}
		else
		{
			current = current->next;
		}
	}

	if (anterior->data.dniNum == dni)
	{
		printf("ERROR: El alumno ya existe en la base de datos\n\n");
	}
	else
	{
		node_t *nuevo = (node_t *)malloc(sizeof(node_t));
		current->next = nuevo;
		nuevo->data = data;
		nuevo->next = anterior;
	}
}

/* APPEND DATA to the END of the list */

void list_add_last(node_t **p_list, data_t data) {
	node_t *list = *p_list;
	node_t *new;

	new = list_new_node(data, NULL);

	if (list_empty(list))
		*p_list = new;
	else 
	{
		node_t *last = list;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

/* REMOVE and return FIRST ELEMENT */

data_t list_remove_first(node_t **p_list) {
	node_t *list = *p_list;

	if (list_empty(list)) {
		printf("Attempt to remove first element from empty list.\n");
		exit(EXIT_FAILURE);
	}

	node_t *first = list->next;

	/* Case of a single element */
	if (first == NULL)
		*p_list = NULL;

	/* Case of two or more elements */
	else
		*p_list = first;

	/* Retrieve first data, free node memory. */
	data_t data = list->data;
	free(list);

	return data;
}

/* REMOVE and return LAST ELEMENT */
data_t list_remove_last(node_t **p_list) {
	node_t *list = *p_list;

	if (list_empty(list)) {
		printf("Attempt to remove last element from empty list.\n");
		exit(EXIT_FAILURE);
	}

	/* At least one element */
	node_t *last = list->next;

	/* Case of a single element */
	if (last == NULL) {
		last = list;
		*p_list = NULL;
	}

	/* Case of two or more elements */
	else {
		node_t *before_last = list;
		while (last->next != NULL) {
			before_last = last;
			last = last->next;
		}
		before_last->next = NULL;
	}

	/* Retrieve last data, free node memory. */
	data_t data = last->data;
	free(last);

	return data;
}

/* Crear DATA para Nodo */
void addAlumne(data_t *data)
{
	char enter;

	printf("----- INTRODUCE LOS DATOS DEL NUEVO ALUMNO -----");

	printf("\n Introduce el nombre del Alumno:");
	scanf("%[^\n]%*c", data->nomAlumne);

	printf("\n Introduce el dni del Alumno (SIN LETRA):");
	scanf("%d", &data->dniNum);
/*
	printf("\n Introduce la letra del dni del Alumno:");
	scanf("%s", &data->dniLetra);

	printf("\n Introduce el correo del Alumno:");
	scanf("%s", data->correu);
*/
	printf("\n Introduce la nota del Alumno:");
	scanf("%f", &data->nota);
/*
	printf("\n Introduce la fecha de nacimiento del Alumno\n");
	printf("	- Año:");
	scanf("%d", &data->fecha.any);
	printf("	- Mes:");
	scanf("%d", &data->fecha.mes);
	printf("	- Dia:");
	scanf("%d", &data->fecha.dia);

	printf("\n Introduce el sexo del Alumno (H/M):");
	scanf("%s", &data->sexe);
*/
	scanf("%c", &enter);
	printf("\n \n");
}