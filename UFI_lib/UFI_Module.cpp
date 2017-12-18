#include <iostream>
#include "../UFI_lib/UFI.h"
#include "../UFI_lib/UFI_Types.h"
#include "../UFI_lib/UFI_Texture.h"
#include "../UFI_lib/UFI_Module.h"
#include "../UFI_lib/UFI_EventController.h"
#include <vector>
#include <iterator>
#include <math.h>
#include <algorithm>

using std::cout;
using std::endl;

/*
 * 
 * 
 * 
 * 
*/
UFI_Button::UFI_Button(){
	//this->Display_back = ButtonDefault.Texture;
	//this->Display_text = ButtonDefault.Text;
};

UFI_Button::~UFI_Button(){
	//if( this->ButtonDefault.Text != nullptr ) delete this->ButtonDefault.Text;
	//if( this->ButtonDefault.Texture != nullptr ) delete this->ButtonDefault.Texture;
};

/*
 * 
 * 
 * 
 * 
*/
UFI_Module::UFI_Module()
{
	RendObjVect.resize(0);
	TextVector.reserve(2);
	Name = "defaultModule (changeble)";
	
	static SDL_Rect defaultPos;   //Set default rectangle:Start
	
	defaultPos.h = 10;
	defaultPos.w = 10;
	defaultPos.x = 0;
	defaultPos.y = 0;
	
	Module_Rect.Source.w = defaultPos.h;
	Module_Rect.Source.h = defaultPos.w;
	Module_Rect.Source.x = defaultPos.x; // I think it is safe;
	Module_Rect.Source.y = defaultPos.y; //Set default rectangle:End

	Module_Rect.Output.w = 0;
	Module_Rect.Output.h = 0;
	Module_Rect.Output.x = 0; // I think it is safe;
	Module_Rect.Output.y = 0; //Set default rectangle:End
	
	CalculatePoints( &Module_Rect.Output );
	
	std::cout<<"Object UFI_Module()\n";
}


UFI_Module::~UFI_Module(){
	
}

UFI_Module::UFI_Module( const UFI_Module& copy){
	this->Name = copy.Name;
	this->Module_Rect.Source.x =  copy.Module_Rect.Source.x;
	this->Module_Rect.Source.y =  copy.Module_Rect.Source.y;
	this->Module_Rect.Source.w =  copy.Module_Rect.Source.w;
	this->Module_Rect.Source.h =  copy.Module_Rect.Source.h;
	
	this->Module_Rect.Output.x =  copy.Module_Rect.Output.x;
	this->Module_Rect.Output.y =  copy.Module_Rect.Output.y;
	this->Module_Rect.Output.w =  copy.Module_Rect.Output.w;
	this->Module_Rect.Output.h =  copy.Module_Rect.Output.h;
	
	this->RendObjVect.resize( copy.RendObjVect.size() );
	std::copy( copy.RendObjVect.begin(), copy.RendObjVect.end(), this->RendObjVect.begin() );
	this->ModuleVect.resize( copy.ModuleVect.size() );
	std::copy( copy.ModuleVect.begin(), copy.ModuleVect.end(), this->ModuleVect.begin() );
	
	this->UpdateObject();
}


void UFI_Module::AddRelativePos( UFI_TextElement* clsTxEl){
	if(clsTxEl != nullptr){
		TextVector.push_back( new UFI_TextElement( *clsTxEl ) );
	
		TextVector.back()->SetPosition( 
			clsTxEl->GetObject()->Rect.Output.x + Module_Rect.Output.x, 
			clsTxEl->GetObject()->Rect.Output.y + Module_Rect.Output.y);
		cout << TextVector.back() << " text = " << TextVector.back()->GetText() << endl;

		UpdateObject();
	}
}


void UFI_Module::AddRelativePos( UFI_Texture* clsTx ){
	if(clsTx != nullptr){
		UFI_RenderObject_t tempRendObj = *clsTx->GetObject();
		
		tempRendObj.Rect.Output.x += Module_Rect.Output.x;
		tempRendObj.Rect.Output.y += Module_Rect.Output.y;
					
		RendObjVect.push_back( tempRendObj );
		
		UpdateObject();
	}
}


