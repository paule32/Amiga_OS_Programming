// ---------------------------------------------------------------------------
// Datei:  screen.c
// Author: Jens Kallup - paule32
//
// Rechte: (c) 2023 by kallup non-profit software
//         all rights reserved.
//
// only for education, or non-profit, and no commercial purpose !!!
// ---------------------------------------------------------------------------
# include <proto/intuition.h>
# include <proto/dos.h>
# include <intuition/screens.h>

#ifndef EXIT_SUCCESS
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
#endif

int main(void) {
    struct IntuitionBase * IntuitionBase;
    if (! (IntuitionBase = (struct IntuitionBase *)OpenLibrary("intuition.library", 0))) {
        // Handle error
        return EXIT_FAILURE;
    }

    struct NewScreen Screen1 = {
        0,0,
        640,480,
        8,
        DETAILPEN, BLOCKPEN,
        HIRES,
        PUBLICSCREEN,
        NULL,
        "My New Screen",
        NULL,
        NULL
    };
    struct Screen *myScreen;

    myScreen = OpenScreen(&Screen1);
    Delay(500);

    if (myScreen) {
        CloseScreen(myScreen);
        CloseLibrary((struct Library *)IntuitionBase);
        return EXIT_SUCCESS;

    }   return EXIT_FAILURE;
}
