#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_POST_COUNT 10
#define MAX_CAND_COUNT 10
#define clrscr() system("clear")
#define getch() getchar()

char post[MAX_POST_COUNT][20];
int cand_count[MAX_CAND_COUNT];
char candidate[MAX_POST_COUNT][MAX_CAND_COUNT][20];
int vote_count[MAX_POST_COUNT][MAX_CAND_COUNT] = {0};
int post_count, voter_count;

void admin(void);
void voter(void);
void election_report(void);
int get_vote(int);
char* calc_result(int i);

void get_pword();
void set_pword();
char admin_pword[20];

char* strupr(char str[]){
    int i;
    for (i=0; i< sizeof(str); i++){
        str[i] = toupper(str[i]);
    }
    return str;
}


int main()
{
    //freopen("input.txt","r",stdin);//redirects standard input
    //freopen("output.txt","w",stdout);//redirects standard output
    set_pword();
    admin();
    printf("\nEnter the number of voters: ");
    scanf("%d", &voter_count);
    int c = 1;
    while(c <= voter_count)
    {
        clrscr();
        printf("\nVoter %d:\n", c++);
        voter();
        printf("your turn is over\n");
    }
    printf("Press any key to view the results\n");
    getch();
    clrscr();
    get_pword();
    election_report();
    getch();
    return 0;
}

void admin()
{
    printf("Enter the number of posts: ");
    scanf("%d", &post_count);
    fflush(stdin);
    int i, j;
    for(i=0; i<post_count; i++)
    {
        printf("\n");
        //fflush(stdin);
        printf( "Enter the name of post %d: ", i+1);
        //fflush(stdin);
        scanf("%s",post[i]);
        
        printf( "No of candidates for %s post: ", strupr(post[i]));
        scanf("%d", &cand_count[i]);
        fflush(stdin);

        for(j=0; j<cand_count[i]; j++)
        {
            printf("Enter the name of the candidate %d: ", j+1);
            scanf("%s", candidate[i][j] );
        }
    }
}

void voter()
{
    int i, j, num;
    for(i=0; i<post_count; i++)
    {
        printf("        %s\n", post[i]);
        for(j=0; j<cand_count[i]; j++)
            printf("        %d. %s \n", j+1, candidate[i][j]);

        num = get_vote(i);
        if(num)
            vote_count[i][num-1]++;
    }
}

int get_vote(int i)
{
    int num;
    printf("Enter your vote for this post:");
    scanf("%d", &num);
    while( num<0 || num>cand_count[i])
    {
        printf("Enter valid vote for this post from 0 to %d:", cand_count[i]);
        scanf("%d", &num);
    }
    return num;
}

void election_report()
{
    int i,j;
    char str[22];
    printf("%-22s|%-22s|%-8s\n\n", "       POST", "      CANDIDATES", " VOTES");

    for(i=0; i<post_count; i++)
    {
        for(j=0; j<cand_count[i]; j++)
        {
            if(j==0)
            {
                sprintf(str, "%d.%s", i+1, post[i]);
                printf("%-22s|", str);
            }
            else
                printf("%-22s|", " ");

            sprintf(str, "%d.%s", j+1, candidate[i][j]);
            printf("%-22s|", str);
            printf("%5d\n", vote_count[i][j]);
        }

        printf("%s\n", calc_result(i));

        int z = 60;
        while(z--)
            printf("%c",'-');
        printf("\n");
    }
}

char* calc_result(int i)
{
    int j;
    int max = vote_count[i][0], count = 0;

    //Find max
    for(j=0; j<cand_count[i]; j++)
        if( vote_count[i][j] > max )
            max = vote_count[i][j];

    //Check for repitition
    int rep_index[MAX_CAND_COUNT];     //To hold the index of candidates with max votes(repeated).
    for(j=0; j<cand_count[i]; j++)
    {
        if( max == vote_count[i][j] )
        {
            rep_index[count++] = j;
        }
    }

    char *str;
    str = (char*) malloc(40);
    if(count == 1)      // if No repitition
        sprintf(str, "The %s is %s", post[i], candidate[i][rep_index[0]] );
    else                //Tie condition
    {
        strcpy(str, "TIE between ");
        for(j=0; j<count; j++)
        {
            strcat(str, candidate[i][rep_index[j]]);
            strcat(str, "; ");
        }
    }
    return str;
}

void set_pword()
{
    clrscr();
    printf("Create your admin password:");
    scanf("%[^\n]", admin_pword);
    //printf("Your pword is %s\n", admin_pword);
    clrscr();
}

void get_pword()
{
    char pword[20], ch;
    int i;
    do
    {
        i = 0;
        printf("\nEnter your admin password:\n");
        fflush(stdin);
//        while( (ch = getch()) != '\r' )
//        {
//            printf("*");
//            pword[i++] = ch;
//        }
//        pword[i] = '\0';
        scanf("%s", pword);
    }
    while(strcmp(pword, admin_pword));
    clrscr();
    return;
}

