
CFLAGS += -Wall -Wextra -ansi -pedantic -D_BSD_SOURCE -g
# Modules and stuff might ignore some data. We don’t want no warning from them.
CFLAGS += -Wno-unused-parameter

Q := @
N := 

%.o: %.c
	@$Necho "  [CC]  $@"
	$Q${CC} ${CFLAGS} -c $<

%.o: %.c %.h
	@$Necho "  [CC]  $@"
	$Q${CC} ${CFLAGS} -c $<

main: main.o recipe.o modules.o ui.o workdir.o download.o configuration.o extraction.o build.o assemble.o
	@$Necho "  [LD]  $@"
	$Q${CC} -o main -larchive -lyaml $^

clean:
	rm *.o main

