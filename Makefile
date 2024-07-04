NAME	= webserv

CC		= g++
RM		= rm -f
# CFLAGS	= -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address
CFLAGS	= -Wall -Wextra -Werror -std=c++98 -g

SRCS_PATH = srcs

INCLUDE_PATH = include

SRCS	= $(wildcard $(SRCS_PATH)/*.cpp)

HEADER	= $(wildcard $(INCLUDE_PATH)/*.hpp)

OBJS	= $(SRCS:.cpp=.o)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
