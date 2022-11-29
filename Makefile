# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llord <llord@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 15:09:46 by llord             #+#    #+#              #
#    Updated: 2022/11/29 13:15:13 by llord            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#                                  COLOURS                                     #
#------------------------------------------------------------------------------#

DEF_COLOR = \033[0;39m
MAGENTA = \033[0;95m
RED = \033[0;91m
YELLOW = \033[0;93m
GREEN = \033[0;92m
CYAN = \033[0;96m
BLUE = \033[0;94m
GRAY = \033[0;90m
WHITE = \033[0;97m

#------------------------------------------------------------------------------#
#                                  GENERICS                                    #
#------------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all bonus clean fclean re run lldb leaks

# Hide calls
export VERBOSE	=	TRUE
ifeq ($(VERBOSE),TRUE)
	HIDE =
else
	HIDE = @
endif


#------------------------------------------------------------------------------#
#                                 VARIABLES                                    #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -rf
INCLUDE =	-I include
LIBS	=	libs/MLX42/libmlx42.a -lglfw -L "/Users/$$USER/.brew/opt/glfw/lib/"

# Dir and file names
NAME	=	so_long
SRCDIR	=	src/
OBJDIR	=	bin/
SRCS	=	$(wildcard $(SRCDIR)*.c)
OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))


#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	$(HIDE)$(CC) $(CFLAGS) -o $@ $^ $(INCLUDE) $(LIBS)
	@echo "$(GREEN)Files compiled$(DEF_COLOR)"

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	$(HIDE)$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(OBJDIR):
	$(HIDE)mkdir -p $(OBJDIR)

# Removes objects
clean:
	$(HIDE)$(RM) $(OBJS)
	@echo "$(MAGENTA)Object files cleaned$(DEF_COLOR)"

# Removes objects and executables
fclean: clean
	$(HIDE)$(RM) $(NAME)
	@echo "$(RED)Executable files cleaned$(DEF_COLOR)"

# Removes objects and executables and remakes
re: fclean all
	@echo "$(CYAN)Cleaned and rebuilt everything!$(DEF_COLOR)"

# Runs the resulting file
run: re
	@echo "$(BLUE)Starting the program...$(DEF_COLOR)"
	./$(NAME) ./levels/map1.ber ./levels/map2.ber ./levels/map3.ber ./levels/map4.ber ./levels/map5.ber ./levels/map6.ber ./levels/map7.ber

lldb:
	@echo "$(RED)Starting the debugging...$(DEF_COLOR)"
	gcc -g -Wall -Werror -Wextra *.h src/*.c -I include libs/MLX42/libmlx42.a -lglfw -L "/Users/$$USER/.brew/opt/glfw/lib/"
	lldb ./a.out ./levels/map1.ber ./levels/map2.ber ./levels/map3.ber ./levels/map4.ber ./levels/map5.ber ./levels/map6.ber ./levels/map7.ber


leaks:
	@echo "$(RED)Starting the debugging...$(DEF_COLOR)"
	gcc -Wall -Werror -Wextra *.h src/*.c -I include libs/MLX42/libmlx42.a -lglfw -L "/Users/$$USER/.brew/opt/glfw/lib/"
	leaks --atExit -- ./a.out ./levels/bug7.ber