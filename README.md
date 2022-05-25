# IoT-GreenHouse
IoT GreenHouse

--- Inleiding ---

We hebben een zeer grote serre die onderverdeeld is in meerdere kweekbakken met verschillende soorten kruiden. Omdat de kweekbakken geregeld van kruid veranderen wil de eigenaar graag een modulair systeem om deze te automatiseren en monitoren.

Elke kweekbak regelt afzonderlijk de ideale kweekomgeving voor het gekozen kruid. Zo zal een kweekbak voor basilicum andere temperatuur, vochtigheid en belichtingsperiodes hebben dan een kweekbak voor groene munt. 

Elke kweekbak zal dus sensoren nodig hebben die de grondvochtigheid en temperatuur monitoren. Indien een vooraf bepaalde grenswaarde overschreden wordt zal er een bepaalde automatisatie/actie ondernomen worden. (te warm -> vensters open, te droog -> water pompen, ...)  De belichting gebeurd ook via een automatisch programma. 
De data van deze sensoren en de bijhorende acties worden opgeslagen in een database en kunnen 
worden weergegeven met grafana. 

Om te voorkomen dat de kweker zijn kweekbakken opnieuw moet programmeren bij elke kruidwisseling zal hij door middel van een RFID tag de bak automatisch kunnen instellen op de gewenste kruiden. Deze instellingen kunnen worden weergegeven op een LCD scherm.



![image](https://user-images.githubusercontent.com/100275526/170331305-647bc62b-0e1d-4867-91a1-9a6d7c003290.png)
