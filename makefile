EXEC   = integration_test

OPTIMIZE =  -O2  


OBJS   = main.o rk_int.o 

CC     = g++

INCL   = rk_int.h

LIBS   = -lm  -lgsl 

CFLAGS = $(OPTIMIZE) 

$(EXEC): $(OBJS) 
	 $(CC) $(OBJS) $(LIBS) -o $(EXEC)   

$(OBJS): $(INCL) 

.PHONY : clean

clean:
	 rm -f $(OBJS) $(EXEC)

