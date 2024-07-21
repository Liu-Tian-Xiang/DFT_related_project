//g++ 32_text_input_and_clipboard_handling.cpp `sdl2-config --libs --cflags` -lGL -lGLU -std=c++11 -lSDL2_image -lSDL2_ttf
/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
  and may not be redistributed without written permission.*/

//Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
#define _SDL_TTF_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const char* BuFile[]={"B1.png","B2.png","B3.png"};
//Texture wrapper class
class LTexture
{
    public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile( std::string path );

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor( Uint8 red, Uint8 green, Uint8 blue );

	//Set blending
	void setBlendMode( SDL_BlendMode blending );

	//Set alpha modulation
	void setAlpha( Uint8 alpha );

	//Renders texture at given point
	void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

	//Gets image dimensions
	int getWidth();
	int getHeight();

    private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//Scene textures
LTexture gPromptTextTexture;
LTexture gInputTextTexture;
LTexture gButton;
LTexture gPicture;

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    free();

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
	//Color key image
	SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
	if( newTexture == NULL )
	{
	    printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}
	else
	{
	    //Get image dimensions
	    mWidth = (loadedSurface->w<=SCREEN_WIDTH?loadedSurface->w:SCREEN_WIDTH/2);
	    mHeight = (loadedSurface->h<=SCREEN_HEIGHT?loadedSurface->h:SCREEN_HEIGHT/2);
	}

	//Get rid of old loaded surface
	SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface != NULL )
    {
	//Create texture from surface pixels
	mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
	if( mTexture == NULL )
	{
	    printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
	}
	else
	{
	    //Get image dimensions
	    mWidth = textSurface->w;
	    mHeight = textSurface->h;
	}

	//Get rid of old surface
	SDL_FreeSurface( textSurface );
    }
    else
    {
	printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }


    //Return success
    return mTexture != NULL;
}
#endif

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
	SDL_DestroyTexture( mTexture );
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
	renderQuad.w = clip->w;
	renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 & IMG_Init(IMG_INIT_PNG)<0)
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
	gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( gWindow == NULL )
	{
	    printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	    success = false;
	}
	else
	{
	    //Create vsynced renderer for window
	    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
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

		//Initialize SDL_ttf
		if( TTF_Init() == -1 )
		{
		    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
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

    //Open the font
    gFont = TTF_OpenFont( "lazy.ttf", 28 );
    if( gFont == NULL )
    {
	printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	success = false;
    }
    else
    {
	//Render the prompt
	SDL_Color textColor = { 0, 0, 0, 0xFF };
	if( !gPromptTextTexture.loadFromRenderedText( "Enter Text:", textColor ) )
	{
	    printf( "Failed to render prompt text!\n" );
	    success = false;
	}

	if( !gButton.loadFromFile(BuFile[0] ) )
	{
	    printf( "Failed to render prompt text!\n" );
	    success = false;
	}

	if( !gPicture.loadFromFile("BG.png" ) )
	{
	    printf( "Failed to render prompt text!\n" );
	    success = false;
	}

    }

    return success;
}

void close()
{
    //Free loaded images
    gPromptTextTexture.free();
    gInputTextTexture.free();
    gButton.free();
    gPicture.free();

    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;

    //Destroy window	
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool isOnButton(Uint32 x,Uint32 y){
    if (x>=0&&x<=64)
	if (y>=0&&y<=64)    return true;
    return false;
}

int main( int argc, char* args[] )
{
    Uint32 Buttonnow=0;
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

	    //Set text color as black
	    SDL_Color textColor = { 0, 0, 0, 0xFF };

	    //The current input text.
	    std::string inputText = "So me Text";
	    gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );

	    //Enable text input
	    SDL_StartTextInput();

	    //While application is running
	    while( !quit )
	    {
		//The rerender text flag
		bool renderText = false;

		//Handle events on queue
		while (SDL_PollEvent( &e ) != 0){

		    switch (e.type){
			case SDL_QUIT:
			    quit=true;
			    break;
			case SDL_MOUSEBUTTONDOWN:
			    if (e.button.button==SDL_BUTTON_LEFT)
				if (isOnButton(e.button.x,e.button.y))
				    if (Buttonnow!=2){
					if (!gButton.loadFromFile(BuFile[2] )) printf( "Failed to initialize!\n" );
					Buttonnow=2;
				    }
			    break;
			case SDL_MOUSEMOTION:
			    if (isOnButton(e.button.x,e.button.y)){
				if (Buttonnow!=1){
				    if (!gButton.loadFromFile(BuFile[1] )) printf( "Failed to initialize!\n" );

				    Buttonnow=1;
				}}else
			    if (Buttonnow!=0){
				if (!gButton.loadFromFile(BuFile[0] )) printf( "Failed to initialize!\n" );

				Buttonnow=0;
			    }
			    break;
			case SDL_MOUSEBUTTONUP:
			    if (isOnButton(e.button.x,e.button.y)){
				if (Buttonnow!=1){
				    //if (!gButton.loadFromFile(BuFile[1] )) printf( "Failed to initialize!\n" );
				    if (gButton.loadFromFile(BuFile[1] )) system("pwd");
				    gPicture.loadFromFile("data_V1.png" );

				    Buttonnow=1;
				}}else
			    if (Buttonnow!=0){
				if (!gButton.loadFromFile(BuFile[0] )) printf( "Failed to initialize!\n" );

				Buttonnow=0;
			    }
			    break;
			case SDL_KEYDOWN:
			    //Handle backspace
			    if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
			    {
				//lop off character
				inputText.pop_back();
				renderText = true;
			    }
			    //Handle copy
			    else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
			    {
				SDL_SetClipboardText( inputText.c_str() );
			    }
			    //Handle paste
			    else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
			    {
				inputText = SDL_GetClipboardText();
				renderText = true;
			    }
			    break;
			case SDL_TEXTINPUT:
			    if( !( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
			    {
				//Append character
				inputText += e.text.text;
				renderText = true;
			    }
		    }
		    //Rerender text if needed
		    if( renderText )
		    {
			//Text is not empty
			if( inputText != "" )
			{
			    //Render new text
			    gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );
			}
			//Text is empty
			else
			{
			    //Render space texture
			    gInputTextTexture.loadFromRenderedText( " ", textColor );
			}
		    }

		    //Clear screen
		    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		    SDL_RenderClear( gRenderer );

		    //Render text textures
		    gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, 0 );
		    gButton.render( 0, 0 );
		    gPicture.render( 0, gButton.getHeight());
		    gInputTextTexture.render( ( SCREEN_WIDTH - gInputTextTexture.getWidth() ) / 2, gPromptTextTexture.getHeight() );

		    //Update screen
		    SDL_RenderPresent( gRenderer );

	    }
	}			
	//Disable text input
	SDL_StopTextInput();

    }
}

//Free resources and close SDL
close();

return 0;
}
