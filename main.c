#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <dos.h>
#include <mmsystem.h>
#include <string.h>
struct ten       //take the winner's namae and score
{
    int score;
    char name[5000];
};
struct ten swape2[1];           //take name of the last winner to start comparing
struct ten swape1;
struct ten swape[200];          //for only top ten


struct player                   //contain player's name,score,move,number of colour
{
    char name[5000];
    int move;
    int score;
    int colour;

};
struct player one= {"",0,0,0};
struct player two= {"",0,0,0};
int done=0,flagtop10,me,row,col,i,j,noft=0,r1,c1,r2,c2,k=0,co1=1,co2=1,turn=1,box2[100][100]= {{0},{0}},v=0,m=0,counter1=0,counter2=0,colour1,colour2,dots,sy=178,end,end1,box3[100][100]= {{0},{0}},box4[100][100]= {{0},{0}},uc=1,box5[100][100]= {{0},{0}},box6[100][100]= {{0},{0}},box7[100][100]= {{0},{0}},flag=0,crc,ccc,mode,saven,loadn,msn;
int flgr=0,modec=0;
double counter=0;
int g_row,g_col,flag2,flag3,greedy[100][100]= {{0},{0}}; //components used for the greedy mode in computer
char p[5000],o[5000],h[5000],g[5000],q[5000];
/*flagtop10:used to check special case in the top 10 (pre_exsisting of name)
*noft: number of total turns depending on game or size -->calculated (((row-1)*col)*2)-(row-col)
*i:used to loop on the noft(number of turns to end the game)
*counter,counter1,counter2:used for time                    *flag:used in players to check if more plays in redo exist or no
*uc(undo counter): used to count the number of the play that is going to be played and be placed in the arrays
*crc:computer row counter(number of horizontal plays in an arrays) -->calculated (row*2)
*ccc:computer column counter(number of vertical plays in an arrays) -->calculated (col*2)
*mode:determine player vs player or player vs computer
*saven:number of file to save at                            *loadn:number of file to load
*flgr:handle special case when no more plays are't found
*box2:contain main colors of players to print the main array with colours //// box6:contain colours for redo plays
*box3:contain undo moves                                    *box5:contain the redo plays
*box4:contain special cases for undo                        *box7:contain special cases for redo*/

