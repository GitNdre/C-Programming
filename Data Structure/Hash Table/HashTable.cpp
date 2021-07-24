#include <bits/stdc++.h>
const int MAX = 10;

struct Node {
    int value;
    Node *next, *prev;
} *head[MAX], *tail[MAX], *curr;

Node *create_node(int value) {
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->value = value;
    temp->next = temp->prev = NULL;
    return temp;
}

// DJB 2 HASH Algorithm
// unsigned long djb2(int value) {
//   unsigned long hash = 5381;
//   while ((value--)) {
//     hash = ((hash << 5) + hash) + value;
//   }

//   return hash % MAX;
// }

int hashing(int value) {
    value = value % MAX;
    return value;
}

void push_head(int index, int value) {
    Node *temp = create_node(value);
    if(!head[index]) head[index] = tail[index] = temp;
    else if(tail[index]) {
        head[index]->prev = temp;
        temp->next = head[index];
        head[index] = temp;
    }
}

void push_tail(int index, int value) {
    Node *temp = create_node(value);
    if(!tail[index]) head[index] = tail[index] = temp;
    else if(tail[index]) {
        tail[index]->next = temp;
        temp->prev = tail[index];
        tail[index] = temp;
    }
}

void insert(int value) {
    int index = hashing(value);
    if(!head[index]) {
        Node *temp = create_node(value);
        head[index] = tail[index] = temp;
    }
    else if(value < head[index]->value) {
        Node *temp = create_node(value);
        if(!head[index]) head[index] = tail[index] = temp;
        else if(tail[index]) {
            head[index]->prev = temp;
            temp->next = head[index];
            head[index] = temp;
        }
    }
    else if(value > tail[index]->value) {
        Node *temp = create_node(value);
        if(!tail[index]) head[index] = tail[index] = temp;
        else if(tail[index]) {
            tail[index]->next = temp;
            temp->prev = tail[index];
            tail[index] = temp;
        }
    }

    else {
        Node *temp = create_node(value);
        Node *curr = head[index];

        while(curr->value < value) {
        curr = curr->next;
        }
        temp->prev = curr->prev;
        temp->next = curr;
        curr->prev->next = temp;
        curr->prev = temp;
    }
}

void print() {
    for(int i = 0; i < MAX; i++) {
        printf("[%d]: ", i + 1);
        curr = head[i];
        while(curr) {
            printf("%d -> ", curr->value);
            curr = curr->next;
        }
        printf("NULL");
        puts("");
    }
}

void search(int value) {
    int key = hashing(value);
    if(!head[key]) {
        puts("NOT FOUND!");
    }
    else {
        curr = head[key];
        int position = 1; 
        while(curr) {
            if(curr->value == value) break;
            else {
                curr = curr->next;
                position += 1;
            }
        }
        if(curr == NULL) puts("NOT FOUND");
        else {
            printf("%d found, At table number %d, position %d\n", value, key, position);
        }        
    }
}

void pop(int value) {
        int key = hashing(value);
    if(!head[key]) {
        puts("NOT FOUND! Can't delete");
    }
    else if(head[key] == tail[key] && head[key]->value == value) {
        Node *temp = head[key];
        head[key] = tail[key] = NULL;
        free(temp);
    }
    else if(head[key] == tail[key] && head[key]->value != value) {
        puts("NOT FOUND! Can't delete");
    }
    else {
        if(head[key]->value == value) {
            //pophead
            Node *temp = head[key];
            head[key] = head[key]->next;
            temp->next = head[key]->prev = NULL;
            free(temp);
        }   
        else if(tail[key]->value == value) {
            // poptail
            Node *temp = tail[key];
            tail[key] = tail[key]->prev;
            temp->prev = tail[key]->next = NULL;
            free(temp);
        }   
        else {
            curr = head[key];
            while(curr->next->value != value && curr->next != tail[key]) {
                curr = curr->next;
            }
            if(curr->next == tail[key]) {
                puts("NOT FOUND! Can't delete");
            }
            else {
                Node *temp2 = curr->next;
                curr->next = temp2->next;
                temp2->next->prev = curr;
                temp2->next = temp2->prev = NULL;
                free(temp2);
            }
        } 
    }
}

int main() {
    insert(1);
    insert(2);
    insert(11); 
    insert(12);
    insert(13);
    insert(3);
    insert(4);
    insert(5);
    insert(6);
    insert(7);
    insert(8);
    insert(9);
    insert(10);
    print();
    search(8);
    pop(8);
    print();
    return 0;
}
