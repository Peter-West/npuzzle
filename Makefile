#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/04 17:52:30 by ppellegr          #+#    #+#              #
#    Updated: 2015/06/04 17:52:30 by ppellegr         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME				:= np
SRCS				:= main.cpp Parser.cpp Solve.cpp Gen.cpp Options.cpp
PATH_OBJ			:= objs
PATH_SRC			:= srcs
PATH_INC			:= incs
CXX					:= clang++-3.5
CXXFLAGS			:= -Wall -Wextra -Werror -std=c++11
DEBUG				:= -g
OBJECTS				:= $(patsubst %.cpp, $(PATH_OBJ)/%.o, $(SRCS))
INCLUDES			:= -I./$(PATH_INC)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LIBRARY) $(DEBUG) $(CXXFLAGS)

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.cpp)
	@mkdir -p $(PATH_OBJ)
	$(CXX) -c -o $@ $(CXXFLAGS) $^ $(DEBUG) $(INCLUDES)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)