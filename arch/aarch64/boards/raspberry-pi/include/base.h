#ifndef _BASE_H_
#define _BASE_H_

/*
 * raspi-3b BCM2836.pdf
 * system overview
 * 0x0000_0000-0x3FFF_FFFF  GPU acess
 * 0x3E00_0000-0x3FFF_FFFF  GPU peripherals acess
 * 0x4000_0000-0xFFFF_FFFF  Local peripherals
 * 0x4000_0000-0x4001_FFFF  ARM timer, IRQs, mailboxes
 * 0x4002_0000-0x4002_FFFF  Debug ROM
 * 0x4003_0000-0x4003_FFFF  DAP
 * 0x4004_0000-0xFFFF_FFFF  Unuesd
 *
 */

#define PBASE 0x3F000000
#define ARM_LOCAL_PERIPHERALS 0x40000000

#endif /* _BASE_H_ */


