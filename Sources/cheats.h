#ifndef CHEATS_H
#define CHEATS_H

#include "plugin.h"

#ifndef ADDSUBFLOAT
    #define ADDTOFLOAT(addr, add_value)            *(float *)(addr) += (float)(add_value)
    #define SUBTOFLOAT(addr, sub_value)            *(float *)(addr) -= (float)(sub_value)
#endif

#ifndef READWRITEFLOAT
    #define READFLOAT(addr)                     *(float *)(addr)
    #define WRITEFLOAT(addr, data)                 *(float *)(addr) = data
#endif

#ifndef ADDSUBTOUNSIGNED
    #define ADDTOUNSIGNED(addr, value)            *(u32 *)(addr) += value
    #define SUBTOUNSIGNED(addr, value)            *(u32 *)(addr) -= value
#endif

unsigned int	GetRev(void);
unsigned int	GetFNsPointer(void);
unsigned int	GetRacePointer(void);
unsigned int	GetRaceCondition(void);
unsigned int    GetOldPointer5CC(void);
unsigned int    GetOldPointer5D0(void);
unsigned int	GetItemPointer(void);
void	writeItem(u32 item);
void	writeSpeed(u32 speed);
void	writeVR(u32 vr);
void	writeLocation(u32 location);
void	writeFlag(u8 flag);
void	invincible(void);
void	alwaysStarPower(void);
void	alwaysBlackKart(void);
void	alwaysShocked(void);
void	alwaysCrushed(void);
void	instantMT(void);
void	hugeBunnyhop(void);
void	fastReverse(void);
void	noCountdown(void);
void	moonjump(void);
void	saveSlotTeleporter(void);
void	maxTimer(void);
void	waterEverywhere(void);
void	driveAnywhere(void);
void	fastBlueShell(void);
void	stoppedBlueShell(void);
void	fastGreenShell(void);
void	stoppedGreenShell(void);
void	dropMushrooms(void);
void	bulletControl(void);
void	disableStarMusic(void);
void	bulletSpeed(void);
void	blueShellRide(void);
void	itemWheel(void);
void	TwoHundredCC(void);
void	FiveHundredCC(void);
void	disableFirstPerson(void);
void	vrExtender(void);
void	randomVR(void);
void	unlockEverything(void);
void	NoDC(void);
void	region_France(void);
void	region_Hawaii(void);
void	region_UpperAntartica(void);
void	region_NorthPole(void);
void	region_Iran(void);
void	region_SaudiArabia(void);
void	region_Cuba(void);
void	region_Russia(void);
void	region_Phillippines(void);
void	flag_Japan(void);
void	flag_Haiti(void);
void	flag_Italy(void);
void	flag_SaudiArabia(void);
void	flag_SouthAfrica(void);
void	flag_Russia(void);
void	flag_USA(void);

#endif
