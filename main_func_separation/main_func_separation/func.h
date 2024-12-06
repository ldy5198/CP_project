#ifndef FUNC_H
#define FUNC_H

typedef struct {
    int currentWeight;
    int currentFloor;
    int skipped;
    int effectFloor;
    int weightChange;
    int previousEffectFloor;
} Player;

typedef void (*CardFunction)(Player*);

void decreaseWeight(Player* player);
void increaseWeight(Player* player);
void resetToPreviousFloorWeight(Player* player);
void skipFloor(Player* player);
void applyBalloonEffect(Player* player);
void randomWeight(Player* player);
void randomMultiple(Player* player);
void showRules();
void selectCard(Player* player, CardFunction cards[], const char* cardDescriptions[]);

#endif
