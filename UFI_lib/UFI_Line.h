#ifndef UFI_LINE_H
#define UFI_LINE_H

class UFI_Line
{
private:
	SDL_Renderer* private_Rend  = nullptr;
	UFI_Line_t* tempLine_ptr;
	int LineCount = 0;
	int Count = 0;
	
	RenderLineList_t RendLineList;
	
public:
	UFI_Line(int);
	~UFI_Line();
	
	void AddPointsToGraph(SDL_Point*, int);
	void LineInit(SDL_Renderer*);
	
	void NewLine(int, int, int, int, SDL_Color);
	void NewLine(SDL_Point, SDL_Point, SDL_Color);
	void NewLine_Future(SDL_Point, int, SDL_Point, SDL_Color);
	void Display();
};

#endif // UFI_LINE_H
