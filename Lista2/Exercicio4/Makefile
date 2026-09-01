COMPILER = g++
FLAGS = -g -O3
BINARYDIR = Binary
EXENAME = busca_local_tsp
MAIN_FILE = busca_local_tsp

TIMER_PATH 	= ../Timer
GRAPH_PATH	= ../Graph

SRCS 		=	$(filter-out $(MAIN_FILE).cpp, $(wildcard *.cpp))
SRCS_TIMER 	= 	$(filter-out $(TIMER_PATH)/main.cpp, $(wildcard $(TIMER_PATH)/*.cpp))
SRCS_GRAPH	= 	$(filter-out $(GRAPH_PATH)/main.cpp, $(wildcard $(GRAPH_PATH)/*.cpp))

OBJS_LOCAL 	= 	$(SRCS:%.cpp=$(BINARYDIR)/%.o)
OBJS_TIMER 	= 	$(SRCS_TIMER:$(TIMER_PATH)/%.cpp=$(BINARYDIR)/timer_%.o)
OBJS_GRAPH 	= 	$(SRCS_GRAPH:$(GRAPH_PATH)/%.CPP=$(BINARYDIR)/graph_%.o)
OBJS 		= 	$(OBJS_LOCAL) $(OBJS_TIMER) $(OBJS_GRAPH)

INCLUDES 	= -I. -I$(TIMER_PATH)

.PHONY: all clean run

all: $(BINARYDIR) $(EXENAME)

$(EXENAME): $(OBJS) $(BINARYDIR)/$(MAIN_FILE).o
	$(COMPILER) $(INCLUDES) $(FLAGS) $^ -o $@ -lm

# Local cpp files
$(BINARYDIR)/%.o: %.cpp
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@ -lm

# Timer cpp files
$(BINARYDIR)/timer_%.o: $(TIMER_PATH)/%.cpp
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@ -lm

# Graph cpp files
$(BINARYDIR)/timer_%.o: $(GRAPH_PATH)/%.cpp
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@ -lm

$(BINARYDIR)/$(MAIN_FILE).o: $(MAIN_FILE).cpp
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@ -lm

$(BINARYDIR):
	mkdir -p $(BINARYDIR)

run:
	./$(EXENAME)

clean:
	rm -rf $(BINARYDIR) $(EXENAME) 
