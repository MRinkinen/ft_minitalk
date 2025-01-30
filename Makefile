NAME = minitalk
SOURCES = $(addprefix $(SRC_DIR)/, \
server.c client.c)
SOURCES_BONUS = $(addprefix $(SRC_BON_DIR)/, \
server_bonus.c client_bonus.c)

OBJECTS = $(SOURCES:.c=.o)
OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)
SRC_DIR	= ./sources/
SRC_BON_DIR = ./sources_bonus/
CFLAGS = -Wall -Wextra -Werror
LIBFTNAME = libft.a
LIBFTDIR = ./libft/

all: $(NAME) 

$(NAME): libft client server 

client: $(SRC_DIR)client.o
	cc $(CFLAGS) $(SRC_DIR)client.c $(LIBFTDIR)$(LIBFTNAME) -o client

server: $(SRC_DIR)server.o
	cc $(CFLAGS) $(SRC_DIR)server.c $(LIBFTDIR)$(LIBFTNAME) -o server

libft: 
	@make -C $(LIBFTDIR)

bonus: .bonus

.bonus : libft client_bonus server_bonus
	@touch .bonus

client_bonus: $(SRC_BON_DIR)client_bonus.o
	cc $(CFLAGS) $(SRC_BON_DIR)client_bonus.c $(LIBFTDIR)$(LIBFTNAME) -o client_bonus

server_bonus: $(SRC_BON_DIR)server_bonus.o
	cc $(CFLAGS) $(SRC_BON_DIR)server_bonus.c $(LIBFTDIR)$(LIBFTNAME) -o server_bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@	

clean:
	@rm -f $(OBJECTS) 	
	@rm -f $(OBJECTS_BONUS) 
	@cd $(LIBFTDIR) && make clean
	@rm -f .bonus
	
fclean: clean
	@rm -f server client client_bonus server_bonus libft/libft.a
	@rm -f $(NAME) 	

re: fclean all	

.PHONY: all libft clean fclean re bonus
