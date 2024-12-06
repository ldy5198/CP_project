#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX_CARDS 20
#define MAX_WEIGHT 2000
#define MAX_FLOORS 20

// �÷��̾� ����ü ����
typedef struct {
    int currentWeight;
    int currentFloor;
    int skipped;
    int effectFloor;
    int previousWeight;
} Player;

// �Լ� ����
void playGame(Player* player); // playGame �Լ� ����

// ī�� ȿ�� �Լ���
void decreaseWeight(Player* player) {
    int decrease = (rand() % 151) + 200;
    player->currentWeight -= decrease;
    if (player->currentWeight < 0) {
        player->currentWeight = 0;
    }
    printf("���԰� %dkg �����߽��ϴ�! ���� ����: %dkg\n", decrease, player->currentWeight);
}

void increaseWeight(Player* player) {
    int increase = (rand() % 51) + 50;
    player->currentWeight += increase;
    printf("���԰� %dkg �����߽��ϴ�! ���� ����: %dkg\n", increase, player->currentWeight);
}

void resetToPreviousFloorWeight(Player* player) {
    if (player->currentFloor > 1) {
        player->currentWeight = player->previousWeight;
        printf("���� ���� ���Է� ���ư��ϴ�! ���� ����: %dkg\n", player->currentWeight);
    }
    else {
        printf("1�������� ���� ���� ���Է� ���ư� �� �����ϴ�!\n");
    }
}

void skipFloor(Player* player) {
    player->currentFloor++;
    player->skipped = 1;
    printf("���� �����ϰ� �Ѿ�ϴ�! ���� ��: %d��\n", player->currentFloor);
}

// ���� ����
void playGame(Player* player) {
    CardFunction cardDeck[MAX_CARDS] = {
        decreaseWeight, increaseWeight, resetToPreviousFloorWeight, skipFloor
    };

    while (player->currentFloor <= MAX_FLOORS && player->currentWeight > 0) {
        int weightLimit = MAX_WEIGHT - ((player->currentFloor - 1) * 100);

        if (player->skipped == 0 && player->currentWeight > weightLimit) {
            printf("���԰� �ʹ� ���ſ� %d���� ���� �� �����ϴ�. ���� ����!\n", player->currentFloor);
            return;
        }

        player->skipped = 0;

        printf("\n%d���� �����߽��ϴ�. �ִ� ��� ����: %dkg\n", player->currentFloor, weightLimit);
        printf("���� ����: %dkg\n", player->currentWeight);

        if (player->currentFloor > 1) {
            player->previousWeight = player->currentWeight;
        }

        CardFunction selectedCards[3];
        const char* cardNames[] = { "���� ����", "���� ����", "���� �� ���Է� ����", "�� �ǳʶٱ�" };
        const char* selectedDescriptions[3];

        for (int i = 0; i < 3; i++) {
            int cardIndex = rand() % 4;
            selectedCards[i] = cardDeck[cardIndex];
            selectedDescriptions[i] = cardNames[cardIndex];
        }

        printf("��� ������ ī��:\n");
        for (int i = 0; i < 3; i++) {
            printf("%d. %s\n", i + 1, selectedDescriptions[i]);
        }

        int choice;
        printf("ī�带 �����ϼ���: ");
        scanf_s("%d", &choice);
        if (choice >= 1 && choice <= 3) {
            selectedCards[choice - 1](player);
        }
        else {
            printf("�߸��� �����Դϴ�. ī�尡 ������� �ʾҽ��ϴ�.\n");
        }

        player->currentFloor++;
    }

    printf("�����մϴ�! ž�� ������ �����߽��ϴ�!\n");
}

int main() {
    srand((unsigned int)time(NULL));

    int choice;
    Player player;

    while (1) {
        system("cls");
        printf("\n\n\n");
        printf("=====================================\n");
        printf("         ž ������ ����\n");
        printf("=====================================\n");
        printf("    1. ���� ����\n");
        printf("    2. ���� ��Ģ ����\n");
        printf("    3. ����\n");
        printf("=====================================\n");
        printf("�����ϼ���: ");
        scanf_s("%d", &choice);

        if (choice == 1) {
            player.currentWeight = MAX_WEIGHT;
            player.currentFloor = 1;
            player.skipped = 0;
            player.previousWeight = MAX_WEIGHT;
            playGame(&player); // �ùٸ��� ȣ��
            printf("�ƹ� Ű�� ���� ���� ȭ������ ���ư�����...\n");
            _getch();
        }
        else if (choice == 2) {
            printf("\n���� ��Ģ:\n");
            printf("1. �÷��̾�� 2000kg�� ���� ���� ä �����մϴ�.\n");
            printf("2. ž�� �� ������ ���� ������ ������, ������ �ʰ��ϸ� ������ ����˴ϴ�.\n");
            printf("3. ī�� ������ ���� ���Ը� �����ϰų� ���� �ǳʶ� �� �ֽ��ϴ�.\n");
            printf("4. 20���� �����ϸ� ���ӿ� �¸��մϴ�.\n\n");
            printf("�ƹ� Ű�� ���� ���� ȭ������ ���ư�����...\n");
            _getch();
        }
        else if (choice == 3) {
            printf("������ �����մϴ�.\n");
            break;
        }
        else {
            printf("�߸��� �����Դϴ�. �ٽ� �Է��ϼ���.\n");
            _getch();
        }
    }

    return 0;
}
