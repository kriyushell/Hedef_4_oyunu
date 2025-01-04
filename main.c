//
// Created by Bahattin on 4.01.2025.
//

#include <stdio.h>


int board[6][7] = {
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '}
};
int counter = 1;
char current_player;
const char players[2][8] = {"Kirmizi", "Yesil"};

void print_board();
void print_info();
int check_to_win(int current_player);
int play(int current_player);

//////// MAIN ////////
int main() {
    print_info();
    print_board();



    int wasnt_it_placed;
    while(1){
        current_player = counter % 2;
        printf("%s Oyuncu: ", players[current_player]);

        wasnt_it_placed = play(current_player);


        while (wasnt_it_placed){
            printf("\n\nIstediginiz sutun dolu!! baska bir sutun secin!!\n\n");
            printf("%s Oyuncu: ", players[current_player]);
            wasnt_it_placed = play(current_player);
        }

        // print the board
        printf("\b");
        print_board();

        if(check_to_win(current_player)){
            printf("\n\n === Tebriklleer ===\n\n");
            printf("%s Oyuncu Kazandi !!!\n", players[current_player]);
            printf("Oyun bitti !!!\n");
            printf("cikmak icin bir tusa basin");
            getchar();
            getchar();
            break;
        }


        if(counter == 42){
            printf("Oyun Berabere bitti!\n");
            printf("cikmak icin bir tusa basin");
            getchar();
            getchar();
            break;
        }
        counter++;
    }
}



//////// FUNCTIONS ////////

void print_board(){


    for (int i = 1; i < 8; ++i) printf("|%d", i);
    printf("|\n");

    for (int i = 0; i < 15; ++i) printf("-");
    printf("\n");
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x <7; x++) {
            printf("|%c", board[y][x]);
        }
        printf("|\n");
    }

    for (int i = 0; i < 15; ++i) printf("-");

    printf("\n\n\n");
}

void print_info(){
    printf(" ------------------------ Hedef 4 Oyununa Hos geldiniz!!! ------------------------ \n");
    printf("Hedef 4 oyununda kurallar basittir. iki oyuncu vardir kirmizi(r) oyuncu ve yesil(g) oyuncu\n");
    printf("sirayla kutunun uzerinden numaralandirilmis deliklerden bir tas atarlar daha sonra sira diger oyuncuya gecer\n");
    printf("eger atilan taslardan 4 tane ayni renk ayni anda anda sag, sol, yukari, asagi ve capraz olmak sartiyla yanyana gelirse\n");
    printf("oyunu o rengin sahibi kazanir ve oyun biter. not: 1 den 7 ye kadar olan bir sayi girmeniz yeterli\n\n\n");
}

int play(int current_player){
    int column_number;
    scanf("%d", &column_number);
    column_number--;

    int wasnt_it_placed = 1;
    for (int y = 5; y >= 0 ; y--) {
        if(board[y][column_number] == ' '){
            board[y][column_number] = current_player ? 'g' : 'r';
            wasnt_it_placed = 0;
            break;
        }
    }

    return wasnt_it_placed; // next player's turn
    // yerleştirilmemişse tekrar yerleştirilmesi istenir.
}
int check_to_win(int current_player) {
    char color = current_player ? 'g':'r';

    // yatay kontrol
    for (int y = 5; y >= 0; y--) {
        for (int i = 0; i <4; i++) {
            if( board[y][i] == color &&
                board[y][i+1] == color &&
                board[y][i+2] == color &&
                board[y][i+3] == color ){
                return 1;
            }
        }
    }

    // dusey kontrol
    for (int x = 0; x < 7; x++) {
        for (int i = 5; i >= 3; i--) {
            if( board[i][x] == color &&
                board[i - 1][x] == color &&
                board[i - 2][x] == color &&
                board[i - 3][x] == color ){
                return 1;
            }
        }
    }

    // capraz yatak kontrol
    for (int y = 5; y >= 3; y--) {
        for (int x = 0; x <= 3; x++) {
            if( board[y][x] == color &&
                board[y - 1][x + 1] == color &&
                board[y - 2][x + 2] == color &&
                board[y - 3][x + 3] == color ){
                return 1;
            }
        }
    }

    // capraz dusey kontrol
    for (int y = 5; y >= 3; y--) {
        for (int x = 6; x >= 3; x--) {
            if( board[y][x] == color &&
                board[y - 1][x - 1] == color &&
                board[y - 2][x - 2] == color &&
                board[y - 3][x - 3] == color ){
                return 1;
            }
        }
    }

    return 0;
}
