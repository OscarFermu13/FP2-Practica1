#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Type definitions */
#include "editar_lista.h"

void load_list(node_t *list)
{
    Alumne alumne;

    FILE *file = fopen("data/alumnes_list.txt", "r");
    if (file == NULL)
    {
        printf("No se han encontrado datos de la lista de alumnos.\n\n");
    }
    else
    {
        while(!feof(file))
        {
            char buf[100];

            fscanf(file, "%s ", buf);
            strcpy(alumne.nomAlumne, buf);

            fscanf(file, "%s ", buf);
            strcpy(alumne.cognomAlumne, buf);

            fscanf(file, "%s ", buf);
            alumne.dniNum = atoi(buf);

            fscanf(file, "%s ", buf);
            alumne.dniLetra = buf[0];

            fscanf(file, "%s ", buf);
            strcpy(alumne.correu, buf);

            fscanf(file, "%s ", buf);
            alumne.nota = atof(buf);

            fscanf(file, "%s ", buf);
            alumne.fecha.dia = atoi(buf);
            fscanf(file, "%s ", buf);
            alumne.fecha.mes = atoi(buf);
            fscanf(file, "%s ", buf);
            alumne.fecha.any = atoi(buf);

            fscanf(file, "%s ", buf);
            alumne.sexe = buf[0];

            list_add_search(&list, alumne, alumne.dniNum);
        }
    }

    fclose(file);
}

void save_list(node_t *list)
{
    node_t *lista = list;
    FILE *file = fopen("data/alumnes_list.txt", "w");

    if (lista != NULL)
    {
        while (lista->next != NULL)
        {
            if (strcmp(lista->data.nomAlumne, "Start") != 0 && strcmp(lista->data.nomAlumne, "End") != 0)
            {
                fprintf(file, "%s %s %d %c %s %f %.02d %.02d %.04d %c\n", lista->data.nomAlumne, lista->data.cognomAlumne, lista->data.dniNum, lista->data.dniLetra, lista->data.correu, lista->data.nota, lista->data.fecha.dia, lista->data.fecha.mes, lista->data.fecha.any, lista->data.sexe);
            }
            lista = lista->next;
        }
    }
    fclose(file);
}

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
            see_last_search(p);
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
            see_last_search(p);
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
    printf("Apellido: %s\n", last->data.cognomAlumne);
    printf("DNI: %d-%c\n", last->data.dniNum, last->data.dniLetra);
	printf("Correo: %s\n", last->data.correu);
	printf("Nota: %.02f\n", last->data.nota);
	printf("Fecha de Nacimiento: %.02d/%.02d/%.04d\n", last->data.fecha.dia, last->data.fecha.mes, last->data.fecha.any);
	printf("Sexo: %c\n", last->data.sexe);
    printf("\n\n");
}

void del_last_search(node_t *lista_total, node_t **last_search)
{
    node_t *list = *last_search;
    char opcion;

    see_last_search(list);

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

void see_list(node_t *list)
{
    node_t *lista = list;
    char opcion, enter;

    printf("Esta seguro de que quiere VER todos los datos de la lista?");
    printf("(s/n)\n");
    scanf("%c", &opcion);
    scanf("%c", &enter);

    while (opcion == 's')
    {
        lista = lista->next;
        if(lista->next != NULL)
        {
            if (strcmp(lista->data.nomAlumne, "Start") != 0 && strcmp(lista->data.nomAlumne, "End") != 0)
            {
                see_last_search(lista);
            }

            if (lista->next->next != NULL)
            {
                printf("\nQuiere continuar?");
                printf("(s/n)\n");
                scanf("%c", &opcion);
                scanf("%c", &enter);
            }
            else
            {
                break;
            }
            
        }
    }

    if(opcion != 's')
    {
        printf("\nCANCELADO\n\n");
    }   
}

void del_list(node_t **list)
{
    node_t *lista = *list;
    node_t *siguiente;
    char opcion, enter;

    printf("Esta seguro de que quiere ELIMINAR todos los datos de la Lista?\nEsta accion no se puede deshacer...");
    printf("\n(s/n)\n");
    scanf("%c", &opcion);
    scanf("%c", &enter);

    if (opcion == 's')
    {
        printf("\nLA LISTA HA SIDO ELIMINADA CON EXITO!\n\n");
        
        while (lista != NULL)
        {
            siguiente = lista->next;
            free(lista);
            lista = siguiente;
        }

        *list = NULL;
    }
    else
    {
        printf("\nCANCELADO\n\n");
    }
}

void num_suspensos(node_t *list)
{
    node_t *lista = list;
    int n = 0;

    while (lista != NULL)
    {
        if (strcmp(lista->data.nomAlumne, "Start") != 0 && strcmp(lista->data.nomAlumne, "End") != 0)
        {
            if (lista->data.nota < 5)
            {
                n++;
            }
            
        }
        lista = lista->next;
    }

    printf("\nEl numero de suspensos es: %d\n\n", n);
}

void num_aprobados(node_t *list)
{
    node_t *lista = list;
    int n = 0;

    while (lista != NULL)
    {
        if (strcmp(lista->data.nomAlumne, "Start") != 0 && strcmp(lista->data.nomAlumne, "End") != 0)
        {
            if (lista->data.nota >= 5)
            {
                n++;
            }
                }
        lista = lista->next;
    }

    printf("\nEl numero de aprobados es: %d\n\n", n);
}

void num_hombres(node_t *list)
{
    node_t *lista = list;
    int n = 0;

    while (lista != NULL)
    {
        if (strcmp(lista->data.nomAlumne, "Start") != 0 && strcmp(lista->data.nomAlumne, "End") != 0)
        {
            if (lista->data.sexe == 'H')
            {
                n++;
            }
        }
        lista = lista->next;
    }

    printf("\nEl numero de hombres es: %d\n\n", n);
}

void num_mujeres(node_t *list)
{
    node_t *lista = list;
    int n = 0;

    while (lista != NULL)
    {
        if (strcmp(lista->data.nomAlumne, "Start") != 0 && strcmp(lista->data.nomAlumne, "End") != 0)
        {
            if (lista->data.sexe == 'M')
            {
                n++;
            }
        }
        lista = lista->next;
    }

    printf("\nEl numero de mujeres es: %d\n\n", n);
}

void nota_alta(node_t *list)
{
    node_t *lista = list;
    node_t *nota_max;
    int dni = 0, nota = 0;

    while (lista != NULL)
    {
        if (strcmp(lista->data.nomAlumne, "Start") != 0 && strcmp(lista->data.nomAlumne, "End") != 0)
        {
            if (lista->data.nota > nota)
            {
                nota = lista->data.nota;
                dni = lista->data.dniNum;
            }
        }
        lista = lista->next;
    }

    printf("\n");
    nota_max = search_dni(list, dni);
}