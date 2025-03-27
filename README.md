# unmatching

## Context

Open Maps For Europe 2 est un projet qui a pour objectif de développer un nouveau processus de production dont la finalité est la construction d'un référentiel cartographique pan-européen à grande échelle (1:10 000).

L'élaboration de la chaîne de production a nécessité le développement d'un ensemble de composants logiciels qui constituent le projet [OME2](https://github.com/openmapsforeurope2/OME2).


## Description

Cette application a pour fonction de supprimer toutes données et les informations attributaires relatives à un pays de manière à pouvoir, dans le contexte d'une mise à jour, injecter les nouvelles données et rejouer le processus de raccordement aux frontières.


## Fonctionnement

Les objets du pays à mettre à jour sont supprimés. Pour les objets fusionnés, résultant du processus de raccordement aux frontières, on supprime pour chaque attribut la partie qui a pour origine le pays traité. Les valeurs des attributs, qui étaient doubles (deux valeurs séparées par un '#', chacune provenant d'un pays différent), deviennent simples (une seul valeur).


## Configuration

Les fichiers de configuration se trouvent dans le [dossier de configuration](https://github.com/openmapsforeurope2/unmatching/tree/main/config) et sont les suivants :
- epg_parameters.ini : regroupe des paramètres de base issus de la bibliothèque libepg qui constitue le socle de développement l'outil. Ce fichier est aussi le fichier chapeau qui pointe vers les autres fichiers de configurations.
- db_conf.ini : informations de connexion à la base de données.
- theme_parameters.ini : configuration des paramètres spécifiques à l'application.


## Utilisation

L'outil s'utilise en ligne de commande.

Paramètres :

* c [obligatoire] : chemin vers le fichier de configuration
* cc [obligatoire] : code pays simple

<br>

Exemples d'appel:
~~~
bin/unmatching --c path/to/config/epg_parmaters.ini --cc lu
~~~