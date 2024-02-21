import os
import requests

def contact_info(tel_number):
    # Ajoutez une entrée dans le fichier /etc/hosts pour résoudre "server"
    hosts_entry = "127.0.0.1 server"
    os.system(f"echo '{hosts_entry}' >> /etc/hosts")

    url = 'http://server:5000/get_info'
    data = {'tel_number': tel_number}
    
    reponse = requests.post(url, json=data)
    
    try:
        reponse.raise_for_status()
        
        result = reponse.json()
        print(f"Name: ========> {result['name']}")
        print(f"Address: ========> {result['address']}")
        print(f"Email: ========> {result['email']}")
        print(f"Profession: ========> {result['profession']}")
    except requests.exceptions.HTTPError as errh:
        print(f"HTTP Error: {errh}")
    except requests.exceptions.ConnectionError as errc:
        print(f"Error Connecting: {errc}")
    except requests.exceptions.Timeout as errt:
        print(f"Timeout Error: {errt}")
    except requests.exceptions.RequestException as err:
        print(f"Error: {err}")

if __name__ == '__main__':
    # Récupérer le numéro de téléphone à partir de la variable d'environnement
    tel_number = os.environ.get('PHONE_NUMBER')

    # Vérifier si le numéro de téléphone est disponible
    if tel_number is None:
        print("Phone number not provided.")
        sys.exit(1)

    contact_info(tel_number)
