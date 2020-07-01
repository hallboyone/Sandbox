CC := g++ # This is the main compiler

SRCDIR   := src
HDDIR    := include
BUILDDIR := build
TESTDIR  := tests
LIBDIR   := /home/hallboyone/Dev/HB1/lib/HB1
TARGET   := stlobj

SRCEXT  := cpp
HDEXT   := hpp

#Search the src dir for all file with a name matching *.cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

#Make the objects from the Sources by exchanging the src dir for the build dir
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

#The flags to be used
CFLAGS  := -Wall -ggdb3 -Werror -Wsign-compare -Wwrite-strings -Wtype-limits -std=c++11
LIB     := -L $(LIBDIR) -lCmdLnFlags -Wl,-rpath=$(LIBDIR)
SRCINC  := -I include 
LIBINC  := -I ~/Dev/HB1/include

# -Xlinker --verbose
$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@echo " $(CC) $(CFLAGS) $(SRCINC) $(LIBINC) -c -o $@ $<"; $(CC) $(CFLAGS) $(SRCINC) $(LIBINC) -c -o $@ $< 

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR)/* $(TARGET)"; $(RM) -r $(BUILDDIR)/* $(TARGET)

.PHONY: clean testall
