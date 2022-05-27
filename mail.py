import imaplib
import email
from email.header import decode_header
from datetime import datetime
import os
from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
import glob
import shutil
# Identification du compte
username = "mail"
password = "password"
count = 0
# Connecte le serveur imap gmail
imap = imaplib.IMAP4_SSL("imap.gmail.com")
# Si on arrive a se connecter au IMAP, alors on entre nos identifiants 
imap.login(username, password)
# Je séléctionne la boite mail, on veut celle par defaut donc :
imap.select("INBOX")

# On recherche les mails d'une source
status, messages = imap.search(None, 'FROM "mail"')

# On convertit les messages en une liste d'ID
messages = messages[0].split(b' ')

for mail in messages:
    _, msg = imap.fetch(mail, "(RFC822)")
    for response in msg:
        if isinstance(response, tuple):
            msg = email.message_from_bytes(response[1])
            # On récupere le sujet du mail
            subject = decode_header(msg["Subject"])[0][0]
            if isinstance(subject, bytes):
                # Si c'est un type bytes on le décode en str
                subject = subject.decode()
            print("Deleting", subject)
            count = 1 + count
    # On écrit dans la console que le mail a était supprimer
    imap.store(mail, "+FLAGS", "\\Deleted")
    #On déplace le fichier dans la corbeille (\\Deleted)

if count > 0 :
    os.system("/home/rascol/Documents/Python/tipod/bin/python /home/rascol/Documents/Python/tipod/data.py")
    today = datetime.now()
    log = open("log.txt", "a")
    log.write("----------------------------------------------------------------\n")
    log.write("Suppréssion d'e-mail(s) a la date : \n" )
    log.write("Date: %s \n" % (today))
    log.write("----------------------------------------------------------------\n")
    log.close
imap.expunge()#On vide la corbeille
imap.close()# On ferme la boite mail
imap.logout()  # on se déconnecte
