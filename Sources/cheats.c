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
	if (g_raceCondition == 1 && READU32(READU32(READU32(0x140002F4) + 0x14) + 0x518) > 0x14000000 && READU32(READU32(READU32(0x140002F4) + 0x14) + 0x518) < 0x18000000)
	{
		g_racePointer = READU32(READU32(READU32(READU32(0x140002F4) + 0x14) + 0x518) + 0x1C);
		return (g_racePointer);
	}
	else
	{
		return (0);
	}
}

unsigned int	GetRaceCondition(void)
{
	unsigned int g_raceCondition;
	if (READU32(0x14000084) > 0x14000000 && READU32(0x14000084) < 0x18000000)
	{
		g_raceCondition = READU8(READU32(READU32(0x14000084) + 0x316C) + 0x118);
		return (g_raceCondition);
	}
	else
	{
		return (0);
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
		return (0);
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
		return (0);
	}
}

unsigned int	GetOldPointer5D0(void)
{
	unsigned int g_oldRacePointer5D0, g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0xFFFFBF4) > 0x14000000 && READU32(0xFFFFBF4) < 0x18000000 && READU32(0x65C528) > 0x14000000 && READU32(0x65C528) < 0x18000000)
	{
		g_oldRacePointer5D0 = READU32(0x65C528);
		return (g_oldRacePointer5D0);
	}
	else
	{
		return (0);
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
		return (0);
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
		if (g_racePointer > 0x15000000 && g_racePointer < 0x18000000)
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
		if (g_racePointer > 0x15000000 && g_racePointer < 0x18000000)
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
		if (g_racePointer > 0x15000000 && g_racePointer < 0x18000000)
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
		if (g_racePointer > 0x15000000 && g_racePointer < 0x18000000)
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
		if (g_racePointer > 0x15000000 && g_racePointer < 0x18000000)
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
		WRITEU8(READU32(0x65C528) + 0x109, 1);
		WRITEU8(READU32(0x65C528) + 0x589, 1);
	}
}

void	moonjump(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && is_pressed(ST + R))
		WRITEU32(g_racePointer + 0x3C, 0x41200000);
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
		WRITEU32(READU32(0x65C528) + 0x80, 0x4650);
}

void	zeroTimer(void)
{
	unsigned int g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0x65C528) > 0x14000000 && READU32(0x65C528) < 0x18000000)
		WRITEU32(READU32(0x65C528) + 0x80, 0);
}

void	waterEverywhere(void)
{
	unsigned int g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0x663954) > 0x14000000 && READU32(0x663954) < 0x18000000 && READU32(READU32(0x663954) + 0x58) > 0x14000000 && READU32(READU32(0x663954) + 0x58) < 0x18000000)
		WRITEU32(READU32(READU32(0x663954) + 0x58) + 0x420, 0x48000000);
}

