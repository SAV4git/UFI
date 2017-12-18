#include "UFI_Types.h"
#include "UFI_Debug.h"
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "stdlib.h"
#include "stdio.h"
#include <iomanip>
#include "string.h"

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::right;

UFI_Debug::UFI_Debug()
{
}

UFI_Debug::~UFI_Debug()
{
}

int UFI_Debug::parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int UFI_Debug::getMemSize_kB(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

void UFI_Debug::PrintRendObjParam(UFI_RenderObject_t* RendObj_ptr){
	cout << "-------------------------------------------------------" << endl;
	cout << "Texture "<< RendObj_ptr->Texture << ", Name = "<< RendObj_ptr->Name << endl;
	cout << "Source" << endl; 
	cout	<< "      h=" << setw(4) << right<< RendObj_ptr->Rect.Source.h 
			<< ", w=" << setw(4) << right << RendObj_ptr->Rect.Source.w << endl;
	
	cout	<< "      x=" << setw(4) << right << RendObj_ptr->Rect.Source.x
			<< ", y=" << setw(4) << right << RendObj_ptr->Rect.Source.y << endl;
	cout << "Output" << endl;
	cout	<< "      h=" << setw(4) << right<< RendObj_ptr->Rect.Output.h 
			<< ", w=" << setw(4) << right << RendObj_ptr->Rect.Output.w << endl;
	
	cout	<< "      x=" << setw(4) << right << RendObj_ptr->Rect.Output.x
			<< ", y=" << setw(4) << right << RendObj_ptr->Rect.Output.y << endl;
}
