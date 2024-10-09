NAME :=	HumanGL

all : $(NAME)

$(NAME):
	@cmake -Bbuild . 
	@cmake --build build --config Debug
	@mv ./build/Debug/HumanGL.exe ./HumanGL.exe
	@echo [SUCCESS] $@ compiled successfully!

clean :
	@rm -rf ./build/
	@echo [CLEAN] Object files have been removed!

fclean : clean
	@rm -rf HumanGL.exe
	@echo [FCLEAN] Executable files have been fully removed!

re : fclean all

.PHONY : all clean fclean re