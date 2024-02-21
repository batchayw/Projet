# Utilisation de l'image MySQL-8.0
FROM mysql:8.0

# Définition des variables d'environnement pour configurer MySQL
ENV MYSQL_ROOT_PASSWORD=root_password
ENV MYSQL_DATABASE=init
ENV MYSQL_USER=app_user
ENV MYSQL_PASSWORD=app_password

# Copie du fichier init.sql dans le répertoire de démarrage de MySQL
COPY ./init.sql /docker-entrypoint-initdb.d/init.sql

# Exposition du port MySQL
EXPOSE 3306

# Commande pour démarrer MySQL
CMD ["mysqld"]

