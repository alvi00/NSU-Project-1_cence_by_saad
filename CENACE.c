#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define INITIAL_POINT "2"
#define MAX_POINT 300
#define MIN_POINT 1
#define WIN_REWORD 3
#define DRAW_REWORD 1
#define PUNISHMENT 1

int  player;
char player_X, player_O;
int  win;
char move, mark;
int  O_move_count;
char O_paths[5][50] = {'\0'};
char gameboard[10]; //this is a string
char auto_train;
int  auto_train_count, total_training_match;
int  exit_CENACE;
int  match, CENACEscore, humanScore;

void choose_player();
void inputmove();
void newboard();
void printboard();
int  checkwin();
int  space_in_board();
void updateLearning_data();
void menu();
void CENACE_intro();
void updateGraphing_data();
void updateGraphing_data();
void scoreUpdate();

int main()
{
    system("cls");
    CENACE_intro();
    menu();
    if(exit_CENACE) 
    {
        system("cls");
        Sleep(250);
        return 0;
    }
    system("mkdir Learning_data");
    system("mkdir Graphing_data");

    start:
    auto_train_count = 0;
    O_move_count = 0;
    match = 1;
    CENACEscore = 0;
    humanScore = 0;

    while(1)
    {
        player = 1;
        newboard();
        choose_player();
        do
        {
            if(player % 2)
            {
                player = 1;
                mark = 'O';
            }
            else
            {
                player = 2;
                mark = 'X';
            }
            system("cls");
            printboard();
            inputmove();

            if(move == '1' && gameboard[0] == ' ')
            {
                gameboard[0] = mark;
            }
            else if(move == '2' && gameboard[1] == ' ')
            {
                gameboard[1] = mark;
            }
            else if(move == '3' && gameboard[2] == ' ')
            {
                gameboard[2] = mark;
            }
            else if(move == '4' && gameboard[3] == ' ')
            {
                gameboard[3] = mark;
            }
            else if(move == '5' && gameboard[4] == ' ')
            {
                gameboard[4] = mark;
            }
            else if(move == '6' && gameboard[5] == ' ')
            {
                gameboard[5] = mark;
            }
            else if(move == '7' && gameboard[6] == ' ')
            {
                gameboard[6] = mark;
            }
            else if(move == '8' && gameboard[7] == ' ')
            {
                gameboard[7] = mark;
            }
            else if(move == '9' && gameboard[8] == ' ')
            {
                gameboard[8] = mark;
            }
            else
            {
                printf("\a\n\tINVALID MOVE!");
                fflush(stdin);
                getch();
                player --;
            }

            win = checkwin();
            if(win == 1)
            {
                scoreUpdate();
                system("cls");
                printboard();
                if(player == 1)
                {
                    printf("\n\n\t>> Player-O won! <<");
                }
                else
                {
                    printf("\n\n\t>> Player-X won! <<");
                }

                updateLearning_data();
                updateGraphing_data();
            }
            else if(win == -1)
            {
                scoreUpdate();
                system("cls");
                printboard();
                printf("\n\n\t>> Draw! <<");

                updateLearning_data();
                updateGraphing_data();
            }

            player ++;

        }while(win == 0);

        //Printing all paths
        printf("\nFile paths: ");
        for(int i = 0; i < O_move_count; i++)
        {
            printf("\n   %s", O_paths[i]);
        }
        
        //Asking user if he/she wants to play again
        if(auto_train != 'y' && auto_train != 'Y')
        {
            char ask;
            printf("\n\n\tPlay again? (y/n) --> ");
            while(1)
            {
                ask = getch();
                printf("%c",ask);
                if(ask == 'y' || ask == 'Y')
                {
                    O_move_count = 0;
                    break;
                }
                else if(ask == 'n' || ask == 'N')
                {
                    system("cls");
                    O_move_count = 0;
                    menu();
                    if(exit_CENACE) 
                    {
                        system("cls");
                        Sleep(250);
                        return 0;
                    }
                    else goto start;
                }
                else if(ask == 8)
                {
                    printf(" \a");
                }
                else if(ask == 13)
                {
                    printf("\t                      ");
                    printf("\n\n\tPlay again? (y/n) --> ");
                }
                else
                {
                    printf("\b \b\a");
                }
            }
        }

        if(auto_train == 'y' || auto_train == 'Y')
        {
            auto_train_count ++;
            O_move_count = 0;
            if(auto_train_count == total_training_match)
            {
                printf("\n\n\tTraining complete.");
                printf("\n\tPress any key to continue. ");
                getch();
                auto_train = 'n';
                system("cls");
                menu();
                if(exit_CENACE) 
                {
                    system("cls");
                    Sleep(250);
                    return 0;
                }
                else goto start;
            }
        }
        match ++;
    }
}

