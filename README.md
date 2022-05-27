**Tipod**
**Projet de BTS - Tipod**

Dans le cadre du projet POLAR POD, Jean Louis Etienne confie au Lycée Louis-Rascol la construction d'un projet parallèle : le TIPOD.

Le TIPOD est une bouée océanographique dérivante qui sera mise à l"eau dans le courant Circumpolaire Antarctique par le navire avitailleur de l'expédition POLAR POD.

Le but étant de relever, enregistrer et transmettre différentes mesures telle que la position GPS, l'hauteur des vagues, température, luminosité, etc..

Notre mission, localiser la bouée. Cette mission consiste a récupérer les informations GPS de la bouée et les transmettre/afficher sur une carte géographique accèssible via le site web.

**Module KIM :**
Pour envoyer les données, nous avons créer un programme (voir dossier "KIM") sur un micro-controleur en c++. 
**Référence du matériel :**

-> FRDM-K64F
-> Module KIM
-> Satélitte déployé par CLS et exploité via le site [Argos Web](https://argos-system.cls.fr/)
-> Serveur Linux sous Debian 11


**Tout les codes du projet sont open-sources et accéssible via ce GitHub.** 

Le dossier TIPOD est identique au dossier du serveur linux. Cependant, nous avons ajouter les deux autres programmes du micro-controlleur permettant l'envoi de données via le module KIM1 et de générer des coordonées avec un GPS.

**Le premier programme, KIM1.cpp** permet d'envoyer des données au satelitte ARGOS WEB le plus proche.
**Le deuxieme programme, GPS.cpp** permet de récuperer les coordonnées GPS et de les mettre en forme pour ensuite les envoyer via le premier programme KIM1.

Les programmes sont séparer dans le GitHub mais seront assembler dans un seul et même main.cpp une fois le projet lancer.

**Le programme Python MAIL.PY** permet de lire la boite de reception et d'éxecuter le programme **DATA.PY** si un mail est détecter.

On modifie le fichier Crontab du serveur linux, lui indiquant de lancer le programme **MAIL.PY** toute les minutes, et le programme **DATA.PY** toute les 12 heures.
Pour cela, on rentre la commande 
```
sudo crontab -e
```

Ensuite, on modifie les lignes de code telle que :
```
# Edit this file to introduce tasks to be run by cron.
#
# Each task to run has to be defined through a single line
# indicating with different fields when the task will be run
# and what command to run for the task
#
# To define the time you can provide concrete values for
# minute (m), hour (h), day of month (dom), month (mon),
# and day of week (dow) or use '*' in these fields (for 'any').
#
# Notice that tasks will be started based on the cron's system
# daemon's notion of time and timezones.
#
# Output of the crontab jobs (including errors) is sent through
# email to the user the crontab file belongs to (unless redirected).
#
# For example, you can run a backup of all your user accounts
# at 5 a.m every week with:
# 0 5 * * 1 tar -zcf /var/backups/home.tgz /home/
#
# For more information see the manual pages of crontab(5) and cron(8)
#
# m h  dom mon dow   command

* * * * * /home/rascol/Documents/Python/tipod/bin/python /home/rascol/Documents/Python/tipod/mail.py
0 12 * * * /home/rascol/Documents/Python/tipod/bin/python  /home/rascol/Documents/python/tipod/data.py
```

Concernant le site internet, le code est disponible sur ce répertoire github : https://github.com/Tekkyu/html-Tipod
Concernant Node-Red, le flow est disponible directement sur le site internet : http://www.tipod.rascol.net:1880/ en rentrant "rascol" comme nom d'utilisateur et mot de passe.
