#include "cheats.h"
#include <stdbool.h>
#include "hid.h"
#include "values.h"
#include <string.h>

u32 offset = 0;
u32 random = 0;
u32 dataX = 0;
u32 dataY = 0;
u32 dataZ = 0;
static u32 x = 0;
static u32 y = 0;
static u32 z = 0;
unsigned int data = 0;
unsigned int g_rev;
unsigned int g_racePointer;
unsigned int g_raceCondition;
unsigned int g_FNsPointer;
unsigned int g_oldRacePointer5CC;
unsigned int g_oldRacePointer5D0;
unsigned int g_itemPointer;

/////////////////////////////////////////////////////////    Start of custom functions    /////////////////////////////////////////////////////////

unsigned int	GetRacePointer(void)
{
	unsigned int g_racePointer, g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0x140002F4) > 0x14000000 && READU32(0x140002F4) < 0x18000000 && READU32(READU32(0x140002F4) + 0x14) > 0x14000000 && READU32(READU32(0x140002F4) + 0x14) < 0x18000000 && READU32(READU32(READU32(0x140002F4) + 0x14) + 0x518) > 0x14000000 && READU32(READU32(READU32(0x140002F4) + 0x14) + 0x518) < 0x18000000)
	{
		g_racePointer = READU32(READU32(READU32(READU32(0x140002F4) + 0x14) + 0x518) + 0x1C);
		return (g_racePointer);
	}
	else
	{
		g_racePointer = 0;
		return (g_racePointer);
	}
}

unsigned int	GetRaceCondition(void)
{
	unsigned int g_raceCondition;
	if (READU32(0x14000084) > 0x13000000 && READU32(0x14000084) < 0x18000000)
	{
		g_raceCondition = READU8(READU32(READU32(0x14000084) + 0x316C) + 0x118);
		return (g_raceCondition);
	}
	else
	{
		g_raceCondition = 2;
		return (g_raceCondition);
	}
}

unsigned int	GetFNsPointer(void)
{
	unsigned int g_FNsPointer, g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0xFFFF6F0) > 0x14000000 && READU32(0xFFFF6F0) < 0x18000000)
	{
		g_FNsPointer = READU32(0xFFFF6F0) + 8;
		return (g_FNsPointer);
    }
	else
	{
		g_FNsPointer = 0;
		return (g_FNsPointer);
	}
}

unsigned int	GetOldPointer5CC(void)
{
	unsigned int g_oldRacePointer5CC, g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0xFFFFBF4) > 0x14000000 && READU32(0xFFFFBF4) < 0x18000000 && READU32(READU32(0xFFFFBF4) + 0x5CC) > 0x14000000 && READU32(READU32(0xFFFFBF4) + 0x5CC) < 0x18000000)
	{
		g_oldRacePointer5CC = READU32(READU32(0xFFFFBF4) + 0x5CC);
		return (g_oldRacePointer5CC);
	}
	else
	{
		g_oldRacePointer5CC = 0;
		return (g_oldRacePointer5CC);
	}
}

unsigned int	GetOldPointer5D0(void)
{
	unsigned int g_oldRacePointer5D0, g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0xFFFFBF4) > 0x14000000 && READU32(0xFFFFBF4) < 0x18000000 && READU32(READU32(0xFFFFBF4) + 0x5D0) > 0x14000000 && READU32(READU32(0xFFFFBF4) + 0x5D0) < 0x18000000)
	{
		g_oldRacePointer5D0 = READU32(READU32(0xFFFFBF4) + 0x5D0);
		return (g_oldRacePointer5D0);
	}
	else
	{
		g_oldRacePointer5D0 = 0;
		return (g_oldRacePointer5D0);
	}
}

unsigned int	GetItemPointer(void)
{
	unsigned int g_itemPointer, g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1)
	{
		if (READU32(0x17782494) > 0x14000000 || READU32(0x177BE494) > 0x14000000)
		{
			if (READU32(0x17782494) < 0x18000000 || READU32(0x177BE494) < 0x18000000)
			{
				g_itemPointer = READU32(READU32(READU32(0x14000074) - 0x1B5C) + 0x27AC);
				return (g_itemPointer);
			}
		}
	}
	else
	{
		g_itemPointer = 0;
		return (g_itemPointer);
	}
}

void	writeItem(u32 item)
{
	unsigned int g_raceCondition = GetRaceCondition(), g_itemPointer = GetItemPointer();
	if (g_raceCondition == 1 && g_itemPointer > 0x14000000 && g_itemPointer < 0x18000000)
	{
		WRITEU32(0x3C + g_itemPointer, 0xFFFFFFFF);
		WRITEU8(0xA8 + g_itemPointer, 3);
		WRITEU8(0xC8 + g_itemPointer, item);
		WRITEU32(0xD8 + g_itemPointer, 0x3F800000);
	}
}

