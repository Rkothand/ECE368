# ***
# *** DO NOT modify this file
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS = -DTEST_MAIN -DTEST_COUNTINT -DTEST_READINT -DTEST_WRITEINT -DTEST_COMPAREINT

SRCS =fileconv.c pa3.c fwt.c 
OBJS = $(SRCS:%.c=%.o)

pa3: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o pa3

fileconv: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o fileconv

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testmemory: pa3
	$(VAL) ./pa3 inputs/examples/7_7.b outputs/7_7.t  outputs/7_7.f outputs/7_7.p
#testing only input3 and output3

testall:  test1b test1c test1d test1e testmemory

test1: pa3
	./pa3

test1a: pa3
	./pa3 inputs/examples/5_5.t
test1b: pa3
	./pa3 inputs/examples/4_5.b outputs/4_5.t  outputs/4_5.f outputs/4_5.p 
	diff inputs/examples/4_5.t outputs/4_5.t
	diff inputs/examples/4_5.ft outputs/4_5.ft
	diff inputs/examples/4_5.f outputs/4_5.f		
	diff inputs/examples/4_5.p outputs/4_5.p
	diff inputs/examples/4_5.pt outputs/4_5.pt
test1c: pa3
	./pa3 inputs/examples/5_4.b outputs/5_4.t  outputs/5_4.f outputs/5_4.p 
	diff inputs/examples/5_4.ft outputs/5_4.ft
	diff inputs/examples/5_4.f outputs/5_4.f
	diff inputs/examples/5_4.t outputs/5_4.t
	diff inputs/examples/5_4.p outputs/5_4.p
	diff inputs/examples/5_4.pt outputs/5_4.pt
test1d: pa3
	./pa3 inputs/examples/5_5.b outputs/5_5.t  outputs/5_5.f outputs/5_5.p 	
	diff inputs/examples/5_5.t outputs/5_5.t
	diff inputs/examples/5_5.ft outputs/5_5.ft
	diff inputs/examples/5_5.f outputs/5_5.f
	diff inputs/examples/5_5.p outputs/5_5.p
	diff inputs/examples/5_5.pt outputs/5_5.pt

test1e: pa3
	./pa3 inputs/examples/7_7.b outputs/7_7.t  outputs/7_7.f outputs/7_7.p 	
	diff inputs/examples/7_7.t outputs/7_7.t
	diff inputs/examples/7_7.ft outputs/7_7.ft
	diff inputs/examples/7_7.f outputs/7_7.f
	diff inputs/examples/7_7.p outputs/7_7.p
	diff inputs/examples/7_7.pt outputs/7_7.pt


clean: # remove all machine generated files
	rm -f pa3 *.o outputs?
