##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=UFI_Constructor
ConfigurationName      :=Debug
WorkspacePath          :=/home/sav4/Documents/prog/sdl
ProjectPath            :=/home/sav4/Documents/prog/sdl/UFI_Constructor
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Arsen
Date                   :=18/12/17
CodeLitePath           :=/home/sav4/.codelite
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="UFI_Constructor.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)SDL2 $(LibrarySwitch)SDL2_ttf $(LibrarySwitch)jpeg $(LibrarySwitch)png 
ArLibs                 :=  "SDL2" "SDL2_ttf" "jpeg" "png" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -std=c++14 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/UFI_UFI_Line.cpp$(ObjectSuffix) $(IntermediateDirectory)/UFI_UFI_Module.cpp$(ObjectSuffix) $(IntermediateDirectory)/UFI_UFI_Debug.cpp$(ObjectSuffix) $(IntermediateDirectory)/UFI_UFI_Window.cpp$(ObjectSuffix) $(IntermediateDirectory)/UFI_UFI_EventController.cpp$(ObjectSuffix) $(IntermediateDirectory)/UFI_UFI_ImageLoader.cpp$(ObjectSuffix) $(IntermediateDirectory)/UFI_UFI_Anim.cpp$(ObjectSuffix) $(IntermediateDirectory)/UFI_UFI_Texture.cpp$(ObjectSuffix) $(IntermediateDirectory)/UFI_UFI.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/UFI_UFI_Render.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sav4/Documents/prog/sdl/UFI_Constructor/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/UFI_UFI_Line.cpp$(ObjectSuffix): UFI/UFI_Line.cpp $(IntermediateDirectory)/UFI_UFI_Line.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sav4/Documents/prog/sdl/UFI_Constructor/UFI/UFI_Line.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UFI_UFI_Line.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UFI_UFI_Line.cpp$(DependSuffix): UFI/UFI_Line.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UFI_UFI_Line.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UFI_UFI_Line.cpp$(DependSuffix) -MM UFI/UFI_Line.cpp

$(IntermediateDirectory)/UFI_UFI_Line.cpp$(PreprocessSuffix): UFI/UFI_Line.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UFI_UFI_Line.cpp$(PreprocessSuffix) UFI/UFI_Line.cpp

$(IntermediateDirectory)/UFI_UFI_Module.cpp$(ObjectSuffix): UFI/UFI_Module.cpp $(IntermediateDirectory)/UFI_UFI_Module.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sav4/Documents/prog/sdl/UFI_Constructor/UFI/UFI_Module.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UFI_UFI_Module.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UFI_UFI_Module.cpp$(DependSuffix): UFI/UFI_Module.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UFI_UFI_Module.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UFI_UFI_Module.cpp$(DependSuffix) -MM UFI/UFI_Module.cpp

$(IntermediateDirectory)/UFI_UFI_Module.cpp$(PreprocessSuffix): UFI/UFI_Module.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UFI_UFI_Module.cpp$(PreprocessSuffix) UFI/UFI_Module.cpp

$(IntermediateDirectory)/UFI_UFI_Debug.cpp$(ObjectSuffix): UFI/UFI_Debug.cpp $(IntermediateDirectory)/UFI_UFI_Debug.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sav4/Documents/prog/sdl/UFI_Constructor/UFI/UFI_Debug.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UFI_UFI_Debug.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UFI_UFI_Debug.cpp$(DependSuffix): UFI/UFI_Debug.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UFI_UFI_Debug.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UFI_UFI_Debug.cpp$(DependSuffix) -MM UFI/UFI_Debug.cpp

$(IntermediateDirectory)/UFI_UFI_Debug.cpp$(PreprocessSuffix): UFI/UFI_Debug.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UFI_UFI_Debug.cpp$(PreprocessSuffix) UFI/UFI_Debug.cpp

$(IntermediateDirectory)/UFI_UFI_Window.cpp$(ObjectSuffix): UFI/UFI_Window.cpp $(IntermediateDirectory)/UFI_UFI_Window.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sav4/Documents/prog/sdl/UFI_Constructor/UFI/UFI_Window.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UFI_UFI_Window.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UFI_UFI_Window.cpp$(DependSuffix): UFI/UFI_Window.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UFI_UFI_Window.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UFI_UFI_Window.cpp$(DependSuffix) -MM UFI/UFI_Window.cpp

$(IntermediateDirectory)/UFI_UFI_Window.cpp$(PreprocessSuffix): UFI/UFI_Window.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UFI_UFI_Window.cpp$(PreprocessSuffix) UFI/UFI_Window.cpp

