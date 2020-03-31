#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "editar_lista.h"

/* FUNCION load_list */
/* Lee el archivo de texto externo y crea los nodos de los alumnos previmente creados */
/* Recibe el puntero a la lista enlazada */
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

/* FUNCION save_list */
/* Recorre los nodos uno a uno y los guarda en un archivo de texto externo */
/* Recibe el puntero a la lista enlazada */
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

/* FUNCION search_dni */
/* Busca en la base de datos un nodo que coincida con el parametro introducido por el usuario */
/* Recibe el puntero a la lista enlazada y el parametro de busqueda (int dni) */
/* Devuelve el nodo encontrado, si no existe devuelve NULL */
node_t *search_dni(node_t *list, int dni)
{
    node_t *p;
    node_t *first;
    data_t *data = NULL;
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
            data = &p->data;
            comprovaDNI(data);
        }
    }

    if (n != 1)
    {
        printf("\n\nEl alumno buscado no existe\n");
    }

    return first;
}

/* FUNCION search_nombre */
/* Busca en la base de datos un nodo que coincida con el parametro introducido por el usuario */
/* Recibe el puntero a la lista enlazada y el parametro de busqueda (char nombre) */
/* Devuelve el nodo encontrado, si no existe devuelve NULL */
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

/* FUNCION see_last_search */
/* Muestra cual ha sido la ultima busqueda realizada por el usuario */
/* Recibe el nodo previamente buscado */
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

/* FUNCION del_last_search */
/* Elimina el nodo perteneciente a la ultima busqueda realizada por el usuario */
/* Recibe el puntero a la lista enlazada y el nodo previamente buscado */
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

/* FUNCION see_list */
/* Recorre uno a uno los nodos de la lista enlazada e imprime la informacion */
/* Recibe el puntero a la lista enlazada */
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

/* FUNCION del_list */
/* Recorre uno a uno los nodos de la lista enlazada y los elimina */
/* Recibe el puntero a la lista enlazada */
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

/* FUNCION num_suspensos */
/* Recorre uno a uno los nodos de la lista enlazada y cuenta el numero de suspensos */
/* Recibe el puntero a la lista enlazada */
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

/* FUNCION num_aprobados */
/* Recorre uno a uno los nodos de la lista enlazada y cuenta el numero de aprobados */
/* Recibe el puntero a la lista enlazada */
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

/* FUNCION num_hombres */
/* Recorre uno a uno los nodos de la lista enlazada y cuenta el numero de hombres */
/* Recibe el puntero a la lista enlazada */
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

/* FUNCION num_mujeres */
/* Recorre uno a uno los nodos de la lista enlazada y cuenta el numero de mujeres */
/* Recibe el puntero a la lista enlazada */
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

/* FUNCION nota_alta */
/* Recorre uno a uno los nodos de la lista enlazada y imprime la informacion del alumno con la nota mas alta */
/* Recibe el puntero a la lista enlazada */
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

/* FUNCION comprovaDNI */
/* Comprueba si el dni introducido es correcto respecto a la formula para calcularlo */
/* Recibe el puntero a la lista enlazada */
bool comprovaDNI(data_t *list)
{

    data_t *p = list;
    bool correcte = true;

    switch (p->dniNum % 23)
    {
    case 0:
        if (p->dniLetra != 'T')
        {
            correcte = false;
        }
        break;
    case 1:
        if (p->dniLetra != 'R')
        {
            correcte = false;
        }
        break;
    case 2:
        if (p->dniLetra != 'W')
        {
            correcte = false;
        }
        break;

    case 3:
        if (p->dniLetra != 'A')
        {
            correcte = false;
        }
        break;

    case 4:
        if (p->dniLetra != 'G')
        {
            correcte = false;
        }
        break;
    case 5:
        if (p->dniLetra != 'M')
        {
            correcte = false;
        }
        break;

    case 6:
        if (p->dniLetra != 'Y')
        {
            correcte = false;
        }
        break;

    case 7:
        if (p->dniLetra != 'F')
        {
            correcte = false;
        }
        break;

    case 8:
        if (p->dniLetra != 'P')
        {
            correcte = false;
        }
        break;

    case 9:
        if (p->dniLetra != 'D')
        {
            correcte = false;
        }

    case 10:
        if (p->dniLetra != 'X')
        {
            correcte = false;
        }
        break;

    case 11:
        if (p->dniLetra != 'B')
        {
            correcte = false;
        }
        break;

    case 12:
        if (p->dniLetra != 'N')
        {
            correcte = false;
        }
        break;

    case 13:
        if (p->dniLetra != 'J')
        {
            correcte = false;
        }
        break;

    case 14:
        if (p->dniLetra != 'Z')
        {
            correcte = false;
        }
        break;

    case 15:
        if (p->dniLetra != 'S')
        {
            correcte = false;
        }
        break;

    case 16:
        if (p->dniLetra != 'Q')
        {
            correcte = false;
        }
        break;

    case 17:
        if (p->dniLetra != 'V')
        {
            correcte = false;
        }
        break;

    case 18:
        if (p->dniLetra != 'H')
        {
            correcte = false;
        }
        break;

    case 19:
        if (p->dniLetra != 'L')
        {
            correcte = false;
        }
        break;

    case 20:
        if (p->dniLetra != 'C')
        {
            correcte = false;
        }
        break;

    case 21:
        if (p->dniLetra != 'K')
        {
            correcte = false;
        }
        break;

    case 22:
        if (p->dniLetra != 'E')
        {
            correcte = false;
        }
        break;
    }
    
    return correcte;
}