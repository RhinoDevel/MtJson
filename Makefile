# MT, 2016apr02
#
# Original source: http://mrbook.org/blog/tutorials/make/

CC=gcc
#CFLAGS=-c -O3 -std=gnu11 -Wall -DNDEBUG
CFLAGS=-c -g -std=gnu11 -Wall
#LDFLAGS=
LDFLAGS=-g
SOURCES=main.c FileSys.c StackEle.c json_state_obj_begin.c JsonArr.c Str.c json_state_obj_end.c JsonEle.c json_state_prop_begin.c JsonObj.c json.c json_state_string.c JsonProp.c json_state_arr_begin.c json_state_val_begin.c JsonStateInput.c json_state_arr_end.c json_state_val_end.c JsonVal.c json_state_begin.c json_state_val_next.c Obj.c json_state_boolean.c json_state_null.c Stack.c json_state_number.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=mtjson

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
