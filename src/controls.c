#include "controls.h"
#include "input.h"
#include "log/zf_log.h"

tCheat gKev_keys[44] = {
    { .code = 0xA11EE75D, .code2 = 0xF805EDDD, .action_proc = SetFlag, .num = 0x0A11EE75D },
    { .code = 0x564E78B9, .code2 = 0x99155115, .action_proc = SetFlag, .num = 0x564E78B9 },
    { .code = 0x1F47E5E8, .code2 = 0xA715222C, .action_proc = SetFlag2, .num = 1 },
    { .code = 0x39D4C4C4, .code2 = 0xF0A2C5B0, .action_proc = FinishLap, .num = 0 },
    { .code = 0x2654216C, .code2 = 0xF8256D15, .action_proc = GetPowerup, .num = 1 },
    { .code = 0x4294EC89, .code2 = 0xC38AD60E, .action_proc = GetPowerup, .num = 2 },
    { .code = 0x2CEB2850, .code2 = 0xA0C2D27E, .action_proc = GetPowerup, .num = 3 },
    { .code = 0x2D5F3125, .code2 = 0x9CE8A541, .action_proc = GetPowerup, .num = 4 },
    { .code = 0x2169C78B, .code2 = 0x7F3C9229, .action_proc = GetPowerup, .num = 5 },
    { .code = 0x2203C0CB, .code2 = 0x79729BE4, .action_proc = GetPowerup, .num = 6 },
    { .code = 0x34F4E3EC, .code2 = 0x868C534D, .action_proc = GetPowerup, .num = 7 },
    { .code = 0x34010316, .code2 = 0x591D1EB2, .action_proc = GetPowerup, .num = 8 },
    { .code = 0x214FE3BC, .code2 = 0x87285111, .action_proc = GetPowerup, .num = 9 },
    { .code = 0x2FABC390, .code2 = 0xC93D9F7, .action_proc = GetPowerup, .num = 10 },
    { .code = 0x2902E890, .code2 = 0x40969F67, .action_proc = GetPowerup, .num = 11 },
    { .code = 0x2F458288, .code2 = 0x58074E2, .action_proc = GetPowerup, .num = 12 },
    { .code = 0x249DA152, .code2 = 0x8F287346, .action_proc = GetPowerup, .num = 13 },
    { .code = 0x23AAE08B, .code2 = 0xA668103D, .action_proc = GetPowerup, .num = 14 },
    { .code = 0x32130661, .code2 = 0x56F03459, .action_proc = GetPowerup, .num = 15 },
    { .code = 0x2734E944, .code2 = 0xFE1E4639, .action_proc = GetPowerup, .num = 16 },
    { .code = 0x28341139, .code2 = 0x355F6D02, .action_proc = GetPowerup, .num = 17 },
    { .code = 0x20508831, .code2 = 0x123D1961, .action_proc = GetPowerup, .num = 18 },
    { .code = 0x346B8BCB, .code2 = 0x4ABA696C, .action_proc = GetPowerup, .num = 19 },
    { .code = 0x3FC93DF0, .code2 = 0x29FA9EFB, .action_proc = GetPowerup, .num = 20 },
    { .code = 0x2A80B09B, .code2 = 0x58516F5, .action_proc = GetPowerup, .num = 21 },
    { .code = 0x2F548FD1, .code2 = 0x696744DA, .action_proc = GetPowerup, .num = 22 },
    { .code = 0x3CB74F32, .code2 = 0xB915D88D, .action_proc = GetPowerup, .num = 23 },
    { .code = 0x297B53BA, .code2 = 0x218D4D2D, .action_proc = GetPowerup, .num = 24 },
    { .code = 0x351BC37D, .code2 = 0xB2A63343, .action_proc = GetPowerup, .num = 25 },
    { .code = 0x2B624386, .code2 = 0x9BA6260E, .action_proc = GetPowerup, .num = 26 },
    { .code = 0x2BA4AE23, .code2 = 0xC163A76C, .action_proc = GetPowerup, .num = 27 },
    { .code = 0x2FB92DCA, .code2 = 0x4AD7D54E, .action_proc = GetPowerup, .num = 32 },
    { .code = 0x3A42191B, .code2 = 0xEFF70F4C, .action_proc = GetPowerup, .num = 35 },
    { .code = 0x2ACA3190, .code2 = 0xD9004F25, .action_proc = GetPowerup, .num = 36 },
    { .code = 0x37C1F613, .code2 = 0xB7FAF351, .action_proc = GetPowerup, .num = 37 },
    { .code = 0x2BA3F603, .code2 = 0x29F2425C, .action_proc = GetPowerup, .num = 38 },
    { .code = 0x416EFF61, .code2 = 0x2667DF4B, .action_proc = GetPowerup, .num = 39 },
    { .code = 0x2554125C, .code2 = 0x393CA35D, .action_proc = GetPowerup, .num = 41 },
    { .code = 0x3FFF84D5, .code2 = 0x84A42DF4, .action_proc = GetPowerup, .num = 41 },
    { .code = 0x37E83018, .code2 = 0xB609AEE6, .action_proc = GetPowerup, .num = 42 },
    { .code = 0x2DB03B19, .code2 = 0x924A84B7, .action_proc = GetPowerup, .num = 43 },
    { .code = 0x30A19FAB, .code2 = 0x2B0C2782, .action_proc = GetPowerup, .num = 44 },
    { .code = 0x0, .code2 = 0x0, .action_proc = 0x0, .num = 0x0 }
};


void CheckKevKeys()
{
  int i = 0;
  tU32 *value;
  char s[128];

  value = KevKeyService();
  if (value[0] == 0) {
    return;
  }

  for (i = 0; gKev_keys[i].action_proc != 0; i++) {
    if (gKev_keys[i].code == value[0] && gKev_keys[i].code2 == value[1]) {
        break;
    }
  }

  if (gKev_keys[i].action_proc == 0) {
        return;
  }
  gKev_keys[i].action_proc(gKev_keys[i].num);
}

void SetFlag (int i) 
{
}

void SetFlag2 (int i) 
{
}

void GetPowerup (int pNum)
{
    ZF_LOGI("%d", pNum);
}

void FinishLap (int i)
{

}
