# Digitalizzazione-di-un-sintetizzatore-analogico-PB13

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
