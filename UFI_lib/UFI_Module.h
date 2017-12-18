#ifndef UFI_Module_H
#define UFI_Module_H

class UFI_Event;

class UFI_Button{
protected:
	struct texture_s{
		UFI_Texture*		Texture_ptr = nullptr;
		UFI_TextElement* 	Title_ptr = nullptr;
		bool				IsActiveted = false;
		SDL_Rect*			Rect;
	};
	
	struct callback_s{
		Func_ptr DefaultFunc;
		Func_ptr FocusedFunc;
		Func_ptr PressedFunc;
		Func_ptr DisabledFunc;
	};
	
public:
	UFI_Button();
	~UFI_Button();
	callback_s CallBack;
	
	bool IsButtonActive = false;
	bool IsEngeDetectorActive = false;

	texture_s ButtonDefault;
	texture_s	ButtonFocused;
	texture_s	ButtonPressed;
	texture_s	ButtonDisabled;
};


class UFI_Module: public UFI_Button{
protected:
	  SDL_Renderer*	p_Rend  = nullptr;
	   SDL_Surface*	p_Surf = nullptr;
		const char*	Name;

		UFI_Rect_t	Module_Rect;
		RenderVect_t	RendObjVect;		

std::vector<UFI_Module*>	ModuleVect;
std::vector<UFI_TextElement*>	TextVector;

			   void 	UpdateObject();
public:
					UFI_Module();
					~UFI_Module();
					UFI_Module( const UFI_Module& );
			   void	AddRelativePos(UFI_Texture*);
			   void	AddRelativePos(UFI_TextElement*);
			   void	AddRelativePos(UFI_Module* , int, int);
			   
			   void	SetPosition( int, int );
			   void	SetPositionX( int );
			   void	SetPositionY( int );
			   void	SetScale( float, float); // BAD function, it scales texture all the time
			   void	SetAlpha( Uint8 );
			   void	SetName( const char* );
	 
			   bool	Display();
			   void   DisplayEdges(SDL_Renderer*);
			   
		UFI_Rect_t*    GetRect();
		const char*	GetName();

		 RenderVect_t  GetObjectVec();
std::vector<UFI_TextElement*>	GetTextVector();
};

#endif // UFI_MODULE_H
