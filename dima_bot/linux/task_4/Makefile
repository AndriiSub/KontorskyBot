CC = gcc
CFLAGS = -Wall -Iinclude

# Директори
OBJDIR = obj
BINDIR = bin
LIBDIR = lib

# Вихідні файли
SRCFILES = src/arraylist.c src/main.c

# Об'єктні файли
OBJFILES = $(OBJDIR)/arraylist.o $(OBJDIR)/main.o

# Виконуваний файл
TARGET = $(BINDIR)/arraylist_program

# Динамічна бібліотека
DYN_LIB = lib/libarraylist.dll

# Статична бібліотека
STATIC_LIB = lib/libarraylist.a

# Правила для зборки
$(TARGET): $(OBJFILES) $(STATIC_LIB)
	$(CC) $(OBJFILES) -L$(LIBDIR) -larraylist -o $(TARGET)

obj/arraylist.o: src/arraylist.c
	$(CC) $(CFLAGS) -c src/arraylist.c -o $(OBJDIR)/arraylist.o

obj/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o $(OBJDIR)/main.o

# Статична бібліотека
lib/libarraylist.a: obj/arraylist.o
	ar rcs $(STATIC_LIB) obj/arraylist.o

# Динамічна бібліотека
lib/libarraylist.dll: obj/arraylist.o
	$(CC) -shared -o $(DYN_LIB) obj/arraylist.o

# Очищення
clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/*.exe $(LIBDIR)/*.a $(LIBDIR)/*.dll