void choose_player()
{
    player_O = '2'; //2 = Computer(CENACE)
    player_X = '1'; //1 = Human
    
    
    // while(1)
    // {
    //     printf("\n\n\tChoose Player-X: 1. Human");
    //     printf("\n\t                 2. Computer");
    //     printf("\n\n\t==> ");
    //     player_X = getch();
    //     printf("%c", player_X);
    //     if(player_X != '1' && player_X != '2')
    //     {
    //         printf("\n\tINVALID OPTION!\n");
    //         continue;
    //     }
    //     break;
    // }

    // while(1)
    // {
    //     printf("\n\n\tChoose Player-O: 1. Human");
    //     printf("\n\t                 2. Computer");
    //     printf("\n\n\t==> ");
    //     player_O = getch();
    //     printf("%c", player_O);
    //     if(player_O != '1' && player_O != '2')
    //     {
    //         printf("\n\tINVALID OPTION!\n");
    //         continue;
    //     }
    //     break;
    // }
    
}

void inputmove()
{
    //Input from human or auto input move while in auto train
    if(player == 2)
    {
        if(auto_train != 'y' && auto_train != 'Y')
        {
            printf("\n\n\tEnter your move (1-9): ");
            move = getch();
        }

        else
        {
            char anti_mark;
            if(mark == 'X') anti_mark = 'O';
            else anti_mark = 'X';

            if     (gameboard[0] == mark && gameboard[1] == mark && gameboard[2] == ' ') move = '3';
            else if(gameboard[1] == mark && gameboard[2] == mark && gameboard[0] == ' ') move = '1';
            else if(gameboard[0] == mark && gameboard[2] == mark && gameboard[1] == ' ') move = '2';

            else if(gameboard[3] == mark && gameboard[4] == mark && gameboard[5] == ' ') move = '6';
            else if(gameboard[4] == mark && gameboard[5] == mark && gameboard[3] == ' ') move = '4';
            else if(gameboard[3] == mark && gameboard[5] == mark && gameboard[4] == ' ') move = '5';

            else if(gameboard[6] == mark && gameboard[7] == mark && gameboard[8] == ' ') move = '9';
            else if(gameboard[7] == mark && gameboard[8] == mark && gameboard[6] == ' ') move = '7';
            else if(gameboard[6] == mark && gameboard[8] == mark && gameboard[7] == ' ') move = '8';

            else if(gameboard[0] == mark && gameboard[3] == mark && gameboard[6] == ' ') move = '7';
            else if(gameboard[3] == mark && gameboard[7] == mark && gameboard[0] == ' ') move = '1';
            else if(gameboard[0] == mark && gameboard[6] == mark && gameboard[3] == ' ') move = '4';

            else if(gameboard[1] == mark && gameboard[4] == mark && gameboard[7] == ' ') move = '8';
            else if(gameboard[4] == mark && gameboard[7] == mark && gameboard[1] == ' ') move = '2';
            else if(gameboard[1] == mark && gameboard[7] == mark && gameboard[4] == ' ') move = '5';

            else if(gameboard[2] == mark && gameboard[5] == mark && gameboard[8] == ' ') move = '9';
            else if(gameboard[5] == mark && gameboard[8] == mark && gameboard[2] == ' ') move = '3';
            else if(gameboard[2] == mark && gameboard[8] == mark && gameboard[5] == ' ') move = '6';

            else if(gameboard[0] == mark && gameboard[4] == mark && gameboard[8] == ' ') move = '9';
            else if(gameboard[4] == mark && gameboard[8] == mark && gameboard[0] == ' ') move = '1';
            else if(gameboard[0] == mark && gameboard[8] == mark && gameboard[4] == ' ') move = '5';

            else if(gameboard[2] == mark && gameboard[4] == mark && gameboard[6] == ' ') move = '7';
            else if(gameboard[4] == mark && gameboard[6] == mark && gameboard[2] == ' ') move = '3';
            else if(gameboard[2] == mark && gameboard[6] == mark && gameboard[4] == ' ') move = '5';


            else if(gameboard[0] == anti_mark && gameboard[1] == anti_mark && gameboard[2] == ' ') move = '3';
            else if(gameboard[1] == anti_mark && gameboard[2] == anti_mark && gameboard[0] == ' ') move = '1';
            else if(gameboard[0] == anti_mark && gameboard[2] == anti_mark && gameboard[1] == ' ') move = '2';

            else if(gameboard[3] == anti_mark && gameboard[4] == anti_mark && gameboard[5] == ' ') move = '6';
            else if(gameboard[4] == anti_mark && gameboard[5] == anti_mark && gameboard[3] == ' ') move = '4';
            else if(gameboard[3] == anti_mark && gameboard[5] == anti_mark && gameboard[4] == ' ') move = '5';

            else if(gameboard[6] == anti_mark && gameboard[7] == anti_mark && gameboard[8] == ' ') move = '9';
            else if(gameboard[7] == anti_mark && gameboard[8] == anti_mark && gameboard[6] == ' ') move = '7';
            else if(gameboard[6] == anti_mark && gameboard[8] == anti_mark && gameboard[7] == ' ') move = '8';

            else if(gameboard[0] == anti_mark && gameboard[3] == anti_mark && gameboard[6] == ' ') move = '7';
            else if(gameboard[3] == anti_mark && gameboard[7] == anti_mark && gameboard[0] == ' ') move = '1';
            else if(gameboard[0] == anti_mark && gameboard[6] == anti_mark && gameboard[3] == ' ') move = '4';

            else if(gameboard[1] == anti_mark && gameboard[4] == anti_mark && gameboard[7] == ' ') move = '8';
            else if(gameboard[4] == anti_mark && gameboard[7] == anti_mark && gameboard[1] == ' ') move = '2';
            else if(gameboard[1] == anti_mark && gameboard[7] == anti_mark && gameboard[4] == ' ') move = '5';

            else if(gameboard[2] == anti_mark && gameboard[5] == anti_mark && gameboard[8] == ' ') move = '9';
            else if(gameboard[5] == anti_mark && gameboard[8] == anti_mark && gameboard[2] == ' ') move = '3';
            else if(gameboard[2] == anti_mark && gameboard[8] == anti_mark && gameboard[5] == ' ') move = '6';

            else if(gameboard[0] == anti_mark && gameboard[4] == anti_mark && gameboard[8] == ' ') move = '9';
            else if(gameboard[4] == anti_mark && gameboard[8] == anti_mark && gameboard[0] == ' ') move = '1';
            else if(gameboard[0] == anti_mark && gameboard[8] == anti_mark && gameboard[4] == ' ') move = '5';

            else if(gameboard[2] == anti_mark && gameboard[4] == anti_mark && gameboard[6] == ' ') move = '7';
            else if(gameboard[4] == anti_mark && gameboard[6] == anti_mark && gameboard[2] == ' ') move = '3';
            else if(gameboard[2] == anti_mark && gameboard[6] == anti_mark && gameboard[4] == ' ') move = '5';

            else
            {
                while(1)
                {
                    //Note that: 1. 'move' is a char.
                    //           2. adding 48 converts an int into a char.
                    move = (char)((rand() % 10) + 48 + 1);
                    if(gameboard[(int)(move - 48) - 1] == ' ')//Accepting computer's input only if there is a blank space
                    {
                        gameboard[9] = '\0';
                        break;
                    }
                    else continue;
                }
            }

        }
        
    }

    //Input from computer
    else
    {
        FILE* file;
        int  i, j = 0, k;
        char current_board[10], cmd[50] = "md Learning_data\\";

        char path[50] = "Learning_data\\";
        char temp[2] = "i";
        char point[4]; //This is a string to store the point read from file
        int  point_list[space_in_board()];
        int  point_pose[space_in_board()];
        int  sum_of_available_move_point = 0;
        
        

        //Creating folder inside learning data starts here
        
        for(i = 0; i <= 8; i ++)
        {
            if(gameboard[i] == ' ')
            {
                current_board[i] = '-';
            }
            else
            {
                current_board[i] = gameboard[i];
            }
        }
        current_board[9] = '\0';//end of string

        strcat(cmd, current_board);
        system(cmd);
        //Creating folder inside learning data ends here

        //Creating the .txt files inside "Learning_data\<FOLDER NAME>\...." starts here
        for(i = 0; i < space_in_board(); i ++)
        {
            point_list[i] = 0;
            point_pose[i] = 0;
        }

        for(i = 0; i < 9; i ++)
        {
            if(gameboard[i] == ' ')
            {
                strcat(path, current_board);
                strcat(path, "\\");
                temp[0] = (char)(i + 1 + 48);
                strcat(path, temp);
                strcat(path, ".txt");
                file = fopen(path, "r");
                    if(file == NULL)//If file doesn't exist then creat file
                    {
                        file = fopen(path, "w");
                        fprintf(file, INITIAL_POINT);
                        fclose(file);

                        file = fopen(path, "r");
                        fgets(point, 4, file); 
                        sum_of_available_move_point += atoi(point);
                        point_list[j] = atoi(point);
                        fclose(file);
                    }
                    else
                    {
                        fgets(point, 4, file); 
                        sum_of_available_move_point += atoi(point);
                        point_list[j] = atoi(point);
                        fclose(file);
                    }
                    point_pose[j] = i;
                    j ++;
                if(i < 8) strcpy(path, "Learning_data\\");
            }
        }
        //Creating the .txt files inside "Learning_data\<FOLDER NAME>\...." ends here

        //Taking input from learning data
        int move_priority[sum_of_available_move_point];

        for(i = 0, j = 0; i < space_in_board(); i ++)
        {
            for(k = 0; k < point_list[i]; k ++)
            {
                move_priority[j] = point_pose[i] + 1;
                j ++;
            }
        }

        printf("\n\n\tEnter your move (1-9): ");
        srand(time(NULL));

        while(1)
        {
            //Note that: 1. 'move' is a char.
            //           2. adding 48 converts an int into a char.
            int move_pose = (rand() % sum_of_available_move_point);
            move = (char)(move_priority[move_pose] + 48);
            if(gameboard[(int)(move - 48) - 1] == ' ')//Accepting computer's input only if there is a blank space
            {
                gameboard[9] = '\0';
                break;
            }
            else continue;
        }
        printf("%c", move);

        //final current-path for given move
        char name_of_txt_file [2] = {move, '\0'};
        strcpy(path, "Learning_data\\");
        strcat(path, current_board);
        strcat(path, "\\");
        strcat(path, name_of_txt_file);
        strcat(path, ".txt");

        strcpy(O_paths[O_move_count], path);
        O_move_count ++;
    }
}

