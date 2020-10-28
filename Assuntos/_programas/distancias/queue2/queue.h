/*
 * queue.h 
 * INTERFACE: funcoes para manipular a fila 
 */

void queueInit(int);
 int queueEmpty();
void queuePut(Item);
Item queueGet();
void queueFree();
