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

int joystick_load_config(const char filename[]);

int main(int argc, char *argv[]) {
	return joystick_load_config(argv[1]);
}

#endif /* XMLCFG_H_ */
