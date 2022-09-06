#ifndef _INPUTS_H_
#define _INPUTS_H_

//door state
#define DOOR_OPENED         0
#define DOOR_CLOSED         1
#define DOOR_HALF_OPEN      2

extern bool spin_inc_f;
extern bool spin_dec_f;
extern u8 spin_dly_tmr;

//==========================================
void init_all_inputs(void);
void update_all_inputs(void);

void spin_signal_input(void);

#endif
