#ifndef UFI_WINDOW_H
#define UFI_WINDOW_H

class UFI_Window{
protected:
	SDL_Window*		win = nullptr;
	SDL_Renderer*		p_renderer = nullptr;
	
	SDL_DisplayMode	Mode;
	int 				display_in_use = 0; /* Only using first display */
	int 				i, display_mode_count;
	
	int 		State;
	bool 	loop = false;
	
	Uint64 renderTime = 0;
	Uint32 renderTime_ms = 0;
	
	Uint64 renderTimeStart = 0;
	Uint64 renderTimeEnd = 0;
	
	UFI_WinParam WinParam;
	
	void InitSDL(void);
public:
	
	UFI_Window();
	~UFI_Window();
	void CreateWithSize(int, int);
	void CreateFullscreen();
	void SetPosition(int, int);
	void SetTitle(const char*);
	bool IsOpen();
	SDL_Renderer* CreateRender();
	void RenderStartFPS(int);
	void RenderEnd();
	bool Close();
	
	void 		GetInfo();
	UFI_WinParam*	GetWinParam();
	SDL_Window*	GetWin_ptr();
	SDL_Renderer*  GetRender();
};

#endif // UFI_WINDOW_H
