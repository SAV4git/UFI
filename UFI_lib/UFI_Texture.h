#ifndef UFI_TEXTURE_H
#define UFI_TEXTURE_H

#include <SDL2/SDL_ttf.h>

/*######################################################
 *     Class UFI_Texture
 * _____________________________________________________
 */
class UFI_Texture
{
private:
	SDL_Renderer*				p_Rend = nullptr;
	SDL_Surface*				p_Surf = nullptr;
	char*					Name;
	const char*				FilePath;
	
	UFI_RenderObject_t*			RendObj_ptr = nullptr;
	UFI_RenderObject_t			RendObj;
	
	void CreateRendObjFromSurface(SDL_Surface*);
	
public:
	UFI_Texture();
	~UFI_Texture();
	UFI_Texture(const UFI_Texture &);
	void CreateTextureBMP(SDL_Renderer*, const char* );
	void CreateTextureJPG(SDL_Renderer*, const char* );
	void CreateTexturePNG(SDL_Renderer*, const char* );
	void CreateTextureRGBA(SDL_Renderer*, SDL_Color);
	UFI_Texture* SetSprite( int, int, int, int);
	UFI_Texture* SetOutputSize( int, int);
	UFI_Texture* SetPosition( int, int); 
	UFI_Texture* SetPositionX( int); 
	UFI_Texture* SetPositionY( int); 
	UFI_Texture* SetAlpha( Uint8);
	UFI_Texture* SetRGBA(SDL_Color);
	void SetObject( UFI_RenderObject_t* );
	
	// Add function to change the renderer
	
	UFI_RenderObject_t* GetObject();
	
	void Display();
};

/*######################################################
 *     Class UFI_TextElement
 * _____________________________________________________
 */
class UFI_TextElement
{
private:
	SDL_Renderer* 	p_Rend = nullptr;
	SDL_Surface* 	p_Surf = nullptr;
	SDL_Texture* 	p_Tx = nullptr;
	
	TTF_Font*		p_font = nullptr;
	TTF_Font*		p_simple_font = nullptr;
	SDL_Color		p_colour;

	UFI_RenderObject_t	RendObj;
	
	int 			p_font_size = 30;
	
	const char*		p_text = " ";
	const char* 		p_file_font = nullptr;
	
	bool NeedUpdate(int, int );
	void OpenFont();
	void UpdateFont();
public:
	UFI_TextElement();
	~UFI_TextElement();
	UFI_TextElement( const UFI_TextElement& );
	UFI_TextElement* CreateTextureFont(SDL_Renderer*, const char*);
	UFI_TextElement* CreateSimpleText(SDL_Renderer*, const char*, int );
	UFI_TextElement* SetSimpleText(const char*, int, int);
	UFI_TextElement* SetTextSetSize(const char*, int);
	UFI_TextElement* SetFontSize( int);
	UFI_TextElement* SetText( const char*);
	UFI_TextElement* SetPosition(int, int);
	UFI_TextElement* SetPositionX(int);
	UFI_TextElement* SetPositionY(int);
	UFI_TextElement* SetTextColor( Uint8, Uint8, Uint8, Uint8);
	UFI_TextElement* SetAlpha( Uint8);
	const char* GetText();
	UFI_RenderObject_t* GetObject();
	
	void Display();
	void DisplayEdges(SDL_Renderer*);
};
/*######################################################
 *     Class UFI_PixelMap
 * _____________________________________________________
 */
class UFI_PixelMap{
private:
	SDL_Renderer*				p_Rend = NULL;
	SDL_Surface*				p_Surf = NULL;
	
	UFI_RenderObject_t*			RendObj_ptr = NULL;
	UFI_RenderObject_t			RendObj;
	
	Uint32* 					Pixels_ptr;
	
public:
	void CreatePixelMapRGB(SDL_Renderer*);
	void CreatePixelMapRGBA(SDL_Renderer*);
	void SetSize(int, int);
	void SetPosition(int, int);
	void Update(Uint32*);
	
	UFI_RenderObject_t* GetObject();
	
	void Display();
};

/*######################################################
 *     Class UFI_LineElement
 * _____________________________________________________
 */
class UFI_LineElement
{
private:
	SDL_Renderer*			p_Rend = nullptr;
	SDL_Surface*			p_Surf = nullptr;
	
	UFI_RenderObject_t*		RendObjLine_ptr = nullptr;
	UFI_RenderObject_t		RendObj;
public:

	UFI_LineElement();
	~UFI_LineElement();
	void CreateLineTextureFromBMP(SDL_Renderer*, const char* );
	void SetSize( int, int);
	void SetPosition( int, int);
	void SetAlpha( Uint8);
	UFI_RenderObject_t* GetObject();
};

#endif // UFI_TEXTURE_H
