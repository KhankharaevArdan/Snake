CXX = g++
CXXFLAGS = -IIncludes
PROG = snake
OBJ = view.o Tview.o Gview.o model.o human.o snake.o
SRC = view.cpp Tview.cpp Gview.cpp model.cpp human.cpp snake.cpp

SRCDIR = Source
INCLDIR = Includes
BUILDDIR = Build

all : $(PROG)

$(PROG) : $(addprefix $(BUILDDIR)/, $(OBJ))
	$(CXX) $(CXXFLAGS) $^ -o $@ 
$(addprefix $(BUILDDIR)/, $(OBJ)) : $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp $(INCLDIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
.PHONY: depend

clean : 
	$(RM) $(BUILDDIR)/*.o

depend : 
	$(CXX) $(CXXFLAGS) $(addprefix $(SRCDIR)/, $(SRC)) -MM > $(BUILDDIR)/.depend 

-include $(BUILDDIR)/.depend