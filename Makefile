SYSCONF_LINK = g++
CPPFLAGS     =
LDFLAGS      =
LIBS         =

DESTDIR = ./bin/
TARGET  = main

dirs := . Lexer Parcer MachineCode Compiler
OBJECTS := $(foreach dir,$(dirs),$(patsubst $(dir)/%.cpp,$(dir)/%.o,$(wildcard $(dir)/*.cpp)))

all: $(DESTDIR)$(TARGET)

$(DESTDIR)$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -Wall -g $(LDFLAGS) -o $(DESTDIR)$(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp
	$(SYSCONF_LINK) -Wall -g $(CPPFLAGS) -c $(CFLAGS) $< -o $@

clean:
	$(foreach dir,$(dirs), rm -f $(dir)/*.o $(objects) mp1)
	rm -f $(DESTDIR)$(TARGET)

