from os import system
from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.options import Options
#from webdriver_manager.chrome import ChromeDriverManager
import glob
import os
import shutil
import socket
from datetime import datetime

"""
Début du programme pour exporter le csv du site internet argos
"""
delay=10 #seconds pour le timeout 
#Définir les options de google, detach = on lui dis de ne pas se fermer apres la fin de l'execution du programm

chrome_path="/usr/bin/google-chrome"
options = Options()
options.add_argument("--headless")
options.add_argument("--no-sandbox")
options.add_argument('--disable-dev-shm-usage')    

chrome_prefs = {
    "DownloadRestricton":0, 
    "download_promt_for_download": "false",
    "browser.set_download_behavior": "allow",
    "behavior": "allow",
    "download.default_directory":r"/home/rascol/Documents/Python/tipod/Téléchargements",
    "downloadPath": "test"} # (windows)

options.add_experimental_option("prefs", chrome_prefs)




#On définit driver avec les options puis on lance le driver avec le action
path= "/home/rascol/Documents/Python/tipod/chromedriver"
driver = webdriver.Chrome(path, chrome_options=options)
action = webdriver.ActionChains(driver)
driver.set_window_size(1024, 600) #on définit la taille de la fenetre google en 1024x600 (il faut la définir avant de le mettre en plein écran)
driver.maximize_window()#on met la fenetre google en plein écran
driver.get("https://argos-system.cls.fr/argos-cwi2/login.html")#on cherche l'url
assert "Argos" in driver.title#envoyer une erreur si dans le titre de la page, argos n'est pas présent

# On définis les classes qu'on va utiliser pour remplir le formulaire de connexion
username = driver.find_element_by_id("username")
password = driver.find_element_by_id("password")

username.send_keys("username") #On envoie RASCOL dans la case username
password.send_keys("password")#On envoie le mot de passe dans la case qui correspond

driver.find_element_by_name("Enter").click()#On cherche le bouton "enter" et on clique

WebDriverWait(driver, delay).until(EC.visibility_of_element_located((By.CSS_SELECTOR, '[alt="Voir vos données"]'))).click()
#On attends que "voir vos données" s'affiche, puis on clique dessus
driver.set_window_size(1024, 600)#On réduit le navigateur pour contouner l'erreur du bouton rechercher
BTrechercher= WebDriverWait(driver, delay).until(EC.visibility_of_element_located((By.ID, 'button-1074-btnInnerEl')))
#On attends que le bouton rechercher s'affiche, puis on clique dessus

action.move_to_element(BTrechercher)
BTrechercher.click()

driver.maximize_window()#on remet le navigateur en plein écran
driver.find_element_by_id("exportbt-1080-btnInnerEl").click()#on clique sur le bouton exporter
#on attends que le logo du CSV s'affiche puis on clique dessus
WebDriverWait(driver,delay).until(EC.visibility_of_element_located((By.CLASS_NAME, "x-file-CSV"))).click()
csvexport="export du csv réussis"
print(csvexport)
#driver.quit()#On ferme le navigateur

"""
Début du programme pour déplacer le csv dans le dossier pour node-red 
(les anciens csv seront supprimer du dossier node-red) mais ils seront tous conserver dans le dossier téléchargement
"""


list_of_files = glob.glob(r'/home/rascol/Documents/Python/tipod/Téléchargements/*.csv') # * veux dire tout, donc *.csv = tout les fichiers csv seulement seront tester
latest_file = max(list_of_files, key=os.path.getctime) # Met dans la variable latest_file le fichier le plus récent
print(latest_file)

destination = r"/home/rascol/Documents/Python/tipod/CSV" # Definis le chemin de destination

files = glob.glob(r'/home/rascol/Documents/Python/tipod/CSV/*') # Définis le chemin de destination dans la variable files 
for f in files: # Pour chaque fichier dans le fichier de destination
    os.remove(f) # Supprimer le fichier

shutil.copy(latest_file, destination) # corascole le fichier le plus récent dans le chemin de destination
list_of_files = glob.glob(r'/home/rascol/Documents/Python/tipod/CSV/*') # * veux dire tout, donc *.csv = tout les fichiers csv seulement seront tester
latest_file = max(list_of_files, key=os.path.getctime) # Met dans la variable latest_file le fichier le plus récent
print(latest_file)

new_fileName= r"/home/rascol/Documents/Python/tipod/CSV/ArgosData.csv" # Définis le nom du nouveau fichier pour rendre plus facile le programme node-red
os.rename(latest_file,new_fileName) # Renomme le dernier fichier trouver par ArgosData.csv
csvmove="déplacement du csv réussis"
"""
Début du programme pour insérez les logs dans le fichier log.txt (sans effacer les anciens))
"""

today = datetime.now()

log = open("log.txt", "a")
log.write("----------------------------------------------------------------\r")
log.write("Date: %s \r" % (today))
log.write("----------------------------------------------------------------\r")
log.write("%s \r" % (csvexport))
log.write("%s \r" % (csvmove))
log.close