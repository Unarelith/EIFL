#---------------------------------------------------------------------------------
# Executable name
#---------------------------------------------------------------------------------
TARGET		= 	eifl

QT_LIBS		=	Core Gui Widgets Network

#---------------------------------------------------------------------------------
# Compiler executables
#---------------------------------------------------------------------------------
CC			=	gcc
CXX			=	g++

#---------------------------------------------------------------------------------
# Compiler flags
#---------------------------------------------------------------------------------
DEFINES		+=	-DQT_NO_DEBUG \
				$(foreach lib,$(QT_LIBS),-DQT_$(shell echo $(lib) | tr "[:lower:]" "[:upper:]")_LIB)

CFLAGS		+=	-g -Wall -Wextra -Wfatal-errors -Wno-variadic-macros -pedantic -MD
CXXFLAGS	+=	$(CFLAGS) -std=c++14 -static-libstdc++ -fPIC $(DEFINES)

#---------------------------------------------------------------------------------
# Libraries
#---------------------------------------------------------------------------------
LIBS		=	$(foreach lib,$(QT_LIBS),-lQt5$(lib)) -lcpr -lcurl -lqt5keychain

#---------------------------------------------------------------------------------
# Source folders
#---------------------------------------------------------------------------------
find_rec	=	$(shell find $(1) -type d)

BUILD		=	build
SOURCES		=	$(call find_rec,source) external
INCLUDES	=	$(call find_rec,include) external

#---------------------------------------------------------------------------------
# Some more include paths
#---------------------------------------------------------------------------------
CXXFLAGS	+=	-I/usr/share/qt/mkspecs/linux-g++ \
				-I/usr/include/qt \
				$(foreach lib,$(QT_LIBS),-I/usr/include/qt/Qt$(lib)) \
				-I/usr/include/x86_64-linux-gnu/qt5 \
				$(foreach lib,$(QT_LIBS),-I/usr/include/x86_64-linux-gnu/qt5/Qt$(lib))

#---------------------------------------------------------------------------------
# Additional folders for libraries
#---------------------------------------------------------------------------------
LIBDIRS		= 	/usr/lib/x86_64-linux-gnu/

ifneq ($(BUILD),$(notdir $(CURDIR)))

#---------------------------------------------------------------------------------
# Source files
#---------------------------------------------------------------------------------
export CFILES	= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
export CPPFILES	= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
export HFILES	= $(foreach dir,$(INCLUDES),$(notdir $(wildcard $(dir)/*.h)))
export HPPFILES	= $(foreach dir,$(INCLUDES),$(notdir $(wildcard $(dir)/*.hpp)))

export OUTPUT	=	$(CURDIR)/$(TARGET)

export VPATH	=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(INCLUDES),$(CURDIR)/$(dir))

export OFILES	=	$(CFILES:.c=.o) $(CPPFILES:.cpp=.oxx) \
					$(HFILES:.h=.moc.o) $(HPPFILES:.hpp=.moc.o)

export INCLUDE	=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir))

export LIBPATHS	=	$(foreach dir,$(LIBDIRS),-L$(CURDIR)/$(dir))

#---------------------------------------------------------------------------------
# Use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
	export LD	=	$(CC)
else
	export LD	=	$(CXX)
endif

#---------------------------------------------------------------------------------
# Makefile targets
#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
	@[ -e TODO ] && echo "Don't forget to read the TODO file." || echo -n
	@fixmes="$(shell cat $(shell find . -name "*.cpp" -or -name "*.hpp") | grep FIXME | wc -l)" && [ "$$fixmes" != "0" ] && echo $$fixmes "fixme(s) remaining." || echo -n

run:
	@./$(TARGET) $(RUN_ARGS)

debug:
	@./$(TARGET) $(RUN_ARGS)

clean:
	@echo "Cleaning temporary build files..."
	@rm -rf $(BUILD)

fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(TARGET)

re: fclean $(BUILD)

.PHONY: $(BUILD) run clean fclean re

#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
all: $(OUTPUT)
	@echo "Done for $(notdir $(OUTPUT))."

$(OUTPUT): $(OFILES)
	@echo "Linking $(notdir $@)..."
	@$(LD) $(OFILES) $(LIBPATHS) $(LIBS) -o $@ $(CXXFLAGS)

%.o: %.c
	@echo "=>" $(notdir $<)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

%.oxx: %.cpp
	@echo "=>" $(notdir $<)
	@$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCLUDE)

%.moc.cpp: %.hpp
	@echo "=>" $(notdir $<)
	@moc $< $(DEFINES) $(INCLUDE) -o $@ --no-notes

%.moc.cpp: %.h
	@echo "=>" $(notdir $<)
	@moc $< $(DEFINES) $(INCLUDE) -o $@ --no-notes

%.moc.o: %.moc.cpp
	@echo "=>" $(notdir $<)
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

-include *.d

.PRECIOUS: %.moc.cpp

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
