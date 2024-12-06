# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2024/11/21 16:15:58 by sakitaha          #+#    #+#              #
#    Updated: 2024/11/23 19:43:06 by sakitaha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX      := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98
RM       := rm -f
TARGET   := program
SRCS     := main.cpp Fixed.cpp Point.cpp bsp.cpp
# SRCS     := main.cpp Fixed.cpp
OBJS     := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

test: $(TARGET)
	@echo "== Running Tests  =="
	./$(TARGET)
	@echo "== Tests Completed =="

debug: CXXFLAGS += -fsanitize=address -g
debug: $(TARGET)
	./$(TARGET)

valgrind: all
	valgrind --leak-check=full ./$(TARGET)

.PHONY: all clean fclean re test debug leaks valgrind
