INC = .
CFLAGS  = -Wall -Werror -Wextra -Wno-unused-parameter -pedantic -O2
C_OBJS = $(patsubst %.c,%.o,$(wildcard *.c))
SUB_C_OBJ = $(patsubst $(EX_DIR)/%.c,$(EX_DIR)/%.o,$(wildcard $(EX_DIR)/*.c))

EX_DIR = examples
TARGET =  test_program

#add the name of your test program below
EXAMPLE = test_root test_last_descendant test_is_equal test_is_sibling test_linear_id test_smallest_ancestor

EXAMPLE_DIR = $(addprefix $(EX_DIR)/,$(EXAMPLE))
DEP_OBJ = tree_based_quadrants.o

all : $(TARGET) $(EXAMPLE_DIR)

%.o : %.c
	gcc -c $< -o $@
	
$(EX_DIR)/%.o : $(EX_DIR)/%.c
	gcc -I$(INC) -c $< -o $@

$(TARGET) : $(C_OBJS)
	gcc $(CFLAGS) $^ -o $@

$(EXAMPLE_DIR) : % : %.o $(DEP_OBJ)
	gcc $(CFLAGS) $^ -o $@

clean :
	-rm $(C_OBJS) $(SUB_C_OBJ)
	-rm -f $(EXAMPLE_DIR) $(TARGET)
