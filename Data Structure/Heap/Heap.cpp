// Heap Using Array

#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

int heap[SIZE + 1] = {0};
int curr_size = 0;

void swap(int *a, int * b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void up_heap(int pos) {
    // Base Case
    if(pos == 1) {
        return;
    }
    int parent = pos / 2;
    if(heap[parent] > heap[pos]) {
        swap(&heap[parent], &heap[pos]);
        up_heap(parent);
    }
}

void insert(int value) {
    if(curr_size == SIZE) {
        puts("FULL");
        return;
    }
    heap[curr_size + 1] = value;
    curr_size += 1;

    // up_heap -> validate min heap rules
    up_heap(curr_size);
}

bool search(int value) {
    for(int i = 1; i <= curr_size; i++) {
        if(heap[i] == value) {
            return true;
        }
    }
    return false;
}

int get_min(int a, int b) {
    if(b > curr_size) return a;
    return (heap[a] > heap[b]) ? b : a;
}

void down_heap(int pos) {
    // base case
    int left_child = 2 * pos;
    int right_child = (2 * pos) + 1;
    if(left_child <= curr_size) {
        int min = get_min(left_child, right_child);
        if(heap[pos] > heap[min]) {
            swap(&heap[pos], &heap[min]);
            down_heap(min);
        }
    }
    else return;
}

void delete_heap() {
    if(curr_size == 0) return;

    int minimum = heap[1];
    swap(&heap[1], &heap[curr_size]);
    curr_size -= 1;
    if(curr_size > 0) {
        down_heap(1);
    }
}

int main() {
    // insert heap
    insert(10);
    insert(20);
    insert(30);
    insert(40);
    insert(5);

    //Print heap
    for(int i = 1; i <= curr_size; i++) {
        printf("%d\n", heap[i]);
    }

    puts("");
    // Search
    if(search(40)) {
        puts("40 Found!");
    }
    else {
        puts("40 Not Found!");
    }

    if(search(100)) {
        puts("100 Found!");
    }
    else {
        puts("100 Not Found!");
    }

    puts("");
    delete_heap();
    for(int i = 1; i <= curr_size; i++) {
        printf("%d\n", heap[i]);
    }

    return 0;
}
