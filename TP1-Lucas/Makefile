# === Exécution rapide ===
#=> mingw32-make run ou make run


# === Configuration ===
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
OBJ = main.o lexique.o utilitaire.o
TARGET = TP1exe

# === Règle par défaut ===
all: $(TARGET)

# === Liaison ===
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^

# === Compilation des .cpp en .o ===
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# === Nettoyage ===
clean:
	del /Q $(OBJ) $(TARGET).exe 2>nul || true

# === Exécution rapide ===
run: all
	.\$(TARGET).exe
