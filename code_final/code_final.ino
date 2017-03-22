/* PROJET DE SCIENCES DE L'INGENIEUR : SIMULATEUR DE VOL

  2016 - 2017

*/

/* Ce programme sera chargé dans la maquette */
// NB : Certaines méthodes "return" sont utilisées pour la simulation. Elles n'ont aucun impact sur le fonctionnement du programme


/* J'inclus la librairie "Servo" qui me permet de contrôler facilement des servomoteurs */

#include <Servo.h>

/* J'initialise les instances associées à mes servomoteurs : une liste de quatre éléments */

Servo servo[6];

/* J'initialise ensuite les variables générales */

int servoPins[6] = {2 , 3 , 4 , 5 , 6 , 7}; // les broches reliées aux servomoteurs
int knobPins[3] = {0 , 1 , 2}; // les broches reliées aux joysticks
int knobVals[3] = {0 , 0 , 0}; // la liste contenant les valeurs lues par les joysticks
int buttonPins[2] = {3 , 4};
int led[4] = {9 , 10 , 11 , 12};
int minCentreMax[6][3] = {
  {76 , 106 , 146}, // Romain (ailerons)
  {10 , 76 , 160}, // Florian (profondeur)
  {15 , 94 , 140}, // Florian (direction)
  {50 , 50, 73}, // Maxence (volets)
  {}, // Roulis
  {}, // Tangage
};
int pos[6] = {90 , 90 , 90 , 90 , 90 , 90}; // position du servomoteur
int dir[6]; // variable déterminant la rotation du servomoteur : 1 si horaire, 0 si trigonométrique, 2 si nulle
int temps[6]; // variable qui stockera le temps entre deux changements de position

/* Je définis ensuite les structures qui permetteront d'associer toutes ces valeurs aux parties */

/* Ces variables vont servir à l'exécution du programme (incrément, tampon, etc) */

int i , y , z;

/* Cette fonction me permet de borner une valeur afin qu'elle ne sorte pas d'un intervalle */

int borner(int variable, int minimum, int maximum) {

	if (variable <= minimum) {

		variable = minimum;
		return variable;

	}

	else if (variable >= maximum) {

		variable = maximum;
		return variable;

	} else return variable;

}

void moveServo(int direction, int delai, Servo a) {

	switch (direction) {

		borner(pos[i], minCentreMax[i][0], minCentreMax[i][2]); // je borne la valeur de position pour qu'elle reste dans les valeurs du servo

		case 0: // si dir = 0
			a.write(pos[i]);
			pos[i]--; // on diminue la position, ce qui fait tourner le servomoteur dans le sens trigonométrique
			digitalWrite(led[i], HIGH);
			delay(delai);
			break;

		case 1: // si dir = 1
			a.write(pos[i]);
			pos[i]++; // on augmente la position, ce qui fait tourner le servomoteur dans le sens horaire
			delay(delai);
			break;

		case 2: // si dir = 2
			a.write(pos[i]); // on ne change pas le position, donc le servomoteur reste fixe
      digitalWrite(led[i], LOW); // comme le servomoteur est fixe, la LED s'éteint
			break;

	}

}

/* Cette fonction me permet de déterminer la rotation du servomoteur par rapport à la valeur lue en sortie du joystick */

int determinerDirection(int a) {

	if (a < 400) {
		return 0;

	} else if (a > 700) {
		return 1;

	} else {
		return 2;

	}
}


// Cette fonction détermine le délai à appliquer entre deux incréments de position, afin de faire varier la vitesse de rotation
int determinerTemps(int y) {

	switch (dir[i]) {
		case 0: // si dir = 0
			return map(y , 405 , 0 , 100 , 0);

		case 1: // si dir = 1
			return map(y , 630 , 1023 , 100 , 0);

		case 2: // si dir = 2
			break;

	}
	return 0;
}

bool changementJoystick() {
	int a , b;
	// La variable i étant publique, elle prend la valeur que la boucle for lui applique
	a = analogRead(knobPins[i]);
	delay(10);
	b = analogRead(knobPins[i]);
	if (a != b) return true;
		else {
			return false;
			digitalWrite(led[i], LOW);
	}

	return 0;
}


bool dansDeadzone(int y) {
  return (y > 400 && y < 630);
}

void setup() {

/* J'associe chacune des instances servo à un port de ma liste servoPins (en suivant l'ordre du montage réel) */
	for (i = 0 ; i < 6 ; i++) {
		servo[i].attach(servoPins[i]);
		servo[i].write(minCentreMax[i][1]); // et je les positionne à leurs valeurs centrales pour l'initialisation
	}

	Serial.begin(9600); // je démarre la communication série pour le déboguage
}

void loop() {
  // Cette partie contrôle les servomoteurs des gouvernes et les LEDs associées aux gouvernes.

	for (i = 0 ; i < 3 ; i++) {
  
		if (changementJoystick()) {
    
      knobVals[i] = analogRead(knobPins[i]);
      Serial.println(knobVals[i]);
    
      if (dansDeadzone(knobVals[i])) {
        Serial.println("Dans Deadzone");
        servo[i].write(minCentreMax[i][1]);
        break;
      }      
			// si un joystick a changé de valeur, on actualise la valeur du servomoteur associé
			  pos[i] = map(knobVals[i], 0 , 1023, minCentreMax[i][0], minCentreMax[i][2]);
			  servo[i].write(pos[i]);
		}

    if (servo[i].read() != minCentreMax[i][1]) {
      // si la position du servomoteur est différente de sa position centrale, on allume la LED associée
      digitalWrite(led[i], HIGH);
    } else digitalWrite(led[i], LOW);
	}

	// Contrôle des volets
	for (i = 0 ; i < 2 ; i++) {
		if (analogRead(buttonPins[i]) != 0) {
      digitalWrite(led[3], HIGH);
			if (i == 0) pos[3]--;
			if (i == 1) pos[3]++;
      borner(pos[3], minCentreMax[3][0], minCentreMax[3][2]);
		}
    if (servo[3].read() != minCentreMax[3][1]) {
      digitalWrite(led[3], HIGH);
    } else digitalWrite(led[3], LOW);

		servo[3].write(pos[3]);
	}
}
