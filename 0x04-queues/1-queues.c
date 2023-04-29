/*Implementing a queue using an array in C*/
// queue is a first in first out data structure
#include <stdio.h>

int queue[256];
int count = 0;


/**
 * enqueue - adds an element at the end of the queue
 * @val: the value that is being added to the queue
 * Description: the function adds the element at the end of the queue
*/
void enqueue(int val){
    queue[count] = val;
    count++;
}

/**
 * dequeue - removes an element at the beginning of the queue
 * Return: the dequeued element
 * Description: the function removes the first element of the queue
*/
int dequeue(){
    // int result = queue[0];
    // for (int i = 0; i < count - 1; i++){
    //     queue[i] = queue[i+1];
    // }
    // count--;
    int tmp = 0;
    int result = queue[0];
    for (int i = 1; i < count; i++){
        queue[tmp] = queue[i];
        tmp++;
    }
    count--;
    return result;
}

void print_queue(){
    for (int i = 0; i < count; i++){
        printf("%d\t", queue[i]);
    }
    printf("\n");
}

int main(void){
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    enqueue(60);

    print_queue();
    dequeue();
    print_queue();
    enqueue(70);
    print_queue();
    dequeue();
    print_queue();
    return (0);
}