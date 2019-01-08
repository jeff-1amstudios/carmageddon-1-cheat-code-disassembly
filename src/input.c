#include "input.h"
#include "log/zf_log.h"
#include "pc/sys.h"

int gKey_poll_counter;
tU32 gLast_poll_keys;
int gCurrent_cursor;
int gCurrent_position;
int gInsert_mode;
int gLetter_x_coords[15];
int gEdge_trigger_mode;
int gVisible_length;
int gLetter_y_coords[15];
int gThe_key;
tU32 gLast_key_down_time;
int gThe_length;
tU32 gLast_roll;
int gLast_key_down;
int gGo_ahead_keys[3];
int gKey_mapping[67];
char gCurrent_typing[110];

//if neither match, exit
// if we don't match & 0xff, 

tU32 *KevKeyService()
{
  static tU32 sum = 0;
  static tU32 code = 0;
  static tU32 code2 = 0;
  static int last_key = -1;
  static int last_single_key = -1;
  static tU32 last_time = 0;
  static tU32 return_val[2];
  tU32 keys;
  
  keys = gLast_key_down;
  //printf("key: %d, %lx, %lx\n", sizeof(long), keys, code2);
  return_val[0] = 0;
  return_val[1] = 0;
  
  if (keys < 0x6B) {
    last_single_key = gLast_key_down;
  }
  else {
    if (keys > 0x6b00) {
      sum = 0;
      code = 0;
      return return_val;
    }
    if ((keys & 0xff) != last_single_key && keys >> 8 != last_single_key) {
      sum = 0;
      code = 0;
      return return_val;
    }
    if (keys >> 8 != last_single_key) {
      sum = 0;
      code = 0;
      return return_val;
    }
    if ((keys & 0xff) == last_single_key) {
      keys = keys >> 8;
    }
    
    keys = keys & 0xff;
  }

  if (keys && keys != last_key) {
    sum += keys;
    code += keys << 11;
    code = (code >> 17) + 16 * code;
    code2 = (code2 >> 29) + keys * keys + 8 * code2;
    ZF_LOGD("accumulate: keys=%lx, sum=%lx, code=%lx, code2=%lx", keys, sum, code, code2);
    last_time = PDGetTotalTime();
    
  }
  else if (PDGetTotalTime() > (last_time + 1000)) {
    ZF_LOGD("final value: last_time=%lu, pdtime=%lu, keys=%lx, sum=%lx, code=%lx, code2=%lx", last_time, PDGetTotalTime(), keys, sum, code, code2);
    return_val[0] = (code >> 11) + (sum << 21);
    return_val[1] = code2;
    code = 0;
    code2 = 0;
    sum = 0;
  }
  last_key = keys;
  return return_val;
}

//working