void gotoxy(int x, int y)           //function used to set console cursor in certain position
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int ispunct(int c);
int isdigit(int c);
int isalpha(int c);
void colour();
void array_dec2(int s,int a,char box[s][a]);
void print_array2(int s,int a,char box[s][a]);
void array_turn12(int s,int a,char box[s][a]);
void array_turn22(int s,int a,char box[s][a]);
void undo1(int s,int a,char box[s][a]);
void undo12(int s,int a,char box[s][a]);
void redo1(int s,int a,char box[s][a]);
void redo12(int s,int a,char box[s][a]);
void computer(int s,int a,char box[s][a]);
void computer1(int s,int a,char box[s][a]);
void print_array3(int s,int a,char box[s][a]);
void print_array4(int s,int a,char box[s][a]);
void array_turn13(int s,int a,char box[s][a]);
void save(int s,int a,char box[s][a]);
void menu();
void last_menu();
void print(int s,int a,char box[s][a]);
void topten();
void playerrank();
int main()
{
    PlaySound("dots and boxes music.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
    menu();
    return 0;
}
void menu()         //contain the starting of the game to choose modes leading to your main game
{

    int x,y,z,c;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    gotoxy(39,6);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223);
    gotoxy(39,9);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",223,223,223,223,223,223,223,223,223,223,223,223,223,223,223);
    gotoxy(39,6);
    printf("%c",219);
    gotoxy(39,7);
    printf("%c",219);
    gotoxy(39,8);
    printf("%c",219);
    gotoxy(38+16,6);
    printf("%c",219);
    gotoxy(38+16,7);
    printf("%c",219);
    gotoxy(38+16,8);
    printf("%c",219);
    gotoxy(40,7);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
    printf(" DOTS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    printf(" & ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    printf("BOXES");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    gotoxy(40,10);
    printf("(1)start game\n");
    gotoxy(40,14);
    printf("(3)load game\n");
    gotoxy(40,12);
    printf("(2)Help");
    gotoxy(40,16);
    printf("(4)top 10 players\n");
    gotoxy(40,18);
    printf("(5)exit\n");
    scanf("%s",q);
    x=atoi(q);
    if (q[1]!='\0')
    {
        x=0;
    }
    switch (x)
    {
    case(1):
tree:
        system("cls");
        gotoxy(40,7);
        printf("(1)Beginner\n");
        gotoxy(40,9);
        printf("(2)expert\n");
        gotoxy(40,11);
        printf("(3)choose the size\n");
        scanf("%s",q);
        y=atoi(q);
        if (q[1]!='\0')
        {
            y=0;
        }
        if (y==1)
        {
beginner:
            system("cls");
            gotoxy(40,7);
            printf("(1)human vs human\n");
            gotoxy(40,9);
            printf("(2)human vs computer\n");
            scanf("%s",q);
            z=atoi(q);
            if (q[1]!='\0')
            {
                z=0;
            }
            if (z==1)
            {
                mode=1;
                system("cls");
                colour();
                system("cls");
                gotoxy(40,7);
                printf("Enter player one name");
                gotoxy(40,9);
                scanf("%s",one.name);
                system("cls");
                gotoxy(40,11);
                printf("Enter player two name");
                gotoxy(40,13);
                scanf("%s",two.name);
                system("cls");
                row=3;
                col=3;
                char box[row*2-1][col*2-1];
                noft=(((row-1)*col)*2)-(row-col);
                dots=noft;
                array_dec2(row*2-1,col*2-1,box);
                print_array2(row*2-1,col*2-1, box);
                last_menu();

            }
            else if(z==2)
            {
                mode=2;
                compmo:
                system("cls");
                gotoxy(40,7);
                printf("(1)easy");
                gotoxy(40,9);
                printf("(2)hard\n");
                scanf("%s",q);
            modec=atoi(q);
            if (q[1]!='\0')
            {
                modec=0;
            }
            if (modec==1||modec==2){
                    system("cls");}
                    else{goto compmo;}
                colour();
                system("cls");
                gotoxy(40,7);
                printf("Enter player one name");
                gotoxy(40,9);
                scanf("%s",one.name);
                strcpy(two.name, "Computer");
                system("cls");
                row=3;
                col=3;
                char box[row*2-1][col*2-1];
                crc=row*2,ccc=col*2;
                noft=(((row-1)*col)*2)-(row-col);
                dots=noft;
                array_dec2(row*2-1,col*2-1,box);
                if(modec==1){
                print_array4(row*2-1,col*2-1, box);
                }
                else if(modec==2){
                print_array3(row*2-1,col*2-1, box);}
                last_menu();
            }
            else goto beginner;
        }
        else if(y==2)
        {
expert:
            system("cls");
            gotoxy(40,7);
            printf("(1)human vs human\n");
            gotoxy(40,9);
            printf("(2)human vs computer\n");
            scanf("%s",q);
            z=atoi(q);
            if (q[1]!='\0')
            {
                z=0;
            }
            if (z==1)
            {
                mode=1;
                system("cls");
                colour();
                system("cls");
                gotoxy(40,7);
                printf("Enter player one name");
                gotoxy(40,9);
                scanf("%s",one.name);
                system("cls");
                gotoxy(40,11);
                printf("Enter player two name");
                gotoxy(40,13);
                scanf("%s",two.name);
                system("cls");
                row=6;
                col=6;
                char box[row*2-1][col*2-1];
                noft=(((row-1)*col)*2)-(row-col);
                dots=noft;
                array_dec2(row*2-1,col*2-1,box);
                print_array2(row*2-1,col*2-1, box);
                last_menu();
            }
            else if(z==2)
            {
                mode=2;
                compmod:
                system("cls");
                gotoxy(40,7);
                printf("(1)easy");
                gotoxy(40,9);
                printf("(2)hard\n");
                scanf("%s",q);
            modec=atoi(q);
            if (q[1]!='\0')
            {
                modec=0;
            }
            if (modec==1||modec==2){
                    system("cls");}
                    else{goto compmod;}
                colour();
                system("cls");
                gotoxy(40,7);
                printf("Enter player one name");
                gotoxy(40,9);
                scanf("%s",one.name);
                strcpy(two.name, "Computer");
                system("cls");
                row=6;
                col=6;
                char box[row*2-1][col*2-1];
                crc=row*2,ccc=col*2;
                noft=(((row-1)*col)*2)-(row-col);
                dots=noft;
                array_dec2(row*2-1,col*2-1,box);
                if(modec==1){
                print_array4(row*2-1,col*2-1, box);
                }
                else if(modec==2){
                print_array3(row*2-1,col*2-1, box);}
                last_menu();
            }
            else goto expert;
        }
        else if(y==3)
        {
choosesize:
            system("cls");
            gotoxy(40,7);
            printf("(1)human vs human\n");
            gotoxy(40,9);
            printf("(2)human vs computer\n");
            scanf("%s",q);
            z=atoi(q);
            if (q[1]!='\0')
            {
                z=0;
            }
            if (z==1)
            {
                mode=1;
                system("cls");
                colour();
                system("cls");
                gotoxy(40,7);
                printf("Enter player one name");
                gotoxy(40,9);
                scanf("%s",one.name);
                system("cls");
                gotoxy(40,11);
                printf("Enter player two name");
                gotoxy(40,13);
                scanf("%s",two.name);
                system("cls");
here:
                gotoxy(40,5);
                printf("{max size 8x8}");
                gotoxy(35,7);
                printf("Enter the size of the array");
                gotoxy(30,10);
                printf("row:");
                scanf("%s",q);
                row=atoi(q);
                if (q[1]!='\0')
                {
                    row=0;
                    system("cls");
                    goto here;
                }
                gotoxy(60,10);
                printf("column:");
                scanf("%s",q);
                col=atoi(q);
                if (q[1]!='\0')
                {
                    col=0;
                    system("cls");
                    goto here;
                }
                if(row==0||col==0)
                {
                    system("cls");
                    goto here;
                }
                row=row+1;
                col=col+1;
                if(row>9||col>9)
                {
                    system("cls");
                    goto here;
                }
                system("cls");
                char box[row*2-1][col*2-1];
                noft=(((row-1)*col)*2)-(row-col);
                dots=noft;
                array_dec2( row*2-1,col*2-1,box);
                print_array2(row*2-1,col*2-1,box);
                last_menu();
            }
            else if(z==2)
            {
                mode=2;
                compmode:
                system("cls");
                gotoxy(40,7);
                printf("(1)easy");
                gotoxy(40,9);
                printf("(2)hard\n");
                scanf("%s",q);
            modec=atoi(q);
            if (q[1]!='\0')
            {
                modec=0;
            }
            if (modec==1||modec==2){
                    system("cls");}
                    else{goto compmode;}
                colour();
                system("cls");
                gotoxy(40,7);
                printf("Enter player one name");
                gotoxy(40,9);
                scanf("%s",one.name);
                strcpy(two.name, "Computer");
                system("cls");
there:
                gotoxy(40,5);
                printf("{max size 8x8}");
                gotoxy(35,7);
                printf("Enter the size of the array");
                gotoxy(30,10);
                printf("row:");
                scanf("%s",q);
                row=atoi(q);
                if (q[1]!='\0')
                {
                    row=0;
                    system("cls");
                    goto here;
                }

                gotoxy(60,10);
                printf("column:");
                scanf("%s",q);
                col=atoi(q);
                if (q[1]!='\0')
                {
                    col=0;
                    system("cls");
                    goto here;
                }
                if(row==0||col==0)
                {
                    system("cls");
                    goto here;
                }
                row=row+1;
                col=col+1;
                if(row>9||col>9)
                {
                    system("cls");
                    goto there;
                }
                system("cls");
                char box[row*2-1][col*2-1];
                crc=row*2,ccc=col*2;
                noft=(((row-1)*col)*2)-(row-col);
                dots=noft;
                array_dec2(row*2-1,col*2-1,box);
                if(modec==1){
                print_array4(row*2-1,col*2-1, box);
                }
                else if(modec==2){
                print_array3(row*2-1,col*2-1, box);}
                last_menu();
            }
            else goto choosesize;
        }
        else goto tree;
        break;


    case(2): //how to play the game with game description and special orders(undo,redo,save)
stay:
        system("cls");
        printf("How To Play!\n\nDots & Boxes is a game where you join between dots to\nClose boxes and win the game, the more you close ,the \nhigher score you will get\n\nGame Play\n\nIn this game you will enter the number of row and column \nof the first point then the row and the column of the \nsecond point you want to join between.\n\nenter\nto undo\n    row1(1111)    \n    column1(any int) \n    row2(any int) \n    column2(any int) \n\nto redo\n    row1(2222)     \n    column1(any int) \n    row2(any int) \n    column2(any int) \n\nto save\n    row1(3333)\n    column1(any int) \n    row2(any int) \n    column2(any int) \n");
        gotoxy(0,30);
        printf("1)menu\n");
        scanf("%s",q);
        me=atoi(q);
        if (q[1]!='\0')
        {
            me=0;
        }
        if(me==1)
        {
            system("cls");
            menu();
        }
        else goto stay;


    case(3):            //load games you have already saved
        system("cls");
loadhere:
        gotoxy(40,7);
        printf("load game 1");
        gotoxy(40,9);
        printf("load game 2");
        gotoxy(40,11);
        printf("load game 3\n");
        gotoxy(40,13);
        printf("4)back\n");
        scanf("%s",q);
        loadn=atoi(q);
        if (q[1]!='\0')
        {
            loadn=0;
            system("cls");
            goto loadhere;
        }
        else if (loadn==4)
        {
            system("cls");
            menu();
        }
        else if (loadn==1||loadn==2||loadn==3)      //choose the file you want to load from 3 already existing files
        {
            int b,mn, size = 0;//size: count the nmber of elemnts in a file
            FILE *fsave;
            if(loadn==1)
            {

                fsave=fopen("1.txt","r");
                if(fsave!=NULL)
                {
                    fseek (fsave, 0, SEEK_END);

                    size = ftell (fsave);
                    rewind(fsave);

                }
                if (size==0)
                {
                    system("cls");
                    Beep(1500,300);
                    printf("file is empty");
                    goto loadhere;
                }
            }
            else if(loadn==2)
            {
                fsave=fopen("2.txt","r");
                if(fsave!=NULL)
                {
                    fseek (fsave, 0, SEEK_END);

                    size = ftell (fsave);
                    rewind(fsave);

                }
                if (size==0)
                {
                    system("cls");
                    Beep(1500,300);
                    printf("file is empty");
                    goto loadhere;
                }
            }
            else if(loadn==3)
            {
                fsave=fopen("3.txt","r");

                if(fsave!=NULL)
                {
                    fseek (fsave, 0, SEEK_END);

                    size = ftell (fsave);
                    rewind(fsave);

                }
                if (size==0)
                {
                    system("cls");
                    Beep(1500,300);
                    printf("file is empty");
                    goto loadhere;
                }
            }
            fscanf(fsave,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d ",&row,&col,&i,&j,&noft,&r1,&c1,&r2,&c2,&k,&co1,&co2,&turn,&mode);
            fscanf(fsave,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d ",&v,&m,&counter1,&counter2,&colour1,&colour2,&dots,&sy,&end,&end1,&uc,&flag,&crc,&ccc);
            fscanf(fsave,"%d %d %d %d %d ",&one.move,&two.move,&one.score,&two.score,&modec);
            fscanf(fsave,"%s %s ",one.name,two.name);
            fscanf(fsave,"%lf",&counter);
            char box[row*2-1][col*2-1];
            for(b=0; b<row*2-1; b++)
            {
                for(mn=0; mn<col*2-1; mn++)
                {
                    fscanf(fsave," %d ",&box2[b][mn]);
                }
            }
            for(b=0; b<row*2-1; b++)
            {
                for(mn=0; mn<col*2-1; mn++)
                {
                    fscanf(fsave," %d ",&box3[b][mn]);
                }
            }
            for(b=0; b<row*2-1; b++)
            {
                for(mn=0; mn<col*2-1; mn++)
                {
                    fscanf(fsave," %d ",&box4[b][mn]);
                }
            }
            for(b=0; b<row*2-1; b++)
            {
                for(mn=0; mn<col*2-1; mn++)
                {
                    fscanf(fsave," %d ",&box5[b][mn]);
                }
            }
            for(b=0; b<row*2-1; b++)
            {
                for(mn=0; mn<col*2-1; mn++)
                {
                    fscanf(fsave," %d ",&box6[b][mn]);
                }
            }
            for(b=0; b<row*2-1; b++)
            {
                for(mn=0; mn<col*2-1; mn++)
                {
                    fscanf(fsave," %d ",&box7[b][mn]);
                }
            }
            for(b=0; b<row*2-1; b++)
            {
                for(mn=0; mn<col*2-1; mn++)
                {
                    fscanf(fsave,"%c",&box[b][mn]);
                }
            }
            fclose(fsave);
            co1=1,co2=1;
            system("cls");
            print(row*2-1,col*2-1,box);
            if(mode==1)             //sets you only the saved mode you were paling at eh time of saving (vs human)
            {
                for(i=i; i<noft; i++)
                {
                    if(turn%2==1)
                    {

                        array_turn12(row*2-1,col*2-1,box);
                    }
                    else if(turn%2==0)
                    {

                        array_turn22(row*2-1,col*2-1,box);
                    }

                }
                last_menu();
            }
            else if(mode==2)    //sets you only the saved mode you were paling at eh time of saving (vs computer)
            {
                co1=1,co2=1;
                system("cls");
                print(row*2-1,col*2-1,box);
                if(modec==1){
                for(i=i; i<noft; i++)
                {

                    if(turn%2==1)
                    {

                        array_turn13(row*2-1,col*2-1,box);
                    }
                    else if(turn%2==0)
                    {

                        computer1(row*2-1,col*2-1,box);
                    }

                }}
                else if (modec==2){
                  for(i=i; i<noft; i++)
                {

                    if(turn%2==1)
                    {

                        array_turn13(row*2-1,col*2-1,box);
                    }
                    else if(turn%2==0)
                    {

                        computer(row*2-1,col*2-1,box);
                    }

                }

                }
                last_menu();
            }
        }
        else goto loadhere;
    case(4):
hna:
        system("cls");
        topten();
        gotoxy(0,8);
        printf("1)menu\n");
        gotoxy(0,30);
        scanf("%s",q);
        me=atoi(q);
        if (q[1]!='\0')
        {
            me=0;
        }
        if(me==1)
        {
            system("cls");
            menu();
        }
        else
        {
            goto hna;
        }

    case(5): //the exit menu choices
        system("cls");
        gotoxy(35,7);
        printf("do you really want to exit");
        gotoxy(30,10);
        printf("(1)yes");
        gotoxy(60,10);
        printf("(2)no\n");
        scanf("%d",&c);
        switch(c)
        {
        case(1):
            exit(0);
        case(2):
            system("cls");
            menu();
        }
    default:
        system("cls");
        menu();

    }

}
void array_dec2(int s,int a,char box[s][a])     //function takes the arrays with the initial size depending on the game mode
{                                                //giving it it's declaration of stars and  to be ready for the players
    for(i=0; i<row*2-1; i++)
    {
        for(j=0; j<col*2-1; j++)
        {
            if(i%2==0&&j%2==0)
            {
                box[i][j]='*';
            }

            else box[i][j]=' ';
        }
    }
}
void print_array2(int s,int a,char box[s][a])   //contain game mode (displays the game interference, swap turns between players till the end of the game)
{

    print(row*2-1,col*2-1,box);
    for(i=0; i<noft; i++)
    {
        if(turn%2==1)                           //if i is odd ,player's one turn
        {

            array_turn12(row*2-1,col*2-1,box);
        }
        else if(turn%2==0)                              //if i is even ,player's two turn
        {

            array_turn22(row*2-1,col*2-1,box);
        }

    }
}
void array_turn12(int s,int a,char box[s][a])
{
    clock_t start = clock();        //start of timer
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colour1);
    printf("\n%.15s's turn....\n",one.name);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    scanf("%s%s%s%s",p,o,h,g);  //take (row,col) of 1st point the (row,column) of second point
    r1 = atoi(p);
    c1 = atoi(o);
    r2 = atoi(h);
    c2 = atoi(g);
    if (r1==1111)   //if the player enter 1111 first the play will be undone
    {
        if(uc==1)
        {
            printf("Can't undo anymore\n");
            i--;
        }
        else
        {
            undo1(row*2-1,col*2-1,box);//undo function
            uc--;
            i--;
        }
        clock_t stop = clock();
        double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
        counter+=elapsed;

        if (counter>=60)
        {
            counter1=counter/60;
            while(counter>=60)
            {
                counter-=60;
            }
            counter2+=counter1;
        }
    }
    else if (r1==2222)//if player enters 2222 it will redo the previous plays
    {
        for(v=0; v<row*2-1; v++)
        {
            for(m=0; m<col*2-1; m++)
            {
                if(box5[v][m]==uc)
                {
                    redo1(row*2-1,col*2-1,box);//redo function
                    uc++;
                    clock_t stop = clock();
                    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
                    counter+=elapsed;

                    if (counter>=60)
                    {
                        counter1=counter/60;
                        while(counter>=60)
                        {
                            counter-=60;
                        }
                        counter2+=counter1;
                    }
                    flag=1;
                    break;
                }
                else flag=0;
            }
            if (flag==1)
            {
                break;
            }
        }
        if (flag==0)//stays zero if there is no more plays to redo
        {
            printf("cant redo anymore");
            i--;
        }

    }
    else if (r1==3333)//enter to save the current game in a file
    {
savehere:
        system("cls");
        gotoxy(40,7);
        printf("save game 1");
        gotoxy(40,9);
        printf("save game 2");
        gotoxy(40,11);
        printf("save game 3\n");
        scanf("%s",q);
        saven=atoi(q);
        if (q[1]!='\0')
        {
            saven=0;
            goto savehere;
        }
        else if (saven==1||saven==2||saven==3)
        {
            save(row*2-1,col*2-1,box);
        }
        else goto savehere;
        system("cls");
        print(row*2-1,col*2-1,box);
        i--;
    }
    //start of restriction on the entered values for rows and columns of points
    else if (p[1]!='\0'||o[1]!='\0'||g[1]!='\0'||h[1]!='\0')
    {
        r1=0;
        c1=0;
        r2=0;
        c2=0;
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }

    else if(r1<=0||r2<=0||c1<=0||c2<=0)
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }
    else if(r1>row||r2>row||c1>col||c2>col)
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;

    }
    else if(r1!=r2&&c1!=c2)
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }
    else if(r1==r2&&c1==c2)
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }

    else if(r1==r2&&box[r1*2-2][((c1*2-2)+(c2*2-2))/2]=='-')
    {
        printf("already exist\n");
        Beep(1500,300);
        i--;
    }
    else if(c1==c2&&box[((r1*2-2)+(r2*2-2))/2][c1*2-2]=='|')
    {
        printf("already exist\n");
        Beep(1500,300);
        i--;
    }
    else if (r1==r2&&(abs(c1-c2)>1))
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }
    else if (c1==c2&&(abs(r1-r2)>1))
    {
        printf("wrong input ,try again!\n");
        i--;
    }
    //end of restrictions on rows and columns
    else
    {
        if (r1==r2)
        {
            //loop to clear all old plays in undo and redo arrays when a new play is done
            for(v=0; v<row*2-1; v++)
            {
                for(m=0; m<col*2-1; m++)
                {
                    if(box5[v][m]==uc||box5[v][m]>uc)
                    {
                        box5[v][m]=0;
                        box6[v][m]=0;
                        box7[v][m]=0;
                    }
                }
            }
            //changes the values of the connecting line between the chosen dots
            box[r1*2-2][((c1*2-2)+(c2*2-2))/2]='-';
            box2[r1*2-2][((c1*2-2)+(c2*2-2))/2]=1;
            box3[r1*2-2][((c1*2-2)+(c2*2-2))/2]=uc;
            box6[r1*2-2][((c1*2-2)+(c2*2-2))/2]=1;
            box5[r1*2-2][((c1*2-2)+(c2*2-2))/2]=uc;
            uc++;
            one.move++;
            turn++;
            dots--;
            //a loop on the main arrays to calculate the score of a box is closed
            for(v=0; v<row*2-1; v++)
            {
                for(m=0; m<col*2-1; m++)
                {
                    if(v%2==1&&m%2==1)
                    {
                        if(box2[v][m-1]!=0&&box2[v-1][m]!=0&&box2[v+1][m]!=0&&box2[v][m+1]!=0&&box[v][m]==' ')
                        {
                            one.score++;
                            printf("\a");
                            box[v][m]='A';
                            box2[v][m]=1;
                            box6[v][m]=1;
                            if (turn%2==0)
                            {
                                turn--;

                            }
                        }
                    }
                }
            }

        }
        else if (c1==c2)
        {
            //loop to clear all old plays in undo and redo arrays when a new play is done
            for(v=0; v<row*2-1; v++)
            {
                for(m=0; m<col*2-1; m++)
                {
                    if(box5[v][m]==uc||box5[v][m]>uc)
                    {
                        box5[v][m]=0;
                        box6[v][m]=0;
                        box7[v][m]=0;
                    }
                }
            }
            //changes the values of the connecting line between the chosen dots
            box[((r1*2-2)+(r2*2-2))/2][c1*2-2]='|';
            box2[((r1*2-2)+(r2*2-2))/2][c1*2-2]=1;
            box3[((r1*2-2)+(r2*2-2))/2][c1*2-2]=uc;
            box6[((r1*2-2)+(r2*2-2))/2][c1*2-2]=1;
            box5[((r1*2-2)+(r2*2-2))/2][c1*2-2]=uc;
            uc++;
            turn++;
            one.move++;
            dots--;
            //a loop on the main arrays to calculate the score of a box is closed
            for(v=0; v<row*2-1; v++)
            {
                for(m=0; m<col*2-1; m++)
                {
                    if(v%2==1&&m%2==1)
                    {
                        if(box2[v][m-1]!=0&&box2[v-1][m]!=0&&box2[v+1][m]!=0&&box2[v][m+1]!=0&&box[v][m]==' ')
                        {
                            one.score++;
                            printf("\a");
                            box[v][m]='A';
                            box2[v][m]=1;
                            box6[v][m]=1;
                            if (turn%2==0)
                            {
                                turn--;

                            }
                        }
                    }
                }
            }
        }
        //end of time counter
        clock_t stop = clock();
        system("cls");
        co1=1,co2=1;
        double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
        counter+=elapsed;
//counter don't exceed 60sec and add a minute
        if (counter>=60)
        {
            counter1=counter/60;
            while(counter>=60)
            {
                counter-=60;
            }
            counter2+=counter1;
        }
        print(row*2-1,col*2-1,box);
    }

}
void array_turn22(int s,int a,char box[s][a])
{
    clock_t start = clock();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colour2);
    printf("\n%.15s's turn....\n",two.name);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    scanf("%s%s%s%s",p,o,h,g);
    r1 = atoi(p);
    c1 = atoi(o);
    r2 = atoi(h);
    c2 = atoi(g);
    if (r1==1111)
    {
        if(uc==1)
        {
            printf("Can't undo anymore\n");
            i--;
        }
        else
        {
            undo1(row*2-1,col*2-1,box);
            uc--;
            i--;
        }
        clock_t stop = clock();
        double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
        counter+=elapsed;

        if (counter>=60)
        {
            counter1=counter/60;
            while(counter>=60)
            {
                counter-=60;
            }
            counter2+=counter1;
        }
    }
    else if (r1==2222)
    {
        for(v=0; v<row*2-1; v++)
        {
            for(m=0; m<col*2-1; m++)
            {
                if(box5[v][m]==uc)
                {
                    redo1(row*2-1,col*2-1,box);
                    uc++;
                    clock_t stop = clock();
                    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
                    counter+=elapsed;

                    if (counter>=60)
                    {
                        counter1=counter/60;
                        while(counter>=60)
                        {
                            counter-=60;
                        }
                        counter2+=counter1;
                    }
                    flag=1;
                    break;
                }
                else flag=0;
            }
            if (flag==1)
            {
                break;
            }
        }
        if (flag==0)
        {
            printf("cant redo anymore");
            i--;
        }

    }
    else if (r1==3333)
    {
savehere:
        system("cls");
        gotoxy(40,7);
        printf("save game 1");
        gotoxy(40,9);
        printf("save game 2");
        gotoxy(40,11);
        printf("save game 3\n");
        scanf("%s",q);
        saven=atoi(q);
        if (q[1]!='\0')
        {
            saven=0;
            goto savehere;
        }
        else if (saven==1||saven==2||saven==3)
        {
            save(row*2-1,col*2-1,box);
        }
        else goto savehere;
        system("cls");
        print(row*2-1,col*2-1,box);
        i--;
    }
    else if (p[1]!='\0'||o[1]!='\0'||h[1]!='\0'||g[1]!='\0')
    {
        r1=0;
        c1=0;
        r2=0;
        c2=0;
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }

    else if(r1<=0||r2<=0||c1<=0||c2<=0)
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }
    else if(r1>row||r2>row||c1>col||c2>col)
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;

    }
    else if(r1!=r2&&c1!=c2)
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }
    else if(r1==r2&&c1==c2)
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }
    else if(r1==r2&&box[r1*2-2][((c1*2-2)+(c2*2-2))/2]=='-')
    {
        printf("already exist\n");
        Beep(1500,300);
        i--;
    }
    else if(c1==c2&&box[((r1*2-2)+(r2*2-2))/2][c1*2-2]=='|')
    {
        printf("already exist\n");
        Beep(1500,300);
        i--;
    }
    else if (r1==r2&&(abs(c1-c2)>1))
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }
    else if (c1==c2&&(abs(r1-r2)>1))
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }
    else
    {
        if (r1==r2)
        {
            for(v=0; v<row*2-1; v++)
            {
                for(m=0; m<col*2-1; m++)
                {
                    if(box5[v][m]==uc||box5[v][m]>uc)
                    {
                        box5[v][m]=0;
                        box6[v][m]=0;
                        box7[v][m]=0;
                    }
                }
            }
            box[r1*2-2][((c1*2-2)+(c2*2-2))/2]='-';
            box2[r1*2-2][((c1*2-2)+(c2*2-2))/2]=2;
            box3[r1*2-2][((c1*2-2)+(c2*2-2))/2]=uc;
            box6[r1*2-2][((c1*2-2)+(c2*2-2))/2]=2;
            box5[r1*2-2][((c1*2-2)+(c2*2-2))/2]=uc;
            uc++;
            turn++;
            two.move++;
            dots--;
            for(v=0; v<row*2-1; v++)
            {
                for(m=0; m<col*2-1; m++)
                {
                    if(v%2==1&&m%2==1)
                    {
                        if(box2[v][m-1]!=0&&box2[v-1][m]!=0&&box2[v+1][m]!=0&&box2[v][m+1]!=0&&box[v][m]==' ')
                        {
                            two.score++;
                            printf("\a");
                            box[v][m]='B';
                            box2[v][m]=2;
                            box6[v][m]=2;
                            if (turn%2==1)
                            {
                                turn--;

                            }
                        }
                    }
                }
            }

        }
        else if (c1==c2)
        {
            for(v=0; v<row*2-1; v++)
            {
                for(m=0; m<col*2-1; m++)
                {
                    if(box5[v][m]==uc||box5[v][m]>uc)
                    {
                        box5[v][m]=0;
                        box6[v][m]=0;
                        box7[v][m]=0;
                    }
                }
            }
            box[((r1*2-2)+(r2*2-2))/2][c1*2-2]='|';
            box2[((r1*2-2)+(r2*2-2))/2][c1*2-2]=2;
            box3[((r1*2-2)+(r2*2-2))/2][c1*2-2]=uc;
            box6[((r1*2-2)+(r2*2-2))/2][c1*2-2]=2;
            box5[((r1*2-2)+(r2*2-2))/2][c1*2-2]=uc;
            uc++;
            turn++;
            two.move++;
            dots--;
            for(v=0; v<row*2-1; v++)
            {
                for(m=0; m<col*2-1; m++)
                {
                    if(v%2==1&&m%2==1)
                    {
                        if(box2[v][m-1]!=0&&box2[v-1][m]!=0&&box2[v+1][m]!=0&&box2[v][m+1]!=0&&box[v][m]==' ')
                        {
                            two.score++;
                            printf("\a");
                            box[v][m]='B';
                            box2[v][m]=2;
                            box6[v][m]=2;
                            if (turn%2==1)
                            {
                                turn--;

                            }
                        }
                    }
                }
            }
        }
        clock_t stop = clock();
        system("cls");
        co1=1,co2=1;
        double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
        counter+=elapsed;

        if (counter>=60)
        {
            counter1=counter/60;
            while(counter>=60)
            {
                counter-=60;
            }

            counter2+=counter1;
        }

        print(row*2-1,col*2-1,box);
    }

}
// function make the players choose their colors
void colour()
{
voy:
    gotoxy(40,10);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),1);
    printf("(1)BLUE");
    gotoxy(40,12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
    printf("(2)GREEN");
    gotoxy(40,14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
    printf("(3)CYAN");
    gotoxy(40,16);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
    printf("(4)RED");
    gotoxy(40,18);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),5);
    printf("(5)MAGENTA");
    gotoxy(40,20);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
    printf("(6)BROWN");
    gotoxy(40,22);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    printf("(7)LIGHTGRAY");
    gotoxy(40,24);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
    printf("(8)DARKGRAY");
    gotoxy(40,26);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
    printf("(9)LIGHTBLUE");
    gotoxy(40,28);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    printf("(10)LIGHTGREEN");
    gotoxy(40,30);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    printf("(11)LIGHTCYAN");
    gotoxy(40,32);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    printf("(12)LIGHTRED");
    gotoxy(40,34);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
    printf("(13)LIGHTMAGENTA");
    gotoxy(40,36);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    printf("(14)YELLOW");
    gotoxy(40,38);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    printf("(15)WHITE");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    gotoxy(20,7);
    printf("player one colour:");
    scanf("%s",q);
    if(isalpha(q[1])||ispunct(q[1])){
        system("cls");
        goto voy;
    }
    else if(isdigit(q[1])&&(isalpha(q[2])||ispunct(q[2]))){
        system("cls");
        goto voy;
    }
    colour1=atoi(q);
    if (colour1<=0||colour1>=16)  //check that the player enter number of two maximum not characters or bigger numbers
    {
        system("cls");
        goto voy;
    }
    gotoxy(50,7);
    printf("player two colour:");
    scanf("%s",p);
    if(isalpha(p[1])||ispunct(p[1])){
        system("cls");
        goto voy;
    }
     else if(isdigit(p[1])&&(isalpha(p[2])||ispunct(p[2]))){
        system("cls");
        goto voy;
    }
    colour2=atoi(p);
    if (colour2<=0||colour2>=16)  //check that the player enter number of two maximum not characters or bigger numbers
    {

        system("cls");
        goto voy;
    }
    if (colour1==colour2)
    {
        system("cls");
        goto voy;
    }
    one.colour=colour1;
    two.colour=colour2;
}
//function take the name of the winner and save it in a file for the top 10 players
void last_menu()
{
again:
    if(one.score>two.score)
    {
        gotoxy(30,25);
        printf("%.15s won",one.name);
        gotoxy(50,25);
        printf("score:%d",one.score);
        //store name and score of the winner in structure array for comparison with old ones
        strcpy(swape2[0].name,one.name);
        swape2[0].score=one.score;

        FILE *topten;
        topten=fopen("top.txt","r");
        for(i=0; i<200; i++)
        {
            fscanf(topten,"%d ",&swape[i].score);//load the old scores
            fscanf(topten,"%s ",swape[i].name);
        }
        fclose(topten);
        flagtop10=0;
        for(i=0; i<200; i++)
        {
            if(strcmp(swape2[0].name,swape[i].name)==0)  //case if the name already exist ,it will compare its score if it is higher it will replace the score with the higher one
            {
                if(swape2[0].score>=swape[i].score){


                swape[i].score=swape2[0].score;
                flagtop10=1;
                break;
                }
                else if(swape2[0].score<swape[i].score){
                    flagtop10=1;
                }
            }
        }
        if(flagtop10==1)    //if it is a special case save it in the top file with the old ones after replacing if it is higher
        {
            FILE *topten;
            topten=fopen("top.txt","w");
            for(i=0; i<200; i++)
            {
                fprintf(topten,"%d ",swape[i].score);
                fprintf(topten,"%s ",swape[i].name);
            }
            fclose(topten);
        }
        else if(flagtop10==0) //if it is not an already existing name save it in the top file
        {
            FILE *topten;
            topten=fopen("top.txt","a");
            fprintf(topten,"%d ",one.score);
            fprintf(topten,"%s ",one.name);
            fclose(topten);
        }
         playerrank();
         gotoxy(70,25);
         printf("rank:%d",done);
    }
    else if(one.score<two.score)
    {
        gotoxy(30,25);
        printf("%.15s won",two.name);
        gotoxy(50,25);
        printf("score:%d",two.score);
        strcpy(swape2[0].name,two.name);
        swape2[0].score=two.score;
          if(strcmp(swape2[0].name,"Computer")==0&&mode==2){//if the computer was the winner don't take it
        }
        else{
        FILE *topten;
        topten=fopen("top.txt","r");
        for(i=0; i<200; i++)
        {
            fscanf(topten,"%d ",&swape[i].score);
            fscanf(topten,"%s ",swape[i].name);
        }
        fclose(topten);
        flagtop10=0;
        for(i=0; i<200; i++)
        {
            if(strcmp(swape2[0].name,swape[i].name)==0)
            {
               if(swape2[0].score>=swape[i].score){


                swape[i].score=swape2[0].score;
                flagtop10=1;
                break;
                }
                else if(swape2[0].score<swape[i].score){
                    flagtop10=1;
                }
            }
        }
        if(flagtop10==1)
        {
            FILE *topten;
            topten=fopen("top.txt","w");
            for(i=0; i<200; i++)
            {
                fprintf(topten,"%d ",swape[i].score);
                fprintf(topten,"%s ",swape[i].name);
            }
            fclose(topten);
        }
        else
        {
            FILE *topten;
            topten=fopen("top.txt","a");
            fprintf(topten,"%d ",two.score);
            fprintf(topten,"%s ",two.name);
            fclose(topten);
        }
    }
     if(strcmp(two.name,"Computer")==0&&mode==2){
        }
   else{ playerrank();
      gotoxy(70,25);
        printf("rank:%d",done);
   }
    }
    else
    {
        gotoxy(45,25);
        printf("DRAAAAAAAW !");
        strcpy(swape2[0].name,one.name);
        swape2[0].score=one.score;
        swape2[1].score=two.score;
        strcpy(swape2[1].name,two.name);
         if(strcmp(swape2[1].name,"Computer")==0&&mode==2){
                strcpy(swape2[0].name,one.name);
        swape2[0].score=one.score;

        FILE *topten;
        topten=fopen("top.txt","r");
        for(i=0; i<200; i++)
        {
            fscanf(topten,"%d ",&swape[i].score);//load the old scores
            fscanf(topten,"%s ",swape[i].name);
        }
        fclose(topten);
        flagtop10=0;
        for(i=0; i<200; i++)
        {
            if(strcmp(swape2[0].name,swape[i].name)==0)  //special case if the name already exist ,it will compare its score if it is higher it will replace the score with the higher one
            {
                if(swape2[0].score>=swape[i].score){


                swape[i].score=swape2[0].score;
                flagtop10=1;
                break;
                }
                else if(swape2[0].score<swape[i].score){
                    flagtop10=1;
                }
            }
        }
        if(flagtop10==1)    //if it is a special case save it in the top file with the old ones after replacing if it is higher
        {
            FILE *topten;
            topten=fopen("top.txt","w");
            for(i=0; i<200; i++)
            {
                fprintf(topten,"%d ",swape[i].score);
                fprintf(topten,"%s ",swape[i].name);
            }
            fclose(topten);
        }
        else if(flagtop10==0) //if it is not an already existing name save it in the top file
        {
            FILE *topten;
            topten=fopen("top.txt","a");
            fprintf(topten,"%d ",one.score);
            fprintf(topten,"%s ",one.name);
            fclose(topten);
        }
        }
        else{
        FILE *topten;
    topten=fopen("top.txt","r");
    for(i=0;i<200;i++){
        fscanf(topten,"%d ",&swape[i].score);
        fscanf(topten,"%s ",swape[i].name);
    }
    fclose(topten);
    flagtop10=0;
    for(i=0;i<200;i++)
    {
        if(strcmp(swape2[0].name,swape[i].name)==0)
        {
            if(swape2[0].score>=swape[i].score){


                swape[i].score=swape2[0].score;
                flagtop10=1;
                break;
                }
                else if(swape2[0].score<swape[i].score){
                    flagtop10=1;
                }
        }
    }
    if(flagtop10==1)
    {
             FILE *topten;
    topten=fopen("top.txt","w");
    for(i=0;i<200;i++){
        fprintf(topten,"%d ",swape[i].score);
        fprintf(topten,"%s ",swape[i].name);
    }
    fclose(topten);
    }
    else{
         FILE *topten;
        topten=fopen("top.txt","a");
        fprintf(topten,"%d ",one.score);
        fprintf(topten,"%s ",one.name);
        fclose(topten);
    }
    flagtop10=0;
    for(i=0;i<200;i++)
    {
        if(strcmp(swape2[1].name,swape[i].name)==0)
        {
           if(swape2[1].score>=swape[i].score){


                swape[i].score=swape2[1].score;
                flagtop10=1;
                break;
                }
                else if(swape2[1].score<swape[i].score){
                    flagtop10=1;
                }
        }
    }
    if(flagtop10==1)
    {
             FILE *topten;
    topten=fopen("top.txt","w");
    for(i=0;i<200;i++){
        fprintf(topten,"%d ",swape[i].score);
        fprintf(topten,"%s ",swape[i].name);
    }
    fclose(topten);
    }
    else{
         FILE *topten;
        topten=fopen("top.txt","a");
        fprintf(topten,"%d ",two.score);
        fprintf(topten,"%s ",two.name);
        fclose(topten);
    }
        }

    }
    gotoxy(35,28);
    printf("1)Main menu");
    gotoxy(59,28);
    printf("2)exit\n");
    scanf("%s",q);
    end=atoi(q);
    if (q[1]!='\0')
    {
        end=0;
    }
    if(end==1)
    {
        //re-initialze all the used variables to zeros preparing for a new gamed
        system("cls");

        for(i=0; i<row*2-1; i++)
        {
            for(j=0; j<col*2-1; j++)
            {
                box2[i][j]=0;
                box3[i][j]=0;
                box4[i][j]=0;
                box5[i][j]=0;
                box6[i][j]=0;
                box7[i][j]=0;
            }
        }

        one.move=0,one.score=0,two.move=0,two.score=0;
        k=0,co1=1,co2=1,turn=1,v=0,m=0,counter=0,counter1=0,counter2=0,sy=178,uc=1,flag=0;
        menu();
    }
    else if (end==2)
    {
tryagain:
        system("cls");
        gotoxy(35,7);
        printf("do you really want to exit");
        gotoxy(30,10);
        printf("(1)yes");
        gotoxy(60,10);
        printf("(2)no\n");

        scanf("%s",q);
        end1=atoi(q);
        if (q[1]!='\0')
        {
            end1=0;
        }
        if(end1==1)
        {
            exit(0);
        }
        else if(end1==2)
        {
            system("cls");
            for(i=0; i<row*2-1; i++)
            {
                for(j=0; j<col*2-1; j++)
                {
                    box2[i][j]=0;
                    box3[i][j]=0;
                    box4[i][j]=0;
                    box5[i][j]=0;
                    box6[i][j]=0;
                    box7[i][j]=0;
                }
            }

            one.move=0,one.score=0,two.move=0,two.score=0;
            k=0,co1=1,co2=1,turn=1,v=0,m=0,counter=0,counter1=0,counter2=0,sy=178,uc=1,flag=0;
            menu();
        }
        else goto tryagain;
    }
    else goto again;
}

