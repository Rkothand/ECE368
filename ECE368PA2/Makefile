# ***
# *** DO NOT modify this file
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS = -DTEST_MAIN -DTEST_COUNTINT -DTEST_READINT -DTEST_WRITEINT -DTEST_COMPAREINT

SRCS =fileconv.c pa2.c hbt.c 
OBJS = $(SRCS:%.c=%.o)

pa2: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o pa2

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testmemory: pa2
	$(VAL) ./pa2 inputs/input3 output3
#testing only input3 and output3

testall: test1 test2 test3 test4 test1a

test1: pa2
	./pa2

test1a: hbt
	./pa4 -b inputs/kkd.txt
test1b: hbt
	./pa4 -e inputs/kkd.txt	
test1c: hbt
	./pa4 -x inputs/kkd.txt		

test2: hbt
	./pa4 -b inputs/ops1.b
	

test3: hbt
	./pa4 inputs/input3 output3
	diff output3 expected/expected3

test4: hbt
	./hbt inputs/input4 output4
	diff output4 expected/expected4

clean: # remove all machine generated files
	rm -f hbt *.o output?
