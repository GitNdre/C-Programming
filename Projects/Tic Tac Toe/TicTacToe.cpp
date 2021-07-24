#include <stdio.h>
#include <stdlib.h>

struct Node {
    int moves;
    Node *next, *prev;
} *head, *tail, *curr;

char board[20][20];
int board_filled = 0;

void menu();
// Linked lists utility
Node *create_node(int moves) {
    Node *temp = (Node *) malloc(sizeof(Node));
    temp->moves = moves;
    temp->next = NULL;
    return temp;
}

void push_head(int moves) {
    Node *temp = create_node(moves);
    if(!head) head = tail = temp;
    else {
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
}

void push_tail(int moves) {
    Node *temp = create_node(moves);
    if(!tail) head = tail = temp;
    else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

void push_mid(int moves) {
  if(!head) {
    Node *temp = create_node(moves);
    head = tail = temp;
  }
  else if(moves < head->moves) push_head(moves);
  else if(moves > tail->moves) push_tail(moves);

  else {
    Node *temp = create_node(moves);
    Node *curr = head;

    while(curr->moves < moves) {
      curr = curr->next;
    }
    temp->prev = curr->prev;
    temp->next = curr;
    curr->prev->next = temp;
    curr->prev = temp;
  }
}

void pop_head() {
    if(!head) return;
    else if(head == tail) {
        free(head);
        head = tail = NULL;
    }
    else {
        Node *new_head = head->next;
        head->next = new_head->prev = NULL;
        free(head);
        head = new_head;
    }
}

void pop_tail() {
    if(!tail) return;
    else if(head == tail) {
        free(head);
        head = tail = NULL;
    }
    else {
        Node *new_tail = tail->prev;
        tail->prev = new_tail->next = NULL;
        free(tail);
        tail = new_tail;
    }
}

void pop_mid(int moves) {
    if(!head) return;
    else if(head->moves == moves) pop_head();
    else if(head->moves == moves) pop_tail();
    else {
        curr = head;
        while(curr && curr->moves != moves) {
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        curr->prev = curr->next = NULL;
        curr = NULL;
        free(curr);
    }
}

void pop_all() {
    while(head) {
        pop_head();
    }
}

void reset_game() {
    char ctr = '1';
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = ctr;
            ctr += 1;
        }
    }
}

// Print board conditions
void print_board() {
	printf(" %c | %c | %c \n",board[0][0],board[0][1],board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n",board[1][0],board[1][1],board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n",board[2][0],board[2][1],board[2][2]);
};

int check_winning() {
    if(board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X') {
        system("cls");
        print_board();
        puts("Player X Wins");
        return 1;
    }
    else if(board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O') {
        system("cls");
        print_board();
        puts("Player O Wins");
        return 1;
    }
    else if(board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X') {
        system("cls");
        print_board();
        puts("Player O Wins");
        return 1;
    }
    else if(board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O') {
        system("cls");
        print_board();
        puts("Player O Wins");
        return 1;
    }
    else if(board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X') {
        system("cls");
        print_board();
        puts("Player X Wins");
        return 1;
    }
    else if(board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O') {
        system("cls");
        print_board();
        puts("Player O Wins");
        return 1;
    }
    else if(board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X') {
        system("cls");
        print_board();
        puts("Player X Wins");
        return 1;
    }
    else if(board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O') {
        system("cls");
        print_board();
        puts("Player O Wins");
        return 1;
    }
    else if(board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X') {
        system("cls");
        print_board();
        puts("Player X Wins");
        return 1;
    }
    else if(board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O') {
        system("cls");
        print_board();
        puts("Player O Wins");
        return 1;
    }
    else if(board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X') {
        system("cls");
        print_board();
        puts("Player X Wins");
        return 1;
    }
    else if(board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O') {
        system("cls");
        print_board();
        puts("Player O Wins");
        return 1;
    }
    else if(board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') {
        system("cls");
        print_board();
        puts("Player X Wins");
        return 1;
    }
    else if(board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') {
        system("cls");
        print_board();
        puts("Player O Wins");
        return 1;
    }
    else if(board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X') {
        system("cls");
        print_board();
        puts("Player X Wins");
        return 1;
    }
    else if(board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O') {
        system("cls");
        print_board();
        puts("Player O Wins");
        return 1;
    }
}

void gameplay(int player) {
    system("cls");
    print_board();
    int tile = -1;
    do {
        printf("Choose a tile [0 ot undo | 10 to exit]: ");
        scanf("%d", &tile);
        getchar();
        if(tile >= 1 && tile <= 9) {
            board_filled += 1;
        }
    } while(tile < 0 || tile > 10);

    if(tile == 0) {
        // undo
        pop_tail();
    }

    if(tile == 1) {
        push_tail(1);
        if(player == 1) {
            board[0][0] = 'X';
        }
        else if(player == 0) {
            board[0][0] = 'O';
        }
    }

    if(tile == 2) {
        push_tail(2);
        if(player == 1) {
            board[0][1] = 'X';
        }
        else if(player == 0) {
            board[0][1] = 'O';
        }
    }

    if(tile == 3) {
        push_tail(3);
        if(player == 1) {
            board[0][2] = 'X';
        }
        else if(player == 0) {
            board[0][2] = 'O';
        }
    }

    if(tile == 4) {
        push_tail(4);
        if(player == 1) {
            board[1][0] = 'X';
        }
        else if(player == 0) {
            board[1][0] = 'O';
        }
    }

    if(tile == 5) {
        push_tail(5);
        if(player == 1) {
            board[1][1] = 'X';
        }
        else if(player == 0) {
            board[1][1] = 'O';
        }
    }

    if(tile == 6) {
        push_tail(6);
        if(player == 1) {
            board[1][2] = 'X';
        }
        else if(player == 0) {
            board[1][2] = 'O';
        }
    }

    if(tile == 7) {
        push_tail(7);
        if(player == 1) {
            board[2][0] = 'X';
        }
        else if(player == 0) {
            board[2][0] = 'O';
        }
    }

    if(tile == 8) {
        push_tail(8);
        if(player == 1) {
            board[2][1] = 'X';
        }
        else if(player == 0) {
            board[2][1] = 'O';
        }
    }

    if(tile == 9) {
        push_tail(9);
        if(player == 1) {
            board[2][2] = 'X';
        }
        else if(player == 0) {
            board[2][2] = 'O';
        }
    }

    if(tile == 10) {
        // save_and_exit();
    }
}

void new_game() {
    int player = 0;
    while(board_filled < 9) {
        if(player == 0) {
            gameplay(player);
            player = 1;
            if(check_winning() == 1) {
                break;
            }
            continue;
        }
        else if(player == 1) {
            gameplay(player);
            player = 0;
            if(check_winning() == 1) {
                break;
            }
            continue;
        }
    }
    printf("Press enter to the main menu");
    getchar();
    pop_all();
    menu();
}

// Load Game

void load_utils(int player, int tile) {
    if(tile == 0) {
        // undo
        pop_tail();
    }

    if(tile == 1) {
        push_tail(1);
        if(player == 1) {
            board[0][0] = 'X';
        }
        else if(player == 0) {
            board[0][0] = 'O';
        }
    }

    if(tile == 2) {
        push_tail(2);
        if(player == 1) {
            board[0][1] = 'X';
        }
        else if(player == 0) {
            board[0][1] = 'O';
        }
    }

    if(tile == 3) {
        push_tail(3);
        if(player == 1) {
            board[0][2] = 'X';
        }
        else if(player == 0) {
            board[0][2] = 'O';
        }
    }

    if(tile == 4) {
        push_tail(4);
        if(player == 1) {
            board[1][0] = 'X';
        }
        else if(player == 0) {
            board[1][0] = 'O';
        }
    }

    if(tile == 5) {
        push_tail(5);
        if(player == 1) {
            board[1][1] = 'X';
        }
        else if(player == 0) {
            board[1][1] = 'O';
        }
    }

    if(tile == 6) {
        push_tail(6);
        if(player == 1) {
            board[1][2] = 'X';
        }
        else if(player == 0) {
            board[1][2] = 'O';
        }
    }

    if(tile == 7) {
        push_tail(7);
        if(player == 1) {
            board[2][0] = 'X';
        }
        else if(player == 0) {
            board[2][0] = 'O';
        }
    }

    if(tile == 8) {
        push_tail(8);
        if(player == 1) {
            board[2][1] = 'X';
        }
        else if(player == 0) {
            board[2][1] = 'O';
        }
    }

    if(tile == 9) {
        push_tail(9);
        if(player == 1) {
            board[2][2] = 'X';
        }
        else if(player == 0) {
            board[2][2] = 'O';
        }
    }

    if(tile == 10) {
        // save_and_exit();
    }
}

void load_game() {
    int player = 0;
    curr = head;
    if(!curr) {
        puts("Pick new game to start the game!");
        printf("Press enter to continue...");
        getchar();
        menu();
    }
    while(curr) {
        if(player == 0) {
            load_utils(player, curr->moves);
            player = 1;
            if(check_winning() == 1) {
                break;
            }
            continue;
        }
        else if(player == 1) {
            load_utils(player, curr->moves);
            player = 0;
            if(check_winning() == 1) {
                break;
            }
            continue;
        }
        curr = curr->next;
    }
    if(board_filled > 9) {
        pop_all();
        menu();
    }
    else {
        while(board_filled < 9) {
            if(player == 0) {
            load_utils(player, curr->moves);
            player = 1;
            if(check_winning() == 1) {
                break;
            }
            continue;
        }
        else if(player == 1) {
            load_utils(player, curr->moves);
            player = 0;
            if(check_winning() == 1) {
                break;
            }
            continue;
        }
        }
    }
    printf("Press enter to continue...");
    getchar();
    menu();
}

void menu() {
    system("cls");
    puts("1. New Game");
    puts("2. Load Game");
    puts("3. Exit");
    int option = 0;
    while(option < 1 || option > 3) {
        scanf("%d", &option);
        getchar();
    }
    switch (option) {
    case 1:
        reset_game();
        new_game();
        break;
    case 2:
        load_game();
        break;
    case 3:
        return;
    }
}

int main() {
    menu();
}
