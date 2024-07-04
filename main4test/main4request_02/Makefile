NAME		=	RequestTest
CPP			=	c++
CPPFLAGS	=	-Wall -Wextra -Werror -std=c++98

# Variable declaration of directory

BUILD_DIR	=	./build

# Variable declaration of file

SRCS		=	mainRequest.cpp Request.cpp Utils.cpp
HDFS		=	Request.hpp Utils.hpp
OBJS		=	$(SRCS:%.cpp=$(BUILD_DIR)/%.o)

all: $(NAME)

# Build step for CPP source

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(BUILD_DIR)/%.o: %.cpp $(HDFS)
	@mkdir -p $(@D)
	@$(CPP) $(CPPFLAGS) -c $< -o $@

bonus: all

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(NAME) $(BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re
