#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Team{
    char name[20];
    int points_scored;
    int points_lost;
    int wins;
    int loses;
    int draws;
    int matches;
    int teamID;
    int leaguePoints;
} Team;

typedef struct Match{
    int id1;
    int id2;
    int points1;
    int points2;
    int matchID;
} Match;

int MatchNumber(int n){
    int x = 0;
    for(int i = n-1; i >0; i--){
        x = x + (n-1);
        n--;
        }
    return 2*x;
}

void addTeam(char str[], Team Clubs[], int teamID){
    int i, j = 0;
    for( i = 0; i < strlen(str) - 1; ++i){
        Clubs[teamID].name[j] = str[i];
        j++;
    }
    Clubs[teamID].teamID = teamID;
}

int learnInstruction(char str[], int n, Team Clubs[]){

    int iter = 0;
    //char * pEnd = str;
    int buf, buf1, buf2, teamid1, teamid2;
    char team1[20], team2[20];
    while(str[iter] != ' '){
        team1[iter] = str[iter];
        iter++;
    }
    team1[iter] = '\0';
    int iter1 = 0;
    while(iter1 < n){
        buf = strcmp(team1, Clubs[iter1].name);
        buf1 = strcmp(team1, "tabela");
        buf2 = strcmp(team1, "exit");
        if(buf == 0){
            teamid1 = iter1;
            break;
        }
        else if(buf1 == 0){
            return 3;
        }
        else if(buf2 == 0)
            return 4;
        iter1++;
    }

    if(iter1 == n){
        printf("W tabeli nie ma druzyny %s!\n", team1);
        return 0;
    }
    iter++;

    if(str[iter] == '-')
        return 1;
    else if(str[iter] == ':')
        return 2;
    iter = iter+2;
    buf = 2;
    iter1 = 0;

    while(str[iter] != ' ' && str[iter] != '\n'){
        team2[iter1] = str[iter];
        iter++;
        iter1++;
    }
    iter1 = 0;
    while(iter1 < n){
       buf = strcmp(team2, "tabela");
        if(buf == 0){
            teamid2 = iter1;
            break;
        }
        iter1++;
    }
    if(buf == 2){
        printf("W tabeli nie ma druzyny %s!\n", team2);
        return 0;
    }
}