void	writeSpeed(u32 speed)
{
	for (int i = 0; i < 0x2D; i++)
	{
		if (READU32(0x140002F4) > 0x14000000 && READU32(0x140002F4) < 0x18000000 && READU32(READU32(0x140002F4) - 0xA4) > 0x14000000 && READU32(READU32(0x140002F4) - 0xA4) < 0x18000000)
		{
			WRITEU32(READU32(READU32(0x140002F4) - 0xA4) - 0x2C3B0 + (i * 4), speed);
			WRITEU32(READU32(READU32(0x140002F4) - 0xA4) - 0x28E90 + (i * 4), speed);
			WRITEU32(READU32(READU32(0x140002F4) - 0xA4) - 0x1C730 + (i * 4), speed);
		}
	}
}

void	writeVR(u32 vr)
{
	if (READU32(0x663D04) > 0x10000000)
	{
		WRITEU32(READU32(0x663D04) - 0xE30, vr);
	}
}

void	writeLocation(u32 location)
{
	if (READU32(0x6673C8) > 0x10000000)
	{
		offset = READU32(0x6673C8);
		WRITEU32(offset + 0xF7CC, location);
	}
}

void	writeFlag(u8 flag)
{
	if (READU32(0x6673C8) > 0x10000000)
	{
		offset = READU32(0x6673C8);
		WRITEU8(offset + 0xE7CA, flag);
		WRITEU8(offset + 0xF7D0, flag);
	}
}

/////////////////////////////////////////////////////////    Start of race codes    /////////////////////////////////////////////////////////

void	invincible(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1)
	{
		if ((g_racePointer > 0x15000000) && (g_racePointer < 0x18000000))
		{
			WRITEU16(g_racePointer + 0x102C, 0xFFFF);
		}
	}
}

void	alwaysStarPower(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1)
	{
		if ((g_racePointer > 0x15000000) && (g_racePointer < 0x18000000))
		{
			WRITEU16(g_racePointer + 0xFF4, 0xFFFF);
		}
	}
}

void	alwaysBlackKart(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1)
	{
		if ((g_racePointer > 0x15000000) && (g_racePointer < 0x18000000))
		{
			WRITEU16(g_racePointer + 0xFF8, 0xFFFF);
		}
	}
}

void	alwaysShocked(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1)
	{
		if ((g_racePointer > 0x15000000) && (g_racePointer < 0x18000000))
		{
			WRITEU16(g_racePointer + 0x1000, 0xFFFF);
		}
	}
}

void	alwaysCrushed(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1)
	{
		if ((g_racePointer > 0x15000000) && (g_racePointer < 0x18000000))
		{
			WRITEU16(g_racePointer + 0x1004, 0xFFFF);
		}
	}
}

void	instantMT(void)
{
	WRITEU32(0x665634, 0);
	WRITEU32(0x665638, 0);
}

void	hugeBunnyhop(void)
{
	WRITEU32(0x6655D0, 0x40400000);
}

void	fastReverse(void)
{
	WRITEU32(0x6655A8, 0x41800000);
}

void	noCountdown(void)
{
	unsigned int g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0x65C528) > 0x14000000 && READU32(0x65C528) < 0x18000000)
	{
		WRITEU8(0x109 + READU32(0x65C528), 1);
		WRITEU8(0x589 + READU32(0x65C528), 1);
	}
}

void	moonjump(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (is_pressed(ST + R))
	{
		if (g_raceCondition == 1)
		{
			WRITEU32(g_racePointer + 0x3C, 0x41200000);
		}
	}
}

void	saveSlotTeleporter(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	static u32 x = 0, y = 0, z = 0;
	if (g_raceCondition == 1)
	{
		if (is_pressed(ST + X))
		{
			x = READU32(g_racePointer + 0x24);
			y = READU32(g_racePointer + 0x28);
			z = READU32(g_racePointer + 0x2C);
		}
		if (is_pressed(ST + Y))
		{
			WRITEU32(g_racePointer + 0x24, x);
			WRITEU32(g_racePointer + 0x28, y);
			WRITEU32(g_racePointer + 0x2C, z);
		}
	}
}

void	maxTimer(void)
{
	unsigned int g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0x65C528) > 0x14000000 && READU32(0x65C528) < 0x18000000)
	{
		WRITEU32(READU32(0x65C528) + 0x80, 0x4650);
	}
}

