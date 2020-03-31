#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "afegir_alumne.h"

/* FUNCION print_menu */
/* Imprime el menu principal y muestra el numero de nodos de la lista enlazada */
/* Recibe el puntero a la lista enlazada */
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

/* FUNCION print_stats */
/* Imprime el menu de estadisticas */
void print_stats(void)
{
    printf("    1 - Mostrar numero de Suspendidos\n");
    printf("    2 - Mostrar numero de Aprobados\n");
    printf("    3 - Mostrar numero de Hombres\n");
    printf("    4 - Mostrar numero de Mujeres\n");
    printf("    5 - Alumno con nota mas alta\n");
    printf("    0 - Volver\n");
}

/* FUNCION list_init */
/* Crea la lista enlazada */
/* Recibe el puntero a la lista enlazada */
void list_init(node_t **p_list)
{
    *p_list = NULL;
}

/* FUNCION list_empty */
/* Comprueba si la lista esta vacia o no */
/* Recibe el puntero a la lista enlazada */
/* Devuelve un booleano, dependiendo de si la lista esta vacia o no */
bool list_empty(node_t *list)
{
    return list == NULL;
}

/* FUNCION list_size */
/* Cuenta el numero de nodos que contiene la lista enlazada */
/* Recibe el puntero a la lista enlazada */
/* Devuelve el numero de nodos que contiene la lista */
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

/* FUNCION list_to_string */
/* Imprime la lista enlazada */
/* Recibe el puntero a la lista enlazada */
/* FUNCION DEBUG */
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

/* FUNCION list_new_node */
/* Crea un nodo */
/* Recibe los datos del nodo a crear y el nodo al que se tiene que enlazar */
/* Devuelve el nodo creado */
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

/* FUNCION list_add_first */
/* Enlaza el nodo creado al nodo anterior */
/* Recibe los datos del nodo a crear y el puntero a la lista enlazada */
void list_add_first(node_t **p_list, data_t data)
{
    node_t *nuevo;

    nuevo = list_new_node(data, *p_list);
    *p_list = nuevo;
}

/* FUNCION list_add_search */
/* Enlaza el nodo creado al nodo que cumple los requisitos (Funcion que inserta nodo en medio de la lista) */
/* Recibe los datos del nodo a crear y el puntero a la lista enlazada */
void list_add_search(node_t **p_list, data_t data, int dni)
{
    node_t *current = *p_list;
    node_t *anterior;
    node_t *nuevo;

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
        nuevo = list_new_node(data, anterior);
        current->next = nuevo;
    }
}

/* FUNCION addAlumne */
/* Pide al usuario que introduzca los datos del alumno a crear */
/* Recibe la estructura de datos que define a cada alumno */
void addAlumne(data_t *data)
{
    char enter;
    bool correcte;
    
    printf("\n-- Introduce los datos del nuevo Alumno --");

    printf("\n Introduce el nombre del Alumno:");
    scanf("%s", data->nomAlumne);

    printf("\n Introduce el primer apellido del Alumno:");
    scanf("%s", data->cognomAlumne);

    printf("\n Introduce el dni del Alumno (SIN LETRA):");
    scanf("%d", &data->dniNum);

	printf("\n Introduce la letra del dni del Alumno:");
	scanf("%s", &data->dniLetra); 
    correcte = comprovaDNI(data);

    while(!correcte)
    {
        printf("El DNI introducido no es valido, vuelva a introducir la letra.\n");
        printf("\n Introduce la letra del dni del Alumno:");
        scanf("%s", &data->dniLetra);

        correcte = comprovaDNI(data);
    }
    
    
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

    while (data->sexe != 'H' && data->sexe != 'M')
    {
        printf("El caracter introducido no es valido, introduzca H o M.\n");
        printf("\n Introduce el sexo del Alumno (Hombre/Mujer):");
        scanf("%s", &data->sexe);
        scanf("%c", &enter);
    }

    printf("\n \n");
}

