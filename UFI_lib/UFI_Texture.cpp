#include <iostream>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../UFI_lib/UFI.h"
#include "../UFI_lib/UFI_Types.h"
#include "../UFI_lib/UFI_Texture.h"
#include "../UFI_lib/UFI_ImageLoader.h"

using std::cout;
using std::endl;

/*######################################################
 *     Class UFI_Texture
 * _____________________________________________________
 */
UFI_Texture::UFI_Texture(){
	
	RendObj_ptr = &RendObj;
	static int N = 0;
	N++;
	this->RendObj.Name = "default";
	std::cout<<"Object UFI_Texture Created #" << N << ", ptr=" << this << endl;
	//cout << ">Texture Created with name - <" << RendObj.Name << ">\n";
}
UFI_Texture::~UFI_Texture(){
	if(!RendObj.Texture) SDL_DestroyTexture( RendObj.Texture );
 	//cout << " > Texture Killed with name - <" << RendObj.Name << ">\n";
}

UFI_Texture::UFI_Texture(const UFI_Texture &copy){
	this->p_Rend = copy.p_Rend;
	//this->p_Surf = copy.p_Surf;
	this->RendObj.Name = copy.RendObj.Name;
	this->RendObj.Rect.Output.x = copy.RendObj.Rect.Output.x;
	this->RendObj.Rect.Output.y = copy.RendObj.Rect.Output.y;
	this->RendObj.Rect.Output.w = copy.RendObj.Rect.Output.w;
	this->RendObj.Rect.Output.h = copy.RendObj.Rect.Output.h;
	
	this->RendObj.Rect.Source.x = copy.RendObj.Rect.Source.x;
	this->RendObj.Rect.Source.y = copy.RendObj.Rect.Source.y;
	this->RendObj.Rect.Source.w = copy.RendObj.Rect.Source.w;
	this->RendObj.Rect.Source.h = copy.RendObj.Rect.Source.h;
	
	this->RendObj.Render = copy.RendObj.Render;
	this->RendObj.Rotate_angle = copy.RendObj.Rotate_angle;
	this->RendObj.Texture = copy.RendObj.Texture;
	this->RendObj.TextureBlendMode = copy.RendObj.TextureBlendMode;
	this->Name = copy.Name;
}

void UFI_Texture::CreateRendObjFromSurface(SDL_Surface* Surf){
	
	RendObj.Texture = SDL_CreateTextureFromSurface(p_Rend, Surf);
	
	RendObj.Rect.Source.x = 0;
	RendObj.Rect.Source.y = 0;
	RendObj.Rect.Source.w = Surf->w;
	RendObj.Rect.Source.h = Surf->h;
	
	RendObj.Rect.Output.w = Surf->w;
	RendObj.Rect.Output.h = Surf->h;
	
	RendObj.TextureBlendMode = SDL_BLENDMODE_BLEND;
	if( FilePath != nullptr ) cout << ">Texture Created with name - <" << FilePath << ">\n";
	
	CalculatePoints( &RendObj );
}


void UFI_Texture::CreateTextureBMP(SDL_Renderer *p_rend, const char* file){
	p_Rend = p_rend;
	RendObj.Render = p_rend;
	FilePath = file;
	Name = (char*) file; //Default Name
	
	p_Surf = SDL_LoadBMP(file);
	CreateRendObjFromSurface(p_Surf);
	
	SDL_FreeSurface(p_Surf);
	p_Surf = nullptr;
}
void UFI_Texture::CreateTextureJPG(SDL_Renderer *p_rend, const char* file){
	
	p_Rend = p_rend;
	RendObj.Render = p_rend;
	FilePath = file;
	Name = (char*) file; //Default Name
	
	p_Surf = load_surface_jpeg(file);
	CreateRendObjFromSurface(p_Surf);
	
	SDL_FreeSurface(p_Surf);
	p_Surf = nullptr;
}
void UFI_Texture::CreateTexturePNG(SDL_Renderer *p_rend, const char* file){
	
	p_Rend = p_rend;
	RendObj.Render = p_rend;
	FilePath = file;
	Name = (char*) file; //Default Name
	
	p_Surf = load_surface_png(file);
	CreateRendObjFromSurface(p_Surf);
	
	SDL_FreeSurface(p_Surf);
	p_Surf = nullptr;
}

