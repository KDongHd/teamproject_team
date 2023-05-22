#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

char *strcasestr(const char *haystack, const char *needle)
{
    int size = strlen(needle);

    while(*haystack) {
        if(strncasecmp(haystack, needle, size) == 0) {
            return (char *)haystack;
        }
        haystack++;
    }

    return NULL;
}

int selectMenu(){
    int menu;
    printf("\n*** Player ***\n");
    printf("1. View Player\n");
    printf("2. Add Player\n");
    printf("3. Update Player\n");
    printf("4. Delete Player\n");
    printf("5. Save Player\n");
    printf("6. Search By Name\n");
    printf("7. Add/Delete Your Team's Player\n");
    printf("8. Add Formation to Your Team\n");
    printf("9. Add Player to Your Team's Formation\n");
    printf("10. View Your Team's Player By Formation\n");
    printf("11. View Your Team's Player\n");
    printf("12. Change Your Team's Formation\n");
    printf("0. Exit\n\n");
    printf("=> Select Menu? ");
    scanf("%d", &menu);
    return menu;
}

int addplayer(player *s){
    getchar();
    printf("Name?");
    scanf("%s",s->name);
    printf("Number of goals?");
    scanf("%u",&s->goal);
    printf("Number of assists?");
    scanf("%u",&s->assist);
    printf("Current league?");
    scanf("%s",s->league);
    printf("Current team?");
    scanf(" %s",s->team);
    s-> myteam = 0;//팀은  일단 0으로 초기화
    printf("%s %u %u %s %s",s->name,s->goal,s->assist,s->league, s->team);
    return 1;
}


void readplayer(player s){
    printf("%s %u %u %s %s",s.name,s.goal,s.assist,s.league, s.team);
}



void listplayer(player *s[], int count) {
printf("\nName Goal Assist League Team\n");
for (int i = 0; i < count; i++) {
    if (s[i]==NULL)
        continue;

    printf("\n%d ", i + 1);
    readplayer(*s[i]);
  }
  printf("\n");
}

int updateplayer(player *s){
    printf("New name?");
    scanf("%s",s->name);
    printf("Edit number of goals");
    scanf("%u",&s->goal);
    printf("Edit number of assists");
    scanf("%u",&s->assist);
    printf("New league?");
    scanf("%s",s->league);
    printf("New team?");
    scanf(" %s",s->team);
    return 1;
}

int selectDataNo(player *s[], int count){
    int no;
    listplayer(s, count);
    myteamshow(s,count);
    printf("Number (Cancel :0)? ");
    scanf("%d", &no);
    return no;
}

int selectMyDataNo(player *s[], int count){
    int no;
    myteamshow(s,count);
    printf("Number (Cancel :0)? ");
    scanf("%d", &no);
    return no;
}

void searchName(player *s[], int count){
    int scnt = 0;
    char search[20];
    printf("Search Menu? ");
    scanf("%s", search);
    for(int i =0; i <count ; i++){
        if(s[i] == NULL) continue;
        if(strcasestr(s[i]->name, search)){
            printf("%2d ", i+1);
            readplayer(*s[i]);
            scnt++;
        }
    }
    if(scnt == 0) printf("=> No data found!");
    printf("\n");
}

void saveData(player *s[], int count){
    FILE *fp;
    fp = fopen("player.txt", "wt");
    for(int i = 0; i < count; i++){
        if(s[i] == NULL) continue;
        fprintf(fp, "%s %u %u %s %s %d\n", s[i]->name, s[i]->goal, s[i]->assist, s[i]->league, s[i]->team, s[i]->myteam);
    }
    fclose(fp);
    printf("=> Saved!");
}

int loadData(player *s[]){
    int count = 0, i = 0;
    FILE *fp;
    fp = fopen("player.txt", "rt");
    for(i=0; i < 100; i++){
        s[i] = (player *)malloc(sizeof(player));
        fscanf(fp, "%s", s[i]->name);
        if(feof(fp)) break;
        fscanf(fp, "%u", &s[i]->goal);
        fscanf(fp, "%u", &s[i]->assist);
        fscanf(fp, "%s", s[i]->league);
        fscanf(fp, " %s", s[i]->team);
        fscanf(fp, "%u", &s[i]->myteam);
    }
    fclose(fp);
    printf("=> Loaded!");
    return i;
}


void myteamadd(player *s[],int count)
{
    int select;
    printf("Would you like to add a player to the team?(To add: 1) Would you like to remove a player from the team ?(To remove : 0)");
    scanf("%d", &select);
    if (select == 1) {
    s[count]->myteam = 1;
    }
	else if(select == 0)
	{
		s[count]->myteam = 0;
	}
}

void myteamformationadd(team *t){
	
	int sum =0;
	t->myteam_goalkeep = 1;  // Fixed number of goalkeepers

	while(sum != 10 ){
        printf("Please enter the number of defenders ");
        scanf("%d", &t->myteam_def);
        printf("Please enter the number of midfielders ");
        scanf("%d", &(t->myteam_middle));
        printf("Please enter the number of forwards ");
	    scanf("%d", &(t->myteam_attack));
	    sum = t->myteam_def + t->myteam_middle + t->myteam_attack;
	}
}

