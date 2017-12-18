#ifndef UFI_TYPES_H
#define UFI_TYPES_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <list>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

/*
 * Function pointer type
 */
typedef void (*Func_ptr)(void);

using EvFlagMask = const Uint64;

struct UFIs_EvFlagMask{
	EvFlagMask Pressed		= 0x00000001;
	EvFlagMask DoubleClk	= 0x00000002;
	EvFlagMask WheelMoved	= 0x00000004;
	EvFlagMask MouseMoved	= 0x00000008;

	EvFlagMask Left		= 0x00000010;
	EvFlagMask Right		= 0x00000020;
	EvFlagMask Mid			= 0x00000040;
	EvFlagMask X1			= 0x00000080;
	EvFlagMask X2			= 0x00000100;

	EvFlagMask Horisontal 	= 0x00000200;
	EvFlagMask Vertical 	= 0x00000400;

	EvFlagMask A1	 		= 0x00004000;
	EvFlagMask A2 			= 0x00008000;
	EvFlagMask A3 			= 0x00010000;
	EvFlagMask A4 			= 0x00020000;
	EvFlagMask A5	 		= 0x00040000;
	EvFlagMask A6 			= 0x00080000;
	EvFlagMask A7 			= 0x00100000;
	EvFlagMask A8 			= 0x00200000;
};

	struct UFIs_MouseButtonAction{
		const Uint32 Pressed	= 0x0001;
		const Uint32 DoubleClk	= 0x0002;
		const Uint32 WheelMoved	= 0x0004;
		const Uint32 MouseMoved	= 0x0008;
			 Uint32 clicks;   /**< 1 for single-click, 2 for double-click, etc. */
	};

	struct UFIs_MouseButton{
		const Uint32 Left	= 0x0010;
		const Uint32 Right	= 0x0020;
		const Uint32 Mid	= 0x0040;
		const Uint32 X1	= 0x0080;
		const Uint32 X2	= 0x0100;
	};

	struct UFIs_MouseScroll{
		int Horisontal = 0;
		int Vertical = 0;
	};

	struct UFIs_MouseCoordinate{
		int x;
		int y;
		SDL_Point Point;
		SDL_Point RelativeXY;
		Uint32 windowID;   		/**< The window with mouse focus, if any */
		SDL_Rect*	Rect = nullptr;/**< The rect with mouse focus, if any */
	};

	struct UFIs_MouseEvent{
		UFIs_MouseScroll		Scroll;
		UFIs_MouseButton		Button;
		UFIs_MouseButtonAction	Action;
		UFIs_MouseCoordinate 	Position;
		Uint32 				Timestamp;
		Uint32				Flags;
	}; 

	struct UFIs_KeyBrdEvent{
		
	};
	
	struct UFIs_TimeEvent{
		Uint64*	Curent = nullptr;
		Uint64 	FromStart = 0;
	};
	
struct UFIs_Event{
	UFIs_MouseEvent	Mouse;
	UFIs_KeyBrdEvent	KeyBoard;
	UFIs_TimeEvent		Time;
};

/*
 * Type for rect points
 */
struct UFI_RectPoints_t{
	SDL_Point		Center;
	SDL_Point		Top_L;
	SDL_Point		Top_R;
	SDL_Point		Bot_L;
	SDL_Point		Bot_R;
};
/*
 * Type for rect
 */
struct UFI_Rect_t{
	SDL_Rect			Output;
	SDL_Rect			Source;
	UFI_RectPoints_t	Point; // must be private or const
};
/*
 * Graph structs
 */
struct UFI_Graph_t{
	std::vector<SDL_Point*> Graph;
};
/*
 * Line structs
 */
struct UFI_Line_t{
	SDL_Color	Color;
	SDL_Point	A;
	SDL_Point	B;
	int			Angle = 0;
	int			Length = 0;
	int			Width = 1; //default
	UFI_Graph_t*ArrPoints;
};

/*
 * Global Type for Rendering process
 */

struct UFI_RenderObject_t{
	const char*			Name = "";
	SDL_Texture*			Texture = nullptr;
	UFI_Rect_t			Rect;
	SDL_BlendMode			TextureBlendMode;
	double				Rotate_angle;
	SDL_Renderer*			Render;
};

//#######################################################
/*
 * Global Colors Set Functions
 */
struct UFI_Color_s{
	inline SDL_Color R(Uint8 red){ return { red, 0, 0, 255 };}
	inline SDL_Color G(Uint8 green){ return { 0, green, 0, 255 };}
	inline SDL_Color B(Uint8 blue){ return { 0, 0, blue, 255 };}
	inline SDL_Color W(Uint8 white){ return { white, white, white, 255 };}
	inline SDL_Color RG(Uint8 r, Uint8 g){ return { r, g, 0, 255 };}
	inline SDL_Color GB(Uint8 g, Uint8 b){ return { 0, g, b, 255 };}
	inline SDL_Color RB(Uint8 r, Uint8 b){ return { r, 0, b, 255 };}
	inline SDL_Color RGB(Uint8 r, Uint8 g, Uint8 b){ return { r, g, b, 255 };}
	inline SDL_Color RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a){ return { r, g, b, a };}
};

//#######################################################

struct UFI_WinParam{
	Uint32 Format;
	int	X;
	int	Y;
	int	W; 
	int	H;
};

//#######################################################

typedef std::list< UFI_RenderObject_t* >	RenderList_t;
typedef std::vector<UFI_RenderObject_t>		RenderVect_t;
typedef std::list< UFI_Line_t* >			RenderLineList_t;
typedef std::list< SDL_Point* >			RenderGraphList_t;

extern RenderList_t			RendList;
extern RenderLineList_t		RendLineList;
extern RenderGraphList_t 	RendGraphList;
//#######################################################
#endif // UFI_TYOES_H