#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<strings.h>

//Define a player.
struct Player
{
    char name[100];
    int score;
    char difficulty[10];
};

//Define gotoxy ... Code::Blocks (My IDE) does not support conio.h.
int gotoxy(int x,int y)
{
    COORD coord = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//This function that catch x, y, score and life from input, create a 2n*n Map (cordinate).
void createMap(int x, int y, int score, int life)
{
    //print SCORE and LIFE above the map.
    gotoxy(0,0);
    printf("SCORE : %d", score);
    gotoxy(x-8, 0);
    printf("LIFE : %d", life);
    //create map formatting.
    for(int i = 1; i<x; i++)
    {
        gotoxy(i, 1);
        printf("!");
    }
    for(int j = 1; j<y; j++)
    {
        gotoxy(0, j);
        printf("!");
    }
    for(int i = 1; i<x; i++)
    {
        gotoxy(i, y-1);
        printf("!");
    }
    for(int j = 1; j<y; j++)
    {
        gotoxy(x, j);
        printf("!");
    }
    printf("\n");
}

//This function that catch snake_length and snake from input, print your snake in your map.
void print_snake(int snake_length, int snake[][2])
{
    for(int i = 1; i<snake_length; i++)
    {
        gotoxy(snake[i][0], snake[i][1]);
        printf("*");
    }
    //Head of the snake.
        gotoxy(snake[0][0], snake[0][1]);
        printf("S");
}
//This function get arrow key from the keyboard in user pc and return array number (see array numbers in Ascii table).
int get_arrow(int arr)
{
    //if key hit in a keyboard
    if(kbhit())
    {
        char ch;
        switch(getch())
        {
            case 0:
            case 224:
                ch = _getch();
                //Don't back and eat yourself...
                if(arr==77&&ch==75)
                    return 77;
                if(arr==75&&ch==77)
                    return 75;
                if(arr==80&&ch==72)
                    return 80;
                if(arr==72&&ch==80)
                    return 72;
                return ch;
                break;
            //Enter Exit to pause the game
            case 27:
                return 0;
                break;
            default:
                return arr;
                break;
        }
    }
    else
    {
        return arr;
    }

}
//This function control the connection of the snake body and handle it by arrows that user enter.
void handle_snake(int snake_length ,int arr, int snake[][2])
{
    //bc and bc2 are for that the system don't forget where snake in.
    int bc[2];
    int bc2[2];
    int o = 0;
    bc[0] = snake[0][0];
    bc[1] = snake[0][1];
    //last_bc is for that when the snake go right, the lastest part of the snake body going to be gone.
    int last_bc[2];
    last_bc[0] = snake[snake_length-1][0];
    last_bc[1] = snake[snake_length-1][1];
    //If user enter up arrow key
    if(arr == 72)
    {
        snake[0][1]--;
        for(int c = 1; c<snake_length; c++)
        {
            if(o==0)
            {
                bc2[0] = snake[c][0];
                bc2[1] = snake[c][1];
                snake[c][0] = bc[0];
                snake[c][1] = bc[1];
                o = 1;
            }
            else
            {
                bc[0] = snake[c][0];
                bc[1] = snake[c][1];
                snake[c][0] = bc2[0];
                snake[c][1] = bc2[1];
                o = 0;
            }
        }
    }
    //If user enter left arrow key
    else if(arr == 75)
    {
        snake[0][0]--;
        for(int c = 1; c<snake_length; c++)
        {
            if(o==0)
            {
                bc2[0] = snake[c][0];
                bc2[1] = snake[c][1];
                snake[c][0] = bc[0];
                snake[c][1] = bc[1];
                o = 1;
            }
            else
            {
                bc[0] = snake[c][0];
                bc[1] = snake[c][1];
                snake[c][0] = bc2[0];
                snake[c][1] = bc2[1];
                o = 0;
            }
        }
    }
    //If user enter right arrow key
    else if(arr == 77)
    {
        snake[0][0]++;
        for(int c = 1; c<snake_length; c++)
        {
            if(o==0)
            {
                bc2[0] = snake[c][0];
                bc2[1] = snake[c][1];
                snake[c][0] = bc[0];
                snake[c][1] = bc[1];
                o = 1;
            }
            else
            {
                bc[0] = snake[c][0];
                bc[1] = snake[c][1];
                snake[c][0] = bc2[0];
                snake[c][1] = bc2[1];
                o = 0;
            }
        }
    }
    //If user enter down arrow key
    else if(arr == 80)
    {
        snake[0][1]++;
        for(int c = 1; c<snake_length; c++)
        {
            if(o==0)
            {
                bc2[0] = snake[c][0];
                bc2[1] = snake[c][1];
                snake[c][0] = bc[0];
                snake[c][1] = bc[1];
                o = 1;
            }
            else
            {
                bc[0] = snake[c][0];
                bc[1] = snake[c][1];
                snake[c][0] = bc2[0];
                snake[c][1] = bc2[1];
                o = 0;
            }
        }
    }
    else
    {

    }
    gotoxy(last_bc[0], last_bc[1]);
    printf(" ");
}
//This function visible a Food as F in our Map.
void generateFood(int n, int p[2], int snake_length, int snake[][2])
{
    time_t t;
    srand((unsigned) time(&t));
    int i[2];
    int x, y, flag = 1;
    do
    {
        //Create a random point (F).
        x = (rand()%((n*2-3)))+2;
        y =(rand()%(n-3))+2;
        for(int i = 0; i<snake_length; i++)
        {
            if(snake[i][0]==x&&snake[i][1]==y)
                flag = 0;
            else
                flag = 1;
        }

    }while(!flag);
    p[0] = x;
    p[1] = y;
}
//This function, check If your snake eat itself or hit the wall return 0 (Sick snake) else return 1 (Healthy snake)!
int checkSnakeHealth(int n, int snake_length, int snake[][2], int *arr)
{
    for(int i = 0; i<snake_length; i++)
    {
        for(int j = i+1; j<snake_length; j++)
        {
            if(snake[i][0]==snake[j][0]&&snake[i][1]==snake[j][1])
                return 0;
        }
    }
    //SaqfOKaf means up and down of the map
    for(int i = 1; i<=n*2; i++)
    {
        if((snake[0][0]==i&&snake[0][1]<=1))
            return 0;
        else if((snake[0][0]==i&&snake[0][1]>=n-1))
        {
            return 0;
        }
    }
    //Divareha means walls
    for(int j = 1; j<=n*2; j++)
    {
        if((snake[0][0]<=0&&snake[0][1]==j)||(snake[0][0]>=n*2&&snake[0][1]==j))
            return 0;
    }

    return 1;
}
//This function check Is your snake eat his food or not, if turn SCORE to SCORE+10, else, waiting for snake to go and eat it's food.
void checkEatFood(int *eat, int *pt, int bcp[2], int point[2], int snake[][2], int bcps[2], int *xp, int *snake_length, int n, int *first, int *score, int life)
{
    if(point[0]==snake[0][0]&&point[1]==snake[0][1])
        {
            *eat = 1;
            *pt = 1;
            *score = *score + 10;
            gotoxy(0, 0);
            printf("SCORE : %d", *score);
            gotoxy(n*2-8, 0);
            printf("LIFE : %d", life);
            bcp[0] = point[0];
            bcp[1] = point[1];
            //snake_length++;
        }
        if(*eat||*first)
        {
            generateFood(n, point, *snake_length, snake);
        }
        //Wait that for last part of the snake body point equals to previous food point then turn snake_length to snake_length+1 (Digestion process).
        if(*xp)
        {
            snake[*snake_length][0] = bcps[0];
            snake[*snake_length][1] = bcps[1];
            *snake_length = *snake_length+1;
            *xp = 0;
        }
        //Create a backup of the last part of the snake body.
        if(*pt&&snake[*snake_length-1][0]==bcp[0]&&snake[*snake_length-1][1]==bcp[1])
        {
            bcps[0] = snake[*snake_length-1][0];
            bcps[1] = snake[*snake_length-1][1];
            *xp = 1;
            *pt = 0;
        }

        gotoxy(point[0], point[1]);
        printf("F");
        *first = 0;
        *eat = 0;
}
//This function generates a Life point (L) in your Map.
void generateLife(int n, int snake[][2], int *life, int point[2], int *isInMap, int score, int snake_length)
{
    time_t t;
    srand((unsigned) time(&t));
    //With a probability of 1/15 this point appears.
    if((rand()%15)==7&&!*isInMap)
    {
        int x, y, flag = 1;
        do
        {
            x = (rand()%((n*2-3)))+2;
            y =(rand()%(n-3))+2;
            for(int i = 0; i<snake_length; i++)
            {
                if(snake[i][0]==x&&snake[i][1]==y)
                    flag = 0;
                else
                    flag = 1;
            }

        }while(!flag);
        point[0] = x;
        point[1] = y;
        *isInMap = 1;
    }
    //With a probability of 1/20, this point disappears.
    if((rand()%20)==19&&*isInMap)
    {
        gotoxy(point[0], point[1]);
        printf(" ");
        *isInMap = 0;
    }
    //When snake eat the Life point.
    if(snake[0][0]==point[0]&&snake[0][1]==point[1]&&*isInMap)
    {
        point[0] = -1;
        point[1] = -1;
        *isInMap = 0;
        *life = *life + 1;
        gotoxy(0, 0);
        printf("SCORE : %d", score);
        gotoxy(n*2-8, 0);
        printf("LIFE : %d", *life);
    }
    //Print L point in your map.
    if(*isInMap)
    {
        gotoxy(point[0], point[1]);
        printf("L");
    }

}
//This function keeps your score in a file next to the game source every time you play.
void writeScores(struct Player player1)
{
    FILE *cfPtr;
    cfPtr = fopen("scores.dat", "ab");
    fwrite(&player1, sizeof(struct Player), 1, cfPtr);
    fclose(cfPtr);
}
//At the end of the game, when you no longer want to play, this function shows you the highest score of all users who have played this game, respectively. If the score of two users is equal, it sorts them by their name.
void printHighScores()
{
    FILE *cfPtr;
    int c = 0;
    //Reads from Scores.dat file.
    cfPtr = fopen("scores.dat", "rb");
    struct Player players[100];
    while(!feof(cfPtr))
        fread(&players[c++], sizeof(struct Player), 1, cfPtr);
    fclose(cfPtr);
    //Sort by scores.
    for(int i = 0; i<c-1; i++)
    {
        int maxIndex = i, maxScore = players[i].score;
        for(int j = i+1; j<c-1; j++)
        {
            if(players[j].score>maxScore)
                maxIndex = j, maxScore = players[j].score;
        }
        struct Player playerBc;
        playerBc = players[i];
        players[i] = players[maxIndex];
        players[maxIndex] = playerBc;
    }
    //Sort by names.
    for(int i = 0; i<c-1; i++)
    {
        int minIndex = i;
        char minName = players[i].name[0];
        for(int j = i+1; j<c-1; j++)
        {
            if(players[j].name[0]<minName&&players[j].score==players[i].score)
                minIndex = j, minName = players[j].name[0];
        }
        struct Player playerBc;
        playerBc = players[i];
        players[i] = players[minIndex];
        players[minIndex] = playerBc;
    }
    //Print the Header of Scores list.
    printf("\n%-20s%-20s%-10s\n", "Name", "Score", "Difficulty");
    for(int i = 0; i<c-1; i++)
    {
        printf("%-20s%-20d%-10s\n", players[i].name, players[i].score, players[i].difficulty);
    }
}
int main()
{
    while(1)
    {
        int n, diff;
        printf("Your Codrinate is 2n*n\nEnter n>=10\tthen enter game difficulty from\t1:Easy\t2:Medium\t3:Hard\nn = ");
        scanf("%d", &n);
        printf("Difficulty = ");
        scanf("%d", &diff);
        if(!(diff>0&&diff<=3)||!(n>=10))
        {
            printf("Wrong input!");
            getch();
            return 0;
        }
        const int LEVEL = 1000000/(diff*(n/3));
        int snake[n*n][2];
        snake[0][0] = 4;
        snake[0][1] = 2;
        snake[1][0] = 3;
        snake[1][1] = 2;
        snake[2][0] = 2;
        snake[2][1] = 2;
        snake[3][0] = 1;
        snake[3][1] = 2;
        int snake_length = 4, score = 0, life = 1;
        int arr = 77, pt = 0, xp = 0;
        int eat = 0, first = 1;
        int point[2], bcp[2], bcps[2];
        int pointLife[2], isInMap = 0, c = 0, playAgain = 0;
        system("cls");
        createMap(n*2, n, score, life);
        while(1)
        {
            handle_snake(snake_length, arr, snake);
            /*for(int i = 0; i<snake_length; i++)
            {
                printf("%d ", snake[i][0]);
            }*/
            print_snake(snake_length, snake);
            checkEatFood(&eat, &pt, bcp, point, snake, bcps, &xp, &snake_length, n, &first, &score, life);
            generateLife(n, snake, &life, pointLife, &isInMap, score, snake_length);
            arr = get_arrow(arr);
            if(!checkSnakeHealth(n, snake_length, snake, &arr))
            {
                if(life==0)
                {
                    while(++c!=3)
                    {
                        system("cls");
                        printf("GAMEOVER!");
                        usleep(500000);
                        system("cls");
                        printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s","                                 _,.-------.,_", "                            ,;~'             '~;,", "                          ,;                     ;,", "                         ;                         ;", "                        ,'                         ',", "                       ,;                           ;,", "                       ; ;      .           .      ; ;", "                       | ;   ______       ______   ; |", "                       |  `/~'     ~' . '~     '~\\'  |", "                       |  ~  ,-~~~^~, | ,~^~~~-,  ~  |", "                        |   |        }:{        |   |", "                        |   l       / | \\       !   |", "                        .~  (__,.--' .^. '--.,__)  ~.", "                        |     ---;' / | \\ `;---     |", "                         \\__.       \\/^\\/       .__/", "                          V| \                 / |V", "       __                  | |T~\___!___!___/~T| |                  _____", "    .-~  ~'-.              | |`IIII_I_I_I_IIII'| |               .-~     '-.", "   /         \             |  \,III I I I III,/  |              /           Y", "  Y          ;              \   `~~~~~~~~~~'    /               i           |", "  `.   _     `._              \   .       .   /               __)         .'", "    )=~         `-.._           \.    ^    ./           _..-'~         ~'<_", " .-~                 ~`-.._       ^~~~^~~~^       _..-'~                   ~.", "/                          ~`-.._           _..-'~                           Y", "{        .~'-._                  ~`-.._ .-'~                  _..-~;         ;", " `._   _,'     ~`-.._                  ~`-.._           _..-'~     `._    _.-", "    ~~'              ~`-.._                  ~`-.._ .-'~              ~~'~", "  .----.            _..-'  ~`-.._                  ~`-.._          .-~~~~-.", " /      `.    _..-'~             ~`-.._                  ~`-.._   (        '.", "Y        `=--~                  _..-'  ~`-.._                  ~`-'         |", "|                         _..-'~             ~`-.._                         ;", "`._                 _..-'~                         ~`-.._            -._ _.'", "   '-.='      _..-'~                                     ~`-.._        ~`.", "    /        `.                                                ;          Y", "   Y           Y                    -By Amin Seifi            Y           |", "   |           ;                        Dr.Kouhsar            `.          /", "   `.       _.'                                     ", "     ~-----'\n\n");
                        usleep(500000);
                    }
                    system("cls");
                    struct Player player1;
                    printf("Would you want to play again?(y/N) ");
                    char pA;
                    scanf("%c", &pA);
                    do
                    {
                        scanf("%c", &pA);
                        if(pA=='y')
                        {
                            playAgain = 1;
                            break;
                        }
                        else if(pA=='N'||pA=='n')
                        {
                            playAgain = 0;
                        }
                    }while(!(pA=='y'||pA=='N'||pA=='n'));

                    printf("Enter your name please : ");
                    scanf("%s", player1.name);
                    player1.score = score;
                    switch(diff)
                    {
                        case 1:
                            strcpy(player1.difficulty, "EASY");
                            break;
                        case 2:
                            strcpy(player1.difficulty, "MEDIUM");
                            break;
                        case 3:
                            strcpy(player1.difficulty, "HARD");
                            break;
                    }

                    writeScores(player1);

                break;
                }
                else
                {
                    life--;
                }
            }

            usleep(LEVEL);
        }
        if(playAgain)
        {
            system("cls");
            continue;
        }
        else
        {
            printHighScores();
            printf("\nThank you for playing my game.\nTel: +989105377044\tMail: seifi@aut.ac.ir, aminseiifi@gmail.com\nContact me for a quote, help or join the team!\n");
            getch();
            break;
        }
    }
    return 0;
    //sleep(1);
    //system("cls");
}