void	UFI_Module::AddRelativePos( UFI_Module* clsModule, int x, int y){
	//printf("Size %d, SizeRendVect %d\n", clsModule->ModuleVect.size(), clsModule->RendObjVect.size() ); 
	
	clsModule->SetPosition(x, y);
	//for (Uint8 i = 0; i < clsModule->GetObjectVec().size(); i++){
	//	printf("W= %d\n", clsModule->GetObjectVec()[i].Rect.Output.w);
	//	printf("H= %d\n", clsModule->GetObjectVec()[i].Rect.Output.h);
	//}

	ModuleVect.push_back( clsModule );
	
	UpdateObject();
}


void UFI_Module::SetPosition( int x, int y ){
	
	for (Uint8 i = 0; i < RendObjVect.size(); i++)
	{
		RendObjVect[i].Rect.Output.x = RendObjVect[i].Rect.Output.x - this->Module_Rect.Output.x + x;
		RendObjVect[i].Rect.Output.y = RendObjVect[i].Rect.Output.y - this->Module_Rect.Output.y + y;
	}
	
	for (Uint8 i = 0; i < ModuleVect.size(); ++i)
	{
		ModuleVect[i]->SetPosition( 
			ModuleVect[i]->GetRect()->Output.x - this->Module_Rect.Output.x + x, 
			ModuleVect[i]->GetRect()->Output.y - this->Module_Rect.Output.y + y 
		);
	}
	
	for (Uint8 i = 0; i < TextVector.size(); ++i)
	{
		TextVector[i]->SetPosition( 
			TextVector[i]->GetObject()->Rect.Output.x - this->Module_Rect.Output.x + x, 
			TextVector[i]->GetObject()->Rect.Output.y - this->Module_Rect.Output.y + y 
		);
	}
	
	UpdateObject();
}

void UFI_Module::SetPositionX( int x ){
	
	for (Uint8 i = 0; i < RendObjVect.size(); i++)
	{
		RendObjVect[i].Rect.Output.x = RendObjVect[i].Rect.Output.x - Module_Rect.Output.x + x;
	}
		
	for (Uint8 i = 0; i < ModuleVect.size(); ++i)
	{
		ModuleVect[i]->SetPositionX( 
			ModuleVect[i]->GetRect()->Output.x - this->Module_Rect.Output.x + x
		);
	}
	
	for (Uint8 i = 0; i < TextVector.size(); ++i)
	{
		TextVector[i]->SetPositionX( 
			TextVector[i]->GetObject()->Rect.Output.x - this->Module_Rect.Output.x + x
		);
	}
	
	UpdateObject();
}

void UFI_Module::SetPositionY( int y ){
	
	for (Uint8 i = 0; i < RendObjVect.size(); i++)
	{
		RendObjVect[i].Rect.Output.y = RendObjVect[i].Rect.Output.y - Module_Rect.Output.y + y;
	}
	
	for (Uint8 i = 0; i < ModuleVect.size(); ++i)
	{
		ModuleVect[i]->SetPositionY( 
			ModuleVect[i]->GetRect()->Output.y - this->Module_Rect.Output.y + y 
		);
	}
	
	for (Uint8 i = 0; i < TextVector.size(); ++i)
	{
		TextVector[i]->SetPositionY( 
			TextVector[i]->GetObject()->Rect.Output.y - this->Module_Rect.Output.y + y
		);
	}

	UpdateObject();
}

void UFI_Module::SetScale( float sw, float sh){

}


void UFI_Module::SetAlpha( Uint8 a ){	
	for( Uint8 i = 0; i < RendObjVect.size(); i++ )
	{
		SDL_SetTextureAlphaMod(RendObjVect[i].Texture, a);
	}
	for (Uint8 i = 0; i < ModuleVect.size(); ++i)
	{
		ModuleVect[i]->SetAlpha( a );
	}
	for (Uint8 i = 0; i < TextVector.size(); ++i)
	{
		TextVector[i]->SetAlpha( a );
	}
}

void	UFI_Module::SetName(const char* name){
	this->Name = name;
}

const char* UFI_Module::GetName(){
	return Name;
}

UFI_Rect_t* UFI_Module::GetRect(){
	return &Module_Rect;
}

RenderVect_t UFI_Module::GetObjectVec(){
	return RendObjVect;
}


std::vector<UFI_TextElement*>	UFI_Module::GetTextVector(){
	return TextVector;
}


