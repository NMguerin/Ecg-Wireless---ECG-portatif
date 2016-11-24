# L2 FDV - Projet Ingénierie 2016/2017 - ECG wireless
#Nina Guérin - Julien Pichon - Simon Fradet 

#Ce programme en python fonctionne avec la bibliothèque matplotlib. Il permet de tracer un électrocardiogramme avec les données acquise grâce à l'ECG wireless.

#Importation des librairies nécéssaires à l'éxécution du programme
from csv import reader
import string
import matplotlib.patches as mpatches
import matplotlib.pyplot as plt

#Cette commande provoque l'ouverture et lecture du fichier data.csv qui contient les données acquises pendant la mesure 
with open('data.csv', 'r') as f:
    data = list(reader(f))

#Cette boucle extrait les valeurs du fichier data.csv et les stocke dans une liste nommé graphe en effaçant les caractères superflus à l'analyse
graphe = []
for line in data:
    ne = str(line)
    new_line = ne.replace('"', '')
    new_line = new_line.replace('b', '')
    new_line = new_line.replace('r', '')
    new_line = new_line.replace('n', '')
    new_line = new_line.replace("'", '')
    new_line = new_line.replace('\\\\', '')
    new_line = new_line.replace(']', '')
    new_line = new_line.replace('[', '')
    new_line = int(new_line)
    graphe += [new_line]


#On utilise la librairie matplotlib pour tracer l'électrocardiogramme grâce au données du fichier data.csv.
plt.plot(range(len(graphe)), graphe)
plt.ylabel('Voltage en mV', fontsize = 14) #legende du graphique en y
plt.xlabel('Temps', fontsize = 14) #legend du graphique en x
plt.title("Rythme cardiaque", fontsize = 16) #titre
plt.grid(True)
plt.axis((0, 2000, 0, 1000))
plt.show()
