COMPILER 				= g++

FLAGS					= -std=c++17 -O3 -Wshadow -flto
LDFLAGS					= -std=c++17 -O3 -flto -lm

BINARYDIR 				= Binary
EXENAME 				= simulated_annealing_mochila
MAIN_FILE 				= simulated_annealing_mochila
TARGET 					= $(BINARYDIR)/$(EXENAME)

MODULES_PATH			= ../../Modules
BACKPACK_MODULES_PATH 	= $(MODULES_PATH)/Backpack

TIMER_PATH 				= $(MODULES_PATH)/Timer
UTILS_PATH 				= $(MODULES_PATH)/Utils
BACKPACK_PATH 			= $(BACKPACK_MODULES_PATH)/Backpack

SRCS 					= $(filter-out $(MAIN_FILE).cpp ./$(MAIN_FILE).cpp, $(wildcard *.cpp))
SRCS_TIMER 				= $(filter-out $(TIMER_PATH)/main.cpp, $(wildcard $(TIMER_PATH)/*.cpp))
SRCS_UTILS 				= $(filter-out $(UTILS_PATH)/main.cpp, $(wildcard $(UTILS_PATH)/*.cpp))
SRCS_BACKPACK			= $(filter-out $(BACKPACK_PATH)/main.cpp, $(wildcard $(BACKPACK_PATH)/*.cpp))

OBJS_LOCAL 				= $(SRCS:%.cpp=$(BINARYDIR)/%.o)
OBJS_TIMER 				= $(SRCS_TIMER:$(TIMER_PATH)/%.cpp=$(BINARYDIR)/timer_%.o)
OBJS_UTILS 				= $(SRCS_UTILS:$(UTILS_PATH)/%.cpp=$(BINARYDIR)/utils_%.o)
OBJS_BACKPACK 			= $(SRCS_BACKPACK:$(BACKPACK_PATH)/%.cpp=$(BINARYDIR)/backpack_%.o)
OBJS_MAIN 				= $(BINARYDIR)/$(MAIN_FILE).o

OBJS 					= $(OBJS_LOCAL) $(OBJS_TIMER) $(OBJS_UTILS) $(OBJS_BACKPACK) $(OBJS_MAIN)

INCLUDES 				= -I. -I$(TIMER_PATH) -I$(UTILS_PATH) -I$(BACKPACK_PATH)

.PHONY: all clean run

all: $(TARGET) 

$(TARGET): $(OBJS) | $(BINARYDIR)
	$(COMPILER) $(OBJS) -o $@ $(LDFLAGS)

# Local cpp files
$(BINARYDIR)/%.o: %.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# Timer cpp files
$(BINARYDIR)/timer_%.o: $(TIMER_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# Utils cpp files
$(BINARYDIR)/utils_%.o: $(UTILS_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# Backpack cpp files
$(BINARYDIR)/backpack_%.o: $(BACKPACK_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

$(BINARYDIR)/$(MAIN_FILE).o: $(MAIN_FILE).cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

$(BINARYDIR)/%.o: %.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

$(BINARYDIR):
	mkdir -p $(BINARYDIR)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BINARYDIR)
