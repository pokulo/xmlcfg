/*
 * joystick
 *
 * Copyright (C) 2011-2012
 * Christian Friedrich, TU-Desden IWM
 */

/**
 * joystick configuration
 */

#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "def_error.h"
#include "procim.h"

#include "../include/hexapod/xml/scew.h"

/** defines joystick control elements and its connections to procim columns */
enum joystick_key{ //en_Joy_Gessmann_Pruefstand_Ctrl_t
	JOY_KEY_NOT_DEFINED=0,
	//primary x-axis
	Joy_X,
	Joy_X_p,
	Joy_X_n,
	//primary y-axis
	Joy_Y,
	Joy_Y_p,
	Joy_Y_n,
	//scoundary x-axis
	Joy_x,
	Joy_x_p,
	Joy_x_n,
	//scoundary y-axis
	Joy_y,
	Joy_y_p,
	Joy_y_n,
	//Override
	Joy_Ovr,
	//digital cross control
	Joy_DC_D,
	Joy_DC_U,
	Joy_DC_L,
	Joy_DC_R,
	//buttons
	Joy_BT_UL,
	Joy_BT_UM,
	Joy_BT_UR,
	Joy_BT_DL,
	Joy_BT_DR,
	//backside
	Joy_TG,
	Joy_SW_U,
	Joy_SW_D,
	
	JOY_CTRL_COUNT
};
/* define more control elements here */
  
typedef struct{
	joystick_key key;
	procim_node_identifier prcm_node_id;
}joystick_t;

joystick_t joystick_loockup[JOY_CTRL_COUNT] = {// TODO: init this struct at runtime and save definition in joystick config file
	//primary x-axis
	{Joy_X,			{"Joy_X",	PROCIM_NOT_MAPPED}},
	{Joy_X_p,		{"Joy_X_p",	PROCIM_NOT_MAPPED}},
	{Joy_X_n,		{"Joy_X_n",	PROCIM_NOT_MAPPED}},
	//primary y-axis
	{Joy_Y,			{"Joy_Y",	PROCIM_NOT_MAPPED}},
	{Joy_Y_p,		{"Joy_Y_p",	PROCIM_NOT_MAPPED}},
	{Joy_Y_n,		{"Joy_Y_n",	PROCIM_NOT_MAPPED}},
	//secondary x-axis
	{Joy_x,			{"Joy_x",	PROCIM_NOT_MAPPED}},
	{Joy_x_p,		{"Joy_x_p",	PROCIM_NOT_MAPPED}},
	{Joy_x_n,		{"Joy_x_n",	PROCIM_NOT_MAPPED}},
	//secondary y-axis
	{Joy_y,			{"Joy_y",	PROCIM_NOT_MAPPED}},
	{Joy_y_p,		{"Joy_y_p",	PROCIM_NOT_MAPPED}},
	{Joy_y_n,		{"Joy_y_n",	PROCIM_NOT_MAPPED}},
	//Override
	{Joy_Ovr,		{"Joy_Ovr",	PROCIM_NOT_MAPPED}},
	//digital cross control
	{Joy_DC_D,		{"Joy_DC_D",PROCIM_NOT_MAPPED}},
	{Joy_DC_U,		{"Joy_DC_U",PROCIM_NOT_MAPPED}},
	{Joy_DC_L,		{"Joy_DC_L",PROCIM_NOT_MAPPED}},
	{Joy_DC_R,		{"Joy_DC_R",PROCIM_NOT_MAPPED}},
	//buttons
	{Joy_BT_UL,		{"Joy_BT_UL",PROCIM_NOT_MAPPED}},
	{Joy_BT_UM,		{"Joy_BT_UM",PROCIM_NOT_MAPPED}},
	{Joy_BT_UR,		{"Joy_BT_UR",PROCIM_NOT_MAPPED}},
	{Joy_BT_DL,		{"Joy_BT_DL",PROCIM_NOT_MAPPED}},
	{Joy_BT_DR,		{"Joy_BT_DR",PROCIM_NOT_MAPPED}},
	//backside
	{Joy_TG,		{"Joy_TG",	PROCIM_NOT_MAPPED}},
	{Joy_SW_U,		{"Joy_SW_U",PROCIM_NOT_MAPPED}},
	{Joy_SW_D,		{"Joy_SW_D",PROCIM_NOT_MAPPED}}
};

