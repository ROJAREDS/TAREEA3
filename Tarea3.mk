#Tarea3.mk

Resultados.pdf: Resultados_hw3.tex ondaen60.png ondaen20.png orbit.png 
    pdflatex Resultados_wh3.tex

ondaen60.png: Onda.py
    python Onda.py

ondaen20.png: Onda.py
    python Onda.py

orbit.png: datos.txt
    python Plots_Planetas.py
datos.txt: Planetas.x
    ./Planetas.x
Planetas.x: Planetas.c
    cc Planetas.c -lm -o Planetas.x
Planetas.c: coordinates.csv
    cc Planetas.c -lm -o Planetas.x