void newboard()
{
    int i;
    gameboard[9] = '\0';
    for(i = 0; i < 9; i ++)
    {
        gameboard[i] = ' ';
    }
}

void printboard()
{
    //printf("\n\t\t 1|2|3");
    //printf("\n\t\t 4|5|6");
    //printf("\n\t\t 7|8|9\n");
    if(auto_train == 'y' || auto_train == 'Y')
    {
        printf("\n\t      Match:%4d", match);
        printf("\n      ___________________________");
        printf("\n     |              /            |");
        printf("\n     | CENACE:%4d vs HUMAN:%4d |", CENACEscore, humanScore);
        printf("\n     |_____________/_____________|");
    }

    else
    {
        printf("\n\t      Match:%4d", match);
        printf("\n      ___________________________");
        printf("\n     |              /            |");
        printf("\n     | CENACE:%4d vs HUMAN:%4d |", CENACEscore, humanScore);
        printf("\n     |_____________/_____________|");
    }

    if(player == 1)
    {
        printf("\n\n\t  Player-O, your turn\n");
    }
    else
    {
        printf("\n\n\t  Player-X, your turn\n");
    }

    printf("\n\t       |       |       ");
    printf("\n\t   %c   |   %c   |   %c   ", gameboard[0], gameboard[1], gameboard[2]);
    printf("\n\t_______|_______|_______");
    printf("\n\t       |       |       ");
    printf("\n\t   %c   |   %c   |   %c   ", gameboard[3], gameboard[4], gameboard[5]);
    printf("\n\t_______|_______|_______");
    printf("\n\t       |       |       ");
    printf("\n\t   %c   |   %c   |   %c   ", gameboard[6], gameboard[7], gameboard[8]);
    printf("\n\t       |       |       \n");
}

