#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CARDS 20 // ī�� ����
#define MAX_WEIGHT 2000 // �ʱ� ����
#define MAX_FLOORS 20 // ž ����� 20������ ����

// �÷��̾� ����ü
typedef struct {
    int currentWeight;
    int currentFloor;
    int skipped; // �� �ǳʶٱ� ī�� ��� ���� �÷���
} Player;

// ī�� �Լ� ������ �迭
typedef void (*CardFunction)(Player*);

// 20���� ī�� ����� �� ũ�� 5�� ������ !!�ӽ�������!! ȿ���� ������
void decreaseWeight(Player* player) {
    int decrease = (rand() % 151) + 50;
    player->currentWeight -= decrease;
    printf("���԰� %dkg �����߽��ϴ�! ���� ����: %dkg\n", decrease, player->currentWeight); // �ϴ� ���� ������ ���� ���� ����?�� ���� ����. 
}

void increaseWeight(Player* player) {
    int increase = (rand() % 51) + 50;
    player->currentWeight += increase;
    printf("���԰� %dkg �����߽��ϴ�! ���� ����: %dkg\n", increase, player->currentWeight);
}

void resetToPreviousFloorWeight(Player* player) {
    int previousFloorWeight = MAX_WEIGHT - (player->currentFloor - 1) * 100;
    player->currentWeight = previousFloorWeight;
    printf("���� ���� ���Է� ���ư��ϴ�! ���� ����: %dkg\n", player->currentWeight);
}

void skipFloor(Player* player) {
    player->currentFloor++;
    player->skipped = 1;  // �� �ǳʶٱ� ī�� ��� ǥ��
    printf("���� �����ϰ� �Ѿ�ϴ�! ���� ��: %d��\n", player->currentFloor);
}

void applyBalloonEffect(Player* player) {
    printf("ǳ�� ȿ���� �ӽ÷� 100kg �����߽��ϴ�!\n"); // ���� ǳ��ȿ���� ���������� ���ӵ�. ���� ����
    player->currentWeight -= 100;                       //ȿ���� �������ȸ� ����Ǹ� ��ŵ�̶� ũ�� �ٸ��� ������ ǳ�� ���ӽð��� 3�� ������ �ϸ� ��������?
}

// ī�� ����
const char* cardNames[] = { "���� ����", "���� ����", "���� �� ���Է� ����", "�� �ǳʶٱ�", "ǳ�� ȿ��" };

// ī�� ����
void selectCard(Player* player, CardFunction cards[], const char* cardDescriptions[]) {
    int cardChoice;
    printf("ī�带 �����ϼ���: 1, 2 �Ǵ� 3\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i + 1, cardDescriptions[i]);
    }
    scanf_s("%d", &cardChoice);

    if (cardChoice >= 1 && cardChoice <= 3) {
        cards[cardChoice - 1](player); // ������ ī�� ����
    }
    else {
        printf("�߸��� �����Դϴ�. ī�尡 ������� �ʾҽ��ϴ�.\n");
    }
}

// ���� ����
void playGame(Player* player) {
    CardFunction cardDeck[MAX_CARDS] = {
        decreaseWeight, increaseWeight, resetToPreviousFloorWeight,
        skipFloor, applyBalloonEffect
    };

    while (player->currentFloor <= MAX_FLOORS && player->currentWeight > 0) {
        // ���� ���� ��� (1���� 2000kg�� ����, 2������ 100kg�� ����)
        int weightLimit = MAX_WEIGHT - ((player->currentFloor - 1) * 100);

        // �� �ǳʶٱ� ī�� ����ߴ��� �˻��ϱ�
        if (player->skipped == 0 && player->currentWeight > weightLimit) {
            printf("���԰� �ʹ� ���ſ� %d���� ���� �� �����ϴ�. ���� ����!\n", player->currentFloor);
            return;
        }

        player->skipped = 0; // ���� ���������� �ٽ� ���� ���� �˻� ����

        // ī�� ���� ����
        printf("\n%d���� �����߽��ϴ�. �ִ� ��� ����: %dkg\n", player->currentFloor, weightLimit);
        printf("���� ����: %dkg\n", player->currentWeight);

        CardFunction selectedCards[3];
        const char* selectedDescriptions[3];
        for (int i = 0; i < 3; i++) {
            int cardIndex = rand() % 5;
            selectedCards[i] = cardDeck[cardIndex];
            selectedDescriptions[i] = cardNames[cardIndex];
        }

        // ī�� ���� �� �����ϱ�
        printf("��� ������ ī��:\n");
        selectCard(player, selectedCards, selectedDescriptions);

        // ���� ������ �̵�
        player->currentFloor++;
    }

    printf("�����մϴ�! ž�� ������ �����߽��ϴ�!\n");
}

int main() {
    srand(time(NULL));

    Player player = { MAX_WEIGHT, 1, 0 }; // skipped �ʱ�ȭ �߰�
    playGame(&player);

    return 0;
}
