//chess.cpp
//
//plays game of chess

//Using SDL, SDL_image, standard IO, math, and strings

#include <cmath>
#include "LTexture.h"
#include "board.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene sprites
SDL_Rect gSpriteClips[ CLIPNUM ];
LTexture gSpriteSheetTexture;

bool init()
{
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    success = false;
  }
  else
  {
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
      printf( "Warning: Linear texture filtering not enabled!" );
    }

    //Create window
    gWindow = SDL_CreateWindow( "Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SIDE, SIDE, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
      printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
      success = false;
    }
    else
    {
      //Create renderer for window
      gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
      if( gRenderer == NULL )
      {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        success = false;
      }
      else
      {
        //Initialize renderer color
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
          printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
          success = false;
        }
      }
    }
  }

  return success;
}

bool loadMedia()
{
  //Loading success flag
  bool success = true;

  //Load sprite sheet texture
  if( !gSpriteSheetTexture.loadFromFile( gRenderer, "Chess_Sprites.png" ) )
  {
    printf( "Failed to load sprite sheet texture!\n" );
    success = false;
  }
  else
  {
    for(int i = 0; i < CLIPNUM; i++)
    {
      gSpriteClips[ i ].x = 83*(i%6);
      gSpriteClips[ i ].y = 83*(i/6);
      gSpriteClips[ i ].w = 83;
      gSpriteClips[ i ].h = 83;
    }
  }

  return success;
}

void close()
{
  //Free loaded images
  gSpriteSheetTexture.free();

  //Destroy window  
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  gRenderer = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
  //The final texture
  SDL_Texture* newTexture = NULL;

  //Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  if( loadedSurface == NULL )
  {
    printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
  }
  else
  {
    //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    if( newTexture == NULL )
    {
      printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
  }

  return newTexture;
}

int main( int argc, char* args[] )
{
  //Start up SDL and create window
  if( !init() )
  {
    printf( "Failed to initialize!\n" );
  }
  else
  {
    //Load media
    if( !loadMedia() )
    {
      printf( "Failed to load media!\n" );
    }
    else
    {  
      //Main loop flag
      bool quit = false;
      
      //Event handler
      SDL_Event e;

      Board chessBoard;

      //Clear screen
      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
      SDL_RenderClear( gRenderer );

      chessBoard.display(gRenderer, gSpriteSheetTexture, gSpriteClips );

      //Update screen
      SDL_RenderPresent( gRenderer );

      bool gameOver = false;

      //While application is running
      while( !quit )
      {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
          //User requests quit
          if( e.type == SDL_QUIT )
            quit = true;
          // Mouse Click  
          if(!gameOver && e.type == SDL_MOUSEBUTTONDOWN) {
       
            chessBoard.handleEvent( &e );

	    if( chessBoard.noMoves() )
	      gameOver = true;

            //Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
        
            chessBoard.display(gRenderer, gSpriteSheetTexture, gSpriteClips );

            //Update screen
            SDL_RenderPresent( gRenderer );
          }
        }
      }
    }
  }
  //Free resources and close SDL
  close();

  return 0;
}
