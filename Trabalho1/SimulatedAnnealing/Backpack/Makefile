COMPILER 				= g++

FLAGS					= -std=c++17 -O3 -Wshadow -flto
LDFLAGS					= -std=c++17 -O3 -flto -lm

BINARYDIR 				= Binary
EXENAME 				= main
MAIN_FILE 				= main
TARGET 					= $(BINARYDIR)/$(EXENAME)

ROOT_DIR				= ../..
MODULES_PATH			= $(ROOT_DIR)/Modules
BACKPACK_MODULES_PATH 	= $(MODULES_PATH)/Backpack

TIMER_PATH 				= $(MODULES_PATH)/Timer
UTILS_PATH 				= $(MODULES_PATH)/Utils
BACKPACK_PATH 			= $(BACKPACK_MODULES_PATH)/Backpack
SA_PATH					= SimulatedAnnealing_Backpack

SRCS 					= $(filter-out $(MAIN_FILE).cpp ./$(MAIN_FILE).cpp, $(wildcard *.cpp))
SRCS_TIMER 				= $(wildcard $(TIMER_PATH)/*.cpp)
SRCS_UTILS 				= $(wildcard $(UTILS_PATH)/*.cpp)
SRCS_BACKPACK 			= $(wildcard $(BACKPACK_PATH)/*.cpp)
SRCS_SA 				= $(wildcard $(SA_PATH)/*.cpp)

OBJS_MAIN 				= $(BINARYDIR)/$(MAIN_FILE).o
OBJS_LOCAL 				= $(patsubst %.cpp, $(BINARYDIR)/%.o, $(notdir $(SRCS)))
OBJS_TIMER 				= $(patsubst %.cpp, $(BINARYDIR)/timer_%.o, $(notdir $(SRCS_TIMER)))
OBJS_UTILS 				= $(patsubst %.cpp, $(BINARYDIR)/utils_%.o, $(notdir $(SRCS_UTILS)))
OBJS_BACKPACK 			= $(patsubst %.cpp, $(BINARYDIR)/backpack_%.o, $(notdir $(SRCS_BACKPACK)))
OBJS_SA 				= $(patsubst %.cpp, $(BINARYDIR)/sa_%.o, $(notdir $(SRCS_SA)))

OBJS 					= $(OBJS_LOCAL) $(OBJS_TIMER) $(OBJS_UTILS) $(OBJS_BACKPACK) $(OBJS_SA) $(OBJS_MAIN)

INCLUDES 				= -I. -I$(SA_PATH) -I$(TIMER_PATH) -I$(UTILS_PATH) -I$(BACKPACK_PATH)

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

# Utils files
$(BINARYDIR)/utils_%.o: $(UTILS_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# Backpack files
$(BINARYDIR)/backpack_%.o: $(BACKPACK_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# SA files
$(BINARYDIR)/sa_%.o: $(SA_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

$(BINARYDIR):
	mkdir -p $(BINARYDIR)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BINARYDIR)
