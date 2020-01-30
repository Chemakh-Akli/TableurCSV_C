SOURCES = Union.c Select.c Formatage.c Aux.c
OBJS = $(SOURCES:%.c = %.o)

gcd: $(OBJS)
	gcc -Wall -o $(OBJS)
Aux.o: Aux.c Aux.h
	gcc -Wall -c Aux.c 
Union.o: Union.c Union.h
	gcc -Wall -c Union.c
Select.o: Select.c Select.h
	gcc -Wall -c Select.c
Formatage.o: Formatage.c Formatage.h
	gcc -Wall -c Formatage.c

clean:
	rm -f gcd $(OBJS)
