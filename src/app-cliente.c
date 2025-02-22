#include "claves.h"
#include <stdio.h>
#include <string.h>

extern Tupla *head;

int main() {
    printf("\n===== INICIANDO PRUEBAS DEL SISTEMA MONOLÍTICO =====\n");

    // 1. Inicializar la lista
    if (init(&head) == 0) {
        printf("Lista inicializada correctamente.\n");
    } else {
        printf("Error al inicializar la lista.\n");
    }

    // 2. Insertar tuplas (set_value)
    double valores1[] = {1.1, 2.2, 3.3};
    if (set_value(1, "Primera Tupla", 3, valores1, (struct Coord){10, 20}) == 0) {
        printf("Tupla con clave 1 insertada correctamente.\n");
    }

    double valores2[] = {4.4, 5.5};
    if (set_value(2, "Segunda Tupla", 2, valores2, (struct Coord){30, 40}) == 0) {
        printf("Tupla con clave 2 insertada correctamente.\n");
    }

    // Intentar insertar una tupla duplicada
    if (set_value(1, "Duplicada", 3, valores1, (struct Coord){50, 60}) == -1) {
        printf("Error al insertar tupla duplicada con clave 1.\n");
    }

    // 3. Verificar la existencia de claves
    printf("\n===== PRUEBA EXIST =====\n");
    printf("¿Existe la clave 1? %s\n", exist(1) ? "Sí" : "No");
    printf("¿Existe la clave 3? %s\n", exist(3) ? "Sí" : "No");

    // 4. Obtener tuplas (get_value)
    printf("\n===== PRUEBA GET_VALUE =====\n");
    char value1[MAX_CHAR_SIZE];
    int N_value2;
    double V_value2[MAX_VECTOR_SIZE];
    struct Coord value3;

    if (get_value(1, value1, &N_value2, V_value2, &value3) == 0) {
        printf("Tupla recuperada: Value1=%s, N_value2=%d, Coords=(%d, %d)\n",
               value1, N_value2, value3.x, value3.y);
        printf("Valores de value2: ");
        for (int i = 0; i < N_value2; i++) {
            printf("%.2f ", V_value2[i]);
        }
        printf("\n");
    } else {
        printf("Error al recuperar la tupla con clave 1.\n");
    }

    // 5. Modificar una tupla existente
    printf("\n===== PRUEBA MODIFY_VALUE =====\n");
    double nuevos_valores[] = {9.9, 8.8};
    if (modify_value(1, "Modificada", 2, nuevos_valores, (struct Coord){70, 80}) == 0) {
        printf("Tupla con clave 1 modificada correctamente.\n");
    } else {
        printf("Error al modificar la tupla con clave 1.\n");
    }

    // 6. Obtener la tupla modificada
    if (get_value(1, value1, &N_value2, V_value2, &value3) == 0) {
        printf("Tupla modificada: Value1=%s, N_value2=%d, Coords=(%d, %d)\n",
               value1, N_value2, value3.x, value3.y);
        printf("Valores de value2: ");
        for (int i = 0; i < N_value2; i++) {
            printf("%.2f ", V_value2[i]);
        }
        printf("\n");
    } else {
        printf("Error al recuperar la tupla modificada con clave 1.\n");
    }

    // 7. Eliminar una tupla
    printf("\n===== PRUEBA DELETE_KEY =====\n");
    if (delete_key(1) == 0) {
        printf("Tupla con clave 1 eliminada correctamente.\n");
    } else {
        printf("Error al eliminar la tupla con clave 1.\n");
    }

    // Verificar eliminación
    printf("¿Existe la clave 1 después de eliminar? %s\n", exist(1) ? "Sí" : "No");

    // 8. Destruir la lista
    printf("\n===== PRUEBA DESTROY =====\n");
    if (destroy() == 0) {
        printf("Lista eliminada correctamente.\n");
    } else {
        printf("Error al eliminar la lista.\n");
    }

    printf("\n===== FIN DE LAS PRUEBAS =====\n");

    return 0;
}