void UFI_Module::DisplayEdges(SDL_Renderer* rend){
	
	p_Rend = rend;
	UFI_RectPoints_t Points[4] = {0};
	
	Points[0] = CalculatePoints(&this->Module_Rect.Output);
	Points[1] = CalculatePoints(&this->Module_Rect.Output);
	Points[2] = CalculatePoints(&this->Module_Rect.Output);
	Points[3] = CalculatePoints(&this->Module_Rect.Output);
	
	for (int i = 0; i < 4; i++){
		SDL_SetRenderDrawColor(this->p_Rend, 255 - 70*i, 0, 70*i, 255);
		
		SDL_RenderDrawLine(p_Rend, Points[i].Bot_L.x, Points[i].Bot_L.y, Points[i].Bot_R.x, Points[i].Bot_R.y);
		SDL_RenderDrawLine(p_Rend, Points[i].Bot_L.x, Points[i].Bot_L.y, Points[i].Top_L.x, Points[i].Top_L.y);
		SDL_RenderDrawLine(p_Rend, Points[i].Top_L.x, Points[i].Top_L.y, Points[i].Top_R.x, Points[i].Top_R.y);
		SDL_RenderDrawLine(p_Rend, Points[i].Top_R.x, Points[i].Top_R.y, Points[i].Bot_R.x, Points[i].Bot_R.y);
	}
}


void UFI_Module::UpdateObject(){

	Module_Rect.Output.h = 0;
	Module_Rect.Output.w = 0;
	
	for (unsigned i = 0; i < RendObjVect.size(); i++)
	{
		SDL_UnionRect(	
			&RendObjVect[i].Rect.Output, 
			&Module_Rect.Output, 
			&Module_Rect.Output
		);
	}
	if(!ModuleVect.size()){
		for (Uint8 i = 0; i < ModuleVect.size(); ++i)
		{
			ModuleVect[i]->UpdateObject();
		}
	}
	//cout << "Updated module size " << RendObjVect.size() << endl;
	
	CalculatePoints( &Module_Rect.Output );
}


bool UFI_Module::Display(){
	// Start of construction process for whole module
	
	for (Uint8 i = 0; i < RendObjVect.size(); ++i)
	{
		SDL_SetRenderDrawBlendMode(RendObjVect[i].Render, RendObjVect[i].TextureBlendMode);
		if(  RendObjVect[i].Rotate_angle == false){	//rendering textures
			//SDL_SetRenderTarget(private_Rend, (*it)->Texture ); //??
			//SDL_RenderSetViewport(RendObjVect[i].Render, &this->Module_Rect.Output );
			SDL_RenderCopy( 
				RendObjVect[i].Render,	
				RendObjVect[i].Texture, 
				&RendObjVect[i].Rect.Source,
				&RendObjVect[i].Rect.Output
			);
			//printf("Render name %d = %s\n", RendObjVect[i].Texture, RendObjVect[i].Name );
		}
		else{
			
			SDL_RenderCopyEx(    				//Sloooooooow func
				RendObjVect[i].Render,	
				RendObjVect[i].Texture,
				&RendObjVect[i].Rect.Source,
				&RendObjVect[i].Rect.Output,
				RendObjVect[i].Rotate_angle,
				NULL,
				SDL_FLIP_NONE
			);
			
		}
	}
	
	for (Uint8 i = 0; i < ModuleVect.size(); ++i){
		ModuleVect[i]->Display();
	}
	if(IsButtonActive){
		for (Uint8 i = 0; i < TextVector.size(); ++i){
			if(TextVector[i] != nullptr){
				if( ButtonDefault.IsActiveted){
					if(TextVector[i] == ButtonDefault.Title_ptr) { TextVector[i]->Display(); }
				}
				else if( ButtonFocused.IsActiveted){
					if( ButtonPressed.IsActiveted){
						 if(TextVector[i] == ButtonPressed.Title_ptr) TextVector[i]->Display();
					}else if(TextVector[i] == ButtonFocused.Title_ptr) TextVector[i]->Display();
				}else TextVector[i]->Display();
			}
		}
	}
	else{
		for (Uint8 i = 0; i < TextVector.size(); ++i){
			if(TextVector[i] != nullptr)
				TextVector[i]->Display();
		}
	}

	//printf("=============================\n");
	return true;
}