void	zeroTimer(void)
{
	unsigned int g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0x65C528) > 0x14000000 && READU32(0x65C528) < 0x18000000)
	{
		WRITEU32(READU32(0x65C528) + 0x80, 0);
	}
}

void	waterEverywhere(void)
{
	unsigned int g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0x663954) > 0x14000000 && READU32(0x663954) < 0x18000000 && READU32(READU32(0x663954) + 0x58) > 0x14000000 && READU32(READU32(0x663954) + 0x58) < 0x18000000)
	{
		WRITEU32(READU32(READU32(0x663954) + 0x58) + 0x420, 0x48000000);
	}
}

void	driveAnywhere(void)
{
	unsigned int g_raceCondition = GetRaceCondition(), g_racePointer = GetRacePointer();
	static unsigned int data = 0;
	if (g_raceCondition != 1)
	{
		data = 0;
		WRITEU32(0x6656D8, 0x14);
	}
	if (g_raceCondition == 1)
	{
		if (is_pressed(ST))
		{
			data = 0;
			WRITEU32(0x6656D8, 0x14);
		}
		if (is_pressed(SE))
		{
			data = 1;
			WRITEU32(0x6656D8, 0xFFFF);
		}
		if (data == 1)
		{
			WRITEU32(g_racePointer + 0x3C, 0);
			if (is_pressed(SE + DU))
			{
				WRITEU32(g_racePointer + 0x3C, 0x41000000);
			}
			if (is_pressed(SE + DD))
			{
				WRITEU32(g_racePointer + 0x3C, 0xC1000000);
			}
		}
	}
}

void	stalking(void) // could optimize a little more
{
	unsigned int g_raceCondition = GetRaceCondition(), g_racePointer = GetRacePointer(), tempActive = 0;
	static unsigned int pointer = 0, active = 0, player = 1;
	float dataY = 0, dataZ = 0;
	static bool held = false;
	if (g_raceCondition != 1)
	{
		player = 1;
		active = 0;
		pointer = 0;
		return;
	}
	if (g_raceCondition == 1)
	{
		if (!is_pressed(Y))
		{
			held = false;
		}
		if (is_pressed(Y))
		{
			tempActive = 1;
			if (is_pressed(DU))
			{
				active = 1;
			}	
			if (is_pressed(DD))
			{
				active = 0;
				player = 1;
			}
			if (!held)
			{
				if (is_pressed(DR))
				{
					held = true;
					player++;
				}
				if (is_pressed(DL))
				{
					held = true;
					player--;
				}
			}
		}
		if (active == 1 || tempActive == 1)
		{
			if (player > 8 || player < 1)
			{
				player = 1;
				return;
			}
			pointer = 0x209C + READU32(0x65DA44) + (player * 0x44);
			if (READU32(pointer) < 0x14000000 || READU32(pointer) > 0x18000000 || READU32(pointer) == g_racePointer || READU32(READU32(pointer) + 0x24) < 0x30000000 || READU32(READU32(pointer) + 0x24) > 0xD0000000 || READU32(READU32(pointer) + 0x2C) < 0x30000000 || READU32(READU32(pointer) + 0x2C) > 0xD0000000)
			{
				player++;
				return;
			}
			if (player > 0 && player < 9 && READU32(pointer) > 0x14000000 && READU32(pointer) < 0x18000000 && g_racePointer > 0x14000000 && g_racePointer < 0x18000000)
			{
				dataY = READFLOAT(READU32(pointer) + 0x28);
				dataY += 40;
				dataZ = READFLOAT(READU32(pointer) + 0x2C);
				if (dataY != 0 && dataY != 40 && dataZ != 0)
				{
					memcpy((void *)(g_racePointer), (void*)(READU32(pointer)), 0x28);
					WRITEFLOAT(g_racePointer + 0x28, dataY);
					WRITEFLOAT(g_racePointer + 0x2C, dataZ);
				}
				else
				{
					player++;
				}
			}
		}
	}
}

/* void	cpuBrawl(void) // untested
{
	int pointer = 0;
	int pointer2 = 0;
	for (int i = 1; i < 6; i++)
	{
		pointer = 0x209C + READU32(0x65DA44) + (i * 0x44);
		pointer2 = pointer + 0x44;
		memcpy((void *)(READU32(pointer)), (void*)(READU32(pointer)), 0x30);
	}
} */

