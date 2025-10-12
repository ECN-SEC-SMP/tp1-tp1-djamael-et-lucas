CXX = g++
CXXFLAGS = -Wall -std=c++17

# Liste des fichiers source
SRC = main.cpp \
      utilitaire.cpp Lexique.cpp LexiqueAvecLignes.cpp\
      
# Générer les fichiers objets
OBJ = $(SRC:.cpp=.o)

# Nom de l'exécutable
EXEC = TP1

# Règle par défaut
all: $(EXEC)

# Édition des liens
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Nettoyage des .o et de l'exécutable
clean:
	rm -f $(OBJ) $(EXEC)
