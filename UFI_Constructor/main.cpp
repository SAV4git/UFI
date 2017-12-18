#include "UFI/UFI.h"
#include <SDL2/SDL.h>

#include <math.h>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>
#include <iostream>
#include <stdio.h>
//  from  RunTerminalCmd
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
//  to    RunTerminalCmd

using std::cout;
using std::endl;

void Createing_textures();
void StartWin2();
void ChooseParamWin2();
void Win2_Rendering();

SDL_Event			event;
SDL_Window*		win = nullptr;
SDL_Renderer*		renderer = nullptr;
SDL_Renderer*		renderer_win2 = nullptr;

UFI_Window			Win, Win2;
UFI_Debug				Debug;

UFI_TextElement		cTX_Log;	// Rendered text cTX_* 

UFI_Texture			cT_Start_Panel, cT_Output_Back, cT_List_Panel;

UFI_Texture			cT_Hex_BG;

UFI_Texture			cT_BackGround; // Textures cT_*
UFI_Texture			cT_BG_black; // Textures cT_*
UFI_Texture			cT_Yb_1; // Textures cT_*
UFI_Texture			cT_Yb_2; // Textures cT_*

UFI_Module			cB_Run;

UFI_Module			cM_Start, cM_Output;

UFI_Anim				cA_LineRizeX;
UFI_Anim				cA_LineRizeAlpha;

Uint64 start_t, end_t, F;
char fps_buffer[16] = " ";

char MouseX[5] =" ", MouseY[5] = " ";

int width = 1200;
int height = 600;

int main(int argc, char **argv)
{
	Setup();
	//F = SDL_GetPerformanceFrequency();
	float fps = 0.0;
	// Infinite LOOP
	while ( Win.IsOpen() ) 
	{
		fps = (float) (1000000000/(double)(end_t - start_t));
		//snprintf( fps_buffer, sizeof fps_buffer, "FPS: %4.1f", fps);
		sprintf(fps_buffer, "FPS: %4.1f", fps);
		//printf("Time Start: %lu, End: %lu, FPS: %f, char FPS: %s \n", start_t, end_t, fps, fps_buffer);
		
		start_t = SDL_GetPerformanceCounter();
		Loop();
		end_t = SDL_GetPerformanceCounter();
	}
	return 0;
}


void Setup(void){
	
	Window_init();
	printf("window init ok\n\n");
	Createing_textures();
	printf("\ntexture init ok\n\n");
	
	printf("mem %d\n", Debug.getMemSize_kB());
	
	int alpha[255] = {100};
	
	for(int i = 0; i < 100; i++) alpha[i] = i; 
	for(int i = 100; i < 150; i++) alpha[i] = 100; 
	for(int i = 150; i < 255; i++) alpha[i] = 255 - i; 
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	
	
	for(int i = 0; i < 255; i++ ){
		Win.RenderStartFPS(50);
		Event.RunEventHendler(renderer); // You always must have this Handler
		if( Ev.Mouse.Scroll.Horisontal < 0) Win.Close();
		cT_Hex_BG.Display();
		cT_Hex_BG.SetAlpha(alpha[i]);
		Win.RenderEnd();
	}
	cA_LineRizeX.Start();
}


void Window_init(void)
{
	printf("\n\n\n > Go go go... \n\n");

	Win.CreateWithSize(width, height);
	//Win.CreateFullscreen();
	Win.SetPosition(10, 10);
	Win.GetInfo();
	
	renderer = Win.CreateRender();
	
	SDL_RenderSetLogicalSize( renderer, width, height );
	SDL_SetRenderDrawColor( renderer, 0, 30, 70, 255 );
}

void Loop(void)
{
	//SDL_SetRenderDrawColor(renderer, 253, 203, 46, 255); Yeloow
	//SDL_SetRenderDrawColor(renderer, 18, 74, 97, 255); 	Blue-up
	
	SDL_SetRenderDrawColor(renderer, 15, 31, 47, 255);
	Win.RenderStartFPS(50);
	
	Event.RunEventHendler(renderer); // You always must have this Handler
	
	if( Ev.Mouse.Scroll.Horisontal < 0) Win.Close();
	
	cT_BackGround.Display();
	cT_BG_black.Display();
	
	cT_List_Panel.Display();
	
	cM_Start.Display();

	cB_Run.Display();
	
	sprintf(MouseX, "%d", Ev.Mouse.Position.x);
	sprintf(MouseY, "%d", Ev.Mouse.Position.y);
	
	//cM_Start.SetRelativeTextElement(*cTX_Log.SetText("New 1"), "New text 1", 50, 120);
	//cM_Start.SetRelativeTextElement(*cTX_Log.SetText("New 2"), "New text 2", 80, 120);
	/*
	static int t = 0;
	if(t > 10) {cM_Start.SetRelativeTextElement(*cTX_Log.SetText(fps_buffer), fps_buffer, 20, 240); t = 0;}
	else t++;
	*/
	
	//cTX_Log.Display();
	//0:0.1:100 = return 0, 0.1, 0.2,....100;
	//cT_Start_Back.SetAlpha( cA_LineRizeAlpha.Animate(0, 3, 400)); 
	
	//cT_Start_Back.SetPosition( Ev.Mouse.Position.x, Ev.Mouse.Position.y );

	Win.RenderEnd();
	
	if( Win2.IsOpen()){
		Win2_Rendering();
	}
}


