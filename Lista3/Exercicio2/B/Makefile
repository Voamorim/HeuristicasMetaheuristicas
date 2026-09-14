COMPILER 	= g++

FLAGS 		= -O3 -Wshadow -flto
LDFLAGS 	= -O3 -flto -lm

BINARYDIR 	= Binary
EXENAME 	= mochila01_itensmaisleves
MAIN_FILE 	= mochila01_itensmaisleves

TIMER_PATH 	= ../../Timer

SRCS 		= $(filter-out $(MAIN_FILE).cpp, $(wildcard *.cpp))
SRCS_TIMER 	= $(filter-out $(TIMER_PATH)/main.cpp, $(wildcard $(TIMER_PATH)/*.cpp))

OBJS_LOCAL 	= $(SRCS:%.cpp=$(BINARYDIR)/%.o)
OBJS_TIMER 	= $(SRCS_TIMER:$(TIMER_PATH)/%.cpp=$(BINARYDIR)/timer_%.o)
OBJS_MAIN 	= $(BINARYDIR)/$(MAIN_FILE).o	

OBJS 		= $(OBJS_LOCAL) $(OBJS_TIMER) $(OBJS_MAIN)

INCLUDES 	= -I. -I$(TIMER_PATH)

.PHONY: all clean run

all: $(EXENAME)

$(EXENAME): $(OBJS) 
	$(COMPILER) $(OBJS) -o $@ $(LDFLAGS) 

# Local cpp files
$(BINARYDIR)/%.o: %.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

# Timer cpp files
$(BINARYDIR)/timer_%.o: $(TIMER_PATH)/%.cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

$(BINARYDIR)/$(MAIN_FILE).o: $(MAIN_FILE).cpp | $(BINARYDIR)
	$(COMPILER) $(INCLUDES) $(FLAGS) -c $< -o $@

$(BINARYDIR):
	mkdir -p $(BINARYDIR)

run: $(EXENAME)
	./$(EXENAME)

clean:
	rm -rf $(BINARYDIR) $(EXENAME) 
