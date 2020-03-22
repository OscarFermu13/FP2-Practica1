#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Type definitions */
#include "editar_lista.h"

node_t *search_dni(node_t *list, int dni)
{
    node_t *p;
    node_t *first;
    int n;

    p = list;
    n = 0;

    if (list == NULL)
        printf("\n\nEl alumno buscado no existe\n");

    for (p = list; p != NULL; p = p->next)
    {
        if (p->data.dniNum == dni)
        {
            printf("\n\nNombre: %s\n\n\n", p->data.nomAlumne);
            n++;
            first = p;
        }
    }

    if (n != 1)
    {
        printf("\n\nEl alumno buscado no existe\n");
    }

    return first;
}

node_t *search_nombre(node_t *list, char *nombre)
{
    node_t *p;
    node_t *first;
    int n = 0;
    int i = 0;

    p = list;
    //first = NULL;

    if (list == NULL)
        printf("No existe");

    for (p = list; p != NULL; p = p->next)
    {
        if (strcmp(p->data.nomAlumne, nombre) == 0)
        {
            printf("\n\nNombre: %s\n", p->data.nomAlumne);
            n++;
            if (n == 1)
            {
                first = p;
                i++;
            }
        }
    }

    if (n != 1)
    {
        printf("\n\nEl alumno buscado no existe\n\n");
    }

    return first;
}

void see_last_search(node_t *last)
{
    printf("Nombre: %s\n", last->data.nomAlumne);
    printf("DNI: %d-%c\n", last->data.dniNum, last->data.dniLetra);
    /*
	printf("Correo: %s\n", last->data.correu);
	printf("Nota: %.02f\n", last->data.nota);
	printf("Fecha de Nacimiento: %.02d/%.02d/%.04d\n", last->data.fecha.dia, last->data.fecha.mes, last->data.fecha.any);
	printf("Sexo: %c\n", last->data.sexe);
	*/
    printf("\n\n");
}

void del_last_search(node_t *lista_total, node_t **last_search)
{
    node_t *list = *last_search;
    char opcion;

    printf("Nombre: %s\n", list->data.nomAlumne);
    printf("DNI: %d-%c\n", list->data.dniNum, list->data.dniLetra);
    /*
	printf("Correo: %s\n", list->data.correu);
	printf("Nota: %.02f\n", list->data.nota);
	printf("Fecha de Nacimiento: %.02d/%.02d/%.04d\n", list->data.fecha.dia, list->data.fecha.mes, list->data.fecha.any);
	printf("Sexo: %c\n", list->data.sexe);
	*/
    printf("\n\n");

    printf("Esta seguro de que quiere ELIMINAR los datos del Alumno?\nEsta accion no se puede deshacer...");
    printf("\n(s/n)\n");
    scanf("%c", &opcion);

    if (opcion == 's')
    {
        printf("\nEL ALUMNO HA SIDO BORRADO CON EXITO!\n\n");

        node_t *list_t = lista_total;

        while (list_t->next->data.dniNum != list->data.dniNum)
        {
            list_t = list_t->next;
        }

        list_t->next = list->next;

        free(list);
    }
    else
    {
        printf("\nCANCELADO\n\n");
    }
}