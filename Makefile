LIB_DIR = lib/
BIN_DIR = bin/
SRC_DIR = src/

MAJOR_VERSION = 1
MINOR_VERSION = 0
# BUILD_VERSION = `cat bld_version`
# TODO: Auto increment version

LIBRARIES = Logger Stack

CXXFLAGS = `cat $(LIB_DIR)Cflags`
SANFLAGS = `cat $(LIB_DIR)SanitizeFlags`
LXXFLAGS = -L$(LIB_DIR) $(addprefix -l, $(LIBRARIES))

CXXFLAGS += -DMAJOR_VERSION=$(MAJOR_VERSION)
CXXFLAGS += -DMINOR_VERSION=$(MINOR_VERSION)
# CXXFLAGS += -DBUILD_VERSION=$(BUILD_VERSION)

# CXXFLAGS += $(SANFLAGS)

SOURCES = Tree/Tree.cpp StringBuffer/StringBuffer.cpp Akkinator.cpp Akkinator_Verbose.cpp

HEADERS_CFG = 

EXECUTABLE  = main.cpp

SRC = $(SOURCES) $(EXECUTABLE)

OBJ = $(SRC:.cpp=.o) 

TARGETS = main

all: $(TARGETS)
	# ./increaseVersion.sh bld_version

main: $(addprefix $(BIN_DIR), $(OBJ))
	g++ $(CXXFLAGS) $^ $(LXXFLAGS) -o $@

$(BIN_DIR)%.o : $(SRC_DIR)%.cpp $(addprefix $(SRC_DIR), $(HEADERS_COM)) 
	g++ -c $(CXXFLAGS) $(LXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm $(BIN_DIR)*
	rm $(TARGETS)
