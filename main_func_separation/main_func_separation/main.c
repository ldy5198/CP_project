#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "func.h"

#define MAX_WEIGHT 2000
#define MAX_FLOORS 20

const char* cardNames[] = {
    "무게 감소",
    "무게 증가",
    "이전 층 무게로 복귀",
    "층 건너뛰기",
    "풍선 효과",
    "랜덤 무게 부여",
    "무게 두배 증가 혹은 두배 감소"
};

void showMainMenu() {
    printf("\n\n\n");
    printf("=====================================\n");
    printf("         탑 오르기 게임\n");
    printf("=====================================\n");
    printf("    1. 게임 시작\n");
    printf("    2. 게임 규칙 설명\n");
    printf("    3. 종료\n");
    printf("=====================================\n");
    printf("선택하세요: ");
}

void playGame(Player* player) {
    CardFunction cardDeck[] = {
        decreaseWeight,
        increaseWeight,
        resetToPreviousFloorWeight,
        skipFloor,
        applyBalloonEffect,
        randomWeight,
        randomMultiple
    };

    while (player->currentFloor <= MAX_FLOORS && player->currentWeight > 0) {
        int weightLimit = MAX_WEIGHT - ((player->currentFloor - 1) * 100);

        if (player->currentWeight > weightLimit) {
            printf("무게가 너무 무거워 %d층에 오를 수 없습니다. 게임 오버!\n", player->currentFloor);
            return;
        }

        printf("\n%d층에 도달했습니다. 최대 허용 무게: %dkg\n", player->currentFloor, weightLimit);
        printf("현재 무게: %dkg\n", player->currentWeight);

        CardFunction selectedCards[3];
        const char* selectedDescriptions[3];
        for (int i = 0; i < 3; i++) {
            int cardIndex = rand() % 7;
            selectedCards[i] = cardDeck[cardIndex];
            selectedDescriptions[i] = cardNames[cardIndex];
        }

        selectCard(player, selectedCards, selectedDescriptions);

        player->currentFloor++;
    }

    if (player->currentFloor > MAX_FLOORS) {
        printf("축하합니다! 탑의 정점에 도달했습니다!\n");
    }
    else {
        printf("게임이 종료되었습니다. 다시 도전해보세요!\n");
    }
}

int main() {
    srand(time(NULL));

    int choice;
    Player player;

    while (1) {
        system("cls"); // 콘솔 화면 지우기 (Windows 전용)
        showMainMenu();
        scanf_s("%d", &choice);

        if (choice == 1) {
            player.currentWeight = MAX_WEIGHT;
            player.currentFloor = 1;
            player.skipped = 0;
            player.effectFloor = 0;
            player.weightChange = 0;
            player.previousEffectFloor = 0;

            playGame(&player);
            printf("아무 키나 눌러 메인 화면으로 돌아가세요...\n");
            (void)_getch(); // 반환값 무시
        }
        else if (choice == 2) {
            showRules();
        }
        else if (choice == 3) {
            printf("게임을 종료합니다.\n");
            break;
        }
        else {
            printf("잘못된 선택입니다. 다시 입력하세요.\n");
            (void)_getch(); // 반환값 무시
        }
    }

    return 0;
}