void	TouchCode(void)
{
	unsigned int g_raceCondition = GetRaceCondition(), g_racePointer = GetRacePointer();
	if (READU32(READU32(0x6789C8) + 0x1A48) == 1 && g_raceCondition == 1 && g_racePointer > 0x16000000 && g_racePointer < 0x18000000)
	{
		unsigned int touch_pointer = *(unsigned int *)0x6789C8;
		float X_Axis = *(float *)(touch_pointer + 0x1BCC);
		float Y_Axis = *(float *)(touch_pointer + 0x1BD0);
		unsigned int map_pointer = READU32(READU32(READU32(READU32(READU32(READU32(0x140002F4) + 0x14) + 0x370) + 0x270) + 0x60) + 0x688);
		float MapStatic1 = *(float *)map_pointer;
		float Map_Scale1 = *(float *)(map_pointer + 4);
		float MapStatic2 = *(float *)(map_pointer + 8);
		float Map_Scale2 = *(float *)(map_pointer + 12);
		Map_Scale1 -= Map_Scale2;
		Map_Scale1 /= 240.f;
		X_Axis *= Map_Scale1;
		Y_Axis *= Map_Scale1;
		X_Axis -= ((320.f * Map_Scale1) - MapStatic2);
		Y_Axis += Map_Scale2;
		*(float *)(g_racePointer + 0x3C) = 0;
		*(float *)(g_racePointer + 0x24) = X_Axis;
		*(float *)(g_racePointer + 0x2C) = Y_Axis;
	}
}

/////////////////////////////////////////////////////////    Start of item codes    /////////////////////////////////////////////////////////

void	fastBlueShell(void)
{
	WRITEU32(0x666094, 0x43000000);
}

void	stoppedBlueShell(void)
{
	WRITEU32(0x666094, 0);
}

void	fastGreenShell(void)
{
	WRITEU32(0x66619C, 0x43000000);
}

void	stoppedGreenShell(void)
{
	WRITEU32(0x66619C, 0);
}

void	dropMushrooms(void)
{
	unsigned int g_oldRacePointer5D0 = GetOldPointer5D0(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && g_oldRacePointer5D0 > 0x14000000 && g_oldRacePointer5D0 < 0x18000000)
	{
		WRITEU32(g_oldRacePointer5D0 + 0x1D0, READU32(g_oldRacePointer5D0 + 0x1F8));
	}
}

void	bulletControl(void)
{
	unsigned int g_raceCondition = GetRaceCondition(), g_racePointer = GetRacePointer();
	if (g_raceCondition == 1 && g_racePointer > 0x14000000 && g_racePointer < 0x18000000)
	{
		WRITEU8(g_racePointer + 0xC32, 64);
	}
}

void	disableStarMusic(void)
{
	unsigned int g_FNsPointer = GetFNsPointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && g_FNsPointer > 0x14000000 && g_FNsPointer < 0x18000000 && READU8(g_FNsPointer + 0x1F7) == 1)
	{
		WRITEU8(g_FNsPointer + 0x1F7, 0);
	}
}

void	bulletSpeed(void)
{
	if (is_pressed(X))
		WRITEU32(0x6655A4, 0x41C00000);
	if (is_pressed(B))
		WRITEU32(0x6655A4, 0xFF7FFFFF);
	if (is_pressed(A))
		WRITEU32(0x6655A4, 0x40F33333);
}

void	blueShellRide(void)
{
	unsigned int dataX = 0, dataY = 0, dataZ = 0, g_raceCondition = GetRaceCondition(), g_racePointer = GetRacePointer();
	if (is_pressed(DL))
	{
		if (g_raceCondition == 1 && READU32(0xFFFFBF4) > 0x14000000 && READU32(0xFFFFBF4) < 0x18000000 && READU32(READU32(0xFFFFBF4) - 0x63C) > 0x14000000 && READU32(READU32(0xFFFFBF4) - 0x63C) < 0x18000000)
		{
			dataX = READU32(READU32(READU32(0xFFFFBF4) - 0x63C) - 0x3CB0);
			dataY = READU32(READU32(READU32(0xFFFFBF4) - 0x63C) - 0x3CAC);
			dataZ = READU32(READU32(READU32(0xFFFFBF4) - 0x63C) - 0x3CA8);
			if (dataX > 0x1000 && dataX < 0xD0000000 &&  dataY > 0x1000 && dataY < 0xD0000000 && dataZ > 0x1000 && dataZ < 0xD0000000)
			{
				WRITEU32(g_racePointer + 0x24, dataX);
				WRITEU32(g_racePointer + 0x28, dataY);
				WRITEU32(g_racePointer + 0x2C, dataZ);
			}
		}
	}
}

