# ***
# *** DO NOT modify this file 
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla 
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose
TESTFALGS = -DTEST_BUILDTREE -DTEST_PRINTPATHX

SRCS = shell_array.c shell_list.c pa1.c
OBJS = $(SRCS:%.c=%.o)

# PA1: $(OBJS)
# 	$(GCC) $(OBJS) -o PA1

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

testall:

PA1: PA1.c
	gcc PA1.c -o PA1

run: PA1
	./PA1 inputs/1K.b 


# test1: PA1
# 	./PA1 inputs/test1in inputs/test1post  output1
# 	diff -w output1 expected/expected1

# test2: PA1
# 	./PA1 inputs/test2in inputs/test2post  output2
# 	diff -w output2 expected/expected2

# test3: PA1
# 	./hw15 inputs/test3in inputs/test3post  output3
# 	diff -w output3 expected/expected3

# test4: PA1
# 	./hw15 inputs/test4in inputs/test4post  output4
# 	diff -w output4 expected/expected4

# test5: PA1
# 	./hw15 inputs/test5in inputs/test5post  output5
# 	diff -w output5 expected/expected5

# test6: PA1
# 	./hw15 inputs/test6in inputs/test6post  output6
# 	diff -w output6 expected/expected6

memory: PA1
	$(VAL) ./hw15 inputs/test6in inputs/test6post  test6memory

clean: # remove all machine generated files
	rm -f hw15 *.o output? vallog testgen