int checkwin() //1 = win, -1 = draw
{
    if     (gameboard[0] == 'X' && gameboard[1] == 'X' && gameboard[2] == 'X') return 1;
    else if(gameboard[3] == 'X' && gameboard[4] == 'X' && gameboard[5] == 'X') return 1;
    else if(gameboard[6] == 'X' && gameboard[7] == 'X' && gameboard[8] == 'X') return 1;
    else if(gameboard[0] == 'X' && gameboard[3] == 'X' && gameboard[6] == 'X') return 1;
    else if(gameboard[1] == 'X' && gameboard[4] == 'X' && gameboard[7] == 'X') return 1;
    else if(gameboard[2] == 'X' && gameboard[5] == 'X' && gameboard[8] == 'X') return 1;
    else if(gameboard[0] == 'X' && gameboard[4] == 'X' && gameboard[8] == 'X') return 1;
    else if(gameboard[2] == 'X' && gameboard[4] == 'X' && gameboard[6] == 'X') return 1;

    else if(gameboard[0] == 'O' && gameboard[1] == 'O' && gameboard[2] == 'O') return 1;
    else if(gameboard[3] == 'O' && gameboard[4] == 'O' && gameboard[5] == 'O') return 1;
    else if(gameboard[6] == 'O' && gameboard[7] == 'O' && gameboard[8] == 'O') return 1;
    else if(gameboard[0] == 'O' && gameboard[3] == 'O' && gameboard[6] == 'O') return 1;
    else if(gameboard[1] == 'O' && gameboard[4] == 'O' && gameboard[7] == 'O') return 1;
    else if(gameboard[2] == 'O' && gameboard[5] == 'O' && gameboard[8] == 'O') return 1;
    else if(gameboard[0] == 'O' && gameboard[4] == 'O' && gameboard[8] == 'O') return 1;
    else if(gameboard[2] == 'O' && gameboard[4] == 'O' && gameboard[6] == 'O') return 1;

    else if(gameboard[0] != ' ' && gameboard[1] != ' ' && gameboard[2] != ' ' && gameboard[3] != ' ' && gameboard[4] != ' ' && gameboard[5] != ' ' && gameboard[6] != ' ' && gameboard[7] != ' ' && gameboard[8] != ' ')
        return -1;

    else return 0;
}

