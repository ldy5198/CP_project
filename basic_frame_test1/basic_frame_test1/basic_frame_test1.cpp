#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX_CARDS 20 // 카드 개수
#define MAX_WEIGHT 2000 // 초기 무게
#define MAX_FLOORS 20 // 탑 꼭대기 20층으로 설정

// 플레이어 구조체
typedef struct {
    int currentWeight;
    int currentFloor;
    int skipped; // 층 건너뛰기 카드 사용 여부 플래그
} Player;

// 카드 함수 포인터 배열
typedef void (*CardFunction)(Player*);

// 20종류 카드 만들기 전 크게 5개 정도만 !!임시적으로!! 효과를 구현함
void decreaseWeight(Player* player) {
    int decrease = (rand() % 151) + 50;
    player->currentWeight -= decrease;
    printf("무게가 %dkg 감소했습니다! 현재 무게: %dkg\n", decrease, player->currentWeight); // 일단 무게 증가나 무게 감소 배율?은 이후 조정. 
}

void increaseWeight(Player* player) {
    int increase = (rand() % 51) + 50;
    player->currentWeight += increase;
    printf("무게가 %dkg 증가했습니다! 현재 무게: %dkg\n", increase, player->currentWeight);
}

void resetToPreviousFloorWeight(Player* player) {
    int previousFloorWeight = MAX_WEIGHT - (player->currentFloor - 1) * 100;
    player->currentWeight = previousFloorWeight;
    printf("이전 층의 무게로 돌아갑니다! 현재 무게: %dkg\n", player->currentWeight);
}

void skipFloor(Player* player) {
    player->currentFloor++;
    player->skipped = 1;  // 층 건너뛰기 카드 사용 표시
    printf("층을 무시하고 넘어갑니다! 현재 층: %d층\n", player->currentFloor);
}

void applyBalloonEffect(Player* player) {
    printf("풍선 효과로 임시로 100kg 감소했습니다!\n"); // 아직 풍선효과가 영구적으로 지속됨. 이후 수정
    player->currentWeight -= 100;                       //효과가 한층동안만 적용되면 스킵이랑 크게 다를게 없으니 풍선 지속시간을 3턴 정도로 하면 괜찮을듯?
}

// 카드 설명
const char* cardNames[] = { "무게 감소", "무게 증가", "이전 층 무게로 복귀", "층 건너뛰기", "풍선 효과" };

// 카드 선택
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

// 게임 규칙 설명 함수
void showRules() {
    printf("\n게임 규칙:\n");
    printf("1. 플레이어는 2000kg의 짐을 가진 채 시작합니다.\n");
    printf("2. 탑의 각 층마다 무게 제한이 있으며, 제한을 초과하면 게임이 종료됩니다.\n");
    printf("3. 카드 선택을 통해 무게를 조절하거나 층을 건너뛸 수 있습니다.\n");
    printf("4. 20층에 도달하면 게임에 승리합니다.\n\n");
    printf("아무 키나 눌러 메인 화면으로 돌아가세요...\n");
    _getch(); // 키 입력 대기
}

// 게임 메인 화면 함수
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


// 게임 진행
void playGame(Player* player) {
    CardFunction cardDeck[MAX_CARDS] = {
        decreaseWeight, increaseWeight, resetToPreviousFloorWeight,
        skipFloor, applyBalloonEffect
    };

    while (player->currentFloor <= MAX_FLOORS && player->currentWeight > 0) {
        // 층별 무게 계산 (1층은 2000kg로 시작, 2층부터 100kg씩 감소)
        int weightLimit = MAX_WEIGHT - ((player->currentFloor - 1) * 100);

        // 층 건너뛰기 카드 사용했는지 검사하기
        if (player->skipped == 0 && player->currentWeight > weightLimit) {
            printf("무게가 너무 무거워 %d층에 오를 수 없습니다. 게임 오버!\n", player->currentFloor);
            return;
        }

        player->skipped = 0; // 다음 루프에서는 다시 무게 제한 검사 적용

        // 카드 선택 과정
        printf("\n%d층에 도달했습니다. 최대 허용 무게: %dkg\n", player->currentFloor, weightLimit);
        printf("현재 무게: %dkg\n", player->currentWeight);

        CardFunction selectedCards[3];
        const char* selectedDescriptions[3];
        for (int i = 0; i < 3; i++) {
            int cardIndex = rand() % 5;
            selectedCards[i] = cardDeck[cardIndex];
            selectedDescriptions[i] = cardNames[cardIndex];
        }

        // 카드 설명 및 선택하기
        printf("사용 가능한 카드:\n");
        selectCard(player, selectedCards, selectedDescriptions);

        // 다음 층으로 이동
        player->currentFloor++;
    }

    printf("축하합니다! 탑의 정점에 도달했습니다!\n");
}

//int main() {
//    srand(time(NULL));
//
//    Player player = { MAX_WEIGHT, 1, 0 }; // skipped 초기화 추가
//    playGame(&player);
//
//    return 0;
//}

// 메인 함수
int main() {
    srand(time(NULL));

    int choice;
    Player player;

    while (1) {
        system("cls"); // 콘솔 화면 지우기 (Windows)
        showMainMenu();
        scanf_s("%d", &choice);

        if (choice == 1) {
            player.currentWeight = MAX_WEIGHT;
            player.currentFloor = 1;
            player.skipped = 0;
            playGame(&player);
            printf("아무 키나 눌러 메인 화면으로 돌아가세요...\n");
            _getch(); // 게임 종료 후 메인 화면으로 돌아가기 위해 대기
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
            _getch();
        }
    }

    return 0;
}