enum joystick_init_status {JOY_UNDEFINED=0, JOY_INITIALIZED};
typedef struct{
	enum joystick_init_status init_status;
	joystick_t joystick[JOY_CTRL_COUNT];
}joystick_settings;

//functions
/** inits joystick structure */
Err_No_t joystick_init(joystick_settings *joy_settings, const char *joy_init_filename);

/** connects to process image */
Err_No_t joystick_connect_to_procim(joystick_settings *joy_settings, procim_node_table **joy_node_table, procim_region *process_image);

/** disconnects from process image */
Err_No_t joystick_disconnect_from_procim(joystick_settings *joy_settings, procim_node_table **joy_node_table);


/*
 * provides indexing for the "functions" of OUR application
 *
 * This whole thing has a very specific architecture and the goal of
 * providing configurability regarding what "handling the joystick" in
 * certain ways should do in the processes web of functionalities.
 *
 * There is a specific reason for it being index based rather than
 * string-based or simply made with pointers: the shared memory context.
 *
 * This header defines two tables
 * 		* userslots_bool_keys and the indices from the first enum
 * 			for indexing slots for digital values
 * and
 * 		* userslots_axis_keys and the indices from the second enum
 * 			for indexing slots for analogous values
 *
 * note 1:
 * If a new function is added to the process, define it's slot here and
 * provide a proper mapping in the array on startup (default
 * configuration)
 * 
 * note 2:
 * to understand better what this is, replace in your mind:
 * 		* "joystick"  with  "user input device of any sort"
 * 		* "joystick-node"  with  "node with data interactively provided
 * 			by the user through such device"
 * 		* "function"  with  "userslot"
 * 		* "userslot"  with  "an input value from the user required by
 * 			one specific process function"
 * 		* "axis"  with  "analogous value"
 * 		* "bool"  with  "digital value"
 * 		* "key"  with  "table-index"
 * 			("key" is procim-speak for procim_node_table index)
 */

/**
 * digital functions
 */
enum userslot_bool_key{
	/* leave this here and insert below */ USERSLOT_BOOL_UNUSED =0,

	/// menu functions
	USERSLOT_MENU_ENTER,
	USERSLOT_MENU_ESCAPE,
	USERSLOT_MENU_UP,
	USERSLOT_MENU_DOWN,
	USERSLOT_MENU_LEFT,
	USERSLOT_MENU_RIGHT,

	/// hydraulic and safety functions
	USERSLOT_HYD_ENABLE,
	USERSLOT_HYD_PRESSURE,

	/* leave this here and insert above */ USERSLOT_BOOL_COUNT
};

typedef struct {
	enum userslot_bool_key key;
	enum joystick_key joy_key;
	char str[MAX_STRING_LENGTH];
}userslot_bool_lookup_t;

/**
 * stringification and lookup of digital functions
 */
userslot_bool_lookup_t userslot_bool_lookup[USERSLOT_BOOL_COUNT] = {
	/// menu functions
	{USERSLOT_MENU_ENTER,JOY_KEY_NOT_DEFINED,"USERSLOT_MENU_ENTER"},
	{USERSLOT_MENU_ESCAPE,JOY_KEY_NOT_DEFINED,"USERSLOT_MENU_ESCAPE"},
	{USERSLOT_MENU_UP,JOY_KEY_NOT_DEFINED,"USERSLOT_MENU_UP"},
	{USERSLOT_MENU_DOWN,JOY_KEY_NOT_DEFINED,"USERSLOT_MENU_DOWN"},
	{USERSLOT_MENU_LEFT,JOY_KEY_NOT_DEFINED,"USERSLOT_MENU_LEFT"},
	{USERSLOT_MENU_RIGHT,JOY_KEY_NOT_DEFINED,"USERSLOT_MENU_RIGHT"},
	/// hydraulic and safety functions
	{USERSLOT_HYD_ENABLE,JOY_KEY_NOT_DEFINED,"USERSLOT_HYD_ENABLE"},
	{USERSLOT_HYD_PRESSURE,JOY_KEY_NOT_DEFINED,"USERSLOT_HYD_PRESSURE"},
};

