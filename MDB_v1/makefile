.PHONY:clean

TARGET=MDB

main: ./src/database.c main.c ./tables/*.c
	gcc -I./include $^ -o $(TARGET)

clean:
	$(RM) -rf $(TARGET)
