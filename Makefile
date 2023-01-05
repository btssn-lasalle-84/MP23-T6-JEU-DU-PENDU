TARGET = pendu.out
SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.h)
OBJ := $(patsubst %.cpp, %.o, $(SOURCES))

CFLAGS = -std=c++11 -Wall -I.
CXX = g++ $(CFLAGS) -c
LD = g++ -o
RM = rm -f

all: $(TARGET)

$(TARGET): $(OBJ)
	$(LD) $@ $^

%.o: %.cpp %.h
	$(CXX) $(CFLAGS) $<


.PHONY: check cppcheck format clean cleanall

check:
	clang-tidy $(SOURCES) --quiet -header-filter='.*' -checks=-*,boost-*,bugprone-*,performance-*,readability-*,portability-*,modernize-use-nullptr,clang-analyzer-*,cppcoreguidelines-* --format-style=none -- -std=c++11

cppcheck:
	cppcheck --enable=all --std=c++11 --platform=unix64 --suppress=missingIncludeSystem --quiet $(SOURCES)

format:
	find . -regex '.*\.\(cpp\|h\)' -exec clang-format -i --style=file {} \;

clean:
	$(RM) *.o

cleanall:
	$(RM) *.o* *.*~ $(TARGET)
