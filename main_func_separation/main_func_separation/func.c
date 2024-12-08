#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// 구조체 정의
typedef struct {
    int currentWeight;
    int currentFloor;
    int skipped;
    int effectFloor;
    int weightChange;
    int previousEffectFloor;
} Player;
    
// 함수 포인터 정의
typedef void (*CardFunction)(Player*);

// 함수 구현부
void decreaseWeight(Player* player) {
    player->weightChange = ((rand() % 151) + 200);
    player->currentWeight -= (player->weightChange);
    if (player->currentWeight <= 0) {
        player->currentWeight = 0;
    }
    printf("무게가 %dkg 감소했습니다! 현재 무게: %dkg\n", player->weightChange, player->currentWeight);
}

void increaseWeight(Player* player) {
    player->weightChange = ((rand() % 51) + 50);
    player->currentWeight += player->weightChange;
    if (player->currentWeight <= 0) {
        player->currentWeight = 0;
    }
    printf("무게가 %dkg 증가했습니다! 현재 무게: %dkg\n", player->weightChange, player->currentWeight);
}

void resetToPreviousFloorWeight(Player* player) {
    player->previousEffectFloor = 1;
    player->currentWeight += player->weightChange;
    printf("이전 층의 무게로 돌아갑니다! 현재 무게: %dkg\n", player->currentWeight);
}

void skipFloor(Player* player) {
    player->currentFloor++;
    player->weightChange = 0;
    player->skipped = 1;  // 층 건너뛰기 카드 사용 표시
    printf("층을 무시하고 넘어갑니다! 현재 층: %d층\n", player->currentFloor);
}

void applyBalloonEffect(Player* player) {
    player->effectFloor = 3;
    player->currentWeight -= 400;
    player->weightChange = 400;
    printf("풍선 효과로 3턴 동안 400kg 감소했습니다! 현재 무게: %dkg\n", player->currentWeight);
}

void randomWeight(Player* player) {
    int minIncrease = -500;
    int maxIncrease = 500;
    int weightIncrease = (rand() % (maxIncrease - minIncrease + 1)) + minIncrease;
    player->currentWeight += weightIncrease;
    player->weightChange = weightIncrease;
    if (player->currentWeight <= 0) {
        player->currentWeight = 0;
    }
    if (weightIncrease > 0) {
        printf("랜덤무게로 %dkg만큼 늘어났습니다.\n", weightIncrease);
    }
    else {
        printf("랜덤무게로 %dkg만큼 줄어들었습니다\n", weightIncrease);
    }
    printf("랜덤으로 무게를 더하거나 뺍니다! 현재 무게: %dkg\n", player->currentWeight);
}

void randomMultiple(Player* player) {
    int effect = rand() % 2;
    if (effect == 0) {
        player->weightChange = player->currentWeight - player->currentWeight * 2;
        player->currentWeight = player->currentWeight *= 2; //무게 두배 증가
    }
    else {
        player->weightChange = player->currentWeight - (player->currentWeight / 2);
        player->currentWeight = (player->currentWeight + 1) / 2; //무게 절반 감소

    }
    printf("랜덤으로 무게가 2배로 나눠지거나 곱해집니다! 현재 무게: %dkg\n", player->currentWeight);
}


void showRules() {
    printf("\n게임 규칙:\n");
    printf("1. 플레이어는 2000kg의 짐을 가진 채 시작합니다.\n");
    printf("2. 탑의 각 층마다 무게 제한이 있으며, 제한을 초과하면 게임이 종료됩니다.\n");
    printf("3. 카드 선택을 통해 무게를 조절하거나 층을 건너뛸 수 있습니다.\n");
    printf("4. 20층에 도달하면 게임에 승리합니다.\n\n");
    printf("아무 키나 눌러 메인 화면으로 돌아가세요...\n");
    (void)getchar();
}

void selectCard(Player* player, CardFunction cards[], const char* cardDescriptions[]) {
    int cardChoice;
    printf("카드를 선택하세요: 1, 2 또는 3\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i + 1, cardDescriptions[i]);
    }
    scanf_s("%d", &cardChoice);

    if (cardChoice >= 1 && cardChoice <= 3) {
        cards[cardChoice - 1](player); // 선택한 카드 실행
    }
    else {
        printf("잘못된 선택입니다. 카드가 적용되지 않았습니다.\n");
    }
}
