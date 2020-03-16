#include <stdio.h>
#include <string.h>

/* Type definitions and prototypes for linked list */
#include "../include/linked_list.h"

/* MAIN: TEST list functions */
void main() {
	node_t *list;
	Alumne alumne;
	int opcion;
	char enter;

	list_init(&list);

	strcpy(alumne.nomAlumne, "Start");
	alumne.dniNum = 00000000;
	list_add_first(&list, alumne);

	strcpy(alumne.nomAlumne, "End");
	alumne.dniNum = 99999999;
	list_add_first(&list, alumne);

	/*addAlumne(&alumne);
	list_add_first(&list, alumne);

	addAlumne(&alumne);
	list_add_search(&list, alumne, alumne.dniNum);*/

	printf("-- MENU -- \n");
	printf("1 - Introducir Alumno\n");
	printf("0 - Salir\n");
	scanf("%d", &opcion);
	scanf("%c", &enter);

	while (opcion != 0)
	{
		switch (opcion)
		{
		case 1:
			addAlumne(&alumne);
			list_add_search(&list, alumne, alumne.dniNum);
			break;

		case 0:
			opcion = 0;
			break;
		}

		printf("\nList size: %u\n", list_size(list));
		printf("List: ");
		list_to_string(list);
		printf("\n");

		printf("\n-- MENU -- \n");
		printf("1 - Introducir Alumno\n");
		printf("0 - Salir\n");
		scanf("%d", &opcion);
		scanf("%c", &enter);
	}

	printf("\nList size: %u\n", list_size(list));
	printf("List: ");
	list_to_string(list);
	printf("\n");
}
