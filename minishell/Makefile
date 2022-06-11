# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#    By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 10:09:10 by mdoquocb          #+#    #+#              #
#    Updated: 2022/06/11 17:20:30 by mdoquocb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT = minishell

	#  BINARY  #

BIN_PATH = Bin/

BIN_NAME = $(PROJECT)

BIN = $(addprefix $(BIN_PATH),$(BIN_NAME))

	#  INCLUDES  #

INC_PATH_MAT = ./Matthis/Includes

INC_PATH_SIH = ./Siham/Includes

INC_FLAGS += -I $(INC_PATH_MAT) -I $(INC_PATH_SIH)

	#  LIB => libft  #

LIB_NAME = ft

LIB_PATH = ../libft/

LIB_INC_PATH = includes

LIB_BIN_PATH = Bin

LIB = $(addprefix $(LIB_PATH),$(LIB_NAME))

INC_FLAGS += -I $(LIB_PATH)$(LIB_INC_PATH)

LIB_FLAGS = -L $(LIB_PATH)$(LIB_BIN_PATH) -l $(LIB_NAME)

	#  SOURCES  #

SRC_PATH_MAT = Matthis/Sources/

SRC_PATH_SIH = Siham/Sources/

SRC_NAME_MAT = $(notdir $(wildcard Matthis/Sources/*.c)) 

SRC_NAME_SIH = $(notdir $(wildcard Siham/Sources/*.c))

SRC = $(addprefix $(SRC_PATH_MAT),$(SRC_NAME_MAT)) $(addprefix $(SRC_PATH_SIH),$(SRC_NAME_SIH))

	#  FLAGS  #

CC = gcc

CC_FLAGS = -g -Wall -Wextra -Werror 

CL = rm -rf


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

	#  COMPILATION  #

all: $(BIN) 
		@echo $(GREEN) Compilation $(PROJECT) is completed !!

$(BIN): libft title directory 
		@$(CC) $(CC_FLAGS) $(INC_FLAGS) $(LIB_FLAGS) -o $(BIN) $(SRC)
		@echo $(BLUE) $(notdir $(BIN)) is created !!

title: 
		@echo $(GREEN)******************$(PROJECT)******************

libft: 
		@$(MAKE) -C ../libft

directory: 	
		@mkdir -p $(BIN_PATH) > /dev/null 2>&1 || true
		@echo $(BLUE) Binary $(PROJECT) directory created !!

norm:
		@printf "\n${GRN}****************${YEL} NORMINETTE ${GRN}****************${ENDCOL}\n"
		@printf "\n${GRN}lib$(LIB_NAME):${BLU}\n\n"
		@norminette $(LIB_PATH)$(INC_PATH)
		@norminette $(LIB_PATH)$(SRC_PATH)
		@printf "\n${GRN}$(PROJECT):${BLU}\n\n"
		@norminette $(INC_PATH)
		@norminette $(SRC_PATH)
		@printf "${NOCOL}"

all_test: test1 test2 test3 test4
		
test1: 
		@

test2: 
		@

test3: 
		@

test4: 
		@

push:
		@cd ../; git add .
		@read -p "name of commit: " INP \
		&& cd ../; git commit -m "$${INP}"
		@cd ../; git push

push_mat:
		@cd Matthis/; git add .
		@read -p "name of commit: " INP \
		&& cd Matthis/; git commit -m "$${INP}"
		@cd Matthis/; git push

push_sih:
		@cd Siham/; git add .
		@read -p "name of commit: " INP \
		&& cd Siham/; git commit -m "$${INP}"
		@cd Siham/; git push

clean: 
		@$(CL) $(OBJ)
		@$(MAKE) clean -C ../libft
		@echo $(RED) Object $(notdir $(OBJ)) is delete !

fclean: clean 
		@$(CL) $(BIN)
		@$(MAKE) fclean -C ../libft
		@echo $(RED) Binary $(notdir $(BIN)) is delete !

finish: 
		@$(CL) $(BIN_PATH)
		@$(MAKE) finish -C ../libft
		@echo $(RED) All $(PROJECT) is delete !

re:	fclean all

.PHONY :	all clean fclean finish re directory title
