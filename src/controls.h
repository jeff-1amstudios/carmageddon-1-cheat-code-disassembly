#pragma once

#include "types.h"

typedef struct  {
    tU32 code;
    tU32 code2;
    void (*action_proc) (int param1);
    int num;
} tCheat;

void CheckKevKeys();
void SetFlag (int i);
void SetFlag2 (int i);
void GetPowerup (int pNum);
void FinishLap (int i);