void UFI_Texture::CreateTextureRGBA(SDL_Renderer *p_rend, SDL_Color color){
	
	p_Rend = p_rend;
	RendObj.Render = p_rend;
	
	Uint32 rmask, gmask, bmask, amask;
	Uint32 width = 100, height = 100; //Default
     /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	    rmask = 0xff000000;
	    gmask = 0x00ff0000;
	    bmask = 0x0000ff00;
	    amask = 0x000000ff;
	#else
	    rmask = 0x000000ff;
	    gmask = 0x0000ff00;
	    bmask = 0x00ff0000;
	    amask = 0xff000000;
	#endif

	p_Surf = SDL_CreateRGBSurface(
		0, width, height, 32,
		rmask, gmask, bmask, amask
	);
		
	if (p_Surf == nullptr) {
	   SDL_Log("SDL_CreateRGBSurface() failed: %p_Surf", SDL_GetError());
	   exit(1);
	}
	
	/* Filling the surface with red color. */
	SDL_FillRect(p_Surf, NULL, SDL_MapRGB(p_Surf->format, color.r, color.g, color.b));
	
	CreateRendObjFromSurface(p_Surf);
}


UFI_Texture* UFI_Texture::SetSprite( int x, int y, int w, int h){
	
	RendObj.Rect.Source.x = x;
	RendObj.Rect.Source.y = y;
	RendObj.Rect.Source.w = w;
	RendObj.Rect.Source.h = h;
	
	if( SDL_RectEmpty( &RendObj.Rect.Source) ){
		cout << "Rect Empty" << endl;
		exit(1);
	}
	
	CalculatePoints(&RendObj);
	return this;
}
UFI_Texture* UFI_Texture::SetOutputSize( int w, int h ){
	
	RendObj.Rect.Output.w = w;
	RendObj.Rect.Output.h = h;
	
	if( SDL_RectEmpty( &RendObj.Rect.Output) ){
		printf("Rect Empty\n");
		exit(1);
	}
	
	CalculatePoints(&RendObj);
	return this;
}
UFI_Texture* UFI_Texture::SetPosition( int x, int y ){
	RendObj.Rect.Output.x = x;
	RendObj.Rect.Output.y = y;
	CalculatePoints(&RendObj);
	return this;
}
UFI_Texture* UFI_Texture::SetPositionX( int x){
	RendObj.Rect.Output.x = x;
	CalculatePoints(&RendObj);
	return this;
}
UFI_Texture* UFI_Texture::SetPositionY( int y ){
	RendObj.Rect.Output.y = y;
	CalculatePoints(&RendObj);
	return this;
}
UFI_Texture* UFI_Texture::SetAlpha( Uint8 a){
	
	SDL_SetTextureAlphaMod(RendObj.Texture, a);
	return this;
}

UFI_Texture* UFI_Texture::SetRGBA(SDL_Color color){
	/* Filling the surface with red color. */
	if (p_Surf == nullptr) {
	   SDL_Log("SDL_CreateRGBSurface() failed: %p_Surf", SDL_GetError());
	   cout << "Texture color can't change or it is a file and it can't change color" << endl << endl;
	   exit(1);
	}

	//SDL_FillRect(p_Surf, NULL, SDL_MapRGB(p_Surf->format, color.r, color.g, color.b));
	SDL_SetTextureColorMod( RendObj.Texture, color.r, color.g, color.b );
	SDL_SetTextureAlphaMod( RendObj.Texture, color.a);
	return this;
}

void UFI_Texture::SetObject(UFI_RenderObject_t* Obj){
	RendObj = *Obj;
}

UFI_RenderObject_t* UFI_Texture::GetObject(){
	return &RendObj;
}

void UFI_Texture::Display(){
	
	SDL_SetRenderDrawBlendMode( RendObj.Render, RendObj.TextureBlendMode);
	if(  RendObj.Rotate_angle == false){	//rendering textures
		SDL_RenderCopy( 
			RendObj.Render,	
			RendObj.Texture, 
			&RendObj.Rect.Source,
			&RendObj.Rect.Output
		);
	}else{
		SDL_RenderCopyEx(    				//Sloooooooow func
			RendObj.Render,	
			RendObj.Texture,
			&RendObj.Rect.Source,
			&RendObj.Rect.Output,
			RendObj.Rotate_angle,
			NULL,
			SDL_FLIP_NONE
		);
	}
}















