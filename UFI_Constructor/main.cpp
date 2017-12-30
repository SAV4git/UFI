#include "../UFI_lib/UFI.h"
#include <SDL2/SDL.h>

#include <math.h>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>
#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;

void Createing_textures();
void StartWin2();
void RunTerminal();
void Win2_Rendering();
void BG_Noize(int, Uint8);

SDL_Event			event;
SDL_Window*		win = nullptr;
SDL_Renderer*		renderer = nullptr;
SDL_Renderer*		renderer_win2 = nullptr;

UFI_Window			Win, Win2;
UFI_Debug				Debug;
UFI_Terminal			Terminal;
//========================================================

UFI_TextElement		cTX_Log;	// Rendered text cTX_*
UFI_TextElement		cTX_Logo;	// Rendered text cTX_*

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
char Memory[10] = " ";

int width = 1200;
int height = 600;

SDL_Rect WinRect;


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


void Window_init(void)
{
	printf("\n\n\n > Go go go... \n\n");

	Win.CreateWithSize(width, height);
	//Win.CreateFullscreen();
	Win.SetPosition(10, 10);
	Win.GetInfo();
	
	renderer = Win.CreateRender();
}


void Setup(void){
	
	Window_init();
	printf("window init ok\n\n");
	Createing_textures();
	printf("\ntexture init ok\n\n");
	
	printf("mem %d\n", Debug.getMemSize_kB());
	
	WinRect.w = width;
	WinRect.h = height;
	WinRect.x = 0;
	WinRect.y = 0;
	int col;
	
	SDL_SetRenderDrawColor( renderer, 0, 30, 70, 255 );
	cTX_Logo.SetTextColor(255, 255, 255, 255);
	for(int i = 0; i < 120; i++){
		Win.RenderStartFPS(200
		);
			
			if(i >= 60){
				if( i <= 80){
					col = 255 - (i - 60)*12;
					cTX_Logo.SetTextColor(col, col, col, 255);
				} else cTX_Logo.SetTextColor(0, 0, 0, 255);
			}
			
			cTX_Logo.Display();
			if(i < 50) SDL_SetRenderDrawColor( renderer, 0, 50 - i, 100 - i*2, 0 );
			else SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
			SDL_RenderDrawRect(renderer, &WinRect);
		Win.RenderEnd();
	}
}


void Loop(void)
{
	//SDL_SetRenderDrawColor(renderer, 253, 203, 46, 255); Yeloow
	//SDL_SetRenderDrawColor(renderer, 18, 74, 97, 255); 	Blue-up
	
	SDL_SetRenderDrawColor(renderer, 15, 31, 47, 255);
	Win.RenderStartFPS(30);
	
	Event.RunEventHendler(renderer); // You always must have this Handler
	
	if( Ev.Mouse.Scroll.Horisontal < 0) Win.Close();
	
	cT_BackGround.Display();
	cT_BG_black.Display();
	
	cT_List_Panel.Display();
	
	cM_Start.Display();
	
	BG_Noize(5000, 140);

	cB_Run.Display();
	
	sprintf(MouseX, "%d", Ev.Mouse.Position.x);
	sprintf(MouseY, "%d", Ev.Mouse.Position.y);
	sprintf(Memory, "%d", Debug.getMemSize_kB());
	
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

	cTX_Logo.CreateTextureFont(renderer,"../Fonts/UnderAuthority.ttf");
	cTX_Logo.SetFontSize(130);
	cTX_Logo.SetText("Welcome to UFI");
	cTX_Logo.SetTextColor(253, 203, 46, 255);
	cTX_Logo.SetPosition(350, 120);
	
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
	cT_Yb_1.SetSprite(460, 0, 129, 49);
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
	cTX_Log.SetTextColor(253, 203, 46, 255);
	
	
	/*
	 * Set cM_Start  
	 */
	
	cM_Start.AddRelativePos(cT_Start_Panel.SetPosition(10, 10));
		
	cM_Start.SetAlpha(180);
		cTX_Log.SetFontSize(35);
		cTX_Log.SetAlpha(255);
		
		cTX_Log.SetText("Welcome");
	cM_Start.AddRelativePos(cTX_Log.SetPosition(200, 8));
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
	
		cTX_Log.SetText("Memory in kB");
	cM_Start.AddRelativePos(cTX_Log.SetPosition(20,80));
		cTX_Log.SetText(Memory);
	cM_Start.AddRelativePos(cTX_Log.SetPosition(150,80));
	
	cM_Start.SetPosition(10, 50);
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
	Event.AddButtonPressed(renderer, &cB_Run, cTX_Log.SetPosition(20, 10), StartWin2);
	
	cB_Run.SetAlpha(190);
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

void RunTerminal(){
	//Terminal.RunTerminalCmd("gedit");
	//Terminal.RunTerminalCmd("zenity --color-selection --show-palette");
	SDL_Color Col;
	Terminal.Zenity_pallete(&Col);
	
	cB_Run.ButtonDefault.Title_ptr->SetTextColor(Col.r, Col.g, Col.b, Col.a);
	cB_Run.ButtonFocused.Title_ptr->SetTextColor(Col.r, Col.g, Col.b, Col.a);
}


void StartWin2(){
	printf("StartWin2()\n");
	if( !Win2.IsOpen() ){
		Win2.CreateWithSize(800, 600);
		Win2.SetTitle("UFI Constructor");
		renderer_win2 = Win2.CreateRender();
		printf("Win2 Started\n");
	} else printf("Win2 opened\n");
}

void Win2_Rendering(){
	if( Ev.Mouse.Scroll.Vertical < 0) Win2.Close();
	
	Win2.RenderStartFPS(60);
	
		 
	Win2.RenderEnd();
}

void BG_Noize(int N, Uint8 alpha){
	static SDL_Point point[100000];
	
	for(int i = 0; i < N; i++){
		point[i].x = rand()%1200;
		point[i].y = rand()%600;
	}
	SDL_SetRenderDrawColor(renderer, 100, 140, 255, alpha >> 3);
	for(int i = 0; i < 600; i +=2){
		SDL_RenderDrawLine(renderer, 0, i, width, i);
	}
	
	SDL_SetRenderDrawColor(renderer, 100, 0, 160, alpha);
	SDL_RenderDrawPoints(renderer, point, N);
}
