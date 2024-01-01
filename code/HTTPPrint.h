/*********************************************************************
 * FileName: HTTPPrint.h
 * Provides callback headers and resolution for user's custom
 * HTTP Application.
 * Processor: PIC18,PIC24E, PIC24F, PIC24H, dsPIC30F, dsPIC33F, dsPIC33E,PIC32
 * Compiler:  Microchip C18, C30, C32
 * 
 * This file is automatically generated by the MPFS Utility
 * ALL MODIFICATIONS WILL BE OVERWRITTEN BY THE MPFS GENERATOR
 *
 * Software License Agreement
 *
 * Copyright (C) 2012 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and 
  * distribute: 
 * (i)  the Software when embedded on a Microchip microcontroller or 
 *      digital signal controller product ("Device") which is 
 *      integrated into Licensee's product; or 
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this 
 * Software for additional information regarding your rights and 
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE 
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER 
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *********************************************************************/

#ifndef __HTTPPRINT_H
#define __HTTPPRINT_H

#include "net/TCPIP.h"

#if defined(STACK_USE_HTTP2_SERVER)

extern HTTP_STUB httpStubs[MAX_HTTP_CONNECTIONS];
extern BYTE curHTTPID;

void HTTPPrint(DWORD callbackID);
void HTTPPrint_dhcpyes(void);
void HTTPPrint_dhcpno(void);
void HTTPPrint_ipdisp(void);
void HTTPPrint_ip(void);
void HTTPPrint_netmask(void);
void HTTPPrint_gw(void);
void HTTPPrint_dns1(void);
void HTTPPrint_dns2(void);
void HTTPPrint_ntp(void);
void HTTPPrint_reset(void);
void HTTPPrint_newip(void);
void HTTPPrint_passChangeStatus(void);
void HTTPPrint_configToken(void);
void HTTPPrint_uptime(void);
void HTTPPrint_time(void);
void HTTPPrint_timezone(void);
void HTTPPrint_cpufreq(void);
void HTTPPrint_configChangeStatus(void);
void HTTPPrint_restore(void);
void HTTPPrint_lstfls(void);
void HTTPPrint_mac(void);

void HTTPPrint(DWORD callbackID)
{
	switch(callbackID)
	{
        case 0x00000004:
			HTTPPrint_dhcpyes();
			break;
        case 0x00000005:
			HTTPPrint_dhcpno();
			break;
        case 0x00000006:
			HTTPPrint_ipdisp();
			break;
        case 0x00000007:
			HTTPPrint_ip();
			break;
        case 0x00000008:
			HTTPPrint_netmask();
			break;
        case 0x00000009:
			HTTPPrint_gw();
			break;
        case 0x0000000a:
			HTTPPrint_dns1();
			break;
        case 0x0000000b:
			HTTPPrint_dns2();
			break;
        case 0x0000000c:
			HTTPPrint_ntp();
			break;
        case 0x0000000d:
			HTTPPrint_reset();
			break;
        case 0x0000000e:
			HTTPPrint_newip();
			break;
        case 0x0000000f:
			HTTPPrint_passChangeStatus();
			break;
        case 0x00000010:
			HTTPPrint_configToken();
			break;
        case 0x00000012:
			HTTPPrint_uptime();
			break;
        case 0x00000013:
			HTTPPrint_time();
			break;
        case 0x00000014:
			HTTPPrint_timezone();
			break;
        case 0x00000015:
			HTTPPrint_cpufreq();
			break;
        case 0x00000016:
			HTTPPrint_configChangeStatus();
			break;
        case 0x00000017:
			HTTPPrint_restore();
			break;
        case 0x00000018:
			HTTPPrint_lstfls();
			break;
        case 0x00000019:
			HTTPPrint_mac();
			break;
		default:
			// Output notification for undefined values
			TCPPutROMArray(sktHTTP, (ROM BYTE*)"!DEF", 4);
	}

	return;
}

void HTTPPrint_(void)
{
	TCPPut(sktHTTP, '~');
	return;
}

#endif

#endif