#include "../UFI_lib/UFI.h"
#include "../UFI_lib/UFI_Terminal.h"
//  from  RunTerminalCmd
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
//  to    RunTerminalCmd

UFI_Terminal::UFI_Terminal()
{
}

UFI_Terminal::~UFI_Terminal()
{
}


std::string UFI_Terminal::RunTerminalCmd(const char* cmd){
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
    //Replace popen and pclose with _popen and _pclose for Windows.
    
    //zenity --file-selection --file-filter=""*.ogg" "*.wav" "*.aac""
}
bool UFI_Terminal::Zenity_pallete(SDL_Color* col){
	std::string tempOut = this->RunTerminalCmd("zenity --color-selection --show-palette");
	printf("Out = %s\n", tempOut.c_str());
	if(tempOut != ""){
		float Col_a = 1;
		sscanf( tempOut.c_str(), "rgb(%u,%u,%u)\n", &col->r, &col->g, &col->b);
		sscanf( tempOut.c_str(), "rgba(%u,%u,%u,%g)\n", &col->r, &col->g, &col->b, &Col_a );
		col->a = (Uint8) (Col_a*255);
		printf(" %u - %u - %u - %u\n", col->r, col->g, col->b, col->a);
		return 1;
	}
	else return -1;
	
}