void Createing_textures(){
	
	cT_Hex_BG.CreateTextureBMP(renderer, "../Textures/Hex_1.bmp");
	cT_Hex_BG.SetPosition( -2, -2 );
	cT_Hex_BG.SetOutputSize( 1210, 610 );
	cT_Hex_BG.SetAlpha( 1 );
	
	cT_BackGround.CreateTextureBMP(renderer, "../Textures/BG.bmp");
	cT_BackGround.SetPosition( -10, -10 );
	cT_BackGround.SetOutputSize( 1210, 610 );
	cT_BackGround.SetAlpha( 10 );
	
	cT_BG_black.CreateTextureBMP(renderer, "../Textures/BG_black.bmp");
	cT_BG_black.SetPosition( -10, -10 );
	cT_BG_black.SetOutputSize( 1210, 610 );
	cT_BG_black.SetAlpha( 120 );
	
	cT_Yb_1.CreateTextureBMP(renderer, "../Textures/Yell_buttons.bmp");
	cT_Yb_1.SetSprite(463, 0, 124, 49);
	cT_Yb_1.SetOutputSize(124, 49);
	cT_Yb_1.SetAlpha(220);
	cT_Yb_1.SetPosition( -463, 0);
	
	cT_Start_Panel.CreateTextureBMP( renderer, "../Textures/Panels.bmp" );
	cT_Start_Panel.SetSprite( 43, 0, 410, 280 );
	cT_Start_Panel.SetOutputSize( 410, 280 );
	cT_Start_Panel.SetAlpha( 150 );
	cT_Start_Panel.SetPosition( 100, 100 );
	
	cT_List_Panel.CreateTextureBMP( renderer, "../Textures/Panels.bmp" );
	cT_List_Panel.SetSprite( 510, 0, 285, 480 );
	cT_List_Panel.SetOutputSize( 285, 480 );
	cT_List_Panel.SetAlpha( 150 );
	cT_List_Panel.SetPosition( 900, 50 );
	
	cTX_Log.CreateTextureFont(renderer, "../Fonts/cordiaub.ttf");
	cTX_Log.SetFontSize(34);
	cTX_Log.SetText("Welcome");
	cTX_Log.SetTextColor(253, 203, 46, 255);
	cTX_Log.SetPosition(300, 108);
	
	
	/*
	 * Set cM_Start  
	 */
	
	cM_Start.AddRelativePos(cT_Start_Panel.SetPosition(10, 10));
	cM_Start.AddRelativePos(cTX_Log.SetPosition(200,10));

		cTX_Log.SetFontSize(25);
		cTX_Log.SetText(fps_buffer);
	cM_Start.AddRelativePos(cTX_Log.SetPosition(50,250));
		cTX_Log.SetText("Mouse X= ");
	cM_Start.AddRelativePos(cTX_Log.SetPosition(20,40));
		cTX_Log.SetText(MouseX);
	cM_Start.AddRelativePos(cTX_Log.SetPosition(100,40));
		cTX_Log.SetText("Mouse Y= ");
	cM_Start.AddRelativePos(cTX_Log.SetPosition(20,60));
		cTX_Log.SetText(MouseY);
	cM_Start.AddRelativePos(cTX_Log.SetPosition(100,60));
	
	cM_Start.SetAlpha(128);
	cM_Start.SetPosition(10, 50);
	
	//Event.AddButtonPressed(renderer, &cM_Start, cTX_Log.SetText(" "), StartWin2); // needs Texture nullptr handler
	//
	Event.AddButtonFocused(renderer, &cM_Start, cTX_Log.SetText(" "), ChooseParamWin2); // needs Texture nullptr handler

	/*
	 * Set cB_Run  
	 */
	cTX_Log.SetFontSize(32);
	cB_Run.AddRelativePos(cT_Yb_1.SetPosition(720, -12));
	
		cTX_Log.SetTextColor(0, 0, 0, 255);
		cTX_Log.SetText("Button");
	Event.AddButtonDefault(renderer, &cB_Run, cTX_Log.SetPosition(25, 8));
		cTX_Log.SetText("Focused");
	Event.AddButtonFocused(renderer, &cB_Run, cTX_Log.SetPosition(20, 8), nullptr);
		cTX_Log.SetText("Pressed");
	Event.AddButtonPressed(renderer, &cB_Run, cTX_Log.SetPosition(20, 10), nullptr);
	
	cB_Run.SetAlpha(180);
	/*
	Event.AddAnimation( cA_LineRizeAlpha, START, cA_LineRizeX.StartWithDelay_ms(200));
	Event.AddAnimation( cA_LineRizeAlpha, END, Callback);
	Event.AddAnimation( cA_LineRizeAlpha, END, cA_LineRizeX.Start);
	*/
	cA_LineRizeX.SetAnim( 0, 720 );
	cA_LineRizeX.SetTime( 10, 1200 );
	cA_LineRizeX.SetLinear();
	
	cA_LineRizeAlpha.SetAnim(50, 150);
	cA_LineRizeAlpha.SetTime(25, 1200);
	cA_LineRizeAlpha.SetLinear();
	
	// Create textures for constructor interface
	
}

void ChooseParamWin2(){
	cM_Start.DisplayEdges(renderer);
}


void StartWin2(){
	if( !Win2.IsOpen() ){
		Win2.CreateWithSize(800, 600);
		Win2.SetTitle("UFI Constructor");
		renderer_win2 = Win2.CreateRender();
		printf("Win2 Started\n");
	} else return;
}

void Win2_Rendering(){
	if( Ev.Mouse.Scroll.Vertical < 0) Win2.Close();
	
	Win2.RenderStartFPS(60);
	
		
	Win2.RenderEnd();
}