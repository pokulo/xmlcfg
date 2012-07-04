/*
 * joystick
 *
 * Copyright (C) 2011-2012
 *   Christian Friedrich, TU-Desden IWM
 */

/**
 * joystick configuration
 */

#include "def_joystick.h"
#include "util.h"

#define MAX_STRING_LENGTH

procim_node_identifier get_bool_joystick_node_id(userslot_bool_key userslot){
	return joystick_loockup[userslot_bool_lookup[userslot].joy_key].prcm_node_id;
}

procim_node_identifier get_axis_joystick_node_id(userslot_bool_key userslot){
	return joystick_loockup[userslot_axis_lookup[userslot].joy_key].prcm_node_id;
}

Err_No_t Joy_parse_config_file(joystick_settings *joy_settings UNUSED, const char *JoyIniFile UNUSED){
	scew_reader *reader = NULL;
	scew_parser *parser = NULL;
	scew_tree *tree = NULL;

	/* Creates an SCEW parser. This is the first function to call. */
	parser = scew_parser_create();

	scew_parser_ignore_whitespaces(parser, SCEW_TRUE);

	/* Loads an XML file. */
	reader = scew_reader_file_create(JoyIniFile);
	if (reader == NULL) {
		scew_error code = scew_error_code();
		scew_printf(_XT("Unable to load file (error #%d: %s)\n"), code,
				scew_error_string(code));
	}

	tree = scew_parser_load(parser, reader);
	if (tree == NULL) {
		scew_error code = scew_error_code();
		scew_printf(_XT("Unable to parse file (error #%d: %s)\n"), code,
				scew_error_string(code));
		if (code == scew_error_expat) {
			enum XML_Error expat_code = scew_error_expat_code(parser);
			scew_printf(_XT("Expat error #%d (line %d, column %d): %s\n"),
					expat_code, scew_error_expat_line(parser),
					scew_error_expat_column(parser),
					scew_error_expat_string(expat_code));
		}

		/* Frees the SCEW parser and reader. */
		scew_reader_free(reader);
		scew_parser_free(parser);

		return EXIT_FAILURE;
	}

	scew_element *elem;

	enum joystick_key get_joystick_key(const char joy_node_name[MAX_STRING_LENGTH]){
		for (int i = 0; i < JOY_CTRL_COUNT; ++i) {
			if (!strcmp(joystick_loockup[i].prcm_node_id.node_name,joy_node_name)){
				if (i==joystick_loockup[i].key)
					return joystick_loockup[i].key;
				else
					return 0;//wrong order or missing entry in enum<->lookup 
			}
		}
		return JOY_KEY_NOT_DEFINED;
	}

	for (int i = 0; i < USERSLOT_BOOL_COUNT; ++i) {
		elem = scew_element_by_name(scew_tree_root(tree),userslot_bool_loockup[i].str);
		if (elem)
			userslot_bool_loockup[i].joy_key = get_joystick_key(scew_attribute_value(scew_element_attribute_by_name(elem,"key")));
			if (userslot_bool_loockup[i].joy_key == 0)
				return EXIT_FAILURE;//wrong order or missing entry in enum<->lookup
		else
			return EXIT_FAILURE;//ERROR WRONG XML: Userslot userslot_bool_loockup[i].str not found
	}

	for (int i = 0; i < USERSLOT_AXIS_COUNT; ++i) {
		elem = scew_element_by_name(scew_tree_root(tree),userslot_axis_loockup[i].str);
		if (elem)
			userslot_axis_loockup[i].joy_key = get_joystick_key(scew_attribute_value(scew_element_attribute_by_name(elem,"key")));
			if (userslot_axis_loockup[i].joy_key == 0)
				return EXIT_FAILURE;//wrong order or missing entry in enum<->lookup
		else
			return EXIT_FAILURE;//ERROR WRONG XML: Userslot userslot_axis_loockup[i].str not found
	}


//	printf("KEY:%s \n", scew_element_name(MENU_DOWN));
//	printf("VAL:%s \n", scew_attribute_value(scew_element_attribute_by_name(MENU_DOWN,"key")));

	/* Free every SCEW variable */
	scew_reader_free(reader);
	scew_parser_free(parser);
	scew_tree_free(tree);
	
	return ERR_NOT_IMPLEMENTED;
}

Err_No_t joystick_init(joystick_settings *joy_settings, const char *joy_init_filename UNUSED)
{
	/* parse joystick config file */ //TODO!!
	
	joy_settings->init_status = JOY_UNDEFINED;
	
//	/* init joystick settings structure */	//TODO: besser machen!!!
//	joy_cfg_t temp_cfg1[JOY_CTRL_COUNT] = joy_cfg_as_before;
//	joy_settings->joy_configurations[JOY_CFG_OLD].en_joy_cfg = JOY_CFG_OLD;
//	memcpy(joy_settings->joy_configurations[JOY_CFG_OLD].joy_cfg, &temp_cfg1,sizeof(joy_settings->joy_configurations[JOY_CFG_OLD].joy_cfg));

//	joy_settings->joystick = joystick_table;
	
	
	joy_settings->init_status = JOY_INITIALIZED;
	
	return ERR_NO_ERROR;
}
Err_No_t joystick_connect_to_procim(joystick_settings *joy_settings, procim_node_table **joy_node_table, procim_region *process_image)
{
	ERR_DECLARE(ret);
	
	//check init status
	if ((joy_settings==NULL) || (joy_settings->init_status!=JOY_INITIALIZED))	return ERR_JOY_NOT_INITIALIZED;
	if (*joy_node_table != NULL)							return ERR_JOY_ALREADY_CONNECTED;
	//(joy_node_table exists and therefore a connection from cfg to procim is already established)
	
	//make node table when connecting from bof
	*joy_node_table = procim_make_node_table();
	
	/* get procim node keys */
//	int i; for (i=0;i<JOY_CTRL_COUNT;++i)
//		if ((ret = procim_node_table_insert(joy_node_table,&(joystick_table[i].prcm_node), 1, process_image)) != ERR_NO_ERROR) return ret;

	return ERR_NO_ERROR;
}
Err_No_t joystick_disconnect_from_procim(joystick_settings *joy_settings, procim_node_table **joy_node_table)
{
	//check init status
	if ((joy_settings==NULL) || (joy_settings->init_status!=JOY_INITIALIZED))	return ERR_JOY_NOT_INITIALIZED;
	if (*joy_node_table == NULL)							return ERR_JOY_NOT_CONNECTED;

	procim_free_node_table(*joy_node_table);
	*joy_node_table = NULL;
	
	return ERR_NO_ERROR;}
