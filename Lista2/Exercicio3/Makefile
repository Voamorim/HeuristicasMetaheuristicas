COMPILER = g++
FLAGS = -g -O3
BINARYDIR = Binary
EXENAME = busca_local_mochila
MAIN_FILE = busca_local_mochila

TIMER_PATH 	= ../Timer

SRCS 		=	$(filter-out $(MAIN_FILE).cpp, $(wildcard *.cpp))
SRCS_TIMER 	= 	$(filter-out $(TIMER_PATH)/main.cpp, $(wildcard $(TIMER_PATH)/*.cpp))

OBJS_LOCAL 	= 	$(SRCS:%.cpp=$(BINARYDIR)/%.o)
OBJS_TIMER 	= 	$(SRCS_TIMER:$(TIMER_PATH)/%.cpp=$(BINARYDIR)/timer_%.o)
OBJS 		= 	$(OBJS_LOCAL) $(OBJS_TIMER)

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

$(BINARYDIR)/$(MAIN_FILE).o: $(MAIN_FILE).cpp
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@ -lm

$(BINARYDIR):
	mkdir -p $(BINARYDIR)

run:
	./$(EXENAME)

clean:
	rm -rf $(BINARYDIR) $(EXENAME) 
