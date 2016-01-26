NAME		=		gomokuu

CC		=		g++

RM		=		rm -f

SRC		=		gomoku/src

INC		=		gomoku/inc

CXXFLAGS	=	-I./$(INC) -std=c++11	# -Wall -Wextra -Werror 

SFML_LDFLAGS	=		-lpthread -lsfml-graphics -lsfml-window -lsfml-system

SRCS		=		$(SRC)/Board.cpp \
				$(SRC)/Eval.cpp \
				$(SRC)/GameCore.cpp \
				$(SRC)/gomoku.cpp \
				$(SRC)/Gui.cpp \
				$(SRC)/Human.cpp \
				$(SRC)/IA.cpp \
				$(SRC)/MinMax.cpp \
				$(SRC)/Player.cpp \
				$(SRC)/SafeQueue.cpp \
				$(SRC)/ScopedLock.cpp \
				$(SRC)/ThreadPool.cpp \
				$(SRC)/UMutex.cpp \
				$(SRC)/UThread.cpp

OBJ		=		$(SRCS:.cpp=.o)

all:				$(NAME)

$(NAME):			$(OBJ)
				$(CC) -o $(NAME) $(OBJ) $(SFML_LDFLAGS)

clean:
				$(RM) $(OBJ)

fclean:				clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:				all clean fclean re