int addMatch(char str[], Team Clubs[], Match Play[], int n, int komb, int *savedMatches){

    int iter = 0;
    char * pEnd = str;
    int buf, teamid1, teamid2;
    char team1[20], team2[20];
    while(str[iter] != ' '){
        team1[iter] = str[iter];
        iter++;
    }
    team1[iter] = '\0';
    int iter1 = 0;
    while(iter1 < n){
        buf = strcmp(team1, Clubs[iter1].name);
        //printf("buf1 = %d\n", buf);
        if(buf == 0){
            teamid1 = iter1;
            break;
        }
        iter1++;
    }

    if(iter1 == n){
        printf("nieznaleziono druzyny 1!", team1);
        return 0;
    }
    iter++;

    if(str[iter] != '-' || str[iter+1] != ' '){
        printf("blad skladni!\n");
        return 0;
    }
    iter = iter+2;
    buf = 2;
    iter1 = 0;

    while(str[iter] != ' ' && str[iter] != '\n'){
    //while(iter < strlen(str)){
        team2[iter1] = str[iter];
        //printf("team2[%d] = %c\n", iter1, str[iter]);
        //printf("team2: %c\n", team2[iter1]);
        iter++;
        iter1++;
    }
    team2[iter1] = '\0';
    iter1 = 0;


    while(team2[iter1] != '\0'){
        //printf("%c", team2[iter1]);
        iter1++;
    }
    //printf("%c\n", team2[iter1]);
    iter1= 0;




    while(iter1 < n){
        buf = strcmp(team2, Clubs[iter1].name);
        //printf("buf2 = %d\n", buf);
        //printf("string1 = %s\tstring2 = %s\n", team2, Clubs[iter1].name);
        if(buf == 0){
            //printf("!!!teamid2 = %d\n", iter1);
            teamid2 = iter1;
            break;
        }
        iter1++;
    }
    //printf("teamid2 = %d\n", teamid2);

    if(buf == 2){
        printf("Nie znaleziono druzyny 2!\n");
        return 0;
    }

    if(str[iter] != ' '){
        printf("blad zapisu!\n");
        return 0;
    }

    iter++;
    if(isdigit(str[iter]) == 0){
        printf("blad zapisu!\n");
        return 0;
    }
    Play[*savedMatches].points1 = strtol ((pEnd+iter),&pEnd,16);//atoi(str[iter]);
    iter++;
    if(str[iter] != ':'){
        printf("blad zapisu!\n");
        return 0;
    }
    iter++;
    if(isdigit(str[iter]) == 0){
        printf("blad zapisu!\n");
        return 0;
    }


    Play[*savedMatches].points2 = strtol ((pEnd+1),&pEnd,16);

    Play[*savedMatches].id1 = teamid1;
    //printf("Play[%d] = %d w addmatch = %d\n", *savedMatches, Play[*savedMatches].id1);

    Play[*savedMatches].id2 = teamid2;
    //printf("Play[%d] = %d w addmatch = %d\n", *savedMatches, Play[*savedMatches].id1);
    Play[*savedMatches].matchID = savedMatches;

    Clubs[teamid1].points_scored = Clubs[teamid1].points_scored + Play[*savedMatches].points1;
    Clubs[teamid1].points_lost = Clubs[teamid1].points_lost + Play[*savedMatches].points2;
    Clubs[teamid1].matches = Clubs[teamid1].matches + 1;

    //printf("w funkcji!!!111\n");
    //printf("teamid2 = %d\n", teamid2);
    //printf("Clubs[%d].points_scored = %d \n", teamid2, Clubs[teamid2].points_scored);
    //printf("Play[%d].points2 = %d\n",*savedMatches, Play[*savedMatches].points2);
    Clubs[teamid2].points_scored = Clubs[teamid2].points_scored + Play[*savedMatches].points2;

    //printf("w funkcji!!!\n");
    Clubs[teamid2].points_lost = Clubs[teamid2].points_lost + Play[*savedMatches].points1;

    Clubs[teamid2].matches = Clubs[teamid2].matches + 1;

    if(Play[*savedMatches].points1 > Play[*savedMatches].points2){
        Clubs[teamid1].wins = Clubs[teamid1].wins + 1;
        Clubs[teamid2].loses = Clubs[teamid2].loses + 1;
        Clubs[teamid1].leaguePoints = Clubs[teamid1].leaguePoints + 3;
    }
    else if(Play[*savedMatches].points1 < Play[*savedMatches].points2){
        Clubs[teamid2].wins = Clubs[teamid2].wins + 1;
        Clubs[teamid1].loses = Clubs[teamid1].loses + 1;
        Clubs[teamid2].leaguePoints = Clubs[teamid2].leaguePoints + 3;
    }
    else{
        Clubs[teamid2].draws = Clubs[teamid2].draws + 1;
        Clubs[teamid1].draws = Clubs[teamid1].draws + 1;
        Clubs[teamid1].leaguePoints = Clubs[teamid1].leaguePoints + 1;
        Clubs[teamid2].leaguePoints = Clubs[teamid2].leaguePoints + 1;
    }


    *savedMatches = *savedMatches + 1;
    return 1;

}

void displayTable(int n, Team Clubs[], Match Play[]){
    typedef struct List{
        int teamid;
        int lgpoints;
    } List;

    List sortedList[n];
    for(int i = 0; i < n; i++){
        sortedList[i].teamid = i;
        sortedList[i].lgpoints = Clubs[i].leaguePoints;
    }
    int i_max, temp1, temp2;
    for(int i = 0; i < n - 1 ; ++i){
        i_max = i;
        //printf("zew i = %d \n", i);
        for(int j = i +1; j < n; j++){
            if(sortedList[j].lgpoints > sortedList[i_max].lgpoints){
                i_max = j;
                temp1 = sortedList[i].lgpoints;
                temp2 = sortedList[i].teamid;
                sortedList[i].lgpoints = sortedList[i_max].lgpoints;
                sortedList[i].teamid = sortedList[i_max].teamid;
                sortedList[i_max].lgpoints = temp1;
                sortedList[i_max].teamid = temp2;
            }
            //printf("wew i = %d  j = %d  n + 1 = %d\n", i , j, n+1);
        }
    }
    for(int i = 0; i < n; ++i){
        printf("%d.\t%s\t%d\t%d-%d\n", i+1, Clubs[sortedList[i].teamid].name, sortedList[i].lgpoints, Clubs[sortedList[i].teamid].points_scored,Clubs[sortedList[i].teamid].points_lost);
    }

}