//undo of player versus player
void undo1(int s,int a,char box[s][a])
{
    int u1,u2,u3,u4;

    for(u1=0; u1<row*2-1; u1++)
    {
        for(u2=0; u2<col*2-1; u2++)
        {

            if(box3[u1][u2]==(uc-1)&&box4[u1][u2]==0) //loop to find the place of the play before the last one
            {
                box3[u1][u2]=0;
                box[u1][u2]=' ';
                dots++;
                if(box2[u1][u2]==1) //if it belong to first player
                {
                    turn--;
                    one.move--;
                    for(u3=0; u3<row*2-1; u3++) //#check for special case# if also the play before before the last one belongs to player one
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            if (box3[u3][u4]==uc-2)
                            {
                                if (box2[u3][u4]==box2[u1][u2])
                                {
                                    box4[u3][u4]=1;
                                }
                            }
                        }
                    }
                    box2[u1][u2]=0;
                }
                else if (box2[u1][u2]==2) //if it belong to second player
                {
                    turn--;
                    two.move--;
                    for(u3=0; u3<row*2-1; u3++)//#check for special case# if also the play before before the last one belongs to player two
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            if (box3[u3][u4]==uc-2)
                            {
                                if (box2[u3][u4]==box2[u1][u2])
                                {
                                    box4[u3][u4]=2;
                                }
                            }
                        }
                    }
                    box2[u1][u2]=0;
                }
            }

            //enters if it is a special case from above
            else if (box3[u1][u2]==uc-1&&box4[u1][u2]!=0)
            {
                box3[u1][u2]=0;
                if(box4[u1][u2]==1)
                {
                    box[u1][u2]=' ';
                    box2[u1][u2]=0;
                    dots++;
                    one.move--;
                }
                else if(box4[u1][u2]==2)
                {
                    box[u1][u2]=' ';
                    box2[u1][u2]=0;
                    dots++;
                    two.move--;
                }
            }
        }
    }

    //checks if a box is opened after it was closed by a player to change the score (by checking the borders of the box and the letter of the player)
    for(u1=0; u1<row*2-1; u1++)
    {
        for(u2=0; u2<col*2-1; u2++)
        {
            if(u1%2==1&&u2%2==1)
            {
                if((box[u1][u2]=='A')&&(box2[u1][u2-1]==0||box2[u1-1][u2]==0||box2[u1+1][u2]==0||box2[u1][u2+1]==0))
                {
                    one.score--;
                    box2[u1][u2]=0;
                    box[u1][u2]=' ';
                    if(turn%2==0)
                    {
                        turn--;
                    }

                }
                else if (isalpha(box[u1][u2])&&(box2[u1][u2-1]==0||box2[u1-1][u2]==0||box2[u1+1][u2]==0||box2[u1][u2+1]==0))
                {
                    two.score--;
                    box2[u1][u2]=0;
                    box[u1][u2]=' ';
                    if(turn%2==1)
                    {
                        turn--;
                    }
                }
            }
        }
    }

    system("cls");
    co1=1,co2=1;
    print(row*2-1,col*2-1,box);
    i--;
}

