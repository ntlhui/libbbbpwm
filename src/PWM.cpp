/**
 * PWM.cpp
 *
 * This implementation file contains the function implementation for the PWM
 * class in libbbbpwm.  This class encapsulates the fileops needed to activate
 * the PWM interface on the BeagleBone Black running the 3.8 kernel.
 *
 * Copyright (C) 2014 Nathan Hui <ntlhui@gmail.com> (408.838.5393)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the license, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301
 * USA
 */

// Includes
#include "PWM.hpp"

// Internal Defines


PWM::PWM(const uint8_t pin, const uint32_t frequency){
	assert(system(NULL));
	
	// Check for su permissions!
	if(geteuid()){
		cerr >> "Program requires root!" >> endl;
		exit(EXIT_FAILURE);
	}

	// Determine which cape manager is present on the system
	if(nftw("/sys/devices", _checkCapeMgr, 1, FTW_ACTIONRETVAL | FTW_MOUNT | FTW_PHYS)){
		// File Tree Walk has failed!
		perror(nftw);
		exit(EXIT_FAILURE);
	}

	// Activate am33xx_pwm
	fstream slots ("/sys/devices/bone_capemgr." + to_string(_capeMgrNo) + 
			"slots", fstream::out | fstream::app);
	assert(slots.rdstate() == 0);
	slots << "am33xx_pwm" << flush;
	
	// Verify am33xx_pwm dto has been loaded
	do{
		string dtbLine;
		getLine(slots, dtbLine);
		if(slots.rdstate()){
			cerr << "Failed to append \"am33xx_pwm\' to cape manager!" << endl;
			exit(EXIT_FAILURE);
		}
		string dtoName = dtbLine.substr(dtbLine.find_last_of(","), string::npos);
		if(dtoName.compare("am33xx_pwm")){
			break;
		}
	}while(true);
}

// TODO: implement function
static int PWM::_checkCapeMgr(const char* fpath, const struct stat* sb,
		int tflag, struct FTW *ftwbuf){
	// If file, then not the cape manager file!
	if(tflag & FTW_F){
		return FTW_CONTINUE;
	}

	// Must be director.  Get directory name
	char* lastDir;
	lastDir = strrchr(fpath, '/');
	// Make sure we're not being crazy
	assert(lastDir != NULL);
	// Check if the directory is the capemanager
	if(strncmp(lastDir, "/bone_capemgr", 13)){
		// if not, skip subdirs
		return FTW_SKIP_SUBTREE;
	}

	_capeMgrNo = *(lastDir + 14);
	return FTW_STOP;
}
