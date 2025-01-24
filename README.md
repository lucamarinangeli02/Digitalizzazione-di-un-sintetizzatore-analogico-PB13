# Digitalizzazione-di-un-sintetizzatore-analogico-PB13
In questo repository trovate alcune guide e alcune spiegazioni relative alle attività svolte sulla Raspberry Pi nel corso dello sviluppo della mia tesi di laurea triennale in Ingegneria elettronica conseguita presso l’università Politecnica di Ancona.
Le guide e le linee di comando riportate in questo documento sono quelle ce ho utilizzato per svolgere e sviluppare il sistema di digitalizzazione del sintetizzatore analogico Viscount PB13.

## Indice
- [Terminale Linux Comandi più comuni](Terminale_Linux_Comandi_più_comuni)
- [Gestione dei pacchetti Apt-get](Gestione_dei_pacchetti_Apt-get)
- [Abilitare Consolle remota tramite porta seriale](Abilitare_Consolle_remota_tramite_porta_seriale)
- [Abilitare server VNC](Abilitare_server_VNC)
- [Installare sul PC un client VNC](Installare_sul_PC_un_client_VNC)
- [Controllare Jack da linea di comando](Controllare_Jack_da_linea_di_comando)
- [Installare il framework qt nella Raspberry](Installare_il_framework_qt_nella_Raspberry)
- [Configurare QtCreator](Configurare_QtCreator)
- [Raspberry Pi – Gestione GPIO.](Raspberry_Pi_–_Gestione_GPIO.)

 
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

## Installare sul PC un client VNC

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


## Installare il framework qt nella Raspberry

Per prima cosa è importante aggiungere e abilitare i giusti repository da cui scaricare i pacchetti.

A tal fine editiamo il file source.list con il seguente comando
- $sudo vi /etc/apt/sources.list

<img width="483" alt="image" src="https://github.com/user-attachments/assets/9197da6f-6a79-4a42-b179-81879f888bae" />

e togliamo il commento alla terzultima riga.

Per una lista dei comandi e una guida all’uso di vi (editor di testo si consolle) è possibile consultare la seguente guida:
- https://www.redhat.com/sysadmin/introduction-vi-editor

Salvato il file eseguiamo i seguenti comandi:

- $sudo apt update
- $sudo apt full-upgrade
- $sudo reboot

Dopo il riavvio eseguire:
- $sudo rpi-update
- $sudo reboot

Dopo il riavvio eseguire:
- $sudo apt-get build-dep qt5-qmake
- $sudo apt-get build-dep libqt5webengine-data
- $sudo apt-get install qtcreator

Al termine vanno installati una serie di pacchetti generici alcuni dei quali non strettamente necessari ma se ne consiglia l’installazione al fine di noaver problemi durante le fasi di compilazione del progetto.

- $sudo apt-get install libboost1.58-all-dev libudev-dev libinput-dev libts-dev libmtdev-dev libjpeg-dev libfontconfig1-dev

- $sudo apt-get install libssl-dev libdbus-1-dev libglib2.0-dev libxkbcommon-dev libegl1-mesa-dev libgbm-dev libgles2-mesa-dev mesa-common-dev
   
- $sudo apt-get install flex bison libxslt-dev ruby gperf libbz2-dev libcups2-dev libatkmm-1.6-dev libxi6 libxcomposite1
   
- $sudo apt-get install libfreetype6-dev libicu-dev libsqlite3-dev libxslt1-dev libavcodec-dev libavformat-dev libswscale-dev
   
- $sudo apt-get install libgstreamer0.10-dev gstreamer-tools libraspberrypi-dev libx11-dev libglib2.0-dev

- $sudo apt-get install  gstreamer-tools libraspberrypi-dev libx11-dev libglib2.0-dev
 
- $sudo apt-get install   libraspberrypi-dev libx11-dev libglib2.0-dev

- $sudo apt-get install freetds-dev  libpq-dev libiodbc2-dev firebird-dev  libxext-dev libxcb1 libxcb1-dev libx11-xcb1

- $sudo apt-get install libx11-xcb-dev libxcb-keysyms1 libxcb-keysyms1-dev libxcb-image0 libxcb-image0-dev libxcb-shm0 libxcb-shm0-dev libxcb-icccm4 libxcb-icccm4-dev