//redo for player versus player
void redo1(int s,int a,char box[s][a])
{
    int u1,u2,u3,u4;

    for(u1=0; u1<row*2-1; u1++)
    {
        for(u2=0; u2<col*2-1; u2++)
        {

            if(box5[u1][u2]==(uc)&&box7[u1][u2]==0)//after increasing the number of the play counter loop to find the place of the next play
            {
                box3[u1][u2]=uc;
                if(u1%2==0&&u2%2==1)
                {
                    box[u1][u2]='-';
                }
                else if(u1%2==1&&u2%2==0)
                {
                    box[u1][u2]='|';
                }

                dots--;
                if(box6[u1][u2]==1)//if it belong to first player
                {
                    turn++;
                    one.move++;
                    for(u3=0; u3<row*2-1; u3++)//#check for special case# if also the plat after redo belongs to player one
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            if (box5[u3][u4]==uc+1)
                            {
                                if (box6[u3][u4]==box6[u1][u2])
                                {
                                    box7[u3][u4]=1;
                                }
                            }
                        }
                    }
                    box2[u1][u2]=1;
                }
                else if (box6[u1][u2]==2)//if it belong to second player
                {
                    turn++;
                    two.move++;
                    for(u3=0; u3<row*2-1; u3++)//#check for special case# if also the plat after redo belongs to player two
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            if (box5[u3][u4]==uc+1)
                            {
                                if (box6[u3][u4]==box6[u1][u2])
                                {
                                    box7[u3][u4]=2;
                                }
                            }
                        }
                    }
                    box2[u1][u2]=2;
                }
            }
            //enter if it is a special case from above
            else if (box5[u1][u2]==uc&&box7[u1][u2]!=0)
            {
                box3[u1][u2]=uc;
                if(box7[u1][u2]==1)
                {
                    if(u1%2==0&&u2%2==1)
                    {
                        box[u1][u2]='-';
                    }
                    else if(u1%2==1&&u2%2==0)
                    {
                        box[u1][u2]='|';
                    }
                    box2[u1][u2]=1;
                    dots--;
                    one.move++;
                }
                else if(box7[u1][u2]==2)
                {
                    if(u1%2==0&&u2%2==1)
                    {
                        box[u1][u2]='-';
                    }
                    else if(u1%2==1&&u2%2==0)
                    {
                        box[u1][u2]='|';
                    }
                    box2[u1][u2]=2;
                    dots--;
                    two.move++;
                }
            }
        }
    }

     //checks if a box is closed after it was opened (after undo) to change the score (by checking the borders of the box and the letter of the player)
    for(u1=0; u1<row*2-1; u1++)
    {
        for(u2=0; u2<col*2-1; u2++)
        {
            if(u1%2==1&&u2%2==1)
            {
                if(box[u1][u2]==' '&&(box2[u1][u2-1]!=0&&box2[u1-1][u2]!=0&&box2[u1+1][u2]!=0&&box2[u1][u2+1]!=0))
                {
                    if (box6[u1][u2]==1)
                    {
                        one.score++;
                        box2[u1][u2]=1;
                        box[u1][u2]='A';
                        if(turn%2==0)
                        {
                            turn++;
                        }
                    }
                    else if (box6[u1][u2]==2)
                    {
                        two.score++;
                        box2[u1][u2]=2;
                        box[u1][u2]='B';
                        if(turn%2==1)
                        {
                            turn++;
                        }
                    }
                }

            }
        }
    }

    system("cls");
    co1=1,co2=1;
    print(row*2-1,col*2-1,box);
}