void UFI_PixelMap::CreatePixelMapRGBA(SDL_Renderer* p_rend){
	RendObj.Render = p_rend;
	
	Uint32 rmask, gmask, bmask, amask;
	Uint32 width = 100, height = 100; //Default
     /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	    rmask = 0xff000000;
	    gmask = 0x00ff0000;
	    bmask = 0x0000ff00;
	    amask = 0x000000ff;
	#else
	    rmask = 0x000000ff;
	    gmask = 0x0000ff00;
	    bmask = 0x00ff0000;
	    amask = 0xff000000;
	#endif

	p_Surf = SDL_CreateRGBSurface(
		0, width, height, 32,
		rmask, gmask, bmask, amask
	);
		
	if (p_Surf == nullptr) {
	   SDL_Log("SDL_CreateRGBSurface() failed: %p_Surf", SDL_GetError());
	   exit(1);
	}
	
	/* Filling the surface with red color. */
	SDL_FillRect(p_Surf, NULL, SDL_MapRGBA(p_Surf->format, 0, 0, 0, 0));
	
	p_Surf = SDL_ConvertSurfaceFormat(p_Surf, SDL_PIXELFORMAT_ARGB8888, 0);
	
	RendObj.Texture = SDL_CreateTextureFromSurface(p_Rend, p_Surf);
	
	RendObj.Rect.Source.x = 0;
	RendObj.Rect.Source.y = 0;
	RendObj.Rect.Source.w = p_Surf->w;
	RendObj.Rect.Source.h = p_Surf->h;
	
	RendObj.Rect.Output.x = 1;
	RendObj.Rect.Output.y = 1;
	RendObj.Rect.Output.w = p_Surf->w;
	RendObj.Rect.Output.h = p_Surf->h;
	
	Pixels_ptr = new Uint32[p_Surf->w*p_Surf->h];
	
	CalculatePoints(RendObj_ptr);
}

void UFI_PixelMap::SetSize(int w, int h){
	RendObj.Rect.Source.w = p_Surf->w;
	RendObj.Rect.Source.h = p_Surf->h;
	
	RendObj.Rect.Output.w = w;
	RendObj.Rect.Output.h = h;
}

void UFI_PixelMap::SetPosition(int x, int y){
	RendObj.Rect.Source.x = 0;
	RendObj.Rect.Source.y = 0;
	
	RendObj.Rect.Output.x = x;
	RendObj.Rect.Output.y = y;
}

void UFI_PixelMap::Update(Uint32* pixels){
	for( int i = 0; i < RendObj.Rect.Output.h*RendObj.Rect.Output.w; i++){
		Pixels_ptr[i] = pixels[i];
	}

	SDL_UpdateTexture(
		RendObj.Texture, 
		&RendObj.Rect.Output, 
		pixels, 
		RendObj.Rect.Output.w*sizeof(Uint32)
	);
}














/*######################################################
 *     Class UFI_TextElement
 * _____________________________________________________
 */
UFI_TextElement::UFI_TextElement(){
	static int N = 0;
	//p_text = new char[255];
	//p_file_font = new char[255];
	
	N++;
	//RendObj.Name = p_text;
	std::cout<<"Object UFI_TextElement Created #" << N << ", ptr=" << this << endl;
	//cout << " > Text Texture Created with name - <" << RendObj.Name <<">\n";
}


UFI_TextElement::~UFI_TextElement(){
	
	if(!RendObj.Texture) SDL_DestroyTexture( RendObj.Texture );
}
UFI_TextElement::UFI_TextElement(const UFI_TextElement& copy){
	
	p_simple_font = copy.p_simple_font;
	p_font_size = copy.p_font_size;
	p_file_font = copy.p_file_font;
	p_text = copy.p_text;
	
	p_Rend = copy.p_Rend;
	RendObj.Render = copy.RendObj.Render;
	RendObj.TextureBlendMode = copy.RendObj.TextureBlendMode;
	RendObj.Name = copy.RendObj.Name;
	
	p_colour.a = copy.p_colour.a;
	p_colour.r = copy.p_colour.r;
	p_colour.g = copy.p_colour.g;
	p_colour.b = copy.p_colour.b;
	
	cout << "copy created" << endl;
	
	UpdateFont();
}


bool UFI_TextElement::NeedUpdate(int old_data, int new_data){
	if( old_data != new_data) return true;
	else return false;
}


void UFI_TextElement::OpenFont(){
	p_font = TTF_OpenFont( p_file_font, p_font_size );
	
	if(!p_font) 
	{
		cout << "\n   Error - TTF_OpenFont:" << TTF_GetError() << "\n\n";
		cout << "\n   Check if <" << p_file_font << "> is in folder\n\n";
		TTF_CloseFont(p_font);
		exit(1);
	}
}


