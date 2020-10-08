SRC = unity/unity.c\
src/announce.c\
src/polling.c\
src/normal.c\
src/admin.c\
test/test_login.c\
main.c

INC = -Iunity\
-Iinc\
-Itest

PROJECT_NAME = ELECTIONADMINISTRATOR.exe

$(PROJECT_NAME): $(SRC)
	gcc $(SRC) $(INC) -o $(PROJECT_NAME)

run:$(PROJECT_NAME)
	./${PROJECT_NAME}
doc:
	make -C documentation

clean:
	rm -rf $(PROJECT_NAME) documentation/html
