/*-----------------------------------------------------
Basic template code for starting a DS app
-----------------------------------------------------*/
#include <nds.h>
#include <stdlib.h>
#include <stdio.h>
#include <nf_lib.h>
#include <maxmod9.h>    // Maxmod definitions for ARM9
#include "soundbank.h"  // Soundbank definitions
#include "soundbank_bin.h"

#include <filesystem.h>


//---------------------------------------------------------------------------------

class Spaceship{
	public:
		s16 char_x = 100;
		s16 char_y = 128;
};

class Laser{
	public:
		s16 x = 0;
		s16 y = 50;
		s16 time = 100;
};

int main(void)
{
	
	consoleDemoInit();

    
	
    // NitroFS Init
    nitroFSInit(NULL);
    NF_SetRootFolder("NITROFS");

    NF_Set2D(0, 0);
    //NF_Set2D(1, 0);

    // Initialize tiled backgrounds system
    NF_InitTiledBgBuffers(); // Initialize storage buffers
    NF_InitTiledBgSys(0);    // Top screen
    //NF_InitTiledBgSys(1);    // Bottom screen

    // Initialize sprite system
    NF_InitSpriteBuffers(); // Initialize storage buffers
    NF_InitSpriteSys(0);    // Top screen

    // Loading And Create of the Tiled Background
    NF_LoadTiledBg("bg/bg3", "bg3", 256, 256);
    //NF_LoadTiledBg("bg/nfl", "nfl", 256, 256);

    NF_CreateTiledBg(0, 3, "bg3");
    //NF_CreateTiledBg(1, 3, "nfl");
	
	// Setup character sprite
    Spaceship flyer;
	Laser laser;

    // Load Sprite

    NF_LoadSpriteGfx("sprite/flyer", 0, 64, 64);
    NF_LoadSpritePal("sprite/flyer", 0);
	
	NF_LoadSpriteGfx("sprite/bullet", 1, 64, 64);
    NF_LoadSpritePal("sprite/bullet", 1);

    // Transfer sprite to VRAM
    NF_VramSpriteGfx(0, 0, 0, false);
    NF_VramSpritePal(0, 0, 0);
	
	NF_VramSpriteGfx(0, 1, 1, false);
    NF_VramSpritePal(0, 1, 1);

    // Create the Sprite
    NF_CreateSprite(0, 0, 0, 0, flyer.char_x, flyer.char_y);
	
	// Initialize DS audio hardware
    soundEnable();
	
	mmInitDefaultMem((mm_addr)soundbank_bin);
	
	mmLoad(MOD_0_SPACE);
	mmStart( MOD_0_SPACE, MM_PLAY_LOOP );
	
	
    while (1)
    {
		if (flyer.char_x < -4)
            flyer.char_x = -4;
        if (flyer.char_x > 256-60)
            flyer.char_x = 256-60;

        if (flyer.char_y < -4)
            flyer.char_y = -4;
        if (flyer.char_y > 192-60)
            flyer.char_y = 192 -60;
		
		

        scanKeys();

        if (KEY_UP & keysHeld())
        {  
			flyer.char_y -= 3;
        }
        else if (keysHeld() & KEY_DOWN)
        {
            flyer.char_y += 3;

        }
        else if (keysHeld() & KEY_RIGHT)
        {
            flyer.char_x += 3;
			
        }
        else if (keysHeld() & KEY_LEFT)
        {
            flyer.char_x -= 3;

        } else if(keysHeld() & KEY_A){
			
			NF_CreateSprite(0, 1, 1, 1, flyer.char_x + 32, flyer.char_y + 32);
		}else if(laser.time == 0){

		}

		

        NF_MoveSprite(0, 0, flyer.char_x, flyer.char_y);
		NF_MoveSprite(0, 1, flyer.char_x, laser.y -= 3);

		
		iprintf("\x1b[16;0HPosition x = %d\n", flyer.char_x);
		iprintf("Position y = %d\n", flyer.char_y);
		iprintf("Position y = %d\n", laser.y);
		

        // Update NF OAM Settings
        NF_SpriteOamSet(0);

        swiWaitForVBlank();

        oamUpdate(&oamMain);
    }
    return 0;
}