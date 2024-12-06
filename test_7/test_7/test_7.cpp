#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX_CARDS 20
#define MAX_WEIGHT 2000
#define MAX_FLOORS 20

// 플레이어 구조체 정의
typedef struct {
    int currentWeight;
    int currentFloor;
    int skipped;
    int effectFloor;
    int previousWeight;
} Player;

// 함수 선언
void playGame(Player* player); // playGame 함수 선언

// 카드 효과 함수들
void decreaseWeight(Player* player) {
    int decrease = (rand() % 151) + 200;
    player->currentWeight -= decrease;
    if (player->currentWeight < 0) {
        player->currentWeight = 0;
    }
    printf("무게가 %dkg 감소했습니다! 현재 무게: %dkg\n", decrease, player->currentWeight);
}

void increaseWeight(Player* player) {
    int increase = (rand() % 51) + 50;
    player->currentWeight += increase;
    printf("무게가 %dkg 증가했습니다! 현재 무게: %dkg\n", increase, player->currentWeight);
}

void resetToPreviousFloorWeight(Player* player) {
    if (player->currentFloor > 1) {
        player->currentWeight = player->previousWeight;
        printf("이전 층의 무게로 돌아갑니다! 현재 무게: %dkg\n", player->currentWeight);
    }
    else {
        printf("1층에서는 이전 층의 무게로 돌아갈 수 없습니다!\n");
    }
}

void skipFloor(Player* player) {
    player->currentFloor++;
    player->skipped = 1;
    printf("층을 무시하고 넘어갑니다! 현재 층: %d층\n", player->currentFloor);
}

// 게임 진행
void playGame(Player* player) {
    CardFunction cardDeck[MAX_CARDS] = {
        decreaseWeight, increaseWeight, resetToPreviousFloorWeight, skipFloor
    };

    while (player->currentFloor <= MAX_FLOORS && player->currentWeight > 0) {
        int weightLimit = MAX_WEIGHT - ((player->currentFloor - 1) * 100);

        if (player->skipped == 0 && player->currentWeight > weightLimit) {
            printf("무게가 너무 무거워 %d층에 오를 수 없습니다. 게임 오버!\n", player->currentFloor);
            return;
        }

        player->skipped = 0;

        printf("\n%d층에 도달했습니다. 최대 허용 무게: %dkg\n", player->currentFloor, weightLimit);
        printf("현재 무게: %dkg\n", player->currentWeight);

        if (player->currentFloor > 1) {
            player->previousWeight = player->currentWeight;
        }

        CardFunction selectedCards[3];
        const char* cardNames[] = { "무게 감소", "무게 증가", "이전 층 무게로 복귀", "층 건너뛰기" };
        const char* selectedDescriptions[3];

        for (int i = 0; i < 3; i++) {
            int cardIndex = rand() % 4;
            selectedCards[i] = cardDeck[cardIndex];
            selectedDescriptions[i] = cardNames[cardIndex];
        }

        printf("사용 가능한 카드:\n");
        for (int i = 0; i < 3; i++) {
            printf("%d. %s\n", i + 1, selectedDescriptions[i]);
        }

        int choice;
        printf("카드를 선택하세요: ");
        scanf_s("%d", &choice);
        if (choice >= 1 && choice <= 3) {
            selectedCards[choice - 1](player);
        }
        else {
            printf("잘못된 선택입니다. 카드가 적용되지 않았습니다.\n");
        }

        player->currentFloor++;
    }

    printf("축하합니다! 탑의 정점에 도달했습니다!\n");
}

int main() {
    srand((unsigned int)time(NULL));

    int choice;
    Player player;

    while (1) {
        system("cls");
        printf("\n\n\n");
        printf("=====================================\n");
        printf("         탑 오르기 게임\n");
        printf("=====================================\n");
        printf("    1. 게임 시작\n");
        printf("    2. 게임 규칙 설명\n");
        printf("    3. 종료\n");
        printf("=====================================\n");
        printf("선택하세요: ");
        scanf_s("%d", &choice);

        if (choice == 1) {
            player.currentWeight = MAX_WEIGHT;
            player.currentFloor = 1;
            player.skipped = 0;
            player.previousWeight = MAX_WEIGHT;
            playGame(&player); // 올바르게 호출
            printf("아무 키나 눌러 메인 화면으로 돌아가세요...\n");
            _getch();
        }
        else if (choice == 2) {
            printf("\n게임 규칙:\n");
            printf("1. 플레이어는 2000kg의 짐을 가진 채 시작합니다.\n");
            printf("2. 탑의 각 층마다 무게 제한이 있으며, 제한을 초과하면 게임이 종료됩니다.\n");
            printf("3. 카드 선택을 통해 무게를 조절하거나 층을 건너뛸 수 있습니다.\n");
            printf("4. 20층에 도달하면 게임에 승리합니다.\n\n");
            printf("아무 키나 눌러 메인 화면으로 돌아가세요...\n");
            _getch();
        }
        else if (choice == 3) {
            printf("게임을 종료합니다.\n");
            break;
        }
        else {
            printf("잘못된 선택입니다. 다시 입력하세요.\n");
            _getch();
        }
    }

    return 0;
}
