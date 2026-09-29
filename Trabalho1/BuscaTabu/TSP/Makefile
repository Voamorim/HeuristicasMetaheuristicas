COMPILER 			= g++

FLAGS				= -std=c++17 -O3 -Wshadow -flto
LDFLAGS				= -std=c++17 -O3 -flto -lm

BINARYDIR 			= Binary
EXENAME 			= simulated_annealing_tsp
MAIN_FILE 			= simulated_annealing_tsp
TARGET 				= $(BINARYDIR)/$(EXENAME)

MODULES_PATH		= ../../Modules
TSP_MODULES_PATH 	= $(MODULES_PATH)/TSP

TIMER_PATH 			= $(MODULES_PATH)/Timer
GRAPH_PATH			= $(TSP_MODULES_PATH)/Graph
UTILS_PATH 			= $(TSP_MODULES_PATH)/Utils
TSP_PATH 			= $(TSP_MODULES_PATH)/TSP

SRCS 				= $(filter-out $(MAIN_FILE).cpp ./$(MAIN_FILE).cpp, $(wildcard *.cpp))
SRCS_TIMER 			= $(filter-out $(TIMER_PATH)/main.cpp, $(wildcard $(TIMER_PATH)/*.cpp))
SRCS_GRAPH			= $(filter-out $(GRAPH_PATH)/main.cpp, $(wildcard $(GRAPH_PATH)/*.cpp))
SRCS_UTILS			= $(filter-out $(UTILS_PATH)/main.cpp, $(wildcard $(UTILS_PATH)/*.cpp))
SRCS_TSP			= $(filter-out $(TSP_PATH)/main.cpp, $(wildcard $(TSP_PATH)/*.cpp))

OBJS_LOCAL 			= $(SRCS:%.cpp=$(BINARYDIR)/%.o)
OBJS_TIMER 			= $(SRCS_TIMER:$(TIMER_PATH)/%.cpp=$(BINARYDIR)/timer_%.o)
OBJS_GRAPH 			= $(SRCS_GRAPH:$(GRAPH_PATH)/%.cpp=$(BINARYDIR)/graph_%.o)
OBJS_UTILS 			= $(SRCS_UTILS:$(UTILS_PATH)/%.cpp=$(BINARYDIR)/utils_%.o)
OBJS_TSP 			= $(SRCS_TSP:$(TSP_PATH)/%.cpp=$(BINARYDIR)/tsp_%.o)
OBJS_MAIN 			= $(BINARYDIR)/$(MAIN_FILE).o

OBJS 				= $(OBJS_LOCAL) $(OBJS_TIMER) $(OBJS_GRAPH) $(OBJS_UTILS) $(OBJS_TSP) $(OBJS_MAIN)

INCLUDES 			= -I. -I$(TIMER_PATH) -I$(GRAPH_PATH) -I$(UTILS_PATH) -I$(TSP_PATH)

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

# Graph cpp files
$(BINARYDIR)/graph_%.o: $(GRAPH_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# Utils cpp files
$(BINARYDIR)/utils_%.o: $(UTILS_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# TSP cpp files
$(BINARYDIR)/tsp_%.o: $(TSP_PATH)/%.cpp | $(BINARYDIR)
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
