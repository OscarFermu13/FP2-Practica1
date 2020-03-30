#include <stdio.h>
#include <string.h>

#include "../include/afegir_alumne.h"
#include "../include/editar_lista.h"

int main() {
	node_t *list;
	node_t *last_search;
	bool trobat = false;
	Alumne alumne;
	int opcion, stats, dni;
	char nombre[100], enter;

	list_init(&list);

	strcpy(alumne.nomAlumne, "Start");
	alumne.dniNum = 00000000;
	list_add_first(&list, alumne);

	strcpy(alumne.nomAlumne, "End");
	alumne.dniNum = 99999999;
	list_add_first(&list, alumne);

	load_list(list);

	print_menu(list);
	scanf("%d", &opcion);
	scanf("%c", &enter);

	while (opcion != 0)
	{
		switch (opcion)
		{
		case 1:
			printf("\n\n---  Introducir Alumno ---\n");
			addAlumne(&alumne);
			list_add_search(&list, alumne, alumne.dniNum);
			break;

		case 2:
			printf("\n\n---  Buscar Alumno ---\n");
			printf("Introduce el dni del alumno a buscar:\n");
			scanf("%d", &dni);
			last_search = search_dni(list, dni);
			trobat = true;
			break;

		case 3:
			printf("\n\n---  Buscar Alumno ---\n");
			printf("Introduce el nombre del alumno a buscar:\n");
			scanf("%s", nombre);
			last_search = search_nombre(list, nombre);
			trobat = true;
			break;

		case 4:
			printf("\n\n---  Ver ultimo Alumno buscado ---\n");
			if (trobat)
			{
				see_last_search(last_search);
			}
			else
			{
				printf("\n\nNo se ha encontrado ningun alumno en la ultima busqueda.\n\n");
			}
			break;

		case 5:
			printf("\n\n---  Eliminar ultimo Alumno buscado ---\n");
			if (trobat)
			{
				del_last_search(list, &last_search);
				trobat = false;
			}
			else
			{
				printf("\n\nNo se ha encontrado ningun alumno en la ultima busqueda.\n\n");
			}
			break;

		case 6:
			printf("\n\n---  Ver toda la lista de Alumnos ---\n");
			see_list(list);
			break;

		case 7:
			printf("\n\n---  Eliminar toda la lista de Alumnos ---\n");
			del_list(&list);
			break;

		case 8:
			printf("\n\n---  MENU - ESTADISTICAS ---\n");
			print_stats();
			scanf("%d", &stats);
			scanf("%c", &enter);

			while (stats != 0)
			{
				switch (stats)
				{
					case 1:
						num_suspensos(list);
						break;

					case 2:
						num_aprobados(list);
						break;

					case 3:
						num_hombres(list);
						break;

					case 4:
						num_mujeres(list);
						break;

					case 5:
						nota_alta(list);
						break;

					default:
						break;
				}

				print_stats();
				scanf("%d", &stats);
				scanf("%c", &enter);
			}
			
			break;

		case 9:
			printf("\nList size: %u\n", list_size(list));
			printf("List: ");
			list_to_string(list);
			printf("\n\n");
			break;

		case 0:
			save_list(list);
			opcion = 0;
			break;
		
		default:
			break;
		}

		print_menu(list);
		scanf("%d", &opcion);
		scanf("%c", &enter);
	}

	if (opcion == 0)
	{
		save_list(list);
	}
	
}