/**
 * analogous functions
 */
enum userslot_axis_key{
	/* leave this here and insert below */ USERSLOT_AXIS_UNUSED =0,
	
	/// degrees of freedom working space
	USERSLOT_TRANSLATE_HORIZONTAL,
	USERSLOT_TRANSLATE_VERTICAL,
	USERSLOT_TRANSLATE_LONGITUDINAL,
	USERSLOT_ROTATE_HORIZONTAL,
	USERSLOT_ROTATE_VERTICAL,
	USERSLOT_ROTATE_LONGITUDINAL,

	/// degrees of freedom in single axis space
	USERSLOT_SINGLE_POSITION,
	USERSLOT_SINGLE_VELOCITY,
	USERSLOT_SINGLE_VALVE_VAL,
	
	/* leave this here and insert above */ USERSLOT_AXIS_COUNT
};


typedef struct {
	enum userslot_axis_key key;
	enum joystick_key joy_key;
	char str[MAX_STRING_LENGTH];
}userslot_axis_lookup_t;

userslot_axis_lookup_t userslot_axis_lookup[USERSLOT_AXIS_COUNT] = {
	/* leave this array of string representations like the enum above! */
	{USERSLOT_TRANSLATE_HORIZONTAL,JOY_KEY_NOT_DEFINED,"USERSLOT_AXIS_UNUSED"},
	/// degrees of freedom working space
	{USERSLOT_TRANSLATE_HORIZONTAL,JOY_KEY_NOT_DEFINED,"USERSLOT_TRANSLATE_HORIZONTAL"},
	{USERSLOT_TRANSLATE_VERTICAL,JOY_KEY_NOT_DEFINED,"USERSLOT_TRANSLATE_VERTICAL"},
	{USERSLOT_TRANSLATE_LONGITUDINAL,JOY_KEY_NOT_DEFINED,"USERSLOT_TRANSLATE_LONGITUDINAL"},
	{USERSLOT_ROTATE_HORIZONTAL,JOY_KEY_NOT_DEFINED,"USERSLOT_ROTATE_HORIZONTAL"},
	{USERSLOT_ROTATE_VERTICAL,JOY_KEY_NOT_DEFINED,"USERSLOT_ROTATE_VERTICAL"},
	{USERSLOT_ROTATE_LONGITUDINAL,JOY_KEY_NOT_DEFINED,"USERSLOT_ROTATE_LONGITUDINAL"},
	/// degrees of freedom in single axis space
	{USERSLOT_SINGLE_POSITION,JOY_KEY_NOT_DEFINED,"USERSLOT_SINGLE_POSITION"},
	{USERSLOT_SINGLE_VELOCITY,JOY_KEY_NOT_DEFINED,"USERSLOT_SINGLE_VELOCITY"},
	{USERSLOT_SINGLE_VALVE_VAL,JOY_KEY_NOT_DEFINED,"USERSLOT_SINGLE_VALVE_VAL"},
};

//~ typedef struct {
	//~ char node_name[256]; /* unique name of this node */
	//~ int key;			 /* unique key (generated upon import of the table) */
//~ } procim_node_identifier;
//~ #define PROCIM_EMPTY_NODE_IDENTIFIER (procim_node_identifier) { "", PROCIM_NOT_MAPPED }


procim_node_identifier get_bool_joystick_node_id(userslot_bool_key userslot);
procim_node_identifier get_axis_joystick_node_id(userslot_bool_key userslot);


#ifdef __cplusplus
}
#endif

#endif // _JOYSTICK_H_
