
TARGETS := count-blanks	\
		i2o-dblank	\
		echo-tab	\
		one-word-perline \
		word-histogram	\
		max-line		\
		great-80-chars-line	
default:
	echo "do nothing for save"
all: $(TARGETS)
	@echo "done"
count-blanks:
	@gcc -o $@ count-blanks.c
i2o-dblank:
	@gcc -o $@ i2o-dblank.c
echo-tab:
	@gcc -o $@ echo-tab.c
one-word-perline:
	@gcc -o $@ one-word-perline.c
word-histogram:
	@gcc -o $@ word-histogram.c
max-line:
	@gcc -o $@ max-line.c
great-80-chars-line:
	@gcc -o $@ great-80-chars-line.c
clean:
	@rm $(TARGETS)