//computer mode greedy
void computer(int s,int a,char box[s][a])
{

    //loop on the main array to check if a box only needs on play to be closed to get more score (by giving its core a value=3)
    for(g_row=0; g_row<row*2-1; g_row++)
    {
        for(g_col=0; g_col<col*2-1; g_col++)
        {
            if(g_row%2==1&&g_col%2==1)
            {
                if(box[g_row][g_col]==' ')
                {
                    if(box2[g_row][g_col-1]!=0&&box2[g_row-1][g_col]!=0&&box2[g_row+1][g_col]!=0&&box2[g_row][g_col+1]==0)
                    {
                        greedy[g_row][g_col]=3;
                        flag3=1; // it value become 1 indicating the existing of box to be close (greed)
                    }
                    else if(box2[g_row][g_col-1]!=0&&box2[g_row-1][g_col]!=0&&box2[g_row+1][g_col]==0&&box2[g_row][g_col+1]!=0)
                    {
                        greedy[g_row][g_col]=3;
                        flag3=1;// it value become 1 indicating the existing of box to be close (greed)
                    }
                    else if(box2[g_row][g_col-1]!=0&&box2[g_row-1][g_col]==0&&box2[g_row+1][g_col]!=0&&box2[g_row][g_col+1]!=0)
                    {
                        greedy[g_row][g_col]=3;
                        flag3=1;// it value become 1 indicating the existing of box to be close (greed)
                    }
                    else if(box2[g_row][g_col-1]==0&&box2[g_row-1][g_col]!=0&&box2[g_row+1][g_col]!=0&&box2[g_row][g_col+1]!=0)
                    {
                        greedy[g_row][g_col]=3;
                        flag3=1;// it value become 1 indicating the existing of box to be close (greed)
                    }
                }
            }
        }
    }
    //box to be closed
    if(flag3==1)
    {
        clock_t start = clock();
        flag2=0;
        //check for the core of each box(row and column are odd) it its value=3 close it
        for(g_row=0; g_row<row*2-1; g_row++)
        {
            for(g_col=0; g_col<col*2-1; g_col++)
            {
                if(g_row%2==1&&g_col%2==1&&greedy[g_row][g_col]==3)
                {
                    for(v=0; v<row*2-1; v++)
                    {
                        for(m=0; m<col*2-1; m++)
                        {
                            if(box5[v][m]==uc||box5[v][m]>uc)
                            {
                                box5[v][m]=0;
                                box6[v][m]=0;
                                box7[v][m]=0;
                            }
                        }
                    }
                    if(box2[g_row][g_col-1]!=0&&box2[g_row-1][g_col]!=0&&box2[g_row+1][g_col]!=0&&box2[g_row][g_col+1]==0)
                    {
                        box[g_row][g_col+1]='|';
                        box2[g_row][g_col+1]=2;
                        box3[g_row][g_col+1]=uc;
                        box6[g_row][g_col+1]=2;
                        box5[g_row][g_col+1]=uc;
                        ccc--;
                    }
                    else if(box2[g_row][g_col-1]!=0&&box2[g_row-1][g_col]!=0&&box2[g_row+1][g_col]==0&&box2[g_row][g_col+1]!=0)
                    {
                        box[g_row+1][g_col]='-';
                        box2[g_row+1][g_col]=2;
                        box3[g_row+1][g_col]=uc;
                        box6[g_row+1][g_col]=2;
                        box5[g_row+1][g_col]=uc;
                        crc--;
                    }
                    else if(box2[g_row][g_col-1]!=0&&box2[g_row-1][g_col]==0&&box2[g_row+1][g_col]!=0&&box2[g_row][g_col+1]!=0)
                    {
                        box[g_row-1][g_col]='-';
                        box2[g_row-1][g_col]=2;
                        box3[g_row-1][g_col]=uc;
                        box6[g_row-1][g_col]=2;
                        box5[g_row-1][g_col]=uc;
                        crc--;
                    }
                    else if(box2[g_row][g_col-1]==0&&box2[g_row-1][g_col]!=0&&box2[g_row+1][g_col]!=0&&box2[g_row][g_col+1]!=0)
                    {
                        box[g_row][g_col-1]='|';
                        box2[g_row][g_col-1]=2;
                        box3[g_row][g_col-1]=uc;
                        box6[g_row][g_col-1]=2;
                        box5[g_row][g_col-1]=uc;
                        ccc--;
                    }
                    flag2=1;  //take a value 1 to break for one play each time
                    flag3=0;  //reset is value
                    greedy[g_row][g_col]=0;

                    uc++;
                    turn++;
                    two.move++;
                    dots--;
                    //check for score
                    for(v=0; v<row*2-1; v++)
                    {
                        for(m=0; m<col*2-1; m++)
                        {
                            if(v%2==1&&m%2==1)
                            {
                                if(box2[v][m-1]!=0&&box2[v-1][m]!=0&&box2[v+1][m]!=0&&box2[v][m+1]!=0&&box[v][m]==' ')
                                {
                                    two.score++;
                                    printf("\a");
                                    box[v][m]='B';
                                    box2[v][m]=2;
                                    box6[v][m]=2;
                                    if (turn%2==1)
                                    {
                                        turn--;

                                    }
                                }
                            }
                        }
                    }
                    clock_t stop = clock();
                    system("cls");
                    co1=1,co2=1;
                    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
                    counter+=elapsed;

                    if (counter>=60)
                    {
                        counter1=counter/60;
                        while(counter>=60)
                        {
                            counter-=60;
                        }
                        counter2+=counter1;
                    }
                    for(v=0; v<row*2-1; v++)
                    {
                        for(m=0; m<col*2-1; m++)
                        {
                            greedy[v][m]=0;
                        }
                    }

                    print(row*2-1,col*2-1,box);
                    break;

                }

            }
            if (flag2==1)
            {
                break;
            }
        }
    }
    else
    {
        //if no boxes to close are found the computer will play randomly
        while(1)
        {
            clock_t start = clock();
hena:
            r1=rand()%(row*2-1);
            c1=rand()%(col*2-1);
            if(box[r1][c1]=='*'||box[r1][c1]=='-'||box[r1][c1]=='|')//check that the place is empty
            {
                goto hena;
            }

            if (r1%2==0&&c1%2==1)
            {
                for(v=0; v<row*2-1; v++)
                {
                    for(m=0; m<col*2-1; m++)
                    {
                        if(box5[v][m]==uc||box5[v][m]>uc)
                        {
                            box5[v][m]=0;
                            box6[v][m]=0;
                            box7[v][m]=0;
                        }
                    }
                }
                box[r1][c1]='-';
                box2[r1][c1]=2;
                box3[r1][c1]=uc;
                box6[r1][c1]=2;
                box5[r1][c1]=uc;
                uc++;
                turn++;
                two.move++;
                dots--;
                for(v=0; v<row*2-1; v++)
                {
                    for(m=0; m<col*2-1; m++)
                    {
                        if(v%2==1&&m%2==1)
                        {
                            if(box2[v][m-1]!=0&&box2[v-1][m]!=0&&box2[v+1][m]!=0&&box2[v][m+1]!=0&&box[v][m]==' ')
                            {
                                two.score++;
                                printf("\a");
                                box[v][m]='B';
                                box2[v][m]=2;
                                box6[v][m]=2;
                                if (turn%2==1)
                                {
                                    turn--;
                                }
                            }
                        }
                    }
                }
                clock_t stop = clock();
                system("cls");
                co1=1,co2=1;
                double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
                counter+=elapsed;

                if (counter>=60)
                {
                    counter1=counter/60;
                    while(counter>=60)
                    {
                        counter-=60;
                    }
                    counter2+=counter1;
                }
                print(row*2-1,col*2-1,box);
                crc--;
                break;
            }
            else if(r1%2==1&&c1%2==0)
            {
                for(v=0; v<row*2-1; v++)
                {
                    for(m=0; m<col*2-1; m++)
                    {
                        if(box5[v][m]==uc||box5[v][m]>uc)
                        {
                            box5[v][m]=0;
                            box6[v][m]=0;
                            box7[v][m]=0;
                        }
                    }
                }
                box[r1][c1]='|';
                box2[r1][c1]=2;
                box3[r1][c1]=uc;
                box6[r1][c1]=2;
                box5[r1][c1]=uc;
                uc++;
                turn++;
                two.move++;
                dots--;
                for(v=0; v<row*2-1; v++)
                {
                    for(m=0; m<col*2-1; m++)
                    {
                        if(v%2==1&&m%2==1)
                        {
                            if(box2[v][m-1]!=0&&box2[v-1][m]!=0&&box2[v+1][m]!=0&&box2[v][m+1]!=0&&box[v][m]==' ')
                            {
                                two.score++;
                                printf("\a");
                                box[v][m]='B';
                                box2[v][m]=2;
                                box6[v][m]=2;
                                if (turn%2==1)
                                {
                                    turn--;

                                }
                            }
                        }
                    }
                }
                clock_t stop = clock();
                system("cls");
                co1=1,co2=1;
                double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
                counter+=elapsed;

                if (counter>=60)
                {
                    counter1=counter/60;
                    while(counter>=60)
                    {
                        counter-=60;
                    }
                    counter2+=counter1;
                }

                print(row*2-1,col*2-1,box);
                ccc--;
                break;

            }
        }
    }
}
void computer1(int s,int a,char box[s][a])
{


        //the computer will play randomly
        while(1)
        {
            clock_t start = clock();
hena:
            r1=rand()%(row*2-1);
            c1=rand()%(col*2-1);
            if(box[r1][c1]=='*'||box[r1][c1]=='-'||box[r1][c1]=='|')//check that the place is empty
            {
                goto hena;
            }

            if (r1%2==0&&c1%2==1)
            {
                for(v=0; v<row*2-1; v++)
                {
                    for(m=0; m<col*2-1; m++)
                    {
                        if(box5[v][m]==uc||box5[v][m]>uc)
                        {
                            box5[v][m]=0;
                            box6[v][m]=0;
                            box7[v][m]=0;
                        }
                    }
                }
                box[r1][c1]='-';
                box2[r1][c1]=2;
                box3[r1][c1]=uc;
                box6[r1][c1]=2;
                box5[r1][c1]=uc;
                uc++;
                turn++;
                two.move++;
                dots--;
                for(v=0; v<row*2-1; v++)
                {
                    for(m=0; m<col*2-1; m++)
                    {
                        if(v%2==1&&m%2==1)
                        {
                            if(box2[v][m-1]!=0&&box2[v-1][m]!=0&&box2[v+1][m]!=0&&box2[v][m+1]!=0&&box[v][m]==' ')
                            {
                                two.score++;
                                printf("\a");
                                box[v][m]='B';
                                box2[v][m]=2;
                                box6[v][m]=2;
                                if (turn%2==1)
                                {
                                    turn--;
                                }
                            }
                        }
                    }
                }
                clock_t stop = clock();
                system("cls");
                co1=1,co2=1;
                double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
                counter+=elapsed;

                if (counter>=60)
                {
                    counter1=counter/60;
                    while(counter>=60)
                    {
                        counter-=60;
                    }
                    counter2+=counter1;
                }
                print(row*2-1,col*2-1,box);
                crc--;
                break;
            }
            else if(r1%2==1&&c1%2==0)
            {
                for(v=0; v<row*2-1; v++)
                {
                    for(m=0; m<col*2-1; m++)
                    {
                        if(box5[v][m]==uc||box5[v][m]>uc)
                        {
                            box5[v][m]=0;
                            box6[v][m]=0;
                            box7[v][m]=0;
                        }
                    }
                }
                box[r1][c1]='|';
                box2[r1][c1]=2;
                box3[r1][c1]=uc;
                box6[r1][c1]=2;
                box5[r1][c1]=uc;
                uc++;
                turn++;
                two.move++;
                dots--;
                for(v=0; v<row*2-1; v++)
                {
                    for(m=0; m<col*2-1; m++)
                    {
                        if(v%2==1&&m%2==1)
                        {
                            if(box2[v][m-1]!=0&&box2[v-1][m]!=0&&box2[v+1][m]!=0&&box2[v][m+1]!=0&&box[v][m]==' ')
                            {
                                two.score++;
                                printf("\a");
                                box[v][m]='B';
                                box2[v][m]=2;
                                box6[v][m]=2;
                                if (turn%2==1)
                                {
                                    turn--;

                                }
                            }
                        }
                    }
                }
                clock_t stop = clock();
                system("cls");
                co1=1,co2=1;
                double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
                counter+=elapsed;

                if (counter>=60)
                {
                    counter1=counter/60;
                    while(counter>=60)
                    {
                        counter-=60;
                    }
                    counter2+=counter1;
                }

                print(row*2-1,col*2-1,box);
                ccc--;
                break;

            }
        }
    }

