/*
 * LTC6804.h
 *
 *  Created on: Dec 29, 2016
 *      Author: elenahuang
 */

#ifndef LTC6804_H_
#define LTC6804_H_

#define TOTAL_IC 1		// total number of ICs in the system

/*
Precalculated pec table
sourced from linear technology sample code for lindruino
*/
static const unsigned int crc15Table[256] = {0x0,0xc599, 0xceab, 0xb32, 0xd8cf, 0x1d56, 0x1664, 0xd3fd, 0xf407, 0x319e, 0x3aac,  //!<precomputed CRC15 Table
    0xff35, 0x2cc8, 0xe951, 0xe263, 0x27fa, 0xad97, 0x680e, 0x633c, 0xa6a5, 0x7558, 0xb0c1,
    0xbbf3, 0x7e6a, 0x5990, 0x9c09, 0x973b, 0x52a2, 0x815f, 0x44c6, 0x4ff4, 0x8a6d, 0x5b2e,
    0x9eb7, 0x9585, 0x501c, 0x83e1, 0x4678, 0x4d4a, 0x88d3, 0xaf29, 0x6ab0, 0x6182, 0xa41b,
    0x77e6, 0xb27f, 0xb94d, 0x7cd4, 0xf6b9, 0x3320, 0x3812, 0xfd8b, 0x2e76, 0xebef, 0xe0dd,
    0x2544, 0x2be, 0xc727, 0xcc15, 0x98c, 0xda71, 0x1fe8, 0x14da, 0xd143, 0xf3c5, 0x365c,
    0x3d6e, 0xf8f7,0x2b0a, 0xee93, 0xe5a1, 0x2038, 0x7c2, 0xc25b, 0xc969, 0xcf0, 0xdf0d,
    0x1a94, 0x11a6, 0xd43f, 0x5e52, 0x9bcb, 0x90f9, 0x5560, 0x869d, 0x4304, 0x4836, 0x8daf,
    0xaa55, 0x6fcc, 0x64fe, 0xa167, 0x729a, 0xb703, 0xbc31, 0x79a8, 0xa8eb, 0x6d72, 0x6640,
    0xa3d9, 0x7024, 0xb5bd, 0xbe8f, 0x7b16, 0x5cec, 0x9975, 0x9247, 0x57de, 0x8423, 0x41ba,
    0x4a88, 0x8f11, 0x57c, 0xc0e5, 0xcbd7, 0xe4e, 0xddb3, 0x182a, 0x1318, 0xd681, 0xf17b,
    0x34e2, 0x3fd0, 0xfa49, 0x29b4, 0xec2d, 0xe71f, 0x2286, 0xa213, 0x678a, 0x6cb8, 0xa921,
    0x7adc, 0xbf45, 0xb477, 0x71ee, 0x5614, 0x938d, 0x98bf, 0x5d26, 0x8edb, 0x4b42, 0x4070,
    0x85e9, 0xf84, 0xca1d, 0xc12f, 0x4b6, 0xd74b, 0x12d2, 0x19e0, 0xdc79, 0xfb83, 0x3e1a, 0x3528,
    0xf0b1, 0x234c, 0xe6d5, 0xede7, 0x287e, 0xf93d, 0x3ca4, 0x3796, 0xf20f, 0x21f2, 0xe46b, 0xef59,
    0x2ac0, 0xd3a, 0xc8a3, 0xc391, 0x608, 0xd5f5, 0x106c, 0x1b5e, 0xdec7, 0x54aa, 0x9133, 0x9a01,
    0x5f98, 0x8c65, 0x49fc, 0x42ce, 0x8757, 0xa0ad, 0x6534, 0x6e06, 0xab9f, 0x7862, 0xbdfb, 0xb6c9,
    0x7350, 0x51d6, 0x944f, 0x9f7d, 0x5ae4, 0x8919, 0x4c80, 0x47b2, 0x822b, 0xa5d1, 0x6048, 0x6b7a,
    0xaee3, 0x7d1e, 0xb887, 0xb3b5, 0x762c, 0xfc41, 0x39d8, 0x32ea, 0xf773, 0x248e, 0xe117, 0xea25,
    0x2fbc, 0x846, 0xcddf, 0xc6ed, 0x374, 0xd089, 0x1510, 0x1e22, 0xdbbb, 0xaf8, 0xcf61, 0xc453,
    0x1ca, 0xd237, 0x17ae, 0x1c9c, 0xd905, 0xfeff, 0x3b66, 0x3054, 0xf5cd, 0x2630, 0xe3a9, 0xe89b,
    0x2d02, 0xa76f, 0x62f6, 0x69c4, 0xac5d, 0x7fa0, 0xba39, 0xb10b, 0x7492, 0x5368, 0x96f1, 0x9dc3,
    0x585a, 0x8ba7, 0x4e3e, 0x450c, 0x8095
                                            };


