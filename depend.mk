cascara.o: cascara.cpp cascara.h gba.h gbaextend.h
font.o: font.cpp font.h
gba.o: gba.cpp gba.h
gbaextend.o: gbaextend.cpp gbaextend.h gba.h
main.o: main.cpp gba.h font.h cascara.h gbaextend.h
oldFunctions.o: oldFunctions.cpp
screenblocks.o: screenblocks.cpp cascara.h gba.h gbaextend.h
