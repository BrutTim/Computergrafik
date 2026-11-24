TARGET = uebung2-terminal.exe
SOURCES = main.cpp Planet.cpp Color.cpp Matrix.cpp cg_math.cpp
HEADERS = Planet.h Color.h Matrix.h Vector.h cg_math.h glut.h freeglut.h freeglut_std.h freeglut_ext.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS) freeglut.lib
	cl /nologo /EHsc $(SOURCES) /Fe:$(TARGET) /link /DEBUG:NONE

run: all
	.\$(TARGET)

clean:
	if exist $(TARGET) del /q $(TARGET)
	for %f in (main Planet Color Matrix cg_math) do @if exist %f.obj del /q %f.obj
