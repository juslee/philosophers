# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/07 04:39:46 by welee             #+#    #+#              #
#    Updated: 2024/09/08 17:38:04 by welee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = $(BINS_DIR)/philo_bonus

SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lpthread
RM = rm -f
MKDIR = mkdir -p
ECHO = echo

SRCS_DIR = srcs
OBJS_DIR = objs
INCS_DIR = includes
BINS_DIR = bin
TEST_DIR = tests
DIST_DIR = dist

NORM = norminette
NORM_FLAGS = -R CheckForbiddenSourceHeader -R CheckDefine

all: $(NAME)

$(NAME): $(OBJS) | $(BINS_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@$(ECHO) "\033[32m$(NAME) compiled\033[0m"

$(BINS_DIR):
	$(MKDIR) $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -I $(INCS_DIR) -c -o $@ $<
	@$(ECHO) "\033[33m$@\033[0m"

clean:
	$(RM) $(OBJS)
	@$(ECHO) "\033[31m$(NAME) object files removed\033[0m"

fclean: clean
	$(RM) $(NAME)
	@$(ECHO) "\033[31m$(NAME) removed\033[0m"

re: fclean all

norm:
	$(NORM) $(NORM_FLAGS) $(SRCS_DIR) $(INCLUDES_DIR)
	@$(ECHO) "\033[32mNorm check completed\033[0m"

.PHONY: all clean fclean re norm test
