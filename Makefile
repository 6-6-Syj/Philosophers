VPATH = src:include

NAME = philo
HEADER = philo.h

DEPS   = $(OBJS:%.o=$(OBJS_DIR)%.d)
-include $(DEPS)

CC = cc
FLAGS = -Wall -Werror -Wextra -Iinclude -pthread -MMD -MP -g3

DEBUG_FLAGS = -g3 -fsanitize=thread
# setarch $(uname -m) -R
VALGRIND = valgrind --tool=drd --trace-barrier=yes --trace-cond=yes --show-stack-usage=yes

#########################################################################################
#																						#
#										   3 threads		6 threads					#
#		tool=drd & flags 					~2 min										#
#		--tool=helgrind 					~1 min			  +2min						#
#																						#
#########################################################################################

SRCS = 	main.c					\
		parsing.c				\
		parsing_utils.c			\
		init.c					\
		getter_setter.c			\
		actions.c				\
		print.c					\
		time.c					\
		utils.c					\
		philosophers.c			\
		watcher.c				\

OBJS_DIR = .obj/
OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

.PHONY: all clean fclean re force debug

all: $(NAME)

$(OBJS_DIR)%.o: %.c $(HEADER) Makefile
	@mkdir -p $(OBJS_DIR)
	@echo "$(MAGENTA)$(BOLD)[Compiling...]$(RESET) $<"
	@$(CC) $(FLAGS) -c $< -o $@


$(NAME): Makefile $(HEADER) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)\nCompilation successful!$(RESET)"
	@echo "$(CYAN)  └─ Ready to run: ./$(NAME)\n$(RESET)"


clean:
	@rm -rf $(OBJS_DIR) $(OBJS)
	@echo "$(RED)$(BOLD)\nCleaning up project files...$(RESET)"
	@echo "$(YELLOW)  └─ Removing object files$(RESET)"


fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)$(BOLD)\nFull clean-up completed:$(RESET)"
	@echo "$(YELLOW)  ├─ Removed object files and directories$(RESET)"
	@echo "$(YELLOW)  └─ Deleted executable: $(NAME)\n$(RESET)"


re: fclean all

debug: FLAGS += $(DEBUG_FLAGS)
debug: $(NAME)

force:
	@true

# **** COLORS **** #

BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m
BOLD = \033[1m
RESET = \033[0m
