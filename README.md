# Ruba Mazzetto
Progetto per il corso di Laboratorio di Programmazione tenuto dal [Dr. Gennaro Vessio]([https://link](https://www.uniba.it/portal_memberdata/gennaro.vessio)).

*UniBA - Laurea Triennale in Informatica e Comunicazione Digitale)*

## Traccia

II "rubamazzetto" è un gioco di carte, variante semplificata della "scopa", molto diffuso in 
Italia. Si gioca con ie carte da gioco italiane da 40 carte suddivise in 4 semi da 10 carte 
ciascuno. Spesso è giocato solo da 2 persone ma si puo giocare anche in 3 e in 4.

Ogni giocatore, nel rispettivo turno, può prendere solo una carta dello stesso valore dal tavolo. 
Ogni qual volta viene effettuata una presa, il giocatore deve tenere scoperta I'uItima carta del 
proprio mazzo: se I'avversario ha in mano una carta dello stesso valore può "rubare" il mazzo (che 
deve essere sempre tenuto girato).

Dopo I'uItima mano, Ie carte rimaste sul tavolo vengono aggiunte a quelle del giocatore che ha 
effettuato I'uItima presa. Lo scopo del gioco è prendere quante piu carte possibile: il punteggio è 
dato semplicemente dalla conta delle carte che ogni giocatore ha preso.

Implementare un sistema che permetta, a giocatori registrati, di sfidarsi nel gioco. II sistema 
deve prevedere la possibilita di salvare Io stato della partita e riprenderlo in un secondo 
momento. Inline, il sistema deve anche conservare (e naturalmente mostrare) Io storico dei 
risultati di ogni giocatore e relative statistiche.

----------

## Documentazione

[Doxygen](https://mauroderosa.github.io/raylib-rubamazzetto-client/docs/html/index.html)

----------

## License

**TO - DO**

## Dependencies and references
### Libraries
- [Raylib](https://www.raylib.com/) (Game Engine)
- [Raygui](https://github.com/raysan5/raygui) (GUI library for Raylib)
- [uthash](https://troydhanson.github.io/uthash/) (C HashMap library)
### Other
- [Doxygen Awesome CSS](https://jothepro.github.io/doxygen-awesome-css/) (Doxygen modern theme)