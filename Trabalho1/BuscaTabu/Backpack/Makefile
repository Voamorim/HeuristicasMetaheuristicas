COMPILER 				= g++

FLAGS					= -std=c++17 -O3 -Wshadow -flto
LDFLAGS					= -std=c++17 -O3 -flto -lm

BINARYDIR 				= Binary
EXENAME 				= main
MAIN_FILE 				= main
TARGET 					= $(BINARYDIR)/$(EXENAME)

ROOT_DIR 				= ../..
MODULES_PATH			= $(ROOT_DIR)/Modules
BACKPACK_MODULES_PATH	= $(MODULES_PATH)/Backpack

TIMER_PATH 				= $(MODULES_PATH)/Timer
IO_PATH 				= $(MODULES_PATH)/Io
BUILDCSV_PATH 			= $(MODULES_PATH)/BuildCSV
BACKPACK_PATH 			= $(BACKPACK_MODULES_PATH)/Backpack
BT_PATH 				= BuscaTabu_Backpack

SRCS 					= $(filter-out $(MAIN_FILE).cpp ./$(MAIN_FILE).cpp, $(wildcard *.cpp))
SRCS_TIMER 				= $(wildcard $(TIMER_PATH)/*.cpp)
SRCS_IO 				= $(wildcard $(IO_PATH)/*.cpp)
SRCS_BUILDCSV 			= $(wildcard $(BUILDCSV_PATH)/*.cpp)
SRCS_BACKPACK			= $(wildcard $(BACKPACK_PATH)/*.cpp)
SRCS_BT					= $(wildcard $(BT_PATH)/*.cpp)

OBJS_MAIN 				= $(BINARYDIR)/$(MAIN_FILE).o
OBJS_LOCAL 				= $(patsubst %.cpp, $(BINARYDIR)/%.o, $(notdir $(SRCS)))
OBJS_TIMER 				= $(patsubst %.cpp, $(BINARYDIR)/timer_%.o, $(notdir $(SRCS_TIMER)))
OBJS_IO 				= $(patsubst %.cpp, $(BINARYDIR)/io_%.o, $(notdir $(SRCS_IO)))
OBJS_BUILDCSV 			= $(patsubst %.cpp, $(BINARYDIR)/buildcsv_%.o, $(notdir $(SRCS_BUILDCSV)))
OBJS_BACKPACK 			= $(patsubst %.cpp, $(BINARYDIR)/backpack_%.o, $(notdir $(SRCS_BACKPACK)))
OBJS_BT 				= $(patsubst %.cpp, $(BINARYDIR)/bt_%.o, $(notdir $(SRCS_BT)))

OBJS 					= $(OBJS_LOCAL) $(OBJS_TIMER) $(OBJS_IO) $(OBJS_BUILDCSV) $(OBJS_BACKPACK) $(OBJS_BT) $(OBJS_MAIN)

INCLUDES 				= -I. -I$(BT_PATH) -I$(TIMER_PATH) -I$(IO_PATH) -I$(BUILDCSV_PATH) -I$(BACKPACK_PATH) 

.PHONY: all clean run

all: $(TARGET) 

# Final binary 
$(TARGET): $(OBJS) | $(BINARYDIR)
	$(COMPILER) $(OBJS) -o $@ $(LDFLAGS)

# Main file
$(BINARYDIR)/$(MAIN_FILE).o: $(MAIN_FILE).cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# Local files
$(BINARYDIR)/%.o: %.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# Timer files
$(BINARYDIR)/timer_%.o: $(TIMER_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# Io files
$(BINARYDIR)/io_%.o: $(IO_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# BuildCSV files
$(BINARYDIR)/buildcsv_%.o: $(TIMER_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# Backpack files
$(BINARYDIR)/backpack_%.o: $(BACKPACK_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# Tabu Search files
$(BINARYDIR)/bt_%.o: $(BT_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

$(BINARYDIR):
	mkdir -p $(BINARYDIR)

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -rf $(BINARYDIR)
