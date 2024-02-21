import csv
import random
import time

# Définir le nombre de messages à générer
nombre_messages = 1000

# Ouvrir un fichier CSV en mode écriture
with open('messages_iot.csv', 'w', newline='') as csvfile:
    # Créer un objet writer CSV
    writer = csv.writer(csvfile)

    # Écrire l'en-tête du fichier CSV
    writer.writerow(['timestamp', 'topic', 'message'])

    # Générer des messages simulés avec des timestamps aléatoires
    for i in range(nombre_messages):
        timestamp = int(time.time())  # Timestamp actuel
        topic = 'topic/' + str(random.randint(1, 10))  # Sujet du message
        message = 'Message ' + str(i)  # Contenu du message
        # Écrire la ligne dans le fichier CSV
        writer.writerow([timestamp, topic, message])

print(f'Le fichier "messages_iot.csv" a été généré avec succès avec {nombre_messages} messages.')