$(IntermediateDirectory)/UFI_UFI_EventController.cpp$(ObjectSuffix): UFI/UFI_EventController.cpp $(IntermediateDirectory)/UFI_UFI_EventController.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sav4/Documents/prog/sdl/UFI_Constructor/UFI/UFI_EventController.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UFI_UFI_EventController.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UFI_UFI_EventController.cpp$(DependSuffix): UFI/UFI_EventController.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UFI_UFI_EventController.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UFI_UFI_EventController.cpp$(DependSuffix) -MM UFI/UFI_EventController.cpp

$(IntermediateDirectory)/UFI_UFI_EventController.cpp$(PreprocessSuffix): UFI/UFI_EventController.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UFI_UFI_EventController.cpp$(PreprocessSuffix) UFI/UFI_EventController.cpp

$(IntermediateDirectory)/UFI_UFI_ImageLoader.cpp$(ObjectSuffix): UFI/UFI_ImageLoader.cpp $(IntermediateDirectory)/UFI_UFI_ImageLoader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sav4/Documents/prog/sdl/UFI_Constructor/UFI/UFI_ImageLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UFI_UFI_ImageLoader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UFI_UFI_ImageLoader.cpp$(DependSuffix): UFI/UFI_ImageLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UFI_UFI_ImageLoader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UFI_UFI_ImageLoader.cpp$(DependSuffix) -MM UFI/UFI_ImageLoader.cpp

$(IntermediateDirectory)/UFI_UFI_ImageLoader.cpp$(PreprocessSuffix): UFI/UFI_ImageLoader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UFI_UFI_ImageLoader.cpp$(PreprocessSuffix) UFI/UFI_ImageLoader.cpp

$(IntermediateDirectory)/UFI_UFI_Anim.cpp$(ObjectSuffix): UFI/UFI_Anim.cpp $(IntermediateDirectory)/UFI_UFI_Anim.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sav4/Documents/prog/sdl/UFI_Constructor/UFI/UFI_Anim.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UFI_UFI_Anim.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UFI_UFI_Anim.cpp$(DependSuffix): UFI/UFI_Anim.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UFI_UFI_Anim.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UFI_UFI_Anim.cpp$(DependSuffix) -MM UFI/UFI_Anim.cpp

$(IntermediateDirectory)/UFI_UFI_Anim.cpp$(PreprocessSuffix): UFI/UFI_Anim.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UFI_UFI_Anim.cpp$(PreprocessSuffix) UFI/UFI_Anim.cpp

$(IntermediateDirectory)/UFI_UFI_Texture.cpp$(ObjectSuffix): UFI/UFI_Texture.cpp $(IntermediateDirectory)/UFI_UFI_Texture.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sav4/Documents/prog/sdl/UFI_Constructor/UFI/UFI_Texture.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UFI_UFI_Texture.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UFI_UFI_Texture.cpp$(DependSuffix): UFI/UFI_Texture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UFI_UFI_Texture.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UFI_UFI_Texture.cpp$(DependSuffix) -MM UFI/UFI_Texture.cpp

$(IntermediateDirectory)/UFI_UFI_Texture.cpp$(PreprocessSuffix): UFI/UFI_Texture.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UFI_UFI_Texture.cpp$(PreprocessSuffix) UFI/UFI_Texture.cpp

$(IntermediateDirectory)/UFI_UFI.cpp$(ObjectSuffix): UFI/UFI.cpp $(IntermediateDirectory)/UFI_UFI.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sav4/Documents/prog/sdl/UFI_Constructor/UFI/UFI.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UFI_UFI.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UFI_UFI.cpp$(DependSuffix): UFI/UFI.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UFI_UFI.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UFI_UFI.cpp$(DependSuffix) -MM UFI/UFI.cpp

$(IntermediateDirectory)/UFI_UFI.cpp$(PreprocessSuffix): UFI/UFI.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UFI_UFI.cpp$(PreprocessSuffix) UFI/UFI.cpp

$(IntermediateDirectory)/UFI_UFI_Render.cpp$(ObjectSuffix): UFI/UFI_Render.cpp $(IntermediateDirectory)/UFI_UFI_Render.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sav4/Documents/prog/sdl/UFI_Constructor/UFI/UFI_Render.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UFI_UFI_Render.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UFI_UFI_Render.cpp$(DependSuffix): UFI/UFI_Render.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UFI_UFI_Render.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UFI_UFI_Render.cpp$(DependSuffix) -MM UFI/UFI_Render.cpp

$(IntermediateDirectory)/UFI_UFI_Render.cpp$(PreprocessSuffix): UFI/UFI_Render.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UFI_UFI_Render.cpp$(PreprocessSuffix) UFI/UFI_Render.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


