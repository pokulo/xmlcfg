/*
 * xmlcfg.h
 *
 *  Created on: 06.06.2012
 *      Author: poku
 */

#ifndef XMLCFG_H_
#define XMLCFG_H_

#include <scew/scew.h>
#include <stdio.h>
#define MAX_STRING_LENGTH
//-------------------------------------joystick--------------------------------------------------
enum joystick_key{
	JOY_KEY_NOT_DEFINED,
	Joy_X,
	Joy_Y,
	Joy_x,
	Joy_y,
	Joy_DC_U,
	Joy_DC_D,
	Joy_DC_L,
	Joy_DC_R,
	JOY_COUNT
};
typedef struct {
	enum joystick_key key;
	char str[63];
}joystick_key_t;

joystick_key_t joy_loockup[JOY_COUNT] = {
		{Joy_X,"Joy_X"},
		{Joy_Y,"Joy_Y"},
		{Joy_x,"Joy_x"},
		{Joy_y,"Joy_y"},
		{Joy_DC_U,"Joy_DC_U"},
		{Joy_DC_D,"Joy_DC_D"},
		{Joy_DC_L,"Joy_DC_L"},
		{Joy_DC_R,"Joy_DC_R"}
};
//-------------------------------------userslots--------------------------------------------------
enum userslot_bool_key{
	MENU_UP,
USERSLOT_MENU_RIGHT	MENU_DOWN,
	MENU_LEFT,
	MENU_RIGHT,
	USERSLOT_BOOL_COUNT
};
typedef struct {
	enum userslot_bool_key key;
	enum joystick_key joy_key;
	char str[MAX_STRING_LENGTH];
}userslot_bool_key_t;

userslot_bool_key_t userslot_bool_lookup[USERSLOT_BOOL_COUNT] = {
		{MENU_UP,JOY_KEY_NOT_DEFINED,"MENU_UP"},
		{MENU_DOWN,JOY_KEY_NOT_DEFINED,"MENU_DOWN"},
		{MENU_LEFT,JOY_KEY_NOT_DEFINED,"MENU_LEFT"},
		{MENU_RIGHT,JOY_KEY_NOT_DEFINED,"MENU_RIGHT"}
};

//-------------------------------------funkctions--------------------------------------------------
int joystick_load_config(const char filename[]);

int main(int argc, char *argv[]) {
	return joystick_load_config(argv[1]);
}

#endif /* XMLCFG_H_ */