void	driveAnywhere(void)
{
	unsigned int g_raceCondition = GetRaceCondition(), g_racePointer = GetRacePointer();
	static unsigned int data = 0;
	if (g_raceCondition != 1)
	{
		data = 0;
		WRITEU32(0x6656D8, 0x14);
		return;
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

void	cpuBrawl(void) // untested
{
	int pointer = 0, pointer2 = 0;
	for (int i = 2; i < 9; i++)
	{
		pointer = 0x209C + READU32(0x65DA44) + (i * 0x44);
		pointer2 = pointer + 0x44;
		memcpy((void *)(READU32(pointer)), (void*)(READU32(pointer)), 0x30);
	}
}

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

/////////////////////////////////////////////////////////    Start of game modes    /////////////////////////////////////////////////////////

void	eliminationMode(void)
{
	WRITEU32(0x468D1C, 0xE1A00000);
	WRITEU32(0x469154, 0xE1A00000);
	WRITEU32(0x4165A8, 0xE1A00000);
	WRITEU32(0x233B54, 0xEA0EDF6D);
	offset = 0x5EB910;
	static const u8 buffer1[] = { 0xFF, 0x1F, 0x2D, 0xE9, 0xC4, 0x11, 0x9F, 0xE5, 0xC4, 0x31, 0x9F, 0xE5, 0xC4, 0x61, 0x9F, 0xE5, 0xC4, 0x71, 0x9F, 0xE5, 0xC4, 0x81, 0x9F, 0xE5, 0, 0x10, 0xD1, 0xE5, 0, 0, 0x51, 0xE3, 0x2, 0, 0, 0x1A, 0, 0x20, 0xA0, 0xE3, 0, 0x20, 0x83, 0xE5, 0x4, 0x20, 0x83, 0xE5, 0x1, 0, 0x51, 0xE3, 0x62, 0, 0, 0x1A, 0xA4, 0x11, 0x9F, 0xE5, 0, 0x90, 0x96, 0xE5, 0xC8, 0x90, 0x99, 0xE5, 0, 0, 0xA0, 0xE3, 0x34, 0, 0x89, 0xE5, 0x38, 0, 0x89, 0xE5, 0, 0x70, 0x97, 0xE5, 0x8, 0x70, 0x87, 0xE0, 0, 0x70, 0x97, 0xE5, 0x7, 0xB0, 0xA0, 0xE1, 0, 0x60, 0x96, 0xE5, 0xF4, 0x50, 0xD6, 0xE5, 0x2, 0, 0x55, 0xE3, 0x3, 0, 0, 0xA, 0x1E, 0x40, 0xA0, 0xE3, 0x46, 0x40, 0xC7, 0xE5, 0, 0, 0xD1, 0xE5, 0x4, 0, 0xC3, 0xE5, 0x2, 0, 0x55, 0xE3, 0x4E, 0, 0, 0x1A, 0, 0x20, 0x93, 0xE5, 0x46, 0x40, 0xD7, 0xE5, 0x1, 0x20, 0x82, 0xE2, 0x40, 0, 0x52, 0xE3, 0x8, 0, 0, 0xBA, 0, 0x20, 0xA0, 0xE3, 0, 0x20, 0x83, 0xE5, 0x1, 0x40, 0x44, 0xE2, 0, 0, 0x54, 0xE3, 0x2, 0, 0, 0xAA, 0x1E, 0x40, 0xA0, 0xE3, 0x46, 0x40, 0xC7, 0xE5, 0x1, 0, 0, 0xEA, 0x46, 0x40, 0xC7, 0xE5, 0, 0x20, 0x83, 0xE5, 0x46, 0x40, 0xD7, 0xE5, 0, 0, 0x54, 0xE3, 0x31, 0, 0, 0x1A, 0, 0x20, 0x93, 0xE5, 0x3E, 0, 0x52, 0xE3, 0x2E, 0, 0, 0x1A, 0x4, 0, 0xD3, 0xE5, 0xC8, 0x80, 0x96, 0xE5, 0, 0x6B, 0x96, 0xE5, 0x80, 0x50, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0x50, 0x90, 0xC6, 0xE5, 0xC4, 0x50, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0xC0, 0x90, 0xC6, 0xE5, 0x8, 0x51, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0x30, 0x91, 0xC6, 0xE5, 0x4C, 0x51, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0xA0, 0x91, 0xC6, 0xE5, 0x90, 0x51, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0x10, 0x92, 0xC6, 0xE5, 0xD4, 0x51, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0x80, 0x92, 0xC6, 0xE5, 0x18, 0x52, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0xF0, 0x92, 0xC6, 0xE5, 0x5C, 0x52, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0x60, 0x93, 0xC6, 0xE5, 0x4, 0, 0x93, 0xE5, 0x1, 0, 0x40, 0xE2, 0x4, 0, 0x83, 0xE5, 0xA, 0, 0, 0xEA, 0x4, 0, 0xD3, 0xE5, 0x8, 0x50, 0x93, 0xE5, 0x20, 0x50, 0x95, 0xE5, 0x1, 0, 0x55, 0xE3, 0x5, 0, 0, 0x1A, 0x1, 0, 0x50, 0xE3, 0x3, 0, 0, 0x1A, 0xC, 0x80, 0x93, 0xE5, 0, 0x90, 0xA0, 0xE3, 0x4, 0x90, 0x88, 0xE5, 0xB8, 0x95, 0xCB, 0xE1, 0xFF, 0x1F, 0xBD, 0xE8, 0x2C, 0x30, 0x93, 0xE5, 0x1D, 0x20, 0xF1, 0xEA, 0xF4, 0xFD, 0x78, 0x14, 0x7C, 0x1, 0x68, 0, 0x28, 0xC5, 0x65, 0, 0xAC, 0x5, 0, 0x14, 0xC4, 0x12, 0, 0, 0xE0, 0x4B, 0x47, 0x15 };
	memcpy((void *)(offset), buffer1, 0x1E8);
	WRITEU32(0x4690FC, 0xEB060A7D);
	offset = 0x5EBAF8;
	static const u8 buffer2[] = { 0x6C, 0x60, 0xA0, 0xE3, 0x59, 0x60, 0xC4, 0xE5, 0xE, 0xF0, 0xA0, 0xE1 };
	memcpy((void *)(offset), buffer2, 0xC);
	WRITEU32(0x3D4E04, 0xEB085B3E);
	offset = 0x5EBB04;
	static const u8 buffer3[] = { 0x8, 0x80, 0x9F, 0xE5, 0, 0, 0x88, 0xE5, 0x20, 0x90, 0x90, 0xE5, 0xE, 0xF0, 0xA0, 0xE1, 0x84, 0x1, 0x68, 0 };
	memcpy((void *)(offset), buffer3, 0x14);
	WRITEU32(0x45CBE4, 0xEA063BCB);
	offset = 0x5EBB18;
	static const u8 buffer4[] = { 0, 0x1, 0x2D, 0xE9, 0xC, 0x80, 0x9F, 0xE5, 0, 0, 0x88, 0xE5, 0, 0x1, 0xBD, 0xE8, 0x4, 0x10, 0x90, 0xE5, 0x2D, 0xC4, 0xF9, 0xEA, 0x88, 0x1, 0x68, 0 };
	memcpy((void *)(offset), buffer4, 0x1C);
}

void	tagMode(void)
{
	u32 g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition(), pointer = 0, d0pointer = 0, ccpointer = 0;
	static u8 playerSlot = 0, taggedPlayer = 0, score = 0;
	static u16 time = 0;
	static bool tagged = false;
	if (g_raceCondition != 1)
	{
		playerSlot = 0;
		pointer = 0;
		taggedPlayer = 0;
		time = 0;
		score = 50;
		tagged = false;
		return;
	}
	if (g_raceCondition == 1 && g_racePointer > 0x16000000 && g_racePointer < 0x18000000 && READU32(0x65DA44) > 0x14000000 && READU32(0x65DA44) < 0x18000000 && READU8(READU32(0x65C9A8) + 0x175A8) < 10 && READU32(0x140005AC) > 0x14000000 && READU32(0x140005AC) < 0x18000000)
	{
		if (READU32(READU32(0x140005AC) + 0x12C8) > 0x14000000 && READU32(READU32(0x140005AC) + 0x12C8) < 0x18000000 && READU32(READU32(0x140005AC) + 0x12C4) > 0x14000000 && READU32(READU32(0x140005AC) + 0x12C4) < 0x18000000)
		{
			ccpointer = READU32(READU32(0x140005AC) + 0x12C4);
			d0pointer = READU32(READU32(0x140005AC) + 0x12C8);
			playerSlot = READU8(READU32(0x65C9A8) + 0x175A8) + 1;
			if (READU16(d0pointer + 0x1878) == 7200)
			{
				score = 50;
				WRITEU8(ccpointer + 0x46, score);
				WRITEU8(ccpointer + 0x54, score);
				if (playerSlot == 1)
				{
					tagged = true;
					score++;
				}
			}
			for (int i = 1; i < 9; i++)
			{
				pointer = READU32(READU32(0x65DA44) + (i * 0x44) + 0x209C);
				if (pointer > 0x14000000 && pointer < 0x18000000)
				{
					if (READU16(pointer + 0xFF4) > 0x40 && READU16(pointer + 0xFF4) < 0x180)
					{
						taggedPlayer = i;
					}
				}
			}
			if (tagged)
			{
				WRITEU16(g_racePointer + 0xFF4, 0xB0);
				if (time == 0 && READU16(d0pointer + 0x1878) != 7200 || (time - 120) > READU16(d0pointer + 0x1878))
				{
					score--;
					time = READU16(d0pointer + 0x1878);
					WRITEU8(ccpointer + 0x46, score);
					WRITEU8(ccpointer + 0x54, score);
					if (time < 6900 && READU16(g_racePointer + 0xFF4) > 0x40 && taggedPlayer != playerSlot)
					{
						WRITEU16(g_racePointer + 0xFF4, 0);
						tagged = false;
						return;
					}
				}
				if (READU16(g_racePointer + 0x1F6C) > 5 && READU16(g_racePointer + 0x1F6C) < 0xA000)
				{
					for (int i = 1; i < 9; i++)
					{
						pointer = READU32(READU32(0x65DA44) + (i * 0x44) + 0x209C);
						if (i == playerSlot)
						{
							continue;
						}
						if (READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) < 40.f && READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) > -40.f)
						{
							if (READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) < 40.f && READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) > -40.f)
							{
								if (READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) < 40.f && READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) > -40.f)
								{
									WRITEU16(g_racePointer + 0xFF4, 0);
									tagged = false; 
									taggedPlayer = i;
								}
							}
						}
					}
				}
			}
			if (!tagged)
			{
				pointer = READU32(READU32(0x65DA44) + (taggedPlayer * 0x44) + 0x209C);
				WRITEU16(g_racePointer + 0xFF4, 0);
				if (time == 0 || (time - 120) > READU16(d0pointer + 0x1878))
				{
					score++;
					time = READU16(d0pointer + 0x1878);
					WRITEU8(ccpointer + 0x46, score);
					WRITEU8(ccpointer + 0x54, score);
					if (time < 6900 && READU16(READU32(READU32(0x65DA44) + (taggedPlayer * 0x44) + 0x209C) + 0xFF4) < 0x40 && playerSlot == taggedPlayer)
					{
						tagged = true;
						taggedPlayer = playerSlot;
						return;
					}
				}
				if (READU16(g_racePointer + 0xC32) == 1 && READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) < 40.f && READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) > -40.f)
				{
					if (READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) < 40.f && READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) > -40.f)
					{
						if (READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) < 40.f && READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) > -40.f)
						{
							WRITEU16(g_racePointer + 0xFF4, 0xB0);
							tagged = true;
							taggedPlayer = playerSlot;
						}
					}
				}
			}
		}
	}
}

