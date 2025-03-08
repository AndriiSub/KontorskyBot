#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef struct {
    float weight;
    float posX, posY;
} Body;

// Функція для знаходження відстані між двома тілами
float compute_distance(Body a, Body b) {
    return hypotf(b.posX - a.posX, b.posY - a.posY);
}

// Пошук найближчого об'єкта
int get_nearest_body(Body* bodies, int size, int targetIndex) {
    int nearestIndex = -1;
    float minDistance = FLT_MAX;
    
    for (int i = 0; i < size; i++) {
        if (i == targetIndex) continue;
        float currentDistance = compute_distance(bodies[i], bodies[targetIndex]);
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            nearestIndex = i;
        }
    }
    return nearestIndex;
}

// Видалення об'єкта зі списку
void remove_body(Body* bodies, int* size, int targetIndex) {
    for (int i = targetIndex; i < *size - 1; i++) {
        bodies[i] = bodies[i + 1];
    }
    (*size)--;
}

int main() {
    int count;
    printf("Введіть кількість об'єктів: ");
    scanf("%d", &count);

    if (count < 1) {
        printf("Некоректний ввід.\n");
        return 1;
    }

    Body* bodies = (Body*)malloc(count * sizeof(Body));

    // Отримання вхідних даних
    for (int i = 0; i < count; i++) {
        printf("Об'єкт %d: Введіть вагу та координати (x, y): ", i + 1);
        scanf("%f %f %f", &bodies[i].weight, &bodies[i].posX, &bodies[i].posY);
    }

    // Об'єднання об'єктів
    while (count > 1) {
        int lightestIndex = 0;
        for (int i = 1; i < count; i++) {
            if (bodies[i].weight < bodies[lightestIndex].weight) {
                lightestIndex = i;
            }
        }

        // Передача ваги найближчому об'єкту
        int nearestIndex = get_nearest_body(bodies, count, lightestIndex);
        bodies[nearestIndex].weight += bodies[lightestIndex].weight;

        // Видалення легшого об'єкта
        remove_body(bodies, &count, lightestIndex);
    }

    // Виведення фінального результату
    printf("Фінальний об'єкт: Вага = %.2f, координати (%.2f, %.2f)\n", 
           bodies[0].weight, bodies[0].posX, bodies[0].posY);

    free(bodies);
    return 0;
}