//function to swap turns between player and computer greedy
void print_array3(int s,int a,char box[s][a])
{

    print(row*2-1,col*2-1,box);
    for(i=0; i<noft; i++)
    {
        if(turn%2==1)
        {

            array_turn13(row*2-1,col*2-1,box);
        }
        else if(turn%2==0)
        {
            computer(row*2-1,col*2-1,box);
        }

    }
}
//function to swap turns between player and computer normal
void print_array4(int s,int a,char box[s][a])
{

    print(row*2-1,col*2-1,box);
    for(i=0; i<noft; i++)
    {
        if(turn%2==1)
        {

            array_turn13(row*2-1,col*2-1,box);
        }
        else if(turn%2==0)
        {
            computer1(row*2-1,col*2-1,box);
        }

    }
}

//function of the player against computer
void array_turn13(int s,int a,char box[s][a])
{
    clock_t start = clock();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colour1);
    printf("\n%.15s's turn....\n",one.name);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    scanf("%s%s%s%s",p,o,h,g);
    r1 = atoi(p);
    c1 = atoi(o);
    r2 = atoi(h);
    c2 = atoi(g);
    if (r1==1111)
    {
        if(uc==1)
        {
            printf("Can't undo anymore\n");
            i--;
        }
        else
        {
            i--;
            do
            {
                undo12(row*2-1,col*2-1,box);
            }
            while(turn%2==0);//you should undo computer's plays without asking the player and when the turn is even it is the computer turn

            clock_t stop = clock();
            double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
            counter+=elapsed;
            if (counter>=60)
            {
                counter1=counter/60;
                while(counter>=60)
                {
                    counter-=60;
                }
                counter2+=counter1;
            }
        }
    }

    else if (r1==2222)
    {
        for(v=0; v<row*2-1; v++)
        {
            for(m=0; m<col*2-1; m++)
            {
                if(box5[v][m]==uc)
                {
                    i--;
                    do
                    {

                        redo12(row*2-1,col*2-1,box);
                        uc++;


                    }
                    while(turn%2==0);//you should redo computer's plays without asking the player and when the turn is even it is the computer turn

                    clock_t stop = clock();
                    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
                    counter+=elapsed;

                    if (counter>=60)
                    {
                        counter1=counter/60;
                        while(counter>=60)
                        {
                            counter-=60;
                        }
                        counter2+=counter1;
                    }
                    flag=1;
                    break;
                }
                else flag=0;
            }
            if (flag==1)
            {
                break;
            }
        }
        if (flag==0)
        {
            printf("cant redo anymore");
            i--;
        }

    }
    else if (r1==3333)
    {
savehere:
        system("cls");
        gotoxy(40,7);
        printf("save game 1");
        gotoxy(40,9);
        printf("save game 2");
        gotoxy(40,11);
        printf("save game 3\n");
        scanf("%s",q);
        saven=atoi(q);
        if (q[1]!='\0')
        {
            saven=0;
            goto savehere;
        }
        else if (saven==1||saven==2||saven==3)
        {
            save(row*2-1,col*2-1,box);
        }
        else goto savehere;
        system("cls");
        print(row*2-1,col*2-1,box);
        i--;
    }
    else if (p[1]!='\0'||o[1]!='\0'||g[1]!='\0'||h[1]!='\0')
    {
        r1=0;
        c1=0;
        r2=0;
        c2=0;
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }

    else if(r1<=0||r2<=0||c1<=0||c2<=0)
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }
    else if(r1>row||r2>row||c1>col||c2>col)
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;

    }
    else if(r1!=r2&&c1!=c2)
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }
    else if(r1==r2&&c1==c2)
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }

    else if(r1==r2&&box[r1*2-2][((c1*2-2)+(c2*2-2))/2]=='-')
    {
        printf("already exist\n");
        Beep(1500,300);
        i--;
    }
    else if(c1==c2&&box[((r1*2-2)+(r2*2-2))/2][c1*2-2]=='|')
    {
        printf("already exist\n");
        Beep(1500,300);
        i--;
    }
    else if (r1==r2&&(abs(c1-c2)>1))
    {
        printf("wrong input ,try again!\n");
        Beep(1500,300);
        i--;
    }
    else if (c1==c2&&(abs(r1-r2)>1))
    {
        printf("wrong input ,try again!\n");
        i--;
    }
    else
    {
        if (r1==r2)
        {
            for(v=0; v<row*2-1; v++)
            {
                for(m=0; m<col*2-1; m++)
                {
                    if(box5[v][m]==uc||box5[v][m]>uc)
                    {
                        box5[v][m]=0;
                        box6[v][m]=0;
                        box7[v][m]=0;
                    }
                }
            }
            box[r1*2-2][((c1*2-2)+(c2*2-2))/2]='-';
            box2[r1*2-2][((c1*2-2)+(c2*2-2))/2]=1;
            box3[r1*2-2][((c1*2-2)+(c2*2-2))/2]=uc;
            box6[r1*2-2][((c1*2-2)+(c2*2-2))/2]=1;
            box5[r1*2-2][((c1*2-2)+(c2*2-2))/2]=uc;
            uc++;
            one.move++;
            turn++;
            dots--;
            crc--;
            for(v=0; v<row*2-1; v++)
            {
                for(m=0; m<col*2-1; m++)
                {
                    if(v%2==1&&m%2==1)
                    {
                        if(box2[v][m-1]!=0&&box2[v-1][m]!=0&&box2[v+1][m]!=0&&box2[v][m+1]!=0&&box[v][m]==' ')
                        {
                            one.score++;
                            printf("\a");
                            box[v][m]='A';
                            box2[v][m]=1;
                            box6[v][m]=1;
                            if (turn%2==0)
                            {
                                turn--;

                            }
                        }
                    }
                }
            }

        }
        else if (c1==c2)
        {
            for(v=0; v<row*2-1; v++)
            {
                for(m=0; m<col*2-1; m++)
                {
                    if(box5[v][m]==uc||box5[v][m]>uc)
                    {
                        box5[v][m]=0;
                        box6[v][m]=0;
                        box7[v][m]=0;
                    }
                }
            }
            box[((r1*2-2)+(r2*2-2))/2][c1*2-2]='|';
            box2[((r1*2-2)+(r2*2-2))/2][c1*2-2]=1;
            box3[((r1*2-2)+(r2*2-2))/2][c1*2-2]=uc;
            box6[((r1*2-2)+(r2*2-2))/2][c1*2-2]=1;
            box5[((r1*2-2)+(r2*2-2))/2][c1*2-2]=uc;
            uc++;
            turn++;
            one.move++;
            dots--;
            ccc--;
            for(v=0; v<row*2-1; v++)
            {
                for(m=0; m<col*2-1; m++)
                {
                    if(v%2==1&&m%2==1)
                    {
                        if(box2[v][m-1]!=0&&box2[v-1][m]!=0&&box2[v+1][m]!=0&&box2[v][m+1]!=0&&box[v][m]==' ')
                        {
                            one.score++;
                            printf("\a");
                            box[v][m]='A';
                            box2[v][m]=1;
                            box6[v][m]=1;
                            if (turn%2==0)
                            {
                                turn--;

                            }
                        }
                    }
                }
            }

        }
        clock_t stop = clock();
        system("cls");
        co1=1,co2=1;

        double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
        counter+=elapsed;

        if (counter>=60)
        {
            counter1=counter/60;
            while(counter>=60)
            {
                counter-=60;
            }
            counter2+=counter1;
        }
        print(row*2-1,col*2-1,box);
    }

}
//undo for player vs computer
void undo12(int s,int a,char box[s][a])
{
    int u1,u2,u3,u4;
    uc--;
    for(u1=0; u1<row*2-1; u1++)
    {
        for(u2=0; u2<col*2-1; u2++)
        {

            if(box3[u1][u2]==(uc)&&box4[u1][u2]==0)
            {
                box[u1][u2]=' ';
                dots++;
                if(box2[u1][u2]==1)
                {
                    turn--;
                    one.move--;
                    for(u3=0; u3<row*2-1; u3++)
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            if (box3[u3][u4]==uc-1)
                            {
                                if (box2[u3][u4]==1)
                                {
                                    box4[u3][u4]=1;
                                }
                            }
                        }
                    }
                    box2[u1][u2]=0;

                }
                else if (box2[u1][u2]==2)
                {
                    turn--;
                    two.move--;
                    for(u3=0; u3<row*2-1; u3++)
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            if (box3[u3][u4]==uc-1)
                            {
                                if (box2[u3][u4]==2)
                                {
                                    box4[u3][u4]=2;
                                }
                            }
                        }
                    }
                    box2[u1][u2]=0;
                }
                box3[u1][u2]=0;
            }
            else if (box3[u1][u2]==uc&&box4[u1][u2]!=0)
            {

                if(box4[u1][u2]==1)
                {
                    box[u1][u2]=' ';
                    box2[u1][u2]=0;
                    dots++;
                    one.move--;
                    //clears all data in special cases array in this loop
                    for(u3=0; u3<row*2-1; u3++)
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {

                            box4[u3][u4]=0;


                        }
                    }
                    //checks for special cases after each special case if a loop exist or a continued series of plays for the player
                    for(u3=0; u3<row*2-1; u3++)
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            if (box3[u3][u4]==uc-1)
                            {
                                if (box2[u3][u4]==1)
                                {
                                    box4[u3][u4]=1;
                                }
                            }
                        }
                    }
                }
                else if(box4[u1][u2]==2)
                {
                    box[u1][u2]=' ';
                    box2[u1][u2]=0;
                    dots++;
                    two.move--;
                    for(u3=0; u3<row*2-1; u3++)
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            box4[u3][u4]=0;
                        }
                    }
                    for(u3=0; u3<row*2-1; u3++)
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            if (box3[u3][u4]==uc-1)
                            {
                                if (box2[u3][u4]==2)
                                {
                                    box4[u3][u4]=2;
                                }

                            }
                        }
                    }
                }
                box3[u1][u2]=0;
            }
        }
    }
    //checks for score
    for(u1=0; u1<row*2-1; u1++)
    {
        for(u2=0; u2<col*2-1; u2++)
        {
            if(u1%2==1&&u2%2==1)
            {
                if((box[u1][u2]=='A')&&(box2[u1][u2-1]==0||box2[u1-1][u2]==0||box2[u1+1][u2]==0||box2[u1][u2+1]==0))
                {
                    one.score--;
                    box2[u1][u2]=0;
                    box[u1][u2]=' ';
                    if(turn%2==0)
                    {
                        turn--;
                    }

                }
                else if (isalpha(box[u1][u2])&&(box2[u1][u2-1]==0||box2[u1-1][u2]==0||box2[u1+1][u2]==0||box2[u1][u2+1]==0))
                {
                    two.score--;
                    box2[u1][u2]=0;
                    box[u1][u2]=' ';
                    if(turn%2==1)
                    {
                        turn--;
                    }
                }
            }
        }
    }
    system("cls");
    co1=1,co2=1;
    print(row*2-1,col*2-1,box);
    i--;


}
void redo12(int s,int a,char box[s][a])
{
    int u1,u2,u3,u4;

    for(u1=0; u1<row*2-1; u1++)
    {
        for(u2=0; u2<col*2-1; u2++)
        {

            if(box5[u1][u2]==(uc)&&box7[u1][u2]==0)
            {

                if(u1%2==0&&u2%2==1)
                {
                    box[u1][u2]='-';
                }
                else if(u1%2==1&&u2%2==0)
                {
                    box[u1][u2]='|';
                }

                dots--;
                if(box6[u1][u2]==1)
                {
                    turn++;
                    one.move++;
                    for(u3=0; u3<row*2-1; u3++)
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            if (box5[u3][u4]==uc+1)
                            {
                                if (box6[u3][u4]==1)
                                {
                                    box7[u3][u4]=1;
                                }
                            }
                        }
                    }
                    box2[u1][u2]=1;
                }
                else if (box6[u1][u2]==2)
                {
                    turn++;
                    two.move++;
                    //checks for special cases
                    for(u3=0; u3<row*2-1; u3++)
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            if (box5[u3][u4]==uc+1)
                            {
                                if (box6[u3][u4]==box6[u1][u2])
                                {
                                    box7[u3][u4]=2;
                                }
                            }
                        }
                    }
                    box2[u1][u2]=2;
                }
                box3[u1][u2]=uc;
            }
            //enters if a special case is found
            else if (box5[u1][u2]==uc&&box7[u1][u2]!=0)
            {

                if(box7[u1][u2]==1)
                {
                    if(u1%2==0&&u2%2==1)
                    {
                        box[u1][u2]='-';
                    }
                    else if(u1%2==1&&u2%2==0)
                    {
                        box[u1][u2]='|';
                    }
                    box2[u1][u2]=1;
                    dots--;
                    one.move++;
                    for(u3=0; u3<row*2-1; u3++)
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            box7[u3][u4]=0;
                        }
                    }
                    for(u3=0; u3<row*2-1; u3++)
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            if (box5[u3][u4]==uc+1)
                            {
                                if (box6[u3][u4]==1)
                                {
                                    box7[u3][u4]=1;
                                }
                                else turn++;
                            }
                        }
                    }

                }
                else if(box7[u1][u2]==2)
                {
                    if(u1%2==0&&u2%2==1)
                    {
                        box[u1][u2]='-';
                    }
                    else if(u1%2==1&&u2%2==0)
                    {
                        box[u1][u2]='|';
                    }
                    box2[u1][u2]=2;
                    dots--;
                    two.move++;
                    //clear all data from special cases
                    for(u3=0; u3<row*2-1; u3++)
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            box7[u3][u4]=0;
                        }
                    }
                    flgr=0;//variable to check weather there is more plays to redo or not, if not increase the turn so that the other player can play
                    for(u3=0; u3<row*2-1; u3++)
                    {
                        for(u4=0; u4<col*2-1; u4++)
                        {
                            if (box5[u3][u4]==uc+1)
                            {
                                if (box6[u3][u4]==2)
                                {
                                    box7[u3][u4]=2;
                                    flgr=1;
                                    break;
                                }
                                else turn++;
                            }
                        }
                        if(flgr==1)
                        {
                            break;
                        }
                    }
                    if(flgr==0)
                    {
                        turn++;
                    }

                }
                box3[u1][u2]=uc;
            }
        }
    }
    for(u1=0; u1<row*2-1; u1++)
    {
        for(u2=0; u2<col*2-1; u2++)
        {
            if(u1%2==1&&u2%2==1)
            {
                if(box[u1][u2]==' '&&(box2[u1][u2-1]!=0&&box2[u1-1][u2]!=0&&box2[u1+1][u2]!=0&&box2[u1][u2+1]!=0))
                {
                    if (box6[u1][u2]==1)
                    {
                        one.score++;
                        box2[u1][u2]=1;
                        box[u1][u2]='A';
                        if(turn%2==0)
                        {
                            turn++;
                        }
                    }
                    else if (box6[u1][u2]==2)
                    {
                        two.score++;
                        box2[u1][u2]=2;
                        box[u1][u2]='B';
                        if(turn%2==1)
                        {
                            turn++;
                        }
                    }
                }

            }
        }
    }
    system("cls");
    co1=1,co2=1;
    print(row*2-1,col*2-1,box);
    i++;
}
void print(int s,int a,char box[s][a])
{
    co1=1,co2=1;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colour1);
    gotoxy(30,3);
    printf("%.15s",one.name);
    gotoxy(30,5);
    printf("colour:");
    printf("%c",sy);
    gotoxy(30,7);
    printf("moves:%d",one.move);
    gotoxy(30,9);
    printf("score:%d",one.score);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colour2);
    gotoxy(70,3);
    printf("%.15s",two.name);
    gotoxy(70,7);
    printf("moves:%d",two.move);
    gotoxy(70,9);
    printf("score:%d",two.score);
    gotoxy(70,5);
    printf("colour:");
    printf("%c",sy);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    gotoxy(50,3);
    printf("time");
    gotoxy(50,5);
    printf("%d:%.f",counter2,counter);
    gotoxy(50,7);
    printf("Dots:%d",dots);
    gotoxy(50,11);
    for(k=0; k<col*2-1; k++)
    {
        if(k%2==0)
        {
            printf("%d ",co1++);
        }
    }
    printf("\n\n");

    for(k=0; k<row*2-1; k++)
    {

        for(j=0; j<col*2-1; j++)
        {
            gotoxy(50+j,13+k);
            if(box2[k][j]==0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                printf("%c",box[k][j]);
            }
            else if(box2[k][j]==1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colour1);
                printf("%c",box[k][j]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            }
            else if(box2[k][j]==2)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colour2);
                printf("%c",box[k][j]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            }
        }
        if(k%2==0)
        {
            printf(" %d",co2++);
        }
        printf("\n");
    }
}
//save function
void save(int s,int a,char box[s][a])
{
    int b,mn;
    FILE *fsave;
    if(saven==1)
    {
        fsave=fopen("1.txt","w");
    }
    else if(saven==2)
    {
        fsave=fopen("2.txt","w");
    }
    else if(saven==3)
    {
        fsave=fopen("3.txt","w");
    }
    fprintf(fsave,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d ",row,col,i,j,noft,r1,c1,r2,c2,k,co1,co2,turn,mode);
    fprintf(fsave,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d ",v,m,counter1,counter2,colour1,colour2,dots,sy,end,end1,uc,flag,crc,ccc);
    fprintf(fsave,"%d %d %d %d %d ",one.move,two.move,one.score,two.score,modec);
    fprintf(fsave,"%s %s ",one.name,two.name);
    fprintf(fsave,"%lf",counter);
    for(b=0; b<row*2-1; b++)
    {
        for(mn=0; mn<col*2-1; mn++)
        {
            fprintf(fsave," %d ",box2[b][mn]);
        }
    }
    for(b=0; b<row*2-1; b++)
    {
        for(mn=0; mn<col*2-1; mn++)
        {
            fprintf(fsave," %d ",box3[b][mn]);
        }
    }
    for(b=0; b<row*2-1; b++)
    {
        for(mn=0; mn<col*2-1; mn++)
        {
            fprintf(fsave," %d ",box4[b][mn]);
        }
    }
    for(b=0; b<row*2-1; b++)
    {
        for(mn=0; mn<col*2-1; mn++)
        {
            fprintf(fsave," %d ",box5[b][mn]);
        }
    }
    for(b=0; b<row*2-1; b++)
    {
        for(mn=0; mn<col*2-1; mn++)
        {
            fprintf(fsave," %d ",box6[b][mn]);
        }
    }
    for(b=0; b<row*2-1; b++)
    {
        for(mn=0; mn<col*2-1; mn++)
        {
            fprintf(fsave," %d ",box7[b][mn]);
        }
    }
    for(b=0; b<row*2-1; b++)
    {
        for(mn=0; mn<col*2-1; mn++)
        {
            fprintf(fsave,"%c",box[b][mn]);
        }
    }
    fclose(fsave);
}

//top ten function
void topten()
{
    FILE *topten;
    topten=fopen("top.txt","r");
    //load all the information of the winners in a structure array
    for(i=0; i<200; i++)
    {
        fscanf(topten,"%d ",&swape[i].score);
        fscanf(topten,"%s ",swape[i].name);
    }
    fclose(topten);

    //loop to sort scores in descending order from higher to lower for top ten
    for(j=0; j<200; j++)
    {
        for(i=j+1; i<200; i++)
        {
            if(swape[i].score>swape[j].score)
            {
                swape1=swape[i];
                swape[i]=swape[j];
                swape[j]=swape1;
            }
        }
    }

    //print only the top 10 players
    for(i=0; i<10; i++)
    {
        gotoxy(35,9+(i*2-1));
        printf("name%d:%.15s",i+1,swape[i].name);
        gotoxy(59,9+(i*2-1));
        printf("score:%d\n",swape[i].score);
    }
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    gotoxy(34,6);
    printf("**********************************");
    gotoxy(34,28);
    printf("**********************************");
    for(i=0;i<=20;i++){
        gotoxy(34,7+i);
        printf("*");
    }
 for(i=0;i<=20;i++){
        gotoxy(67,7+i);
        printf("*");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    gotoxy(46,5);
    printf("TOP TEN");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

}

//player rank function that copies the rank of the player whatever it was between the others, even he was't of the top ten
void playerrank()
{
    FILE *topten;
    topten=fopen("top.txt","r");
    for(i=0;i<200;i++){
        fscanf(topten,"%d ",&swape[i].score);
        fscanf(topten,"%s ",swape[i].name);
    }
    fclose(topten);
 for(j=0;j<200;j++)
    {
    for(i=j+1;i<200;i++)
    {
        if(swape[i].score>swape[j].score)
        {
            swape1=swape[i];
            swape[i]=swape[j];
            swape[j]=swape1;
        }
    }
    }
    if(one.score>two.score)
    {
        for(i=0;i<200;i++)
        {
            if(strcmp(swape[i].name,one.name)==0)
            {
                done=i+1;
                break;
            }
        }
    }
    //find the rank of the player
   else if(one.score<two.score)
    {
        for(i=0;i<200;i++)
        {
            if(strcmp(swape[i].name,two.name)==0)
            {
                done=i+1;

                break;
            }
        }
    }
}