void displayMatch(char str[], Team Clubs[], Match Play[], int n,int savedMatches){
    int iter = 0;
    int buf, teamid1, teamid2;
    char team1[9], team2[9];
    while(str[iter] != ' '){
        team1[iter] = str[iter];
        iter++;
    }
    team1[iter] = '\0';
    int iter1 = 0;
    while(iter1 < n){
        buf = strcmp(team1, Clubs[iter1].name);
        if(buf == 0){
            teamid1 = iter1;
            break;
        }
        iter1++;
    }
    if(iter1 == n){
        printf("Nieznaleziono druzyny %s!\n", team1);
        return;
    }
    iter++;
    if(str[iter] != ':' || str[iter+1] != ' '){
        printf("blad skladni tuetej!\n");
        return;
    }
    iter = iter+1;
    buf = 2;
    iter1 = 0;

    while(iter < strlen(str)){
        iter++;
        team2[iter1] = str[iter];
       // printf("team2: %c\n", team2[iter1]);
        iter1++;
    }
    iter1 = 0;
    while(iter1 < n){
        buf = strcmp(team2, Clubs[iter1].name);
        if(buf == 0){
            //printf("!!!teamid2 = %d\n", iter1);
            teamid2 = iter1;
            break;
        }
        iter1++;
    }
    if(buf == 2){
        printf("Nie zanaleziono druzyny %s\n", team2);
        return 0;
    }

    for( int i = 0; i < n; ++i){
        //printf("PLay[%d].id1 = %d \t Play[%d].id2 = %d\n", i, Play[i].id1, i, Play[i].id2);
       // printf("teamid1 = %d \t teamid2 = %d\n", teamid1, teamid2);
        if(Play[i].id1 == teamid1 && Play[i].id2 == teamid2){
            printf("%d : %d\n", Play[i].points1, Play[i].points2);
            return;
        }
        else{
            printf("mecz sie nie odbył!\n");
            return;
            }
    }
    //printf("cos tam \n");


}

int main()
{
    char ch2;
    int odp;
    int xyz;
    int savedMatches = 0;
    int komb;
    printf("Podaj liczbe druzyn: ");
    int n;
    scanf("%d", &n);
    Team *Clubs = malloc(n * sizeof(Team));
    char *str;

    Team druzyna;

    komb = MatchNumber(n);
    Match *Play = malloc(komb * sizeof(Team));

    int c;
    char tekst[100];
    char input[30];
    char ch = 'x';
    char ch1 = getchar();
    char c1;
    int iterator;

    for(int i = 0; i < n; ++i){
        ch = 'x';
        iterator = 0;
        printf("Druzyna %d: ", i + 1);
        while(ch != '\n')    // terminates if user hit enter
        {
            ch = getchar();
            input[iterator] = ch;
            iterator++;

        }
        input[iterator] = '\0';
        addTeam(input, Clubs, i);
        Clubs[i].points_scored = 0;
        Clubs[i].points_lost = 0;
        Clubs[i].wins = 0;
        Clubs[i].loses = 0;
        Clubs[i].draws = 0;
        Clubs[i].matches = 0;
        //Clubs[i].teamID = 0;
        Clubs[i].leaguePoints = 0;
        //printf("nazwa klubu: %s\nid: %d\n", Clubs[i].name, Clubs[i].teamID);

    }

    while(1){

        ch = 'x';
        iterator = 0;

        while((ch = getchar()) != '\n' && ch != EOF)    // terminates if user hit enter
        {
            input[iterator] = ch;
            iterator++;
        }
        input[iterator] = '\0';

        //printf("wczytany input:%s\n", input);
        odp = learnInstruction(input, n, Clubs);
        if(odp == 1){
            xyz = addMatch(input, Clubs, Play, n, komb, &savedMatches);
            continue;
        }
        else if(odp == 2){
            displayMatch(input, Clubs, Play, komb, savedMatches);
            continue;
        }
        else if(odp == 3){
            displayTable(n, Clubs, Play);
            continue;
        }

        if(odp == 4)
            break;
    }


    printf("Koniec dzialania programu\n");
    free(Clubs);
    free(Play);
    return 0;

}