- $sudo apt-get install libxcb-sync1 libxcb-sync-dev libxcb-render-util0 libxcb-render-util0-dev libxcb-xfixes0-dev libxrender-dev libxcb-shape0-dev libxcb-randr0-dev

- $sudo apt-get install libxcb-glx0-dev libxi-dev libdrm-dev libssl-dev libxcb-xinerama0 libxcb-xinerama0-dev

- $sudo apt-get install libatspi-dev libssl-dev libxcursor-dev libxcomposite-dev libxdamage-dev libfontconfig1-dev
 
- $sudo apt-get install  libssl-dev libxcursor-dev libxcomposite-dev libxdamage-dev libfontconfig1-dev

- $sudo apt-get install libxss-dev libxtst-dev libpci-dev libcap-dev  libxrandr-dev libnss3-dev libdirectfb-dev libaudio-dev

- $sudo apt-get install libssl-dev libdbus-1-dev libglib2.0-dev libxkbcommon-dev libegl1-mesa-dev libgbm-dev libgles2-mesa-dev mesa-common-dev

- $sudo apt-get install libasound2-dev libpulse-dev gstreamer1.0-omx libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev  gstreamer1.0-alsa

- $sudo apt-get install libvpx-dev  libsnappy-dev libnss3-dev

Al termine per controllare la presenza e le versioni dei compilatiti installati digitando sul terminale:

- $ gcc -v

e

- $ g++ -v


<img width="482" alt="image" src="https://github.com/user-attachments/assets/ffe7a0e2-416c-41cd-b9ec-d55513326f21" />
 
<img width="482" alt="image" src="https://github.com/user-attachments/assets/366a94fe-b026-46cd-8e2f-d70376d1efd9" />

 

##  Configurare QtCreator

Terminata l'installazione dei pacchetti, sul menu della Raspberry troviamo una serie di nuove applicazioni, tra cui QtCreator.

 <img width="381" alt="image" src="https://github.com/user-attachments/assets/9a14d12b-f72b-4342-a2cb-1893d6c408f3" />

Clicchiamo con il mouse sulla voce Qt Creator e avviamo il programma
Per prima cosa apriamo la finestra delle Preferenze (Edit → Preferences) e selezioniamo la pagina Kits.

<img width="482" alt="image" src="https://github.com/user-attachments/assets/e261f927-477c-43f9-a4fc-f73edbcac67d" />

Nei Box relativi ai compilatori, selezioniamo i compilatori GCC

<img width="454" alt="image" src="https://github.com/user-attachments/assets/f1a7212d-3619-4aec-9edc-02b64be74b07" />

Clicchiamo su OK e Apply.

A questo punto tutto è configurato e siamo pronti a sviluppare la nostra applicazione.


## Raspberry Pi – Gestione GPIO.

Per gestire i GPIO della Raspberry è stata utilizzata un libreria open source appositamente sviluppata chiamata WiringPi

https://github.com/WiringPi/WiringPi

Si tratta di una libreria Cpp per Raspberry Pi tramite la quale è possibile gestire i pin digitali, quelli analogici, le comunicazioni SPI, quelle I2C e molto altro.
La libreria è scritta in Cpp ed è molto efficiente e relativamente semplice da installare e usare.

Prima di avventurarsi nel processo di installazione della libreria è sempre consigliabile controllare se già è presente nel nostro sistema.
Questa libreria viene infatti molto spesso distribuita insieme al sistema operativo della Raspberry e non è affatto strano che sia già presente nel nostro sistema.
Per controllare se la libreria è già installata dalla consolle digitare:
- $gpio-v
Se il comando restituisce il numero di versione e altre informazioni sulla libreria, possiamo dedurre che la libreria è già installata.

Una volta accertato che la libreria è nel nostro sistema possiamo digitare il seguente comando:
- $gpio readall

Il quale ci restituisce una panoramica completa di tutti i pin disponibili sulla tua scheda Pi.

