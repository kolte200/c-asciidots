SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%,obj/%,$(SRC:.c=.o))

# Debug mode
#LDFLAGS = -fdiagnostics-color=always -g3
#CFLAGS = -fdiagnostics-color=always -g3

# Release mode
LDFLAGS = -O2
CFLAGS = -O2

# Test if we are on a Windows or an Unix shell
ifeq ($(shell echo "a"),"a")
    RMDIR = if exist $(1) rmdir /S /Q $(1)
	RMFILE = if exist $(1) del /S /Q $(1)
	MKDIR = if not exist $(1) mkdir $(1)
	OUTFILENAME = asciidots.exe
else
    RMDIR = rm -rf $(1)
	RMFILE = rm -f $(1)
	MKDIR = mkdir -p $(1)
	OUTFILENAME = asciidots
endif


all: clean obj $(OUTFILENAME)

obj:
	$(call MKDIR,obj)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUTFILENAME): $(OBJ)
	$(CC) -o $(OUTFILENAME) $^ $(LDFLAGS)

clean:
	$(call RMFILE,$(OUTFILENAME))
	$(call RMDIR,obj)
