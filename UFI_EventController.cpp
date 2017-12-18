#include <SDL2/SDL.h>

#include <iostream>

#include "UFI/UFI.h"
#include "UFI/UFI_Types.h"
#include "UFI/UFI_Texture.h"
#include "UFI/UFI_Module.h"
#include "UFI/UFI_EventController.h"

#include <string>
#include <bitset>
#include <iterator>
#include <list>
#include <vector>
#include <map>

#include <bitset>

using std::cout;
using std::endl;

UFI_EventHendler::UFI_EventHendler(){

	Ev_MouseClickButton.SetEvFlags( EvFlagsMask.Pressed | EvFlagsMask.Left );
}
UFI_EventHendler::~UFI_EventHendler(){}

void UFI_EventHendler::TextEditHandler(){
	
	KeyB.composition = event.edit.text;
	KeyB.cursor = event.edit.start;
	KeyB.selection_len = event.edit.length;
}


void UFI_EventHendler::TextInputHandler(){
	
	KeyB.text += event.text.text;
	std::cout << KeyB.text << std::endl;
}


void UFI_EventHendler::Motion_Handler(){
	
	//Mouse.Position.x = event.motion.x;
	//Mouse.Position.y = event.motion.y;
	//Mouse.Memory.Position_DxDy.x = event.motion.xrel;
	//Mouse.Memory.Position_DxDy.x = event.motion.yrel;
	
	Ev.Mouse.Timestamp = event.button.timestamp;
	Ev.Mouse.Position.x = event.button.x;
	Ev.Mouse.Position.y = event.button.y;
	Ev.Mouse.Position.Point.x = event.button.x;
	Ev.Mouse.Position.Point.y = event.button.y;
	Ev.Mouse.Position.RelativeXY.x = event.motion.xrel;
	Ev.Mouse.Position.RelativeXY.y = event.motion.yrel;
	
	
	EvFlags |= EvFlagsMask.MouseMoved;
	//printf("%d, %d\n", this->Position.x, this->Position.y);
}


void UFI_EventHendler::ButtonDown_Handler(){
	
	Ev.Mouse.Timestamp = event.button.timestamp;
	
	Ev.Mouse.Action.clicks = event.button.clicks;
	
	EvFlags |= EvFlagsMask.Pressed;
	cout << "Prs" << endl;
	
	if( event.button.button == SDL_PRESSED){
		
		EvFlags |= EvFlagsMask.Pressed;
		Ev.Mouse.Flags |= Ev.Mouse.Action.Pressed;
		
		if( event.button.button == SDL_BUTTON_LMASK){
			Ev.Mouse.Flags |= Ev.Mouse.Button.Left;
			EvFlags |= EvFlagsMask.Left;
			cout << "L" << endl; 
		}
		if( event.button.button == SDL_BUTTON_RMASK){
			cout << "Right Pressed" << endl; 
			/*
			 * 
				It didn`t work with the touch mouse button;
			* 
			*/ 
			Ev.Mouse.Flags |= Ev.Mouse.Button.Right;
			EvFlags |= EvFlagsMask.Right;
			cout << "R" << endl; 
		}
		if( event.button.button == SDL_BUTTON_MMASK){
			Ev.Mouse.Flags |= Ev.Mouse.Button.Mid;
			EvFlags |= EvFlagsMask.Mid;
			cout << "M" << endl; 
		}
	}
	
	if( event.button.clicks >= 2 ){
		Ev.Mouse.Flags |= Ev.Mouse.Action.DoubleClk;
		EvFlags |= EvFlagsMask.DoubleClk;
		cout << "DblClk" << endl; 
	}
	else {
		Ev.Mouse.Flags &= ~Ev.Mouse.Action.DoubleClk;
	}
}


