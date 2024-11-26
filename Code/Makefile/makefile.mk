COMPILER = g++
COMPILER_FLAGS = -Wall -g -std=c++17 -O3
LINKER_FLAGS = -Wall -g
ARCHIVER = ar
ARCHIVER_FLAGS = rvs

ADDITIONAL_HEADER_PATH = 
ADDITIONAL_LIBRARY_PATH = 
ADDITIONAL_LIBRARIES = 

HEADER_PATH		= ./Code/Inc
SOURCE_PATH 	= ./Code/Src
OBJECT_PATH 	= ./Code/Obj



SOURCE_FILES = $(wildcard $(SOURCE_PATH)/*.cpp) $(wildcard $(SOURCE_PATH)/*/*.cpp) $(wildcard $(SOURCE_PATH)/*/*/*.cpp) $(wildcard $(SOURCE_PATH)/*/*/*/*.cpp) $(wildcard $(SOURCE_PATH)/*/*/*/*/*.cpp) $(wildcard $(SOURCE_PATH)/*/*/*/*/*/*.cpp) $(wildcard $(SOURCE_PATH)/*/*/*/*/*/*/*.cpp) $(wildcard $(SOURCE_PATH)/*/*/*/*/*/*/*/*.cpp)
OBJECT_FILES_TEMP = $(patsubst %.cpp, %.o, $(SOURCE_FILES))
OBJECT_FILES = $(subst $(SOURCE_PATH), $(OBJECT_PATH), $(OBJECT_FILES_TEMP))
OUTPUT_FILE_NAME = util



$(info Projects Directory is: $(PROJECTS_PATH))
$(info Building "$(OUTPUT_FILE_NAME)" from Files located in: $(SOURCE_PATH))
$(info Source Files located in $(SOURCE_PATH): $(SOURCE_FILES))
$(info )



all: library

executable: $(OBJECT_FILES)
	$(COMPILER) $(LINKER_FLAGS) -o ./$(OUTPUT_FILE_NAME).exe $(OBJECT_FILES) $(ADDITIONAL_LIBRARY_PATH) $(ADDITIONAL_LIBRARIES)

library: $(OBJECT_FILES)
	$(ARCHIVER) $(ARCHIVER_FLAGS) ./lib$(OUTPUT_FILE_NAME).a $(OBJECT_FILES)

$(OBJECT_PATH)/%.o: $(SOURCE_PATH)/%.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@ -I$(HEADER_PATH) $(ADDITIONAL_HEADER_PATH)