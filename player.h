#include <stdio.h>


typedef struct{
char name[20];//선수 이름
char league[20];//뛰고 있는 league
char team[30];//뛰고 있는 team
unsigned int goal;//골 개수
unsigned int assist;//어시스트 개수
int myteam;
int myteam_form[12];
} player;

typedef struct{
int myteam_goalkeep;//나의 팀의 포메이션 ex ) 1 <= 골키퍼 4 <- 수비수 5 <- 미드필더 1 <- 공격수 이런식으로 팀의 포메이션을 지정가능
int myteam_def;
int myteam_middle;
int myteam_attack;

} team;



int selectMenu();
int addplayer(player *s);
void listplayer(player *s[], int count);
int updateplayer(player *s);
int selectDataNo(player *s[], int count);
int selectMyDataNo(player *s[], int count);
void searchName(player *s[], int count);
void saveData(player *s[], int count);
int loadData(player *s[]);

void myteamadd(player *s[],int count);
void myteamformationadd(team *t);
void formation_player_add(player *s[], int count,team* t);
void myteamshow(player *s[],int count);
void showMyTeamFormation(player *s[], int count, team *t); 
void changeMyTeamFormation(player *s[], int count, team *t);
void movePlayer(player *s[], int count, int oldPos, int newPos);
int countPlayersInPosition(player *s[], int count, int position);