void UFI_TextElement::UpdateFont(){
	OpenFont();

	p_Surf = TTF_RenderText_Blended( p_font, p_text, p_colour );
	SDL_DestroyTexture(RendObj.Texture);
	
	RendObj.Texture = SDL_CreateTextureFromSurface( p_Rend, p_Surf );
	
	RendObj.Rect.Source = p_Surf->clip_rect;
	
	SDL_QueryTexture(	RendObj.Texture, 
						NULL, 
						NULL, 
						&RendObj.Rect.Output.w, 
						&RendObj.Rect.Output.h );
	
	CalculatePoints(&RendObj);
	
	SDL_FreeSurface(p_Surf);
	TTF_CloseFont(p_font);
}


UFI_TextElement* UFI_TextElement::CreateTextureFont(SDL_Renderer *p_rend, const char * file_font){
	
	p_Rend = p_rend;
	RendObj.Render = p_rend;
	
	p_file_font = file_font;
	
	printf("File path %s, file_font %s", p_file_font, file_font);
	p_text = " blended default ";
	this->RendObj.Name = " blended default ";
	
	p_colour = { 255, 0, 0, 255 }; // def
	
	UpdateFont();
	return this;
}


UFI_TextElement* UFI_TextElement::CreateSimpleText(SDL_Renderer *p_rend, const char* file_font, int ptsize ){
	
	if(!NeedUpdate(p_font_size, ptsize)) return this;
	
	p_Rend = p_rend;
	RendObj.Render = p_rend;
	
	p_file_font = file_font;
	p_font_size = ptsize;
	p_text = " simple default ";
	this->RendObj.Name = " simple default ";
	
	p_colour = { 255, 255, 255, 255 };
	
	UpdateFont();// def
	return this;
}


UFI_TextElement*  UFI_TextElement::SetSimpleText (const char *text, int x, int y){
	if(!(NeedUpdate(RendObj.Rect.Output.x, x)||
		NeedUpdate(RendObj.Rect.Output.y, y))) return this;
		
	p_text = text;
	this->RendObj.Name = text;
	
	RendObj.Rect.Output.x = x;
	RendObj.Rect.Output.y = y;
	
	UpdateFont();
	return this;
}


UFI_TextElement*  UFI_TextElement::SetTextSetSize (const char *text, int ptsize){
	
	p_font_size = ptsize;
	p_text = text;
	this->RendObj.Name = text;
	
	UpdateFont();
	return this;
}


UFI_TextElement*  UFI_TextElement::SetFontSize( int ptsize){
	
	if(!NeedUpdate(p_font_size, ptsize)) return this;
	
	p_font_size = ptsize;

	UpdateFont();
	return this;
}


UFI_TextElement*  UFI_TextElement::SetText( const char* text){
	if(text != nullptr){
		p_text = text;
		this->RendObj.Name = text;
		UpdateFont();
	}else p_text = "*";
	return this;
}


UFI_TextElement*  UFI_TextElement::SetPosition(int x, int y){
	
	if(!(NeedUpdate(RendObj.Rect.Output.x, x)||
		NeedUpdate(RendObj.Rect.Output.y, y))) return this;
	
	RendObj.Rect.Output.x = x;
	RendObj.Rect.Output.y = y;
	
	CalculatePoints(&RendObj);
	return this;
}


UFI_TextElement*  UFI_TextElement::SetPositionX(int x){
	if(!NeedUpdate(RendObj.Rect.Output.x, x)) return this;
	
	RendObj.Rect.Output.x = x;
	
	CalculatePoints(&RendObj);
	return this;
}


UFI_TextElement*  UFI_TextElement::SetPositionY(int y){
	if(!NeedUpdate(RendObj.Rect.Output.y, y)) return this;
	
	RendObj.Rect.Output.y = y;
	
	CalculatePoints(&RendObj);
	return this;
}


UFI_TextElement*  UFI_TextElement::SetTextColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	
	if(!(NeedUpdate(p_colour.r, r)||
		NeedUpdate(p_colour.g, g)||
		NeedUpdate(p_colour.b, b)||
		NeedUpdate(p_colour.a, a))) return this;
		
	p_colour.r = r;
	p_colour.g = g;
	p_colour.b = b;
	p_colour.a = a;

	UpdateFont();
	this->SetAlpha(a);

	return this;
}


