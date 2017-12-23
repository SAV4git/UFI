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
SDL_Color UFI_Terminal::Zenity_pallete(){
	UFI_Color_s a;
	
	a.
}
