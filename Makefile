# Compiler yang digunakan
CC = gcc

# Flags untuk kompilasi
CFLAGS = 

# Libraries yang diperlukan
LDFLAGS = 

# file .c lain
CFILE = functions/ADTList.c functions/ADTBioskop.c

# Daftar file source code
SRCS = main.c

# Nama file output
TARGET = main.exe

# Rule untuk kompilasi
$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFILE) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

# Rule untuk membersihkan file hasil kompilasi
clean:
	del $(TARGET)