/*
select the adc conversion mode
should always run the device at 7khz(normal mode)
*/

//static const uint8_t 	modeFast = 0x1;
static const uint8_t	modeNormal = 0x2;
//static uint8_t	modeFiltered = 0x3;



/*
define cell selection CH[2:0] used in commands
*/

static const uint8_t cellSelect_all = 0x00;
//static uint8_t cellSelect_os = 0x01;		//cell one and cell seven
//static uint8_t cellSelect_te = 0x02;		//cell two and cell eight
//static uint8_t cellSelect_tn = 0x03;		//cell three and cell nine
//static uint8_t cellSelect_ft = 0x04;		//cell four and cell ten
//static uint8_t cellSelect_fe = 0x05;		//cell five and cell eleven
//static uint8_t cellSelect_st = 0x06;		//cell six and cell twelve



/*

*/

//static uint8_t selfTestFirst = 0x0;
//static uint8_t selftTestSecond = 0x1;


/*
define discharge permit
since the device uses passive cell balancing, should always be nah
*/

static const uint8_t notdischarge = 0x0;
//static uint8_t discharge = 0x1;



/*
Pull-Up/Pull-Down Current for Open Wire Conversion
*/

//static uint8_t pulldown = 0x0;
//static uint8_t pullup = 0x1;



/*
Status Group Selection
May or may not implement


struct statusGroup{
	uint8_t all = 0x0;
	uint8_t soc = 0x1;	//sum of cells measurement
	uint8_t itmp = 0x2;	//internal die temperature
	uint8_t va = 0x3;	//analog power supply voltage
	uint8_t vd = 0x4;	//digital power suppy voltage
};

*/







//define functions
void LTC6804();

void LTC6804_inloop();

void LTC_initialize();

void LTC_wakeup_idle();

void LTC_wakeup_sleep();

uint16_t pec15_calc(uint8_t len, uint8_t *data);

//
void print_cells();

//
void init_cfg();

//prints float
void Serial2_print(float number);

//
void run_command(uint32_t cmd);



/*****convert commands into function for easy access*****/



//WRCFG
void LTC_writeConfig(uint8_t total_ic,uint8_t config[][6]);

//RDCFG
int LTC_readConfig(uint8_t total_ic, uint8_t r_config[][8]);

//RDCV_breifly read the voltages and stores it into the global variables declared in LTC6804.c
void LTC_readReg_brief(uint8_t reg,uint8_t total_ic,uint8_t *data);

//RDCV_complete
int LTC_readReg_complete(uint8_t reg,uint8_t total_ic,uint16_t cell_codes[][12]);

//RDCVB
//void LTC_readRegB();

//RDCVC
//void LTC_readRegC();

//RDCVD
//void LTC_readRegD();

//RDSTATA
//void LTC_readStaA();

//RDSTATB
//void LTC_readStaB();

//ADCV
void LTC_startADC();

//ADOW
//void LTC_openWireCheck();

//CVST
//void LTC_selfTest();

//ADSTAT
//void LTC_startStaADC();

//STATST
//void LTC_selfTestSta();

//CLRCELL
void LTC_clearCell();

//CLRSTAT
//void LTC_clearStatus();






#endif /* LTC6804_H_ */
