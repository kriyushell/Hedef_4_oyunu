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

struct back_step_data {
    int x_coordinate;
    int y_coordinate;
};

struct back_step_data back_step;

int counter = 0;
char current_player;
const char players[2][8] = {"Kirmizi", "Yesil"};

// Is there a right of withdrawal?
int right_of_withdrawal = 0;

void print_board();
void print_info();
int check_to_win(int current_player);
int play(int current_player);
int check_input_character(char character);

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
            if(wasnt_it_placed == 1){
                printf("\n\nIstediginiz sutun dolu!! baska bir sutun secin!!\n\n");
            }else if (wasnt_it_placed == 2){
                printf("\n\nGecersiz Karakter girdiniz!!!\n");
                printf("lutven sayi[1-7] veya hamleyi geri al ('g', 'G') giriniz\n\n");
            } else if (wasnt_it_placed == 3){
                printf("\n\nGeri alma hakkiniz bitti!!!\n\n");
            }

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
    printf("oyunu o rengin sahibi kazanir ve oyun biter. not: 1 den 7 ye kadar olan bir sayi girmeniz yeterli\n");
    printf("oyunda yanlizca bir hamlenizi geri alma sansiniz vardir. hamlenizi geri almak icin 'g' ve 'G'(geri) giriniz.\n\n\n");
}
int check_input_character(char character){
    if(character >= '1' && character <= '7'){
        return ( (int)character - (int)'7' + 7);
    } else if (character == 'g'){
        return (int)character;
    }else if (character == 'G'){
        return (int)character;
    }else{
        return 0;
    }
}


int play(int current_player){
    char input_character;
    scanf("%c", &input_character);
    // clear buffer
    while (getchar() != '\n');

    int column_number = check_input_character(input_character);
    if(column_number == 0){
        return 2;
    }
    if((char)column_number == 'g' || (char)column_number == 'G'){
        if(right_of_withdrawal == 1){
            board[back_step.y_coordinate][back_step.x_coordinate] = ' ';
            right_of_withdrawal = 0;
            return 0;
        }else{
            return 3;
        }
    }


    column_number--;

    int wasnt_it_placed = 1;
    for (int y = 5; y >= 0 ; y--) {
        if(board[y][column_number] == ' '){
            char player = current_player ? 'g' : 'r';

            board[y][column_number] = player;

            back_step.x_coordinate = column_number;
            back_step.y_coordinate = y;

            right_of_withdrawal = 1;
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

