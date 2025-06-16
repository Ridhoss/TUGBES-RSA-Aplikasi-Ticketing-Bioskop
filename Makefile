# Compiler yang digunakan
CC = gcc

# Flags untuk kompilasi
CFLAGS = 

# Libraries yang diperlukan
LDFLAGS = 

# file .c lain
CFILE = views/views.c views/viewsUser.c views/Auth.c models/ADTTree.c models/ADTKota.c models/ADTBioskop.c models/ADTTeater.c models/ADTAkun.c models/ADTJadwal.c models/ADTFilm.c models/ADTList.c library/body/date.c library/body/timing.c models/ADTPemesanan.c models/ADTStack.c models/ADTQueue.c

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
