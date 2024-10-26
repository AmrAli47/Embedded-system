/* 
 * File:   main.cpp
 * Author: Amr Ali
 */

#include "main.h"
#include "Bootloader.h"



void CppMain() {
	BL B;

	while(1)
	{
		B.BL_Fetch_Host_Command();
	}
}