void	shineTheif(void)
{
	u32 g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition(), pointer = 0, d0pointer = 0, ccpointer = 0;
	static u8 playerSlot = 0, shinePlayer = 0, score = 0;
	static u16 time = 0;
	static bool withShine = false;
	if (g_raceCondition != 1)
	{
		playerSlot = 0;
		pointer = 0;
		shinePlayer = 0;
		time = 0;
		score = 0;
		withShine = false;
		return;
	}
	if (g_raceCondition == 1 && g_racePointer > 0x16000000 && g_racePointer < 0x18000000 && READU32(0x65DA44) > 0x14000000 && READU32(0x65DA44) < 0x18000000 && READU8(READU32(0x65C9A8) + 0x175A8) < 10 && READU32(0x140005AC) > 0x14000000 && READU32(0x140005AC) < 0x18000000)
	{
		if (READU32(READU32(0x140005AC) + 0x12C8) > 0x14000000 && READU32(READU32(0x140005AC) + 0x12C8) < 0x18000000 && READU32(READU32(0x140005AC) + 0x12C4) > 0x14000000 && READU32(READU32(0x140005AC) + 0x12C4) < 0x18000000)
		{
			ccpointer = READU32(READU32(0x140005AC) + 0x12C4);
			d0pointer = READU32(READU32(0x140005AC) + 0x12C8);
			playerSlot = READU8(READU32(0x65C9A8) + 0x175A8) + 1;
			if (READU16(d0pointer + 0x1878) == 7200)
			{
				score = 0;
				WRITEU8(ccpointer + 0x46, score);
				WRITEU8(ccpointer + 0x54, score);
				if (playerSlot == 1)
				{
					withShine = true;
				}
			}
			for (int i = 1; i < 9; i++)
			{
				pointer = READU32(READU32(0x65DA44) + (i * 0x44) + 0x209C);
				if (pointer > 0x14000000 && pointer < 0x18000000)
				{
					if (READU16(pointer + 0xFF4) > 0x40 && READU16(pointer + 0xFF4) < 0x180)
					{
						shinePlayer = i;
					}
				}
			}
			if (withShine)
			{
				WRITEU16(g_racePointer + 0xFF4, 0xB0);
				if (time == 0 && READU16(d0pointer + 0x1878) != 7200 || (time - 120) > READU16(d0pointer + 0x1878))
				{
					score++;
					time = READU16(d0pointer + 0x1878);
					WRITEU8(ccpointer + 0x46, score);
					WRITEU8(ccpointer + 0x54, score);
					if (time < 6900 && READU16(g_racePointer + 0xFF4) > 0x40 && shinePlayer != playerSlot)
					{
						WRITEU16(g_racePointer + 0xFF4, 0);
						withShine = false;
						return;
					}
				}
				if (READU16(g_racePointer + 0x1F6C) > 5 && READU16(g_racePointer + 0x1F6C) < 0xA000)
				{
					for (int i = 1; i < 9; i++)
					{
						pointer = READU32(READU32(0x65DA44) + (i * 0x44) + 0x209C);
						if (i == playerSlot)
						{
							continue;
						}
						if (READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) < 40.f && READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) > -40.f)
						{
							if (READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) < 40.f && READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) > -40.f)
							{
								if (READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) < 40.f && READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) > -40.f)
								{
									WRITEU16(g_racePointer + 0xFF4, 0);
									withShine = false; 
									shinePlayer = i;
								}
							}
						}
					}
				}
			}
			if (!withShine)
			{
				pointer = READU32(READU32(0x65DA44) + (shinePlayer * 0x44) + 0x209C);
				WRITEU16(g_racePointer + 0xFF4, 0);
				if (time == 0 || (time - 120) > READU16(d0pointer + 0x1878))
				{
					time = READU16(d0pointer + 0x1878);
					if (time < 6900 && READU16(READU32(READU32(0x65DA44) + (shinePlayer * 0x44) + 0x209C) + 0xFF4) < 0x40 && playerSlot == shinePlayer)
					{
						withShine = true;
						shinePlayer = playerSlot;
						return;
					}
				}
				if (READU16(g_racePointer + 0xC32) == 1 && READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) < 40.f && READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) > -40.f)
				{
					if (READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) < 40.f && READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) > -40.f)
					{
						if (READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) < 40.f && READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) > -40.f)
						{
							WRITEU16(g_racePointer + 0xFF4, 0xB0);
							withShine = true;
							shinePlayer = playerSlot;
						}
					}
				}
			}
		}
	}
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