void myteamshow(player *s[], int count) {
printf("\nMY TEAM\n");
printf("Name goal assist League Team\n");
for (int i = 0; i < count; i++) {
    if (s[i]->myteam == 0)
        continue;

    printf("\n%d ", i + 1);
    readplayer(*s[i]);
  }
  printf("\n");
}

void formation_player_add(player *s[], int count, team* t)
{
	printf("Please set the formation for the players added to the current team");
	printf("The current team's formation numbers are: Goalkeeper: %d Defender: %d Midfielder: %d Forward: %d ",t->myteam_goalkeep, t->myteam_def,t->myteam_middle,t->myteam_attack );
	int team_count = 1;
       	printf("\n\n");	
	for (int i =0; i < t->myteam_attack ; i++)
	{
		printf("%d       ",team_count);
		team_count++;
	}
	printf("\n\n");
	for (int i =0; i < t->myteam_middle ; i++)
        {
                printf("%d       ",team_count);
                team_count++;
        }
	printf("\n\n");
	for (int i =0; i < t->myteam_def ; i++)
        {
		
                printf("%d       ",team_count);
                team_count++;
        }
	printf("\n\n");
	for (int i =0; i < t->myteam_goalkeep ; i++)
        {
		
                printf("           %d",team_count);
                team_count++;
        }
	printf("\n\n");
	int position; 
	printf("Which position would you like to place the player in? ");
	scanf("%d",&position);
	s[count-1]->myteam_form[position-1] = 1;
    
    if (s[count-1]->myteam_form[position - 1] == 1) {
        printf("The player has been successfully added to the formation.\n");
    } else {
        printf("The player has not been successfully added to the formation.\n");
    }
}


void showMyTeamFormation(player *s[], int count, team *t) {
    char *team_form[12];
    for(int i = 0; i < 12; i++) {   // initialize team_form array
        team_form[i] = "X";
    }

    for (int i = 0; i < count; i++) {
        if (s[i]->myteam == 1) {
            for (int j = 0; j < 12; j++) {
                if (s[i]->myteam_form[j] == 1) {
                    team_form[j] = s[i]->name;
                }
            }
        }
    }

    // Print team formation
    printf("\nTeam Formation:\n");
    for (int i = 0; i < t->myteam_attack; i++) {
        printf("%s       ", team_form[i]);
    }
    printf("\n\n");
    for (int i = 0; i < t->myteam_middle; i++) {
        printf("%s       ", team_form[i + t->myteam_attack]);
    }
    printf("\n\n");
    for (int i = 0; i < t->myteam_def; i++) {
        printf("%s       ", team_form[i + t->myteam_attack + t->myteam_middle]);
    }
    printf("\n\n");
    for (int i = 0; i < t->myteam_goalkeep; i++) {
        printf("           %s", team_form[i + t->myteam_attack + t->myteam_middle + t->myteam_def]);
    }
    printf("\n\n");
}



void changeMyTeamFormation(player *s[], int count, team *t) {
    int sum = 0, old_def = t->myteam_def, old_middle = t->myteam_middle, old_attack = t->myteam_attack;
    t->myteam_goalkeep = 1;  // Fixed number of goalkeepers

    while(sum != 10 ){
        printf("Please enter the number of defenders ");
        scanf("%d", &t->myteam_def);
        printf("Please enter the number of midfielders ");
        scanf("%d", &(t->myteam_middle));
        printf("Please enter the number of forwards ");
        scanf("%d", &(t->myteam_attack));
        sum = t->myteam_def + t->myteam_middle + t->myteam_attack;
    }

    if(old_def > t->myteam_def && countPlayersInPosition(s, count, 2) >= old_def) {
        printf("Which defender would you like to change to a midfielder? ");
        movePlayer(s, count, 2, 3); // Move defender to midfielder
    }
    
    if(old_middle > t->myteam_middle && countPlayersInPosition(s, count, 3) >= old_middle) {
        if(old_def < t->myteam_def) {
            printf("Which midfielder would you like to change to a defender? ");
            movePlayer(s, count, 3, 2); // Move midfielder to defender
        } else if(old_attack < t->myteam_attack) {
            printf("Which midfielder would you like to change to an attacker? ");
            movePlayer(s, count, 3, 4); // Move midfielder to attacker
        }
    }
    
    if(old_attack > t->myteam_attack && countPlayersInPosition(s, count, 4) >= old_attack) {
        printf("Which attacker would you like to change to a midfielder? ");
        movePlayer(s, count, 4, 3); // Move attacker to midfielder
    }
}

int countPlayersInPosition(player *s[], int count, int position) {
    int playersInPosition = 0;
    for(int i = 0; i < count; i++) {
        if(s[i]->myteam_form[position-1] == 1) {
            playersInPosition++;
        }
    }
    return playersInPosition;
}

void movePlayer(player *s[], int count, int oldPos, int newPos) {
    int playerNo;
    scanf("%d", &playerNo);

    if(playerNo > count || playerNo <= 0){
        printf("Invalid player number. Please try again.\n");
        return;
    }

    // Check if the player is in the correct old position
    if(s[playerNo-1]->myteam_form[oldPos-1] != 1) {
        printf("The player is not in the specified old position. Please try again.\n");
        return;
    }

    // Update player position
    for(int i = 0; i < 12; i++)
        s[playerNo-1]->myteam_form[i] = 0;
    s[playerNo-1]->myteam_form[newPos-1] = 1;

    printf("Player position changed.\n");
}
