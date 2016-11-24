# L2 FDV - Projet Ingénierie 2016/2017 - ECG wireless
#Nina Guérin - Julien Pichon - Simon Fradet 

#Ce programme en python fonctionne avec la bibliothèque matplotlib. Il permet de tracer un électrocardiogramme en direct avec les données acquise en wifi grâce à l'ECG wireless et de stockés ces données dans un fichier nommé data.csv.

#Importation des librairies nécéssaires à l'éxécution du programme
import sys
from socket import *
import random
import serial
import numpy as np
import matplotlib.pyplot as plt



data = open("data.txt", "w")

#Tant qu'on n'arrête pas le programme, les valeurs renvoyés par le port série sont 1) enregistrées dans  un fichier nommé data.csv, et une ligne est sauté entre chaque valeur et 2) 
plt.ion()
i = 0

def main(threadname,q):
    serverSocket = socket(AF_INET, SOCK_DGRAM)
    serverSocket.bind(('', 2390))

    while True:
        rand = random.randint(0, 10)
        message, address = serverSocket.recvfrom(1024)
        data.write(str(message))
        print(message)
        y = message
        print(i)
        print(y)
        global i
        i += 1
        plt.scatter(i, y)
        plt.pause(0.001)
      
if __name__ == '__main__':
    sys.exit(main(0,0))
