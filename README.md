# Digitalizzazione-di-un-sintetizzatore-analogico-PB13
In questo repository trovate alcune guide e alcune spiegazioni extra relative alle attività svolte sulla Raspberry Pi nel corso dello sviluppo della mia tesi di laurea triennale in Ingegneria elettronica conseguita presso l’università Politecnica di Ancona.
Le guide e le linee di comando riportate in questo documento sono quelle ce ho utilizzato per svolgere e sviluppare il sistema di digitalizzazione del sintetizzatore analogico Viscount PB13

## Terminale Linux Comandi più comuni
- Comando **pwd** - visualizza il path e la directory corrente
- Comando **cd** - accede ad una directory
- Comando **ls** - visualizza contenuto di una directory
- Comando **tree** - mostra la struttura ad albero del file system
- Comando **cat** - mostra il contenuto di un file di testo
- Comando **touch** - crea un nuovo file
- Comando **cp** - copia file
- Comando **mv** - sposta e rinomina file
- Comando **rm** - elimina file
- Comando **su** - fa acquisire i diritti di utente di root
- Comando **whoami** - mostra nome utente connesso
- Comando **chmod** - modifica i permessi dei files e direcotry
- Comando **rmdir** - elimina directory


## Gestione dei pacchetti Apt-get.
Di seguito vengono mostratialcuni dei comandi più comuni relativi all’installazione di nuovi pacchetti su Raspberry Pi.

Per installare un nuovo software dal repository o aggiornarne uno eseguire il comando:
- $apt-get install nome_pkg
Per rimuovere il software indesiderato digitare nel terminale:
- $apt-get remove nome_pkg
Per cercare un pacchetto per nome digitare nel terminale:
- $apt-cache search nome_pkg
Per aggiornare l'elenco dei pacchetti digitare nel terminale:
- $apt-get update
Per aggiorna il sistema digitare nel terminale:
- $apt-get upgrade

Da notare che la lista dei server da consultare durante la ricerca di nuovi pacchetti o da cui scaricarne di nuovi è salvata all’interno del file: 
/etc/apt/sources.list
Tale file può essere modificato per rimuovere o aggiungere nuovi repository.

## Abilitare Consolle remota tramite porta seriale.

- $sudo raspi-config

  selezonare:
  ![image](https://github.com/user-attachments/assets/e2230b42-b16d-4780-a5dc-b39635740b59)

 ## Abilitare server VNC
 
- $sudo apt install realvnc-vnc-server

- $sudo raspi-config

 selezonare:
![image](https://github.com/user-attachments/assets/87aa87e7-84c9-4521-b156-4ecded476b64)

## Installare sul PC uno dei tanti software client CNV disponibili in rete

Come Client VNC su PC può essere installato il software RealVNC scaricabile da questo link:

https://www.realvnc.com

Per connettersi alla scheda Raspberry è necessario conoscre il suo indirizzo IP.

L’indirizzo Ip può essere ottenuto o digitando il comando:
- $ifconfig
Sulla consolle seriale installata precedentemente

![image](https://github.com/user-attachments/assets/6928d49c-a1c8-4192-af9c-5c07f6dea2c7)


A questo punto:
- Avviare il client VNC sul PC. 
- Creare una nuova connessione all’indirizzo Ip della scheda. 
- Inserire utente e password.


Vedremo comparire l’intero schermo della Raspberry sul nostro PC.
Sarà possibile interagire con la scheda utilizzando direttamente la tastiera e il mouse del PC.

![image](https://github.com/user-attachments/assets/36b0fc16-56d4-438b-8258-cbde7a747aec)


## Controllare Jack da linea di comando

Il server Jack, può essere completamente controllato da linea di comando.
Da linea di comando possiamo avviare, fermare il server, creare connessioni, controllare il suo funziona-mento e gestire molte altre cose.

Con il comando

- $jackd -d alsa -d hw:1 -r 44100 -p 1024 -n 2

possiamo avviare il server utilizzando il driver audio ALSA (-d alsa ), specificando la scheda au-dio (-d hw:1) ed impostando frequenza, dimensione e numero dei buffer.

Con il comando:

- $jack_control start

Possiamo avviare il server impostato precedentemente

- $jack_control stop

Possiamo fermarlo

Con il comando:

- $jack_connect port1 port2

Possiamo connettere due porte jack insieme da riga di comando.

- **Esempio**:  jack_connect csoundBouncey:output1 system:playback_1
