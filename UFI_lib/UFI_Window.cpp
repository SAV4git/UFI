#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../UFI_lib/UFI_Types.h"
#include "../UFI_lib/UFI_EventController.h"
#include "../UFI_lib/UFI_Window.h"

UFI_Window::UFI_Window(){
	WinParam.X = 25;
	WinParam.Y = 25;
	WinParam.W = 100; 
	WinParam.H = 100;
	
	renderTime = 0;
	renderTimeStart = SDL_GetPerformanceCounter();
	renderTimeEnd = 0;
	
}


UFI_Window::~UFI_Window()
{
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(p_renderer);
	TTF_Quit();
	SDL_Quit();
	
}


void UFI_Window::InitSDL(void)
{
	//-----------------------------------------------------------------------
	// Initialization of SDL2
	//-----------------------------------------------------------------------
	State = SDL_Init(SDL_INIT_VIDEO);
	
	display_mode_count = SDL_GetNumDisplayModes(display_in_use);
	
	// Init SDL text
	//-----------------------------------------------------------------------
	TTF_Init();
}


void UFI_Window::CreateWithSize(int w, int h)
{
	InitSDL();
	
	WinParam.W = w;
	WinParam.H = h;
	
	if (State == 0){
		win = SDL_CreateWindow("Default Window", WinParam.X, WinParam.Y, WinParam.W, WinParam.H, 0);
		if (win){ loop = true; }
		else {
			printf("Here could be your perfect window, but you have failed to do it\n");
		}
	}
	else{
		printf("Something went HORRIBLY WRONG with SDL_Init\n");
	}
}


void UFI_Window::CreateFullscreen()
{
	InitSDL();
	
	if (State == 0){
		
		win = SDL_CreateWindow("Default Window", WinParam.X, WinParam.Y, WinParam.H, WinParam.H, 0);
		
		//SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN); //REAL
		SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP); //FAKE
		
		if (win){ loop = true; }
		else {
			printf("Here could be your perfect window, but you have failed to do it\n");
		}
	}
	else{
		printf("Something went HORRIBLY WRONG with SDL_Init\n");
	}
	
	WinParam.H = Mode.h; 
	WinParam.W = Mode.w;
}

void UFI_Window::SetPosition(int x, int y)
{
	SDL_SetWindowPosition(this->win, x, y);
	WinParam.X = x;
	WinParam.Y = y;
}


void UFI_Window::SetTitle(const char* title)
{
	SDL_SetWindowTitle(win, title);
}


bool UFI_Window::IsOpen()
{
	if(this->win != nullptr) return loop;
	else return false;
}


bool UFI_Window::Close()
{
	if(this->win != nullptr){
		loop = false;
		SDL_DestroyRenderer(this->p_renderer);
		SDL_DestroyWindow(this->win);
	}
	
	return this->loop;
}

UFI_WinParam* UFI_Window::GetWinParam()
{
	return &WinParam;
}
SDL_Window* UFI_Window::GetWin_ptr()
{
	return win;
}
void UFI_Window::GetInfo()
{
	cout << "INFO - START" << endl << endl;
	
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		  compiled.major, compiled.minor, compiled.patch);
	printf("But we are linking against SDL version %d.%d.%d.\n\n",
		  linked.major, linked.minor, linked.patch);
	//-----------------------------------------------------------------------
	// Check displays and count
	//-----------------------------------------------------------------------
	SDL_Log("SDL_GetNumVideoDisplays(): %i", SDL_GetNumVideoDisplays());

	display_mode_count = SDL_GetNumDisplayModes(display_in_use);
	
	if (display_mode_count < 1) {
		SDL_Log("SDL_GetNumDisplayModes failed: %s", SDL_GetError());
	}
	SDL_Log("SDL_GetNumDisplayModes: %i", display_mode_count);
	
	cout << endl;
	
	for (i = 0; i < display_mode_count; ++i) {
		if (SDL_GetDisplayMode(display_in_use, i, &Mode) != 0) {
			SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
		}
		WinParam.Format = Mode.format;

		SDL_Log(
			"Mode %i\tbpp %i\t%s\t%i x %i",
			i,
			SDL_BITSPERPIXEL(Mode.format),
			SDL_GetPixelFormatName(Mode.format),
			Mode.w,
			Mode.h
		);
	}
	
	//-----------------------------------------------------------------------
	//	SDL_GetCurrentVideoDriver
	//-----------------------------------------------------------------------
	cout << endl << "CurrentVideoDriver: " << SDL_GetCurrentVideoDriver() << endl << endl;
	//-----------------------------------------------------------------------
	cout << "INFO - END" << endl << endl;
}


SDL_Renderer* UFI_Window::CreateRender()
{
	p_renderer = SDL_CreateRenderer( this->win, -1, SDL_RENDERER_ACCELERATED );
	SDL_RenderSetLogicalSize( p_renderer, this->WinParam.W, this->WinParam.H );
	return p_renderer;
}


void UFI_Window::RenderStartFPS(int fps)
{
	if(this->win != nullptr){
		renderTime = renderTimeEnd - renderTimeStart;
		renderTime_ms = renderTime/1000000;
	
		if(renderTime_ms > (Uint32)1000/fps) printf("RenderTime: %d \n ", renderTime_ms );
		else SDL_Delay((Uint32) (1000/fps) - renderTime_ms );
	
		SDL_RenderClear( p_renderer );
		renderTimeStart = SDL_GetPerformanceCounter();
	}
}

void UFI_Window::RenderEnd()
{
	if(this->win != nullptr){
		SDL_RenderPresent( p_renderer );
		renderTimeEnd = SDL_GetPerformanceCounter();
	}
}

SDL_Renderer* UFI_Window::GetRender()
{
	return p_renderer;
}
