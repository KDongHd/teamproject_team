#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"


int selectMenu(){
    int menu;
    printf("\n*** player ***\n");
    printf("1. 선수조회\n");
    printf("2. 선수추가\n");
    printf("3. 선수수정\n");
    printf("4. 선수삭제\n");
    printf("5. 선수저장\n");
    printf("6. 이름검색\n");
    printf("7. 자기팀 선수 추가/삭제 \n");
    printf("8. 자기팀 포메이션 추가\n");
    printf("9. 자기팀 포메이션에 선수 추가\n");
    printf("10. 자기팀 선수 포메이션으로 조회\n");
    printf("11. 자기팀 선수  조회\n");
    printf("12. 자기팀 포메이션 변경\n");
    printf("0. 종료\n\n");
    printf("=> 원하는 메뉴는? ");
    scanf("%d", &menu);
    return menu;
}




int addplayer(player *s){
    printf("이름은?");
    scanf("%s",s->name);
    printf("goal number");
    scanf("%u",&s->goal);
    printf("assist number");
    scanf("%u",&s->assist);
    printf("뛰고 있는 리그");
    scanf("%s",s->league);
    printf("뛰고 있는 팀");
    scanf(" %[^\n]s",s->team);
    s-> myteam = 0;//팀은  일단 0으로 초기화
    printf("%s %u %u %s ",s->name,s->goal,s->assist,s->league);
}


void readplayer(player s){

    printf("%s %u %u %s",s.name,s.goal,s.assist,s.league);
}

void listplayer(player *s[], int count) {
printf("\n이름 goal assist 리그 팀\n");
for (int i = 0; i < count; i++) {
    if (s[i]==NULL)
        continue;

    printf("\n%d ", i + 1);
    readplayer(*s[i]);
  }
  printf("\n");
}
int updateplayer(player *s){
      printf("새 이름은?");
      scanf("%s",s->name);
      printf("edit goal number");
      scanf("%u",&s->goal);
      printf("edit assist number");
      scanf("%u",&s->assist);
      printf("새로 뛰고 있는 리그");
      scanf("%s",s->league);
      printf("새로 뛰고 있는 팀");
      scanf(" %[^\n]s",s->team);
      return 1;

}
int selectDataNo(player *s[], int count){
    int no;
    listplayer(s, count);
    printf("번호는 (취소 :0)? ");
    scanf("%d", &no);
    return no;
    }

void searchName(player *s[], int count){
    int scnt = 0;
    char search[20];
    printf("검색할 메뉴는? ");
    scanf("%s", search);
    for(int i =0; i <count ; i++){
        if(s[i] == NULL) continue;
        if(strstr(s[i]->name, search)){
        printf("%2d ", i+1);
        readplayer(*s[i]);
        scnt++;
    }
    }
    if(scnt == 0) printf("=> 검색된 데이터 없음!");
        printf("\n");
    }

void saveData(player *s[], int count)
{
    FILE *fp;
    fp = fopen("player.txt", "wt");
    for(int i = 0; i < count; i++){
        if(s[i] == NULL) continue;
        fprintf(fp, "%s %u %u %s %s %u\n"
        ,s[i]->name,s[i]->goal,s[i]->assist,s[i]->league,s[i]->team,s[i]->myteam);
    }
    fclose(fp);
    printf("=> 저장됨! ");
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
        fscanf(fp, " %[^\n]s", s[i]->team);
        fscanf(fp, "%u", &s[i]->myteam);
    }
    fclose(fp);
    printf("=> 로딩 성공!\n");
    return i;
}


void myteamadd(player *s[],int count)
{
        int select;
        printf("팀에 선수를 추가하시겠습니까?(추가하려면 : 1) 팀에 선수를 삭제하시겠브니까 ?(삭제하려면 : 0)");
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

	while(sum != 11 ){
        printf("골키퍼의 숫자를 넣어주세요 (골키퍼는 항상 1명입니다. ), 또한 모든 선수들은 11명이여야합니다. ");
	scanf("%d", &t->myteam_goalkeep);

        printf("수비수 숫자를 넣어 주세요 ");
        scanf("%d", &t->myteam_def);
        printf("미드필더  숫자를 넣어 주세요 ");
        scanf("%d", &(t->myteam_middle));
        printf("공격수  숫자를 넣어 주세요 ");
	scanf("%d", &(t->myteam_attack));
	sum = t->myteam_def + t->myteam_goalkeep+ t->myteam_middle+ t->myteam_attack;
	}
}

void myteamshow(player *s[], int count) {
printf("\n이름 goal assist 리그 팀 myteam\n");
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
	printf("\n이름 goal assist 리그 팀 myteam\n");
	for (int i = 0; i < count; i++) {
    	if (s[i]->myteam == 0)
        continue;

   	printf("\n%d ", i + 1);
    	readplayer(*s[i]);
  	}
  	printf("\n");
	

	printf("현재 팀에 추가된 선수들의 포메이션을 정해 주세요");
	printf("현재 팀에 포메이션숫자는 골키퍼: %d 수비수: %d 미드필더: %d 공격수: %d ",t->myteam_goalkeep, t->myteam_def,t->myteam_middle,t->myteam_attack );
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
}