void UFI_EventHendler::ButtonUp_Handler(){
	
	Ev.Mouse.Flags &= ~(Ev.Mouse.Action.Pressed | Ev.Mouse.Action.DoubleClk);
	
	EvFlags &= ~EvFlagsMask.Pressed;
	cout << "unPresed" << endl;
	EvFlags &= ~EvFlagsMask.Left;
	
	if( event.button.button == SDL_RELEASED){
		if(	event.button.button == SDL_BUTTON_LMASK ){
			//Mouse.Button.Left = false;
			Ev.Mouse.Flags &= ~Ev.Mouse.Button.Left;
			EvFlags &= ~EvFlagsMask.Left;
			cout << "upL" << endl; 
		}
		if( event.button.button == SDL_BUTTON_RMASK){
			//Mouse.Button.Right = false;
			Ev.Mouse.Flags &= ~Ev.Mouse.Button.Right;
			EvFlags &= ~EvFlagsMask.Right;
			cout << "upR" << endl; 
		}
		if( event.button.button == SDL_BUTTON_MMASK){
			//Mouse.Button.Midle = false;
			Ev.Mouse.Flags &= ~Ev.Mouse.Button.Mid;
			EvFlags &= ~EvFlagsMask.Mid;
			cout << "upM" << endl; 
		}
	}
}


void UFI_EventHendler::Wheel_Handler(){

	Ev.Mouse.Scroll.Horisontal = event.wheel.x;
	Ev.Mouse.Scroll.Vertical = event.wheel.y;
	EvFlags |= EvFlagsMask.WheelMoved;
	if (event.wheel.x != 0) EvFlags |= EvFlagsMask.Horisontal;  
	if (event.wheel.y != 0) EvFlags |= EvFlagsMask.Vertical;
	cout << "Wheel" << endl; 
}

void UFI_EventHendler::VirtualButtonHandler(){

	for(unsigned i = 0; i < ButtonVect.size(); i++){
		
		if(ButtonVect[i]->IsButtonActive){
			//Ev_MouseClickButton.Mouse.Position.Rect = &ButtonVect[i]->GetRect()->Output;
			Ev_MouseClickButton.Mouse.Position.Rect = ButtonVect[i]->ButtonFocused.Rect;
			
			ButtonVect[i]->ButtonDefault.IsActiveted = true;
			ButtonVect[i]->ButtonPressed.IsActiveted = false;
			
			if( Ev_MouseClickButton.IsInRect() ){
				ButtonVect[i]->ButtonFocused.IsActiveted = true;
				ButtonVect[i]->ButtonDefault.IsActiveted = false;
				ButtonVect[i]->ButtonPressed.IsActiveted = false;
				
				if( ButtonVect[i]->CallBack.FocusedFunc!= nullptr)
					ButtonVect[i]->CallBack.FocusedFunc();
					
				if( Ev_MouseClickButton.PassedFlagsCheck() ){
					ButtonVect[i]->ButtonPressed.IsActiveted = true;
					
					if( ButtonVect[i]->CallBack.PressedFunc != nullptr){
						ButtonVect[i]->CallBack.PressedFunc();
						printf("f\n");
					}
						
						
				}else{
					ButtonVect[i]->ButtonPressed.IsActiveted = false;
				}
			}else{
				ButtonVect[i]->ButtonFocused.IsActiveted = false;
			}
			
			if(ButtonVect[i]->ButtonDefault.Title_ptr == nullptr)
				ButtonVect[i]->ButtonDefault.IsActiveted = false;
		}
		
	}
}


void UFI_EventHendler::AddButtonDefault( SDL_Renderer* rend, UFI_Module* button, UFI_TextElement* textEl ){
	button->IsButtonActive = true;
	
	button->AddRelativePos( textEl );
								
	button->ButtonDefault.Title_ptr = button->GetTextVector().back();
	cout << "D Add =" << button->GetTextVector().back() << endl;
	
	button->ButtonDefault.Rect = &textEl->GetObject()->Rect.Output;
	ButtonVect.push_back( button );
}


void UFI_EventHendler::AddButtonFocused( SDL_Renderer* rend, UFI_Module* button, UFI_TextElement* textEl, Func_ptr CallBack ){
	button->IsButtonActive = true;
	button->AddRelativePos( textEl );
	button->ButtonFocused.Title_ptr = button->GetTextVector().back(); 
	button->ButtonFocused.Rect = &button->ButtonFocused.Title_ptr->GetObject()->Rect.Output;
	if(CallBack != nullptr) button->CallBack.FocusedFunc = CallBack;
	ButtonVect.push_back( button );
}