![image](https://github.com/user-attachments/assets/f2ddc6cf-a9ba-47f5-9580-5b120675cc3f)

La tabella che viene mostrata a schermo è divisa in 2 parti speculari, e ognuna delle quali rappresenta una delle due file di pin presenti sul connettore di espansione della scheda.
Per fare un confronto, riporto qui di seguito la piedinatura della Raspberry Pi

![image](https://github.com/user-attachments/assets/0299d545-5042-4ee4-ab2c-f8989818e658)

Ecco il significato di ogni colonna della tabella:

•	Physical : riporta il nome del pin fisico GPIO header, in modo da poter essere localizzato sulla scheda.
•	V : il "valore" corrente del pin, sostanzialmente questa colonna dice se il pin specificato è set-tato ad un livello BASSO o ALTO.
•	Mode : un pin deve essere impostato in una determinata "modalità" per eseguire operazioni. Le modalità più comuni per i pin digitali sono INPUT (è possibile leggere il valore dal pin) e OUTPUT (è possibile scrivere un valore sul pin). Puoi anche notare la modalità ALT0, che qui viene utilizzata per il protocollo I2C (SDA, SCL) e il protocollo SPI (MOSI, MISO, SCLK).
•	Name : se guardi la seconda immagine con la piedi natura del Raspberry Pi, puoi vedere che la colonna "Nome" mostra solo la funzione standard di ciascun pin e, se applicabile, sovrascrive questa funzione standard con la funzione alternativa. 
E bene tenerete sempre presente che che i numeri GPIO corrispondono alla colonna "wPi" e non alla colonna "BCM".
•	wPi : questi sono i numeri dei pin effettivamente utilizzati dalla libreria WiringPi. 
Questa convenzione di numerazione è stata stabilita molto tempo fa quando la libreria Wirin-gPi è stata scritta per la prima volta. Questa numerazione garantisce che i numeri dei pin ri-mangano gli stessi per tutte le revisioni della scheda. A meno che non si utilizzi una scheda molto vecchia (<Raspberry Pi 2), non comunque più senso utilizzare questa convenzione.
•	BCM : la scheda Raspberry Pi ha un BCM2835 (canale SOC Broadcom). 
Questa colonna definisce i numeri dei pin e le funzioni alternative per il GPIO header. Questa convenzione di numerazione è ora la più utilizzata nella comunità Raspberry Pi.
Per ricapitolare, questa tabella aiuta  ad ottenere una rapida panoramica di tutti i pin, quale numero utiliz-zare per ciascun pin e la sua modalità/stato corrente.
Come regola generale si preferisce utilizzare la convenzione di numerazione BCM rispetto alla convenzio-ne WiringPi.

**Installare la libreria.**

Nel caso in cui la libreria non fosse installata o che nel nostro file system non siano presenti il file .h da in-cludere nel nostro progetto, possiamo installare la libraia in questo modo:
Scarichiamo il file come .tar o come .zip dal repository ufficiale:

https://github.com/WiringPi/WiringPi

Una volta scompattati i file in una directory eseguiamo il comando:

$./build

La libreria viene compilata automaticamente e tutti i file copiati nelle directory del sistema.

![image](https://github.com/user-attachments/assets/bb377ebd-e8dc-4c8d-8125-7f06a6c5ac77)

Per poter utilizzare la libreria è necessario avere il file .SO da lincare dinamicamente al programma che la utilizzata e il file header .h nel quale sono riportati tutti i prototipi delle funzioni che porteremmo utilizzare nel nostro codice.
Il file  libwiringPi.so (libreria dinamica) viene copiato nella directory /usr/local/lib
Mentre gli header ( i file .h) in /usr/local/include.
Ovviamente i due path dovranno esser inseriti nelle variabili d’ambiente giuste affinché il compilatore li trovi.

**Utilizzo della libreria in un programma c/c++.**

Il segmento di codice seguente mostra un esempio di utilizzo della libreria e mostra come accendere o spegnere un led collegato al BCM pin 17 in base allo stato di un pulsante collegato al BCM pin 18
```
#include <wiringPi.h>

#define PIN_LED 17
#define PIN_BUTTON 18

int main (int argc, char **argv)
{
    wiringPiSetupGpio();
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
    printf("LED and button pins have beens setup.\n");
    while (1)
    {   
        if (digitalRead(PIN_BUTTON) == HIGH) {
            digitalWrite(PIN_LED, HIGH);
        }
        else {
            digitalWrite(PIN_LED, LOW);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
```
