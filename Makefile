TARGET			?= xqc

BUILD_DIR		?= build
OBJS_DIR		?= $(BUILD_DIR)/tmp
SRC_DIRS		?= src

SRCS				:= $(shell find $(SRC_DIRS) -name *.c)
OBJS				:= $(SRCS:%=$(OBJS_DIR)/%.o)
DEPS				:= $(OBJS:.o=.d)

INC_DIRS		:= $(shell find $(SRC_DIRS) -type d)
INC_FLAGS		:= $(addprefix -I,$(INC_DIRS))

CFLAGS			?= -Wall $(INC_FLAGS) -MMD -MP
CC					:= gcc


$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(BUILD_DIR)/$@ $(LDFLAGS)

$(TARGET)-debug: $(OBJS)
	$(CC) -g $(OBJS) -o $(BUILD_DIR)/$@ $(LDFLAGS)

$(OBJS_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: test

test:
	./$(BUILD_DIR)/xqc build /home/runner/xQuantico/src/test.xqua

.PHONY: debugtest

debugtest:
	valgrind -v --leak-check=yes ./$(BUILD_DIR)/xqc build /home/runner/xQuantico/src/test.xqua


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P			?= mkdir -p
