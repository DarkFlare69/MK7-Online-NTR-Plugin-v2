#include "cheats.h"

#define ENTRY_COUNT 300

typedef struct s_menu
{
    int         count;
    int         status;
    u32         f[ENTRY_COUNT];
    u32         s[ENTRY_COUNT];
    int         a[ENTRY_COUNT];
    const char  *t[ENTRY_COUNT];
    const char  *n[ENTRY_COUNT];
    void        (*fp[ENTRY_COUNT])();
}             t_menu;


typedef void    (*FuncPointer)(void);
extern t_menu menu;


void    new_super_unselectable_entry(char *str, FuncPointer function)
{
    int index;

    index = menu.count;
    if (index >= 300)
        return;
    new_unselectable_entry(str);
    menu.f[index] |= BIT(0) | BIT(1);
    menu.fp[index] = function;
}

void with_note_common(const char *name, const char *note, void (*cheatfunction)(void), int type)
{
    int     index;

    if (type == 0)
        index = new_entry((char *)name, cheatfunction);
    else if (type == 1)
        index = new_radio_entry((char *)name, cheatfunction);
    else if (type == 2)
        index = new_spoiler((char *)name);
    else return;
    set_note(note, index);
}

void new_entry_with_note(const char *name, const char *note, void (*cheatfunction)(void))
{
    with_note_common(name, note, cheatfunction, 0);
}

void new_radio_entry_with_note(const char *name, const char *note, void (*cheatfunction)(void))
{
    with_note_common(name, note, cheatfunction, 1);
}

void new_spoiler_with_note(const char *name, const char *note)
{
    with_note_common(name, note, NULL, 2);
}

char	*builder_name = "DarkFlare";

	static const char * const invincible_note = "You will be invincible. You will also appear blinking on other people's screens online.";
	static const char * const alwaysStarPower_note = "You will always have star effects, such as invincibility and color.";
	static const char * const alwaysBlackKart_note = "Your kart will be black as if you got bloopered.";
	static const char * const alwaysShocked_note = "Your kart will always be small as if you got shocked.";
	static const char * const alwaysCrushed_note = "Your kart will always be flat as if you got crushed. This is only visible on opponents screens online. On your screen, you'll appear normally.";
	static const char * const instantMT_note = "You will instantly get red and blue MiniTurbos when drifting.";
	static const char * const hugeBunnyhop_note = "You will jump very high when hopping before a drift.";
	static const char * const TwoHundredCC_note = "You will go 200cc speeds. Restart the race after applying the code for the effect to take place.";
	static const char * const FiveHundredCC_note = "You will go 500cc speeds. Restart the race after applying the code for the effect to take place.";
	static const char * const fastReverse_note = "You will reverse at higher speeds than before when holding B.";
	static const char * const moonjump_note = "-Start + R = Enable";
	static const char * const saveSlotTeleporter_note = "-Start + X = Save Current Position\n-Start + Y = Load Saved Position";
	static const char * const itemWheel_note = "-X = Bullet\n-Y = Tanooki\n-Start = Blue Shell\n-Select = Lightning\n-D-Pad Left = Lucky 7\n-D-Pad Right = Red Shell\n-D-Pad Up = Green Shell\n-D-Pad Down = Bob-Omb";
	static const char * const dropMushrooms_note = "This code replaces green shells with droppable mushrooms. Throw a 'green shell' to drop a mushroom.";
	static const char * const fastBlueShell_note = "Blue shells will go very fast.";
	static const char * const stoppedBlueShell_note = "Blue shells will not move after being thrown.";
	static const char * const fastGreenShell_note = "Green shells will go very fast.";
	static const char * const stoppedGreenShell_note = "Green shells will not move after being thrown.";
	static const char * const bulletControl_note = "You will be able to control your bullets."; // make sure to update this after adding controls to bullet
	static const char * const bulletSpeed_note = "-X = Very Fast\n-B = Stopped\n-A = Normal Speed";
	static const char * const blueShellRide_note = "-D-Pad Left = Enable\nYou will warp to a blue shell and ride it.";
	static const char * const disableStarMusic_note = "The star music won't play when you're in a star.";
	static const char * const maxTimer_note = "The timer will freeze at 4:59.9xx.";
	static const char * const waterEverywhere_note = "You will always be underwater.";
	static const char * const noCountdown_note = "You will be able to drive when the countdown normally would be happening.";
	static const char * const disableFirstPersonView_note = "You will not be able to activate first person view by pressing Up on the D-Pad.";
	static const char * const NoDC_note = "You will not get disconnected unless the cause of the disconnection is an actual network problem.";
	static const char * const vrExtender_note = "-Start = 999999\n-Select = 420000\n-D-Pad Down = 0\n-D-Pad Up = 696969\n-D-Pad Right = 666666\n-D-Pad Left = 777777";
	static const char * const randomVR_note = "A random VR value will be generated.";
	static const char * const unlockEverything_note = "Everything will be unlocked. After enabling, save the game by completing a time trial or something, exit the game, and open it again. At this point everything should be permanently unlocked.";
	static const char * const driveAnywhere_note = "-Start = Disable\n-Select = Enable\n-Select + Up = Go Up\n-Select + Down = Go Down";
	static const char * const stalking_note = "-Y + Right = Increase\n-Y + Left = Decrease\n-Y + Up = Stalk the player until code is disabled\n-Hold Y to stalk the player temporarily, release Y to stop stalking\n-Y + Down = Disable Code";
	static const char * const TouchCode_note = "Touch the bottom screen or drag your stylus across it to warp your kart to that position on the map!";
	static const char * const fastGame_note = "The game will move at a very fast speed. Unstable, use at your own risk!";
	static const char * const eliminationMode_note = "Every 30 seconds, the player in last place will be eliminated. The last player standing wins! This mode works best in rooms with more players.";
	static const char * const tagMode_note = "One player will be 'it' and they have to try and tag another player by running into them! You will lose points the longer you are 'it' and also gain points for not being 'it'. The tagged person can will always be in a star.";
	static const char * const shineTheif_note = "One player will start off with the 'shine' and they have to protect it from other people, who will try to steal it by running into the player with the shine! You will gain points the longer you have the shine. The person with the shine will always be in a star.\nD-Pad Left = Use Gained Boost";

