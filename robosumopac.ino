
#include <Arduino.h>
#include <bridgeH_new.h>
#include <qtr_new.h>
#include <sumo_new.h>
#include <sharp_new.h>

int speedD=0;
int speedE=0;
int distance;
int distanceQtrD;
int distanceQtrE;
bool corBrancaD;
bool corBrancaE;
float inFilter;
float distanceFiltered;

sharp_n sharp1(A0);   
qtr_n qtrD(A1, 400);
qtr_n qtrE(A2, 400);

void setup() {
  
 Serial.begin(9600);

  Serial.println("Sumo Luta");
}

void loop() {

inFilter =sharp1.getDistance();

distanceFiltered = filterMediaMovel(inFilter); 

bridgeH_n bridgeH_D(3,4,5,speedD);
bridgeH_n bridgeH_E(7,8,6,speedE);

distance = distanceFiltered;
distanceQtrD= qtrD.getValue();
distanceQtrE= qtrE.getValue();

corBrancaD =qtrD.getcolorWhite();
corBrancaE =qtrE.getcolorWhite();

// Construtor 

sumo_n sumoV1(corBrancaD,corBrancaE,distance,55,500,800);

speedD = sumoV1.getRSpeed();
speedE = sumoV1.getLSpeed();

  Serial.print(distance);
    Serial.print("  ");
  Serial.print(sumoV1.getIndex());
     Serial.print("  ");
  Serial.println(sharp1.getDistance());
    
}

  float filterMediaMovel(float xis) {
    static float media = 0.0;
    static int indice = 1;

    if (indice == 0 || indice == 50) {
        indice = 1;
        media = 0.0;
    }

    media = media + (xis - media) / indice++;

    return media;

  }
