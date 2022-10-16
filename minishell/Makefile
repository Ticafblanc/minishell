# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tonted <tonted@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 10:09:10 by mdoquocb          #+#    #+#              #
#    Updated: 2022/10/16 08:41:29 by tonted           ###   ########.fr        #
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
SRC = $(wildcard $(SRC_PATH)/*.c)
SRC += $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

#  OBJECTS  #
OBJ = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))

#  FLAGS  #
CC = gcc
# CC_FLAGS =  -g -Wall -Wextra -Werror 
CC_FLAGS =  -g 
CL = rm -rf

LEAK = leaks -atExit --
LEAKS = valgrind --leak-check=full --track-fds=yes #--trace-children=yes -s -q

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
		@cd ../readline; ./configure > /dev/null 2>&1 || true
		@$(MAKE) -C ../readline > /dev/null 2>&1 || true

directory: 	
		@mkdir -p $(OBJ_PATH) > /dev/null 2>&1 || true
		@echo $(BLUE) Binary $(PROJECT) directory created !!

#   LAUNCH	#
run: all
		@./Bin/minishell

val: all
		$(LEAKS) ./Bin/minishell


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

#  TESTER  #
	all_test: test1 test2 test3 test4
			
	test1: 
			@

	test2: 
			@

	test3: 
			@

	test4: 
			@

#  GIT  #
	clone_repo:
			@git clone --recurse-submodules git@github.com:Ticafblanc/minishell.git

	update_repo:
			@cd ../; git fetch

	pull_repo:
			@cd ../; git pull

	push:
			@cd ../; git add .
			@read -p "name of commit: " INP \
			&& cd ../; git commit -m "$${INP}"
			@cd ../; git push

	add_remote_42:
			@cd ../; git remote add 42 git@vogsphere.42quebec.com:vogsphere/intra-uuid-ce31cfe3-ce34-4011-892f-c1e9fb9c73c1-4171290-mdoquocb

	add_remote_matthis:
			@cd ../; git remote add Matthis https://github.com/Ticafblanc/minishell.git

	add_remote_Siham:
			@cd ../; git remote add Siham https://github.com/Siham42/Minishell.git

	remove_remote_42:
			@git remote rm 42

	remove_remote_Matthis:
			@git remote rm Matthis

	remove_remote_Siham:
			@git remote rm Siham
			
	add_submodule:
			@cd  ../; git submodule add git@github.com:Ticafblanc/libft.git

	pull_submodule:
			@cd ../; git submodule update --init --recursive

	update_submodule:
			@cd ../libft; git fetch

	push_upgrade_submodule:
			@cd ../; git submodule update --remote --merge

	remove_submodule:
			@cd ../; git submodule deinit libft
			@cd ../; git rm libft

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
	@echo $(OBJ)

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