void    my_menus(void)
{
	new_spoiler("Kart Codes");
		new_entry_with_note("Invincibility", invincible_note, invincible);
		new_entry_with_note("Always Star Power", alwaysStarPower_note, alwaysStarPower);
		new_entry_with_note("Always Black Kart", alwaysBlackKart_note, alwaysBlackKart);
		new_entry_with_note("Always Shocked", alwaysShocked_note, alwaysShocked);
		new_entry_with_note("Always Crushed", alwaysCrushed_note, alwaysCrushed);
		new_entry_with_note("Instant MiniTurbo", instantMT_note, instantMT);
		new_entry_with_note("Huge Bunnyhop", hugeBunnyhop_note, hugeBunnyhop);
	exit_spoiler();
	
	new_spoiler("Speed & Movement Codes");
		new_entry_with_note("200cc", TwoHundredCC_note, TwoHundredCC);
		new_entry_with_note("500cc", FiveHundredCC_note, FiveHundredCC);
		new_entry_with_note("Fast Reverse Speeds", fastReverse_note, fastReverse);
		new_entry_with_note("Stalking Hack (See Note)", stalking_note, stalking);
		new_entry_with_note("Touch Screen Teleporter", TouchCode_note, TouchCode);
		new_entry_with_note("Moonjump (See Note)", moonjump_note, moonjump);
		new_entry_with_note("Drive Anywhere (See Note)", driveAnywhere_note, driveAnywhere);
		new_entry_with_note("Save Slot Teleporter (See Note)", saveSlotTeleporter_note, saveSlotTeleporter);
	exit_spoiler();
	
	new_spoiler("Item Codes");
		new_entry_with_note("Item Wheel (See Note)", itemWheel_note, itemWheel);
		new_entry_with_note("Drop Mushrooms (See Note)", dropMushrooms_note, dropMushrooms);
		new_entry_with_note("Fast Blue Shell", fastBlueShell_note, fastBlueShell);
		new_entry_with_note("Stopped Blue Shell", stoppedBlueShell_note, stoppedBlueShell);
		new_entry_with_note("Fast Green Shell", fastGreenShell_note, fastGreenShell);
		new_entry_with_note("Stopped Green Shell", stoppedGreenShell_note, stoppedGreenShell);
		new_entry_with_note("Control Bullet (See Note)", bulletControl_note, bulletControl);
		new_entry_with_note("Bullet Speed Modifier (See Note)", bulletSpeed_note, bulletSpeed);
		new_entry_with_note("Blue Shell Ride (See Note)", blueShellRide_note, blueShellRide);
		new_entry_with_note("Disable Star Music", disableStarMusic_note, disableStarMusic);
	exit_spoiler();
	
	new_spoiler("Course Codes");
		//new_entry_with_note("CPU Brawl", invincible_note, cpuBrawl); // this code hasn't been tested
		new_entry_with_note("Max Timer", maxTimer_note, maxTimer);
		new_entry_with_note("Water Everywhere", waterEverywhere_note, waterEverywhere);
	exit_spoiler();
	
	new_spoiler("Menu & Unlock Codes");
		new_entry_with_note("No Countdown", noCountdown_note, noCountdown);
		new_entry_with_note("Disable First Person View", disableFirstPersonView_note, disableFirstPersonView);
		new_entry_with_note("No Disconnect", NoDC_note, NoDC);
		new_entry_with_note("Fast Game/Anti-Matrix", fastGame_note, fastGame);
		new_entry_with_note("VR Extender (See Note)", vrExtender_note, vrExtender);
		new_entry_with_note("Random VR", randomVR_note, randomVR);
		new_entry_with_note("Unlock Everything", unlockEverything_note, unlockEverything);
	exit_spoiler();
	
	new_spoiler("Custom Game Modes");
		new_entry_with_note("Shine Thief", shineTheif_note, shineTheif);
		new_entry_with_note("Tag", tagMode_note, tagMode);
		new_entry_with_note("Elimination Mode", eliminationMode_note, eliminationMode);
	exit_spoiler();
	
	new_spoiler("Region & Flag Codes"); // work on lining the region/flags up and add more
		new_spoiler("Region Codes");
			new_entry("France", region_France);
			new_entry("Saudi Arabia", region_SaudiArabia);
			new_entry("Hawaii", region_Hawaii);
			new_entry("Upper Antartica", region_UpperAntartica);
			new_entry("North Pole", region_NorthPole);
			new_entry("Iran", region_Iran);
			new_entry("Cuba", region_Cuba);
			new_entry("Philippines", region_Phillippines);
			new_entry("Russia", region_Russia);
		exit_spoiler();
		new_spoiler("Flag Codes");
			new_entry("Japan", flag_Japan);
			new_entry("Saudi Arabia", flag_SaudiArabia);
			new_entry("United States of America", flag_USA);
			new_entry("Haiti", flag_Haiti);
			new_entry("Italy", flag_Italy);
			new_entry("South Africa", flag_SouthAfrica);
			new_entry("Russia", flag_Russia);
		exit_spoiler();
	exit_spoiler();
}
