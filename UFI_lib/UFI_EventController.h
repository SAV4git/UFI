#ifndef UFI_EVENTCONTROLLER_H
#define UFI_EVENTCONTROLLER_H

class UFI_Module;
class UFI_Button;
class UFI_Texture;
class UFI_TextElement;

using EvFlag = Uint64;

class UFI_Mouse
{
private:
	SDL_Cursor*		cursor_X;
	SDL_Cursor*		cursor_arrow;
	
public:
	// Create function which will hold stuff
	
	// Create cursors
	//cursor_X = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	//cursor_arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
};

class UFI_Keyboard
{
public:
	std::string text = " ";
	char * composition;
	Sint32 cursor;
	Sint32 selection_len;
};

extern UFI_Mouse	Mouse;
extern UFI_Keyboard	KeyB;

/*
 * Events for Mouse,  
 * 
 */
class UFI_Event{
private:
	
	struct EvStruct{
		Func_ptr 		Func = nullptr;
		EvFlag		Flags;
	};
	
	EvStruct EventStruct;
	
	std::list<EvStruct>	EvStructList;

public:
	void PrintFlags();
	void SetEvFlags(EvFlag);
	void	SetCallBack(Func_ptr);
	UFIs_MouseEvent	Mouse;
	UFIs_KeyBrdEvent	KeyBoard;
	
	bool PassedFlagsCheck();
	bool IsInRect();
	bool IsInRect(SDL_Rect*);
	
	UFI_Event* GetEv();
};

/*
 * Events Hendler
 * 
 */
class UFI_EventHendler
{
protected:
	SDL_Renderer*	private_Rend = NULL;
	
	std::vector< UFI_Module* > 	ButtonVect;
	std::vector< UFI_Button >	ButtonActionVect;
	std::vector< UFI_Texture*>	TextureVect;
	std::vector< SDL_Rect >		RectVect;
	
	EvFlag EvFlags;
	
	UFI_Event Ev_MouseClickButton;
	UFI_Event Ev_MouseInButton;
	
	void VirtualButtonHandler();
	
	void TextEditHandler();
	void TextInputHandler();
	void Motion_Handler();
	void ButtonDown_Handler();
	void ButtonUp_Handler();
	void Wheel_Handler();
	void CheckFlags();
	
	bool IsMouseInside = false;
	bool IsMouseInsideRect = false;
	
public:
	UFI_EventHendler();
	~UFI_EventHendler();
	void RunEventHendler( SDL_Renderer* );
	void AddButtonPressed( SDL_Renderer*, UFI_Module*, UFI_TextElement*, Func_ptr);
	void AddButtonFocused( SDL_Renderer*, UFI_Module*, UFI_TextElement*, Func_ptr);
	void AddButtonDefault( SDL_Renderer*, UFI_Module*, UFI_TextElement*);
	EvFlag GetFlags();
};

#endif // UFI_EVENTCONTROLLER_H