UFI_TextElement*  UFI_TextElement::SetAlpha( Uint8 a){
	
	if(!NeedUpdate(p_colour.a, a)) return this;
	
	this->p_colour.a = a;
	
	SDL_SetTextureAlphaMod(this->RendObj.Texture, a); // ????????????????? Didn`t work!
	return this;
	//cout << "Nope Alpha in this texture, resave with Alpha" << endl;
}


const char* UFI_TextElement::GetText(){ return this->RendObj.Name; }


UFI_RenderObject_t* UFI_TextElement::GetObject(){
	return &RendObj;
}


void UFI_TextElement::Display(){
	
	UpdateFont();
	//SDL_SetRenderDrawBlendMode(RendObjVect.Render, &RendObjVect[i].TextureBlendMode);
	SDL_SetTextureAlphaMod(this->RendObj.Texture, this->p_colour.a);
	
	if(&RendObj != nullptr){
		SDL_RenderCopy( 
			RendObj.Render,	
			RendObj.Texture, 
			&RendObj.Rect.Source,
			&RendObj.Rect.Output
		);
	}
	//printf("Text Name %s\n", this->RendObj.Name);
}
void UFI_TextElement::DisplayEdges(SDL_Renderer* rend)
{
	this->p_Rend = rend;
	UFI_RectPoints_t Points[4] = {0};
	
	Points[0] = CalculatePoints(&this->RendObj.Rect.Output);
	Points[1] = CalculatePoints(&this->RendObj.Rect.Output);
	Points[2] = CalculatePoints(&this->RendObj.Rect.Output);
	Points[3] = CalculatePoints(&this->RendObj.Rect.Output);
	
	for (int i = 0; i < 4; i++){
		SDL_SetRenderDrawColor(this->p_Rend, 255 - 70*i, 0, 70*i, 255);
		
		SDL_RenderDrawLine(p_Rend, Points[i].Bot_L.x, Points[i].Bot_L.y, Points[i].Bot_R.x, Points[i].Bot_R.y);
		SDL_RenderDrawLine(p_Rend, Points[i].Bot_L.x, Points[i].Bot_L.y, Points[i].Top_L.x, Points[i].Top_L.y);
		SDL_RenderDrawLine(p_Rend, Points[i].Top_L.x, Points[i].Top_L.y, Points[i].Top_R.x, Points[i].Top_R.y);
		SDL_RenderDrawLine(p_Rend, Points[i].Top_R.x, Points[i].Top_R.y, Points[i].Bot_R.x, Points[i].Bot_R.y);
	}
}






/*######################################################
 *     Class UFI_LineElement
 * _____________________________________________________
 */
UFI_LineElement::UFI_LineElement(){
	RendObjLine_ptr = new UFI_RenderObject_t;
	std::cout << ">Line element created\n";
}
UFI_LineElement::~UFI_LineElement(){
	//std::cout << ">Kill Line Element>\n";
	delete RendObjLine_ptr;
}
void UFI_LineElement::CreateLineTextureFromBMP(SDL_Renderer *p_rend, const char* file){
	p_Rend = p_rend;
	RendObjLine_ptr->Render = p_rend;
	
	p_Surf = SDL_LoadBMP(file);
	RendObjLine_ptr->Texture = SDL_CreateTextureFromSurface(p_rend, p_Surf);
	
	RendObjLine_ptr->Rect.Source.x = 0;
	RendObjLine_ptr->Rect.Source.y = 0;
	RendObjLine_ptr->Rect.Source.w = p_Surf->w;
	RendObjLine_ptr->Rect.Source.h = p_Surf->h;
	
	RendObjLine_ptr->Rect.Output.x = 0;
	RendObjLine_ptr->Rect.Output.y = 0;
	RendObjLine_ptr->Rect.Output.w = p_Surf->w;
	RendObjLine_ptr->Rect.Output.h = p_Surf->h;
	
	SDL_FreeSurface(p_Surf);
}
void UFI_LineElement::SetSize(int w, int h){
	
	RendObjLine_ptr->Rect.Output.h = h;
	RendObjLine_ptr->Rect.Output.w = w;
}
void UFI_LineElement::SetPosition(int x, int y){
	
	RendObjLine_ptr->Rect.Output.x = x;
	RendObjLine_ptr->Rect.Output.y = y;
}
UFI_RenderObject_t* UFI_LineElement::GetObject(){
	return RendObjLine_ptr;
}
