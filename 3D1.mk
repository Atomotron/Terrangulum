##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=3D1
ConfigurationName      :=Debug
WorkspacePath          := "J:\Program Files\CodeLite\3D1"
ProjectPath            := "J:\Program Files\CodeLite\3D1\3D1"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Owner
Date                   :=17/08/2015
CodeLitePath           :="J:\Program Files\CodeLite"
LinkerName             :=J:/Assorted/MinGW/bin/g++.exe
SharedObjectLinkerName :=J:/Assorted/MinGW/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
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
ObjectsFileList        :="3D1.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=J:/Assorted/MinGW/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)"J:/Program Files/CodeLite/3D1/glfw-3.1.1/include" $(IncludeSwitch)"J:/Program Files/CodeLite/3D1/glm" 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)glfw3 $(LibrarySwitch)opengl32 $(LibrarySwitch)gdi32 
ArLibs                 :=  "libglfw3" "opengl32" "gdi32" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)"J:/Program Files/CodeLite/3D1/glfw-3.1.1/lib-mingw" $(LibraryPathSwitch)"J:/Program Files/CodeLite/3D1/3D1/src" 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := J:/Assorted/MinGW/bin/ar.exe rcu
CXX      := J:/Assorted/MinGW/bin/g++.exe
CC       := J:/Assorted/MinGW/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall -std=c++14 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := J:/Assorted/MinGW/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=J:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/glew.c$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/model.cpp$(ObjectSuffix) $(IntermediateDirectory)/shader.cpp$(ObjectSuffix) $(IntermediateDirectory)/object.cpp$(ObjectSuffix) $(IntermediateDirectory)/scene.cpp$(ObjectSuffix) $(IntermediateDirectory)/collisions.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/glew.c$(ObjectSuffix): glew.c $(IntermediateDirectory)/glew.c$(DependSuffix)
	$(CC) $(SourceSwitch) "J:/Program Files/CodeLite/3D1/3D1/glew.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/glew.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/glew.c$(DependSuffix): glew.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/glew.c$(ObjectSuffix) -MF$(IntermediateDirectory)/glew.c$(DependSuffix) -MM "glew.c"

$(IntermediateDirectory)/glew.c$(PreprocessSuffix): glew.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/glew.c$(PreprocessSuffix) "glew.c"

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "J:/Program Files/CodeLite/3D1/3D1/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/model.cpp$(ObjectSuffix): model.cpp $(IntermediateDirectory)/model.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "J:/Program Files/CodeLite/3D1/3D1/model.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/model.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/model.cpp$(DependSuffix): model.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/model.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/model.cpp$(DependSuffix) -MM "model.cpp"

$(IntermediateDirectory)/model.cpp$(PreprocessSuffix): model.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/model.cpp$(PreprocessSuffix) "model.cpp"

$(IntermediateDirectory)/shader.cpp$(ObjectSuffix): shader.cpp $(IntermediateDirectory)/shader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "J:/Program Files/CodeLite/3D1/3D1/shader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/shader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shader.cpp$(DependSuffix): shader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/shader.cpp$(DependSuffix) -MM "shader.cpp"

$(IntermediateDirectory)/shader.cpp$(PreprocessSuffix): shader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shader.cpp$(PreprocessSuffix) "shader.cpp"

$(IntermediateDirectory)/object.cpp$(ObjectSuffix): object.cpp $(IntermediateDirectory)/object.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "J:/Program Files/CodeLite/3D1/3D1/object.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/object.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/object.cpp$(DependSuffix): object.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/object.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/object.cpp$(DependSuffix) -MM "object.cpp"

$(IntermediateDirectory)/object.cpp$(PreprocessSuffix): object.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/object.cpp$(PreprocessSuffix) "object.cpp"

$(IntermediateDirectory)/scene.cpp$(ObjectSuffix): scene.cpp $(IntermediateDirectory)/scene.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "J:/Program Files/CodeLite/3D1/3D1/scene.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/scene.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/scene.cpp$(DependSuffix): scene.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/scene.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/scene.cpp$(DependSuffix) -MM "scene.cpp"

$(IntermediateDirectory)/scene.cpp$(PreprocessSuffix): scene.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/scene.cpp$(PreprocessSuffix) "scene.cpp"

$(IntermediateDirectory)/collisions.cpp$(ObjectSuffix): collisions.cpp $(IntermediateDirectory)/collisions.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "J:/Program Files/CodeLite/3D1/3D1/collisions.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/collisions.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/collisions.cpp$(DependSuffix): collisions.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/collisions.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/collisions.cpp$(DependSuffix) -MM "collisions.cpp"

$(IntermediateDirectory)/collisions.cpp$(PreprocessSuffix): collisions.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/collisions.cpp$(PreprocessSuffix) "collisions.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