void UFI_EventHendler::AddButtonPressed( SDL_Renderer* rend, UFI_Module* button, UFI_TextElement* textEl, Func_ptr CallBack ){
	button->IsButtonActive = true;
	if(textEl != nullptr){
	button->AddRelativePos( textEl );
		button->ButtonPressed.Title_ptr = button->GetTextVector().back();
		button->ButtonPressed.Rect = &button->ButtonPressed.Title_ptr->GetObject()->Rect.Output;
	}else button->ButtonPressed.Rect = &button->GetRect()->Output;
	
	if(CallBack != nullptr) button->CallBack.PressedFunc = CallBack;
	ButtonVect.push_back( button );
}


EvFlag UFI_EventHendler::GetFlags(){
	return EvFlags;
}


void UFI_EventHendler::RunEventHendler(SDL_Renderer* rend){
	SDL_StartTextInput();

	while (SDL_PollEvent(&event)) {
		EvFlags &= ~(EvFlagsMask.MouseMoved); 
		switch(event.type){ 
			case SDL_MOUSEBUTTONUP:{
				ButtonUp_Handler();
				VirtualButtonHandler();
				break;
			}
			case SDL_MOUSEBUTTONDOWN:{
				ButtonDown_Handler();
				VirtualButtonHandler();
				break;
			}
			case SDL_MOUSEMOTION:{
				Motion_Handler();
				VirtualButtonHandler();
				break;
			}
			case SDL_MOUSEWHEEL:{
				Wheel_Handler();break;
			}
			case SDL_TEXTINPUT:{
				TextInputHandler();break;
			}
			case SDL_TEXTEDITING:{
				TextEditHandler();break;
			}
			case SDL_QUIT:{
				break;
			}
			default:  break;
		}
		//cout << "Get = " << std::bitset<16>(EvFlags) << endl;
		EvFlags &= EvFlagsMask.Left | EvFlagsMask.Right | EvFlagsMask.Mid | EvFlagsMask.Pressed | EvFlagsMask.MouseMoved;
		//cout << "Default = " << std::bitset<16>(EvFlags) << endl;
	}
}




/*
 * 
 * 
 * 
 * 
 */
 
 
void UFI_Event::SetEvFlags(EvFlag flags){
	this->EventStruct.Flags = flags;
}


void UFI_Event::SetCallBack(Func_ptr func){
	this->EventStruct.Func = func;
}


bool UFI_Event::IsInRect(){
	if ( this->Mouse.Position.Rect != nullptr ) {
		if (SDL_PointInRect( &Ev.Mouse.Position.Point, this->Mouse.Position.Rect ) ){

			return true;
		}
	}

	return false;
}


bool UFI_Event::IsInRect(SDL_Rect* rect){
	if ( this->Mouse.Position.Rect != nullptr ) {
		if (SDL_PointInRect( &this->Mouse.Position.Point, rect ) ){
			return true;
		}else return false;
		
		/*
		cout << "Get = " << std::bitset<16>(Event.GetFlags()) << endl;
		cout << "Get = " << std::bitset<16>(this->EventStruct.Flags) << endl;
		cout << "State " << std::bitset<16>(Event.GetFlags() & this->EventStruct.Flags) <<  endl;
		cout << "State Bit " << (this->EventStruct.Flags && (Event.GetFlags() & this->EventStruct.Flags)) <<  endl;
		*/
	}
	return false;
}


bool UFI_Event::PassedFlagsCheck(){
	if( this->EventStruct.Flags && (Event.GetFlags() & this->EventStruct.Flags )) return true;
	else return false;
}


void UFI_Event::PrintFlags(){
	static int n = 0;
	
	if ( Ev.Mouse.Flags != 0){
			cout <<n++<< "|" << std::bitset<4>(Ev.Mouse.Flags>>12) 
					<< "|" << std::bitset<4>(Ev.Mouse.Flags>>8) 
					<< "|" << std::bitset<4>(Ev.Mouse.Flags>>4)
					<< "|" << std::bitset<4>(Ev.Mouse.Flags)
					<< "|" << endl;
					
	}
}