int space_in_board()
{
    int i, spc = 0;
    for(i = 0; i < 9; i ++)
    {
        if(gameboard[i] == ' ') spc++;
    }
    return spc;
}

void updateLearning_data()
{
    FILE* file;
    int i;
    char point[4];
    int intpoint;        
    
    for(i = 0; i < O_move_count; i ++)
    {
        file = fopen(O_paths[i], "r");
        fgets(point, 4, file);
        intpoint = atoi(point);
        fclose(file);

        if(win == 1 && player == 1) intpoint += WIN_REWORD; //player 1 = CENACE
        else if(win == -1) intpoint += DRAW_REWORD;
        else intpoint -= PUNISHMENT;

        if(intpoint >= MAX_POINT) intpoint = MAX_POINT;
        else if(intpoint <= MIN_POINT) intpoint = MIN_POINT;

        sprintf(point, "%d", intpoint);

        file = fopen(O_paths[i], "w");
        fprintf(file, point);
        fclose(file);
    }
    
}

void menu()
{
    menu:
    exit_CENACE = 0;

    printf("\n\n\t1. Auto Train CENACE");
    printf("\n\t2. Play");
    printf("\n\t3. Rules");
    printf("\n\t4. About");
    printf("\n\t5. Exit");
    printf("\n\n\t--> ");

    char choice = getch();
    printf("%c", choice);

    switch (choice)
    {
        case '1':
        system("cls");

        printf("\n\tTraining may take some time.");
        printf("\n\tDo not exit the program during training.");
        printf("\n\tContinue? (y/n) --> ");

        auto_train = getch();
        printf("%c", auto_train);

        if(auto_train == 'y' || auto_train == 'Y')
        {
            printf("\n\tMatches to be played --> ");
            scanf("%d", &total_training_match);
            fflush(stdin);
        }
        else
        {
            system("cls");
            goto menu;
        }
        return;
        break;
        
        case '2':
        return;
        break;

        case '3':
        system("cls");
        printf("\nUnder development");
        getch();
        system("cls");
        goto menu;
        break;

        case '4':
        system("cls");
        printf("\n     _______________________________________________________");
        printf("\n    |                                                       |");
        printf("\n    | Computer Educable Noughts and Crosses Engine (CENACE) |");
        printf("\n    |_______________________________________________________|\n");

        printf("\n\tAuthor: Aaban Saad Preyanta");
        printf("\n\tNSU ID: 2233389642");
        printf("\n\tBachelor of Computer Science and Engineering");
        printf("\n\tDepartment of Electrical and Computer Engineering");
        printf("\n\tNorth South University, Dhaka, Bangladesh\n");

        printf("\n\tThe name CENACE originated from the 1961 MENACE reinforcement learning model by Donald Michie. ");
        printf("\n\tI have programmed CENACE as a computer simulation of Michie's MENACE. ");
        printf("\n\tInstead of matchboxes, CENACE uses folders and text files to keep track of its moves.\n");
        printf("\n  ____________________________________________________________________________________________________\n\n");

        printf("\n\tMENACE: The Matchbox Educable Noughts and Crosses Engine was a ");
        printf("\n\tmechanical computer made from 304 matchboxes designed and built by ");
        printf("\n\tartificial intelligence researcher Donald Michie in 1961. ");
        printf("\n\tIt was designed to play human opponents in games of noughts and crosses (tic-tac-toe) ");
        printf("\n\tby returning a move for any given state of play ");
        printf("\n\tand to refine its strategy through reinforcement learning. (Wikipedia)");
        
        
        getch();
        system("cls");
        goto menu;
        break;

        case '5':
        exit_CENACE = 1;
        return;
        break;

        default:
        getch();
        system("cls");
        goto menu;
        break;

    }
}

