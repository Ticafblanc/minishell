# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 10:09:10 by mdoquocb          #+#    #+#              #
#    Updated: 2022/11/24 14:23:28 by tblanco          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT = minishell

#  BINARY  #
BIN_PATH = Bin
BIN_NAME = $(PROJECT)
BIN = $(addprefix $(BIN_PATH)/,$(BIN_NAME))

#  INCLUDES  #
INC_PATH = ./Includes
INC_FLAGS = -I $(INC_PATH)

#  LIB => libft  #
LIB_NAME = ft
LIB_PATH = ../libft/
LIB_INC_PATH = includes
LIB_BIN_PATH = Bin
LIB = $(addprefix $(LIB_PATH),$(LIB_NAME))
INC_FLAGS += -I $(LIB_PATH)$(LIB_INC_PATH)
LIB_FLAGS = -L $(LIB_PATH)$(LIB_BIN_PATH) -l $(LIB_NAME)

#  LIB => readline  #
LIB_NAME_1 = readline
LIB_NAME_2 = history
LIB_PATH_1 = ../readline
LIB_1 = $(addprefix $(LIB_PATH_1),$(LIB_NAME_1))
LIB_2 = $(addprefix $(LIB_PATH_1),$(LIB_NAME_2))

#INC_FLAGS += -I ~/.brew/opt/readline/include
INC_FLAGS += -DREADLINE_LIBRARY -I $(LIB_PATH_1)

#LIB_FLAGS += -L ~/.brew/opt/readline/lib -lreadline -lncurses
#LIB_FLAGS += -L../readline -lreadline -lncurses
LIB_FLAGS += -L $(LIB_PATH_1) -l $(LIB_NAME_1) -l $(LIB_NAME_2) -l curses #

#  PATH CONFIGURATION  ##
SRC_PATH = Sources
OBJ_PATH = $(BIN_PATH)/Objects

#  DIRECTORIES CONFIGURATION #
DIRS = $(shell find $(SRC_PATH) -type d | sed 's/$(SRC_PATH)\///g' | sed -n '1!p')
SRCDIRS	= $(foreach dir, $(DIRS), $(addprefix $(SRC_PATH)/, $(dir)))
OBJDIRS = $(foreach dir, $(DIRS), $(addprefix $(OBJ_PATH)/, $(dir)))

#  SOURCES  #
# SRC = $(wildcard $(SRC_PATH)/*.c)
# SRC += $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))
SRC = Sources/handle_signals.c Sources/init.c Sources/main.c Sources/status.c Sources/utils/development.c Sources/utils/utils.c Sources/utils/utils_env.c Sources/utils/utils_env_line.c Sources/utils/utils_errors.c Sources/utils/utils_free.c Sources/utils/utils_libc.c Sources/utils/utils_tabstr.c Sources/builtins/builtins.c Sources/builtins/cd.c Sources/builtins/echo.c Sources/builtins/env.c Sources/builtins/exit.c Sources/builtins/export.c Sources/builtins/pwd.c Sources/builtins/unset.c Sources/execution/funcs_execute.c Sources/execution/interpret_vars.c Sources/execution/main_execute.c Sources/execution/manage_arg.c Sources/execution/manage_wildcard.c Sources/execution/strmatch.c Sources/execution/utils_execute.c Sources/parsing/main_parsing.c Sources/parsing/manage_braces.c Sources/parsing/manage_operators.c Sources/parsing/manage_redirection.c Sources/parsing/utils_parsing.c Sources/parsing/utils_parsing_findnextword.c

#  OBJECTS  #
OBJ = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))

#  FLAGS  #
CC = gcc
CC_FLAGS =  -g -Wall -Wextra -Werror 
#CC_FLAGS =  -g 
CL = rm -rf

LEAK = leaks -atExit --
LEAKS = valgrind --leak-check=full --track-fds=yes --trace-children=yes -s -q

#  COLORS STR #
GREEN = "\x1b[32m""\x1b[M"
RED= "\x1b[31m""\x1b[M"
BLUE = "\x1b[34m""\x1b[M"

#  COLORS  #
ENDCOL = \033[0m
REDS = \033[1;31m
YEL = \033[1;33m
ORG = \033[0;33m
GRN = \033[1;32m
DGRAY = \033[1;30m
BLU = \033[1;34m
RESET ="\e[0m"

#  COMPILATION  #

all: buildrepo $(BIN)
		@echo $(GREEN) Compilation $(PROJECT) is completed !!
		
$(OBJ_PATH)%.o:$(SRC_PATH)%.c
		@$(CC) $(CC_FLAGS) $(INC_FLAGS) -c $< -o $@
		@echo $(BLUE) $(notdir $@) is created !!

$(BIN): title libft readline directory $(OBJ) 
		@$(CC) $(OBJ) $(LIB_FLAGS) -o $(BIN) 
		@echo $(BLUE) $(notdir $(BIN)) is created !!

title: 
		@echo $(GREEN)******************$(PROJECT)******************
		@printf "\n${BLU} ==>Compilation in progress please wait ==>${ENDCOL}\n\n"

libft: 
		@$(MAKE) -C ../libft > /dev/null 2>&1 || true

readline:
		@test -f ../readline/libreadline.a \
		|| cd ../readline; ./configure > /dev/null 2>&1 || true; \
		$(MAKE) -C ../readline > /dev/null 2>&1 || true

directory: 	
		@mkdir -p $(OBJ_PATH) > /dev/null 2>&1 || true
		@echo $(BLUE) Binary $(PROJECT) directory created !!

#   LAUNCH	#
run: re
		@./Bin/minishell

runval: re
		@$(LEAKS) ./Bin/minishell

val: re
		@read -p "command : " INP\
			&& $(LEAKS) ./Bin/minishell -c "$$INP"



#  NORMINETTE  #
norm:
		@printf "\n${GRN}****************${YEL} NORMINETTE ${GRN}****************${ENDCOL}\n"
		@printf "\n${GRN}lib$(LIB_NAME):${BLU}\n\n"
		@norminette $(LIB_PATH)$(INC_PATH)
		@norminette $(LIB_PATH)$(SRC_PATH)
		@printf "\n${GRN}$(PROJECT):${BLU}\n\n"
		@norminette $(INC_PATH)
		@norminette $(SRC_PATH)
		@printf "${NOCOL}"

clean: 
		@$(CL) $(OBJ_PATH)
		@echo $(RED) Object $(notdir $(OBJ)) is delete !

fclean: clean 
		@$(CL) $(BIN)
		@echo $(RED) Binary $(notdir $(BIN)) is delete !

finish: 
		@$(CL) $(BIN_PATH)
		@$(MAKE) finish -C ../libft > /dev/null 2>&1 || true
		@$(MAKE) clean -C ../readline > /dev/null 2>&1 || true
		@$(MAKE) distclean -C ../readline > /dev/null 2>&1 || true
		@echo $(RED) All $(PROJECT) is delete !

re:	fclean all

printdir:
	@echo $(SRC)

buildrepo	:
	$(HIDE)$(call make-repo)

.PHONY :	all clean fclean finish re directory title

define make-repo
	$(HIDE)mkdir -p $(OBJ_PATH)
	$(HIDE)for dir in $(DIRS); \
   	do \
	mkdir -p $(OBJ_PATH)/$$dir; \
   	done
endef

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),TRUE)
    HIDE =
else
    HIDE = @
endif
