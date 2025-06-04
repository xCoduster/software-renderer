ifndef ($(OS))
    OS = windows
endif

ifeq ($(OS),linux)
    CXX = g++
    LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    BUILDDIR := build-linux
    EXT := ""
else ifeq ($(OS),windows)
    CXX = x86_64-w64-mingw32-g++
    LDFLAGS = -L /root/raylib-win/src -lraylib -lgdi32 -lwinmm
    BUILDDIR := build
    EXT := ".exe"
endif

ifndef ($(TARGET))
	TARGET = DEBUG
endif

ifeq ($(TARGET),DEBUG)
    CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast -Woverloaded-virtual -fmax-errors=3 -O0 -g
else ifeq ($(TARGET),RELEASE)
    CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast -Woverloaded-virtual -fmax-errors=3 -O3
endif

DEPFLAGS = -MMD -MF $(DEPDIR)/$*.d
INCFLAGS = -Isrc -isystem /usr/local/include

SRCS := $(shell find -path "./src/*.cc")

OBJDIR := $(BUILDDIR)/objs
OBJS := $(addprefix $(OBJDIR)/,$(notdir $(basename $(SRCS))))
OBJS := $(addsuffix .o,$(OBJS))

DEPDIR := $(BUILDDIR)/deps
DEPFILES := $(addprefix $(DEPDIR)/,$(notdir $(basename $(SRCS))))
DEPFILES := $(addsuffix .d,$(DEPFILES))

# nya mappar måste läggas till här, separerade med ":"
VPATH = src:src/render:src/world:src/math

.PHONY: default
default: run

.PHONY: build
build: $(BUILDDIR)/game

.PHONY: show
show:
	@echo $(SRCS)
	@echo $(OBJS)

$(OBJDIR):
	mkdir -p $@

$(DEPDIR):
	mkdir -p $@

# $(var) ger värdet av variabeln
# $@ refererar till målet och $^ till beroenden
$(BUILDDIR)/game: $(OBJS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# % är en wildcard , $< refererar till första beroendet
#%.o: %.cc
$(OBJDIR)/%.o: %.cc $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCFLAGS) $(DEPFLAGS)

.PHONY: run
run: $(BUILDDIR)/game
	./$(BUILDDIR)/game$(EXT)

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)

$(DEPFILES):
include $(DEPFILES)
