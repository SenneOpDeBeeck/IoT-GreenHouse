# IoT-GreenHouse

IoT Project (YX0470 | 2022)

By Senne Op de Beeck


![image](https://user-images.githubusercontent.com/100275526/171277205-1b145003-5639-4eae-8c50-a66960d09802.png)


--- Inleiding ---

We hebben een zeer grote serre die onderverdeeld is in meerdere kweekbakken met verschillende soorten kruiden. Omdat de kweekbakken geregeld van kruid veranderen wil de eigenaar graag een modulair systeem om deze te automatiseren en monitoren.

Elke kweekbak regelt afzonderlijk de ideale kweekomgeving voor het gekozen kruid. Zo zal een kweekbak voor basilicum andere temperatuur, vochtigheid en belichtingsperiodes hebben dan een kweekbak voor groene munt. 

Elke kweekbak zal dus sensoren nodig hebben die de grondvochtigheid en temperatuur monitoren. Indien een vooraf bepaalde grenswaarde overschreden wordt zal er een bepaalde automatisatie/actie ondernomen worden. (te warm -> vensters open, te droog -> water pompen, ...)  De belichting gebeurd ook via een automatisch programma. 
De data van deze sensoren en de bijhorende acties worden opgeslagen in een database en kunnen 
worden weergegeven met grafana. 

Om te voorkomen dat de kweker zijn kweekbakken opnieuw moet programmeren bij elke kruidwisseling zal hij door middel van een RFID tag de bak automatisch kunnen instellen op de gewenste kruiden. Deze instellingen kunnen worden weergegeven op een LCD scherm.


Procedure
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
WEEK 1

Toen we de uitleg kregen van wat de eindopdracht inhoud ben ik meteen begonnen met nadenken en opzoeken van hoe ik dit project het beste zou kunnen realiseren. Thuis ben ik er dan ook direct ingevlogen. Eerst heb ik opgeschreven welke componenten dat ik allemaal nodig zou hebben en heb ik een kleine schets gemaakt van hoe ik ongeveer wou dat het er zou uitzien. 
Ik heb niet veel langer zitten treuzelen en heb mijn eerste componenten besteld zoals mijn bloempotten, waterpomp en warmte mat. Deze kwamen een kleine week later aan. Dan ben ik begonnen met programmeren van de verschillende sensoren die ik moest gebruiken. Zo heb ik al de nodige componenten aan de praat gekregen. Dit ging het later allemaal veel makkelijker maken om ze uiteindelijk in mijn eindprogramma te zetten. Zo ben ik aan het einde van deze week rustig kunnen beginnen aan het maken van mijn eindprogramma. ![image](https://user-images.githubusercontent.com/100275526/170356357-856b8fe1-6f5e-4b42-b18d-e174c75eb2d0.png)


WEEK 2

Week 2 ben ik verdergegaan met maken van mijn eindprogramma. Dit was de opdracht die we moesten maken tegen het begin van week 3, een klein prototype programma. Na wat puzzelen en de juiste stukken code in mijn programma te zetten had ik al een klein werkend project. Zo kon ik al de waardes van mijn sensoren uitlezen en zo ook mijn lcd en Rfid reader laten functioneren.
Tussendoor ben ik dan ook al wat beginnen werken aan mijn documentatie en heb ik verschillende tussentittels geplaatst van onderwerpen waar ik wat uitleg over zou gaan geven. De laatste componenten zoals een paar sensoren, transfo ’s, prototype plaatjes, enz. heb ik dan ook besteld zodat ik al men materiaal had.
In bakje waar het prototype plaatje en de transfo’s inkomen heb ik gaten gemaakt waar ik later al de bekabeling door kan steken, 3 gaatjes voor leds in de steken en dus ook een gat waar de 230V voeding binnen komt. Ik moest ook nog wat extra spullen halen zoals een bodemplaat, statief voor de led strip, … die ben ik dan snel gaan halen in de gamma. 
Ik dacht dat het ook wel leuk zou zijn om mijn Rfid reader en lcd scherm in een case te steken die dat met een 3D printer is gemaakt. Dus heb ik een paar ontwerpen doorgestuurd naar de leerkracht en heeft hij mij hier goed mee geholpen.

![image](https://user-images.githubusercontent.com/100275526/171844006-f3ad1be3-768d-4340-9787-576edbba359c.png)


WEEK 3

Week 3 ben ik verdergegaan met het maken van de plank. Zo heb ik de kabelgoten geplaatst zodat de draadjes van de sensoren ordelijk bij de prototypeplaatjes kunnen komen en het er ook mooier uit komt te zien. Zo kwam al direct bij een probleem hoe ik een connectie kon maken met de RFID reader. Ik dacht eerst gewoon de draadjes te solderen aan de pinnen maar dat ging moeilijker dan gedacht. Dus heb ik gebruik gemaakt van stukken female header pinnen en zo de 2 draadjes aan elkaar heb gesoldeerd. Zo kom ik er voordeligger uit want nu kan ik de header pinnen van de RFID reader af halen en deze opnieuw gebruiken. 
Dit hetzelfde voor het lcd scherm. Ook ben ik het prototype bordje beginnen solderen en heb ik de verschillende relais, esp32 header pinnen en weerstanden al gesoldeerd. 
De volgende dag heb ik al de bedrading van de sensoren richting de prototypeplaatjes gelegd. Jammer genoeg moest ik door wat vertraging nog wachten op men led strip en heb ik de verschillende voedingspanning al gesoldeerd die konden. De laatste dag van deze week kreeg ik uiteindelijk men led strip aan en heb ik deze gesoldeerd aan een stuk draad dat richting de prototypeplaatjes gaat en zo zijn al de componenten geplaatst. 

![image](https://user-images.githubusercontent.com/100275526/171844046-e7a1d191-1748-4a8d-842e-ecb6da7db3da.png)
![image](https://user-images.githubusercontent.com/100275526/171844056-13899954-08f4-4521-95e2-1985fe1e6f00.png)



WEEK 4

De nieuwe week startte ik met het solderen van al de signaaldraden aan de headerpinnen van de esp32. Aan de voorkant van het pcb bakje heb ik 3 gaten gemaakt waar ik leds heb in gestoken zo wanneer oftewel de pomp aangaat er een rood lampje gaat branden, als de warmte mat aangaat er een geel lampje gaat branden en als de ramen geopend worden er een groen lampje zal branden. Zo is heel mijn prototype bordje gesoldeerd en klaar om te testen. Toen ik de stekker in het stopcontact stak zag ik meteen dat het lcd schermpje niet brandde. Meteen ben ik begonnen met uitmeten en vond ik redelijk snel de fout, zo was de 5V verbinding die ik had gesoldeerd niet goed samengesmolten en gaf het niet door. Dit probleem heb ik makkelijk kunnen oplossen door even mijn soldeerbout tegen het soldeersel te houden zodat het in mekaar smelt.

De opdracht die deze week moest afzijn was de MQTT connectie maken. Dit was niet zo een heel moeilijke taak vond ik zelf. Zo moest ik alleen een publish sturen van de esp32 naar de raspberry pi, die stuurt de waardes door naar de influx data base die ik heb ingesteld en zo via de influx data base wordt de data doorgestuurd naar grafana. Op grafana heb ik 4 verschillende dashboards gemaakt met elk de specifieke waarde van een sensor.

![image](https://user-images.githubusercontent.com/100275526/171844083-981cd1b9-fb2c-4e03-9482-ffcc521be2d0.png)


WEEK 5

Week 5 heb ik mijn plank zo goed als afgemaakt door alle componenten te plaatsen op de bodemplaat en het praktische gedeelte voorlopig klaar was. Daarna ben ik eens wat beginnen testen met het prototype plaatje en kwam ik al snel op een volgend probleem. Zo gaf de grond temperatuur sensor heel te tijd aan dat de temperatuur te laag was en zo de warmte mat aangestuurd werd. Dit terwijl hij wel gewoon de juiste waarde stuurde. Zo zag ik in mijn programma een stomme fout waarbij ik de verkeerde memory had ingegeven. 


WEEK 6

De voorlaatste week ben ik de laatste probleempjes aan het proberen op te lossen. Als de Pomp en de micro servo motor aangingen(soms apart ook) “crasht” de esp en komen er verschillende rare tekens op het LCD scherm. Zelf denk ik dat het komt doordat ze te veel stroom trekken. Daarom heb ik besloten de micro servo motor uit men project te halen. In dit proces heb ik per ongeluk men transfo een beetje los getrokken waardoor dat ineens men lcd en grondtemperatuur sensor het niet meer doen. Dit kom omdat er een piekstroom is ontstaan en zo de 5V apparaten overbelast heeft. Hier heb ik dus een nieuwe lcd en sensor voor moeten gaan halen. Nadat ik deze aangesloten had en mijn project terug spanning gaf werkte men project terug helemaal. Zo kon ik de dag erna men project werkend gaan voorstellen aan al mijn medeleerlingen en docent.

Hieronder zie je nog een mooi dashboard met verschillende grafieken van al de waardes die ik binnenkreeg in men database en zo naar grafana gestuurd werden.
![image](https://user-images.githubusercontent.com/100275526/171844117-7222ab80-b68c-4428-b68e-81425a950e9f.png)


WEEK 7

De paar dagen na de presentatie heb ik besteed aan het afwerken van mijn documentatie. Zo heb ik ook een hoofdstuk aangemaakt op mijn GitHub pagina met allerlei info over dit project. Naast dit heb ik ook een youtube video gemaakt met wat uitleg over mijn project.

Link youtube video: https://youtu.be/OGu_YNZe474


AANSLUITINGEN
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

RFID - Reader

Component pin	Kleur draad Aansluiting
3.3V	BLAUW	          3.3V ESP
GND	  BLAUW / WIT	    GND ESP
SDA  	ORANJE	        D5
SCK	  ORANJE / WIT	  D18
MOSI	GROEN	          D23
MISO	GROEN / WIT	    D19



LCD - Scherm

Component pin	Kleur draad	Aansluiting
5V	BRUIN	5V ESP
GND	BRUIN / WIT	GND ESP
SDA	ORANJE	D21
SCL	ORANJE / WIT	D22



Moisture sensor

Component pin	Kleur draad	Aansluiting
3.3V	BLAUW	3.3V ESP
GND	BLAUW / WIT	GND ESP
SIGNAL	ORANJE	D35



DHT22

Component pin	Kleur draad	Aansluiting
3.3V	BLAUW	3.3V ESP
GND	BLAUW / WIT	GND ESP
SIGNAL	ORANJE	D33



DS18B20 Grond sensor

Component pin	Kleur draad	Aansluiting
5V	BRUIN	5V ESP
GND	BRUIN / WIT	GND ESP
SIGNAL	ORANJE	D4



Waterpomp

Component pin	Kleur draad	Aansluiting
3,3V	BRUIN	3,3V ESP
GND	BRUIN / WIT	GND ESP
RELAIS	>>	D14



Led Strip

Component pin	Kleur draad	Aansluiting
12V		12V Transfo
GND		GND Transfo
RELAIS	>>	D12



Warmtemat

Component pin	Kleur draad	Aansluiting
230V	(BRUIN)	230V Transfo
GND	(BLAUW)	GND Transfo
RELAIS	>>	D13



Leds

Component pin	Aansluiting	Toepassing
ROOD	D27	(POMP)
GEEL	D26	(WARMTEMAT)
GROEN	D32	(RAMEN)


EAGLE SCHEMA
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

![image](https://user-images.githubusercontent.com/100275526/171844861-3fc9603b-8e19-4767-9dbd-a685b8b82cb1.png)


PCB DESIGN
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

![image](https://user-images.githubusercontent.com/100275526/171845023-0f1e6739-f734-465b-94d5-bbd7bc752ac5.png)





