#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window.

bool init();

//Loads media

bool loadMedia();

//Frees media and shuts down SDL

void close();

//Loads individual image

SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to

SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displated image

SDL_Surface* gStretchedSurface = NULL;

bool init()
{
    //Initialization flag
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initiliaze! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            printf("Window coule not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }else{
        //Get window surface
        gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia()
{
    //Loading successful
    bool success = true;

    //Load stretching surface
    gStretchedSurface = loadSurface("./stretch.bmp");
    if(gStretchedSurface == NULL)
    {
        printf("Failed to load stretchign image!\n");
        success = false;
    }

    return success;
}

void close()
{
    //Free loaded image
    SDL_FreeSurface( gStretchedSurface );
    gStretchedSurface == NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow == NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
    //The final optimzed image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if(loadedSurface == NULL)
    {
        printf("Unable to load image &s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        //Convert sufrace to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL);
        if( optimizedSurface == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface);
    }

    return optimizedSurface;
}

int main(int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init())
    {
        printf("Failed to initilize\n");
    }
    else
    {
        //Load Media
        if ( !loadMedia() )
        {
            printf( "Failed to load media!\n");
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while (!quit)
            {
                while( SDL_PollEvent(&e) != 0)

                //User requests quit
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }

                //Apply the image stretched
                SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = SCREEN_WIDTH;
                stretchRect.h = SCREEN_HEIGHT;
                SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);

                //Update the surface
                SDL_UpdateWindowSurface( gWindow);

            }

        }

    }
    close();

    return 0;
}


