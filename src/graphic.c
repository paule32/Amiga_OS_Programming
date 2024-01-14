// ---------------------------------------------------------------------------
// Datei:  graphic.c
// Author: Jens Kallup - paule32
//
// Rechte: (c) 2023 by kallup non-profit software
//         all rights reserved.
//
// only for education, or non-profit, and no commercial purpose !!!
// ---------------------------------------------------------------------------
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include <proto/exec.h>
# include <proto/dos.h>
# include <proto/graphics.h>
# include <proto/intuition.h>

#ifndef EXIT_SUCCESS
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
#endif

int main(void)
{
struct IntuitionBase * IntuitionBase;
struct IntuiMessage  * msg;
struct GfxBase       * GfxBase;

struct Screen *screen;
struct Window *window;
    
    if (!(IntuitionBase = (struct IntuitionBase *)OpenLibrary("intuition.library", 0))) {
        // Handle error
        return EXIT_FAILURE;
    }

    if (!(GfxBase = (struct GfxBase *)OpenLibrary("graphics.library", 39))) {
        // handle error
        return EXIT_FAILURE;
    }
    
    // Create a new screen
    struct NewScreen newScreen = {
        .Width = 734,   // Width of the screen
        .Height = 234,  // Height of the screen
        .Depth = 4,     // Number of bitplanes (colors)
        .DetailPen = 0,
        .BlockPen = 1,
        .ViewModes = HIRES,  // Screen resolution mode
        .Type = CUSTOMSCREEN,
    };

    screen = OpenScreen(&newScreen);
    if (!screen) {
        // Handle error
        CloseLibrary((struct Library *)IntuitionBase);
        return EXIT_FAILURE;
    }

    // Create a new window that covers the entire screen
    window = OpenWindowTags(NULL,
        WA_CustomScreen, screen,
        WA_Left, 0,
        WA_Top, 734,
        WA_Width, screen->Width,
        WA_Height, screen->Height,
        WA_CloseGadget, TRUE,
        WA_DragBar, TRUE,
        WA_DepthGadget, FALSE,
        WA_SizeGadget, FALSE,
        WA_IDCMP, IDCMP_CLOSEWINDOW,
        TAG_END);

    if (!window) {
        // Handle error
        CloseScreen(screen);
        CloseLibrary((struct Library *)IntuitionBase);
        return EXIT_FAILURE;
    }
    
    char buffer[32] = "Amiga-Dresden.DE - Community -";
    SetWindowTitles(window, buffer, (UBYTE *)buffer);
    
    ULONG relX = window->LeftEdge + window->BorderLeft;
    ULONG relY = window->TopEdge  + window->BorderTop;
    
    SetRGB4(&(screen->ViewPort), 0,   0,   0,   0);
    SetRGB4(&(screen->ViewPort), 1,   0,   0, 180);
    SetRGB4(&(screen->ViewPort), 2, 200,   0,  50);
    SetRGB4(&(screen->ViewPort), 3, 200, 200, 200);
    
    SetRast (window->RPort, 0);
    
    SetAPen (window->RPort, 1); 
    RectFill(window->RPort, relX, relY-8, window->Width, window->Height);
    
    SetAPen (window->RPort, 2);
    RectFill(window->RPort, 5, window->Height - 21, window->Width, window->Height-4);
    
    SetAPen (window->RPort, 3);
    RectFill(window->RPort,  10, window->Height - 18, 120, window->Height-7);
    RectFill(window->RPort, 135, window->Height - 18, 255, window->Height-7);
    RectFill(window->RPort, 270, window->Height - 18, 380, window->Height-7);
    RectFill(window->RPort, 395, window->Height - 18, 505, window->Height-7);
    RectFill(window->RPort, 520, window->Height - 18, 630, window->Height-7);
    
    SetAPen(window->RPort, 0);
    SetFont(window->RPort, window->RPort->Font);
    
    char buffer_time[] = "12:02:21";
    SetAPen(window->RPort, 1);
    SetFont(window->RPort, window->RPort->Font);
    
    Move(window->RPort, window->Width - 90, window->Height-10);
    Text(window->RPort, buffer_time, strlen(buffer_time));
    
    
    // Wait for the user to close the window
    WaitPort(window->UserPort);
    msg = (struct IntuiMessage *)GetMsg(window->UserPort);
    if (msg->Class == IDCMP_CLOSEWINDOW) {
        // Clean up and exit
        CloseWindow(window);
        CloseScreen(screen);
    }

    CloseLibrary((struct Library *)IntuitionBase);
    return EXIT_SUCCESS;
}
