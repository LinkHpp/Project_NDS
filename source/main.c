/*-----------------------------------------------------
Basic template code for starting a DS app
-----------------------------------------------------*/
#include <nds.h>
#include <stdio.h>
#include <nf_lib.h>

int main(int argc, char **argv)
{

    // Setup character sprite
    s16 char_x = 100;
    s16 char_y = 128;

    // NitroFS Init
    nitroFSInit();
    NF_SetRootFolder("NITROFS");

    NF_Set2D(0, 0);
    NF_Set2D(1, 0);

    // Initialize tiled backgrounds system
    NF_InitTiledBgBuffers(); // Initialize storage buffers
    NF_InitTiledBgSys(0);    // Top screen
    NF_InitTiledBgSys(1);    // Bottom screen

    // Initialize sprite system
    NF_InitSpriteBuffers(); // Initialize storage buffers
    NF_InitSpriteSys(0);    // Top screen

    // Loading And Create of the Tiled Background
    NF_LoadTiledBg("bg/bg3", "bg3", 256, 256);
    NF_LoadTiledBg("bg/nfl", "nfl", 256, 256);

    NF_CreateTiledBg(0, 3, "bg3");
    NF_CreateTiledBg(1, 3, "nfl");

    // Load Sprite

    NF_LoadSpriteGfx("sprite/flyer", 0, 64, 64);
    NF_LoadSpritePal("sprite/flyer", 0);

    // Transfer sprite to VRAM
    NF_VramSpriteGfx(0, 0, 0, false);
    NF_VramSpritePal(0, 0, 0);

    // Create the Sprite
    NF_CreateSprite(0, 0, 0, 0, char_x, char_y);

    while (1)
    {

        scanKeys();

        if (KEY_UP & keysHeld())
        {
            char_y -= 3;
            iprintf("      UP\n");
        }
        else if (keysHeld() & KEY_DOWN)
        {
            char_y += 3;
            iprintf("      DOWN\n");
        }
        else if (keysHeld() & KEY_RIGHT)
        {
            char_x += 3;
            iprintf("      RIGHT\n");
        }
        else if (keysHeld() & KEY_LEFT)
        {
            char_x -= 3;
            iprintf("      LEFT\n");
        }

        NF_MoveSprite(0, 0, char_x, char_y);

        // Update NF OAM Settings
        NF_SpriteOamSet(0);

        swiWaitForVBlank();

        oamUpdate(&oamMain);
    }
    return 0;
}
