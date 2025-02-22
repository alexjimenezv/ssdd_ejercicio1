#include "claves.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



Tupla *head = NULL;


int init(Tupla **l) {
    *l = NULL;
    return 0;
}


int destroy(){
    // Comprobar que no está vacia
    if (head == NULL) {
        printf("Error: No hay tuplas para eliminar.\n");
        return -1;
    }

    // no usamos delete key para que no haya problemas de seguridad
    Tupla *actual = head;
    Tupla *temp;

    while (actual != NULL) {
        temp = actual; 
        actual = actual->next; 
        free(temp); 
    }

    head = NULL; 
    printf("Todas las tuplas han sido eliminadas correctamente.\n");

    return 0;
}

int set_value(int key, char *value1, int N_value2, double *V_value2, struct Coord value3){
	if (N_value2 < 1 || N_value2 > MAX_VECTOR_SIZE) {
        printf("Error: El tamaño del vector value2 (%d) está fuera del rango permitido (1-32).\n", N_value2);
        return -1;
    }

    if (exist(key) == 1) return -1;

    Tupla *nueva_tupla = (Tupla *)malloc(sizeof(Tupla));
    if (nueva_tupla == NULL) {
        printf("Error: No se pudo asignar memoria para la nueva tupla.\n");
        return -1;
    }

    nueva_tupla->key = key;

    // Se necesita espacio para el fin de cadena
    strncpy(nueva_tupla->value1, value1, MAX_CHAR_SIZE - 1); 

    // Aseguramos que acaba en fin de cadena en el elemento MAX_CHAR_SIZE, pero el indice MAX_CHAR_SIZE - 1
    nueva_tupla->value1[MAX_CHAR_SIZE - 1] = '\0'; 


    nueva_tupla->N_value2 = N_value2;
    for (int i = 0; i < N_value2; i++) {
        nueva_tupla->value2[i] = V_value2[i];
    }

    nueva_tupla->value3 = value3;

    nueva_tupla->next = head;
    head = nueva_tupla;

    printf("Tupla con clave %d insertada correctamente.\n", key);
    return 0; 
}

int get_value(int key, char *value1, int *N_value2, double *V_value2, struct Coord *value3) {
    // Verificar que no hay ningún valor nulo

    Tupla *actual = head;

    while (actual != NULL) {
        if (actual->key == key) {
            strncpy(value1, actual->value1, MAX_CHAR_SIZE - 1);
            value1[MAX_CHAR_SIZE - 1] = '\0';

            *N_value2 = actual->N_value2;
            for (int i = 0; i < *N_value2; i++) {
                V_value2[i] = actual->value2[i];
            }

            *value3 = actual->value3;

            printf("Tupla encontrada: Key=%d, Value1=%s, Coords=(%d, %d)\n",
                   key, value1, value3->x, value3->y);

            return 0; 
        }
        actual = actual->next;
    }

    printf("Error: Clave %d no encontrada.\n", key);
    return -1;
}

int modify_value(int key, char *value1, int N_value2, double *V_value2, struct Coord value3) {
    Tupla *actual = head;

    while (actual != NULL) {
        if (actual->key == key) {
            // Modificar value1 si no es NULL
            if (value1 != NULL) {
                strncpy(actual->value1, value1, MAX_CHAR_SIZE - 1);
                actual->value1[MAX_CHAR_SIZE - 1] = '\0';
            }

            // Modificar value2 si es válido
            if (V_value2 != NULL && N_value2 > 0 && N_value2 <= MAX_VECTOR_SIZE) {
                actual->N_value2 = N_value2;
                for (int i = 0; i < N_value2; i++) {
                    actual->value2[i] = V_value2[i];
                }
            }

            // Modificar value3
            actual->value3 = value3;

            return 0;
        }
        actual = actual->next;
    }

    printf("Error: Clave %d no encontrada.\n", key);
    return -1;
}


int delete_key(int key){
    Tupla *actual = head;
    Tupla *anterior = NULL;

    while (actual != NULL) {
        if (actual->key == key) {
            // Si es la cabeza de la lista
            if (anterior == NULL) {
                head = actual->next;  
            } else {
                // Asignamos el next del nodo anterior al next del nodo actual que se va a liberar
                anterior->next = actual->next;  
            }

            free(actual);
            return 0;
        }

        anterior = actual;
        actual = actual->next;
    }

    printf("Error: La clave %d no existe.\n", key);
    return -1;
}	

int  exist(int key){
	Tupla *actual = head;

    while (actual != NULL) {
        if (actual->key == key) {
            return 1;
        }
        actual = actual->next;
    }
    printf("No existe la clave %d", key);
    return 0;
}	