void	itemWheel(void)
{
	unsigned int g_raceCondition = GetRaceCondition(), g_itemPointer = GetItemPointer();
	if (g_raceCondition == 1 && g_itemPointer > 0x14000000 && g_itemPointer < 0x18000000)
	{
		if (is_pressed(X))
			writeItem(9);
		if (is_pressed(Y))
			writeItem(13);
		if (is_pressed(ST))
			writeItem(6);
		if (is_pressed(SE))
			writeItem(10);
		if (is_pressed(DL))
			writeItem(14);
		if (is_pressed(DR))
			writeItem(2);
		if (is_pressed(DD))
			writeItem(4);
		if (is_pressed(DU))
			writeItem(1);
	}
}

/////////////////////////////////////////////////////////    Start of speed codes    /////////////////////////////////////////////////////////

void	TwoHundredCC(void)
{
	writeSpeed(0x413C0000);
}

void	FiveHundredCC(void)
{
	writeSpeed(0x41A00000);
}

/////////////////////////////////////////////////////////    Start of menu codes    /////////////////////////////////////////////////////////

void	disableFirstPersonView(void)
{
	offset = READU32(READU32(0x14000084) + 0x316C); // for some reason this doesn't work when it's reduced to one line...
	WRITEU8(offset + 0x119, 0);
}

void	vrExtender(void)
{
	if (READU32(0x663D04) > 0x10000000)
	{
		if(is_pressed(ST))
		{
			writeVR(999999);
		}
		if(is_pressed(SE))
		{
			writeVR(420000);
		}
		if(is_pressed(DD))
		{
			writeVR(0);
		}
		if(is_pressed(DU))
		{
			writeVR(696969);
		}
		if(is_pressed(DR))
		{
			writeVR(666666);
		}
		if(is_pressed(DL))
		{
			writeVR(777777);
		}
	}
}

void	randomVR(void)
{
	unsigned int random = 0;
	if (READU16(0x14296A90) > 20000 && READU16(0x14296A90) < 200000)
	{
		random = READU16(0x14296A90) * 5;
		if (READU32(0x663D04) > 0x14000000 && READU32(0x663D04) < 0x18000000)
		{
			writeVR(random);
		}
	}
}

void	unlockEverything(void)
{
	if (READU32(0x6673C8) > 0x10000000 && READU32(0x6673C8) < 0x18000000)
	{
		offset = READU32(0x6673C8);
		WRITEU8(0x6BA3 + offset, 0x3F);
		WRITEU32(0x6BA4 + offset, 0x1FF003F);
		WRITEU16(0x6BAC + offset, 0x3FFF);
		WRITEU8(0x6BB0 + offset, 0x7F);
		WRITEU8(0x6BB4 + offset, 0x3F);
		WRITEU8(0x6BB8 + offset, 0xFF);
	}
}

void	NoDC(void)
{
	unsigned int g_oldRacePointer5CC = GetOldPointer5CC(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && g_oldRacePointer5CC > 0x14000000 && g_oldRacePointer5CC < 0x18000000)
	{
		WRITEU8(g_oldRacePointer5CC + 0x40, 2);
	}
}

void	fastGame(void)
{
	if (READU32(0x140002F4) > 0x14000000 && READU32(0x140002F4) < 0x18000000)
	{
		WRITEU32(READU32(READU32(0x140002F4) + 0x14) + 0x2B4, 0);
	}
}

/////////////////////////////////////////////////////////    Start of region & flag codes    /////////////////////////////////////////////////////////

void	region_France(void)
{
	writeLocation(France);
}

void	region_Hawaii(void)
{
	writeLocation(Hawaii);
}

void	region_UpperAntartica(void)
{
	writeLocation(UpperAntartica);
}

void	region_NorthPole(void)
{
	writeLocation(NorthPole);
}

void	region_Iran(void)
{
	writeLocation(Iran);
}

void	region_SaudiArabia(void)
{
	writeLocation(SaudiArabia);
}

void	region_Cuba(void)
{
	writeLocation(Cuba);
}

void	region_Russia(void)
{
	writeLocation(RussiaEnmelen);
}

void	region_Phillippines(void)
{
	writeLocation(Phillippines);
}

void	flag_Japan(void)
{
	writeFlag(Japan);
}

void	flag_Haiti(void)
{
	writeFlag(Haiti1);
}

void	flag_Italy(void)
{
	writeFlag(Italy);
}

void	flag_SaudiArabia(void)
{
	writeFlag(SaudiArabia1);
}

void	flag_SouthAfrica(void)
{
	writeFlag(SouthAfrica);
}

void	flag_Russia(void)
{
	writeFlag(Russia);
}

void	flag_USA(void)
{
	writeFlag(UnitedStates1);
}

/////////////////////////////////////////////////////////    End of codes    /////////////////////////////////////////////////////////