COMPILER 			= g++

FLAGS				= -std=c++17 -O3 -Wshadow -flto
LDFLAGS				= -std=c++17 -O3 -flto -lm

BINARYDIR 			= Binary
EXENAME 			= main
MAIN_FILE 			= main
TARGET 				= $(BINARYDIR)/$(EXENAME)

ROOT_DIR 			= ../..
MODULES_PATH		= $(ROOT_DIR)/Modules
TSP_MODULES_PATH 	= $(MODULES_PATH)/TSP

TIMER_PATH 			= $(MODULES_PATH)/Timer
UTILS_PATH 			= $(MODULES_PATH)/Utils
GRAPH_PATH			= $(TSP_MODULES_PATH)/Graph
TSP_PATH 			= $(TSP_MODULES_PATH)/TSP
BT_PATH				= BuscaTabu_TSP

SRCS 				= $(filter-out $(MAIN_FILE).cpp ./$(MAIN_FILE).cpp, $(wildcard *.cpp))
SRCS_TIMER 			= $(wildcard $(TIMER_PATH)/*.cpp)
SRCS_UTILS			= $(wildcard $(UTILS_PATH)/*.cpp)
SRCS_GRAPH			= $(wildcard $(GRAPH_PATH)/*.cpp)
SRCS_TSP			= $(wildcard $(TSP_PATH)/*.cpp)
SRCS_BT				= $(wildcard $(BT_PATH)/*.cpp)

OBJS_MAIN 			= $(BINARYDIR)/$(MAIN_FILE).o
OBJS_LOCAL 			= $(patsubst %.cpp, $(BINARYDIR)/%.o, $(notdir $(SRCS)))
OBJS_TIMER			= $(patsubst %.cpp, $(BINARYDIR)/timer_%.o, $(notdir $(SRCS_TIMER)))
OBJS_UTILS			= $(patsubst %.cpp, $(BINARYDIR)/utils_%.o, $(notdir $(SRCS_UTILS)))
OBJS_GRAPH			= $(patsubst %.cpp, $(BINARYDIR)/graph_%.o, $(notdir $(SRCS_GRAPH)))
OBJS_TSP			= $(patsubst %.cpp, $(BINARYDIR)/tsp_%.o, $(notdir $(SRCS_TSP)))
OBJS_BT				= $(patsubst %.cpp, $(BINARYDIR)/bt_%.o, $(notdir $(SRCS_BT)))

OBJS 				= $(OBJS_LOCAL) $(OBJS_TIMER) $(OBJS_UTILS) $(OBJS_GRAPH) $(OBJS_TSP) $(OBJS_BT) $(OBJS_MAIN)

INCLUDES 			= -I. -I$(TIMER_PATH) -I$(UTILS_PATH) -I$(GRAPH_PATH) -I$(TSP_PATH) -I$(BT_PATH)

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

# Graph files
$(BINARYDIR)/graph_%.o: $(GRAPH_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# TSP files
$(BINARYDIR)/tsp_%.o: $(TSP_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# Tabu Search files
$(BINARYDIR)/bt_%.o: $(BT_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

$(BINARYDIR):
	mkdir -p $(BINARYDIR)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BINARYDIR)
