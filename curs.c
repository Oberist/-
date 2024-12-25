#include <stdio.h>
#include <stdlib.h>

// Структура очереди
typedef struct Queue {
    int *data;      // Указатель на массив для хранения элементов
    int front;      // Индекс начала очереди
    int back;       // Индекс конца очереди
    int capacity;   // Максимальный размер очереди
    int size;       // Текущий размер очереди
} Queue;
// Создание очереди с заданной емкостью
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));       // Выделение памяти для структуры
    queue->data = (int*)malloc(capacity * sizeof(int)); // Выделение памяти для массива
    queue->front = 0;                                   // Начальный индекс
    queue->back = -1;                                   // Конечный индекс
    queue->capacity = capacity;                        // Емкость очереди
    queue->size = 0;                                   // Текущий размер очереди
    return queue;
}
// Добавление элемента в очередь
void enqueue(Queue* queue, int value) {
    if (queue->size == queue->capacity) {              // Если очередь заполнена, увеличиваем размер
        queue->capacity *= 2;                          // Увеличиваем емкость в 2 раза
        queue->data = (int*)realloc(queue->data, queue->capacity * sizeof(int));
        if (!queue->data) {                            // Проверка выделения памяти
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }
    queue->back = (queue->back + 1) % queue->capacity; // Оборачивание индекса конца очереди
    queue->data[queue->back] = value;                 // Добавляем элемент
    queue->size++;                                    // Увеличиваем размер
}
// Удаление элемента из очереди
int dequeue(Queue* queue) {
    if (queue->size == 0) {                            // Если очередь пуста
        printf("Queue is empty.\n");
        return -1;
    }
    int value = queue->data[queue->front];            // Получаем значение из начала очереди
    queue->front = (queue->front + 1) % queue->capacity; // Сдвигаем индекс начала очереди
    queue->size--;                                    // Уменьшаем размер
    return value;                                     // Возвращаем удаленное значение
}
// Проверка, пуста ли очередь
int isEmpty(Queue* queue) {
    return queue->size == 0;                          // Возвращает 1, если очередь пуста
}
// Проверка, заполнена ли очередь
int isFull(Queue* queue) {
    return queue->size == queue->capacity;           // Возвращает 1, если очередь заполнена
}
// Освобождение памяти, занятой очередью
void freeQueue(Queue* queue) {
    free(queue->data);                                // Освобождаем память для массива
    free(queue);                                      // Освобождаем память для структуры
}
// Пример работы с очередью
int main() {
    int initialCapacity = 5;
    Queue* queue = createQueue(initialCapacity);
    // Добавление элементов в очередь
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 5);
    printf("Dequeued: %d\n", dequeue(queue));         // Удаление элемента
    printf("Dequeued: %d\n", dequeue(queue));
    // Добавление дополнительных элементов
    enqueue(queue, 6);
    enqueue(queue, 7);
    // Вывод элементов очереди
    printf("Elements in the queue: ");
    while (!isEmpty(queue)) {
        printf("%d ", dequeue(queue));
    }
    printf("\n");
    // Освобождение памяти
    freeQueue(queue);
    return 0;
}




