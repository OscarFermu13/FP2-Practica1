#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Type definitions */
#include "afegir_alumne.h"

/* INITIALIZE list */

void print_menu(node_t *list)
{
    printf("\nLa lista contiene %d Alumnos \n", list_size(list));
    printf("----- MENU ----- \n");
    printf("1 - Introducir Alumno\n");
    printf("2 - Buscar Alumno - (Por DNI)\n");
    printf("3 - Buscar Alumno - (Por Nombre)\n");
    printf("4 - Ver ultimo Alumno buscado\n");
    printf("5 - Eliminar ultimo Alumno buscado\n");
    printf("6 - Ver toda la lista de Alumnos\n");
    printf("7 - Eliminar toda la lista de Alumnos\n");
    printf("8 - Mostrar Estadisticas\n");
    printf("0 - Salir\n");
}

void print_stats(void)
{
    printf("    1 - Mostrar numero de Suspendidos\n");
    printf("    2 - Mostrar numero de Aprobados\n");
    printf("    3 - Mostrar numero de Hombres\n");
    printf("    4 - Mostrar numero de Mujeres\n");
    printf("    5 - Alumno con nota mas alta\n");
    printf("    0 - Volver\n");
}

void list_init(node_t **p_list)
{
    *p_list = NULL;
}

/* Check if list is EMPTY */
bool list_empty(node_t *list)
{
    return list == NULL;
}

/* SIZE of list */
size_t list_size(node_t *list)
{
    node_t *p;
    size_t n;

    n = 0;
    for (p = list; p != NULL; p = p->next)
        n++;

    if (n == 0)
    {
        return 0;
    }
    else
    {
        return n - 2;
    }    
}

/* DISPLAY list as a STRING */
void list_to_string(node_t *list)
{
    node_t *p;

    printf("( ");
    for (p = list; p != NULL; p = p->next)
    {
        if (strcmp(p->data.nomAlumne, "Start") != 0 && strcmp(p->data.nomAlumne, "End") != 0)
        {
            printf("Nombre: %s, DNI: %d | ", p->data.nomAlumne, p->data.dniNum);
        }
    }

    printf(")");
}

/* CREATE and INITIALIZE NEW NODE */
node_t *list_new_node(data_t data, node_t *next)
{

    /* Create new node */
    node_t *p = (node_t *)malloc(sizeof(node_t));
    if (p == NULL)
    {
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

void list_add_first(node_t **p_list, data_t data)
{
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
    

/* Crear DATA para Nodo */
void addAlumne(data_t *data)
{
    char enter;
    
    printf("\n-- Introduce los datos del nuevo Alumno --");

    printf("\n Introduce el nombre del Alumno:");
    scanf("%s", data->nomAlumne);

    printf("\n Introduce el primer apellido del Alumno:");
    scanf("%s", data->cognomAlumne);

    printf("\n Introduce el dni del Alumno (SIN LETRA):");
    scanf("%d", &data->dniNum);


	printf("\n Introduce la letra del dni del Alumno:");
	scanf("%s", &data->dniLetra); 

    comprovaDNI(data);

	printf("\n Introduce el correo del Alumno:");
	scanf("%s", data->correu);

	printf("\n Introduce la nota del Alumno:");
	scanf("%f", &data->nota);

	printf("\n Introduce la fecha de nacimiento del Alumno\n");
	printf("	- Dia:");
	scanf("%d", &data->fecha.dia);
	printf("	- Mes:");
	scanf("%d", &data->fecha.mes);
	printf("	- Año:");
	scanf("%d", &data->fecha.any);

	printf("\n Introduce el sexo del Alumno (Hombre/Mujer):");
	scanf("%s", &data->sexe);
    scanf("%c", &enter);
    printf("\n \n");


}

