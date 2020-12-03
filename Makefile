#################################################################################
##################################### VARS ######################################
#################################################################################

NAME =			ft_malcolm

###### SOURCES #######

SRC_NAME =		ft_malcolm.c\
				parsing.c\
				utils.c

SRC_DIR =		./sources/
SRC =			${addprefix $(SRC_DIR), $(SRC_NAME)}

#objects
OBJ_NAME =		$(SRC_NAME:.c=.o)
OBJ_DIR =		./objects/
OBJ =			${addprefix $(OBJ_DIR), $(OBJ_NAME)}

###### HEADERS ########

HEADER_DIR =	./includes/
HEADER_NAME =	ft_malcolm.h
HEADER =		${addprefix $(HEADER_DIR), $(HEADER_NAME)}

#######  MISC  ########

FLAGS =			-g3 -O0 -Wall -Wextra -Werror
DEBUG_FLAGS =	$(FLAGS) -fsanitize=address
CC =			gcc

#################################################################################
##################################### RULES #####################################
#################################################################################

.PHONY: all clean fclean re lre
.SILENT:

########## GENERALS ##########

all:	$(OBJ_DIR) $(NAME) $(HEADER)

re:	fclean all

lre:
	rm -r $(OBJ_DIR)
	make all

clean:
	rm -rf $(OBJ_DIR)

fclean:
	rm -rf $(OBJ_DIR) $(NAME) *.dSYM
	printf "\033[31m\033[1m\033[4mCleaning\033[0m\033[31m : Everything\033[0m [$(NAME)]\n";

debug:
	rm -r $(OBJ_DIR)
	make $(NAME)_debug

######### COMPILATION #########

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -I$(HEADER_DIR)
	printf "\n \033[1m\033[4m\033[35m\\^/ Done compiling \\^/\033[0m [$(NAME)]\n"
	make --no-print-directory header_print

$(NAME)_debug: ./auteur $(OBJ_DIR) $(HEADER) $(OBJ)
	$(CC) $(DEBUG_FLAGS) $(OBJ) -o $(NAME) -I$(HEADER_DIR)
	printf "\n \033[1m\033[4m\033[35m\\^/ Done compiling \\^/\033[0m [$(NAME)]\n"
	make --no-print-directory header_print

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ -I$(HEADER_DIR)
	printf "\033[32m\033[1m\033[4mCompiling\033[0m\033[32m : %-30s \033[0m [$(NAME)]\n" $@

$(OBJ_DIR): $(ALL_OBJ_DIR)
	mkdir -p $(OBJ_DIR)

$(ALL_OBJ_DIR):
	mkdir -p $@
	printf "\033[32m\033[1m\033[4mCreated\033[0m\033[32m : $@ obj dir\033[0m"

header_print:
	#TODO : header
	printf "##########\033[32m NISAUVIG \033[0m##########"
