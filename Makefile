# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/13 17:47:10 by thepaqui          #+#    #+#              #
#    Updated: 2026/10/08 18:52:24 by thepaqui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= warp_example

CC= g++-10

CCFLAGS= -Wall -Wextra -Werror -std=c++2a

ifeq ($(OS),Windows_NT)
	LIBS= -lglfw3 -lgdi32 -lopengl32 -I C:\GLFW\include -I C:\GLFW\lib-mingw-w64
else
	LIBS= -lglfw -ldl
endif

WARP_DIR= ./warp

WARP_LIB= $(WARP_DIR)/libwarp.a

INCLUDES= -I/usr/include/GLFW -I$(WARP_DIR)/include/ -L$(WARP_DIR)/ -lwarp

SRCS= main.cpp

OBJS= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME) : $(WARP_LIB) $(OBJS)
	@$(CC) $(CCFLAGS) -o $(NAME) $(OBJS) $(INCLUDES) $(LIBS)
	@echo "🎉 "$(NAME)" created successfully!"

%.o: %.cpp $(WARP_LIB)
	@$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@
	@echo "✅ Compiled "$@" successfully!"

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(WARP_DIR) clean
	@echo "🧹 Cleaned all object files!"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(WARP_DIR) fclean
	@echo "🧹 Removed "$(NAME)" successfully!"

re: fclean all

$(WARP_LIB):
	@$(MAKE) -C $(WARP_DIR)

.PHONY: all clean fclean re