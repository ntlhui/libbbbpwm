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
	assert(system(NULL)
}