void CENACE_intro()
{
    system("cls");
    printf("\n\t%c%c%c      %c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n\t%c%c%c      %c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n\t%c%c%c      %c%c%c", 219, 219, 219, 219, 219, 219);
    printf("\n\t%c%c%c      %c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n\t%c%c%c      %c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n\t%c%c%c      %c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n\t%c%c%c      %c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n\t%c%c%c      %c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
    Sleep(1500);
    system("cls");

    printf("\n\t%c%c%c", 219, 219, 219);
    printf("\n\t%c%c%c  %c%c", 219, 219, 219, 219, 219);
    printf("\n\t%c%c%c   %c", 219, 219, 219, 219);
    printf("\n\t%c%c%c      %c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("%c",219);
    printf("\n\t%c%c%c      %c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("%c",219);
    printf("\n\t%c%c%c      %c%c%c  %c%c%c  %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n\t%c%c%c      %c%c%c  %c%c%c  %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n\t%c%c%c      %c%c%c  %c%c%c  %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n\t%c%c%c      %c%c%c  %c%c%c  %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n\t%c%c%c      %c%c%c  %c%c%c  %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);

    Sleep(1000);
    system("cls");

    printf("\n\t%c%c%c%c%c%c%c  %c%c%c%c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("%c%c%c%c%c%c%c   %c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);

    printf("\n\t%c%c       %c%c       ", 219, 219);
    printf("%c%c   %c%c   %c%c", 219, 219, 219, 219, 219, 219);

    printf("\n\t%c%c       %c%c       ", 219, 219);
    printf("%c%c   %c%c   %c%c", 219, 219, 219, 219, 219, 219);

    printf("\n\t%c%c       %c%c%c%c%c%c%c  ", 219, 219);
    printf("%c%c   %c%c   %c%c", 219, 219, 219, 219, 219, 219);

    printf("\n\t%c%c       %c%c       ", 219, 219);
    printf("%c%c   %c%c   %c%c", 219, 219, 219, 219, 219, 219);

    printf("\n\t%c%c       %c%c       ", 219, 219);
    printf("%c%c   %c%c   %c%c", 219, 219, 219, 219, 219, 219);

    printf("\n\t%c%c%c%c%c%c%c  %c%c%c%c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("%c%c   %c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);

    printf("\n");

    printf("\n\t%c%c%c%c%c%c%c%c%c%c   ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("%c%c%c%c%c%c%c   %c%c%c%c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    
    printf("\n\t%c%c      %c%c   ", 219, 219, 219, 219);
    printf("%c%c        %c%c       ", 219, 219, 219, 219);
   
    printf("\n\t%c%c      %c%c   ", 219, 219, 219, 219);
    printf("%c%c        %c%c       ", 219, 219, 219, 219);
   
    printf("\n\t%c%c%c%c%c%c%c%c%c%c   ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("%c%c        %c%c%c%c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219, 219);
   
    printf("\n\t%c%c      %c%c   ", 219, 219, 219, 219);
    printf("%c%c        %c%c       ", 219, 219, 219, 219);
   
    printf("\n\t%c%c      %c%c   ", 219, 219, 219, 219);
    printf("%c%c        %c%c       ", 219, 219, 219, 219);
   
    printf("\n\t%c%c      %c%c   ", 219, 219, 219, 219, 219, 219);
    printf("%c%c%c%c%c%c%c   %c%c%c%c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);


    Sleep(1000);
    printf("\n\n\tLoading CENACE %c     0%c", 196, 37);
    int i;
    for(i = 0; i < 100; i += 12)
    {
        Sleep(100);
        printf("\b\b\b\b\b\b\b\b\\    %2d%c", i, 37);
        Sleep(100);
        printf("\b\b\b\b\b\b\b\b/    %2d%c",i + 2, 37);
        Sleep(100);
        printf("\b\b\b\b\b\b\b\b%c    %2d%c", 196, i + 3, 37);
    }
    Sleep(500);
    system("cls");
    Sleep(1000);
}

void updateGraphing_data()
{
    FILE *file_lastScore, *file_scoreList;
    char path1[] = "Graphing_data\\Last_Score.txt";
    char path2[] = "Graphing_data\\Score_List.txt";
    char score[100];
    int  intscore;

    file_lastScore = fopen(path1, "r");
    if(file_lastScore == NULL)
    {
        file_lastScore = fopen(path1, "w");
        fprintf(file_lastScore, 0);
        fclose(file_lastScore);
    }
    fgets(score, 20, file_lastScore);
    intscore = atoi(score);
    fclose(file_lastScore);

    if(win == 1 && player == 1) intscore += WIN_REWORD;
    else if(win == -1) intscore += DRAW_REWORD;
    else intscore -= PUNISHMENT;

    sprintf(score, "%d", intscore);

    file_lastScore = fopen(path1, "w");
    fprintf(file_lastScore, score);
    fclose(file_lastScore);

    file_scoreList = fopen(path2, "a");
    fprintf(file_scoreList, strcat(score, "\n"));
    fclose(file_scoreList);
}

void scoreUpdate()
{
    if(win == 1 && player == 1)
    {
        CENACEscore += WIN_REWORD;
        humanScore -= PUNISHMENT;
    }
    else if(win == 1 && player == 2)
    {
        humanScore += WIN_REWORD;
        CENACEscore -= PUNISHMENT;
    }

    if(win == -1)
    {
        CENACEscore += DRAW_REWORD;
        humanScore +=  DRAW_REWORD;
    }
}

