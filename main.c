#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

int main(void){
    player *sp[100];
    team t;
    int index=0;
    int count = 0, menu;
    int result=0;
    count = loadData(sp);
    index=count;

    //팀 포메이션 초기화
    t.myteam_attack = 3;
    t.myteam_def = 4;
    t.myteam_middle = 3;
    t.myteam_goalkeep = 1;

    while (1){
        menu = selectMenu();
        if (menu == 0) break;
        else if(menu == 1){
            if(count > 0)
            listplayer(sp, index);
            else
            printf("No data.\n");
        }

        else if (menu == 2){
            sp[index] = (player *)malloc(sizeof(player));
            count += addplayer(sp[index++]);


        }
        else if(menu == 3){
            int no = selectDataNo(sp, index);
            if(no == 0){
                printf("=> Cancelled!\n");
            continue;
            }
            updateplayer(sp[no-1]);
        }

    else if (menu == 4) {
      int no = selectDataNo(sp, index);
      if (no == 0) {
        printf("=> Cancelled!\n");
        continue;
      }
      int deleteok;
      printf("Are you sure you want to delete it?(Delete:1)");
      scanf("%d", &deleteok);
      if (deleteok == 1) {
        if (sp[no-1])
        free(sp[no-1]);
        sp[no-1] = NULL;
        count--;

        printf("Deleted\n");
    } else
            printf("Cancelled\n");
    }
    else if(menu == 5){
      saveData(sp, index);
    }

    else if(menu==6)
    {
        searchName(sp,index);
    }
    else if(menu==7)
    {
        int no = selectDataNo(sp, count);
        if (no == 0) {
        printf("=> Cancelled!\n");
        continue;
        }

        myteamadd(sp,no-1);
    }

    else if(menu==8)
    {
        myteamformationadd(&t);
    }
    else if(menu==9)
    {
	int no = selectMyDataNo(sp, count);
        if (no == 0) {
        printf("=> Cancelled!\n");
        continue;
        }
	formation_player_add(sp, no, &t);
    }
    
    else if(menu == 10) {
        showMyTeamFormation(sp, index, &t);
    }

    else if(menu==11)
    {
        myteamshow(sp,index);
    }
    
    else if(menu == 12) {
        changeMyTeamFormation(sp, index, &t);
    }

	}    
    printf("Terminated!\n");
    return 0;


}
