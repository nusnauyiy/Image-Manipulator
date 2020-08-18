EXE = PNGmanipulator

OBJS_EXE = lodepng.o PNG.o HSLAPixel.o chain.o block.o main.o lab_intro.o sketchify.o

CXX = clang++
CXXFLAGS = -stdlib=libc++ -std=c++1y -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -stdlib=libc++ -std=c++1y -lc++abi -lpthread -lm

all: PNGmanipulator

$(EXE) : $(OBJS_EXE)
	$(LD) $(OBJS_EXE) $(LDFLAGS) -o $(EXE)

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp -o $@

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp -o $@

chain.o : block_chain/chain_given.cpp block_chain/chain.cpp block_chain/chain.h block_chain/block.h
	$(CXX) $(CXXFLAGS) block_chain/chain.cpp -o $@

block.o : block_chain/block.cpp block_chain/block.h cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) block_chain/block.cpp -o $@

HSLAPixel.o : cs221util/HSLAPixel.cpp cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/HSLAPixel.cpp -o $@

main.o : main.cpp cs221util/PNG.h block_chain/chain.h block_chain/block.h
	$(CXX) $(CXXFLAGS) main.cpp -o main.o

lab_intro.o : basic_effect/lab_intro.cpp basic_effect/lab_intro.h
	$(CXX) $(CXXFLAGS) basic_effect/lab_intro.cpp -o $@

sketchify.o : sketchification/sketchify.cpp sketchification/sketchify.h 
	$(CXX) $(CXXFLAGS) sketchification/sketchify.cpp -o $@

clean :
	-rm -f *.o $(EXE)