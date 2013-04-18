// Testing generative algorithms based on the book "The Selfish Gene" by Richard Dawkins
// Copyright 2011,2013
// Jeroen Doggen - jeroendoggen@gmail.com

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <math.h>

using namespace std;

#define LENGTH 8                                  // key length
#define NUMCHILDREN 1000                          // number of children in each generation: higher -> better convergence, too high -> lots op cpu cycles needed), too low -> no convergence

// Function prototypes
void setInitialValue(int initval);                // select initial parent (and secret key(commented))
void drawMenu();                                  // debug and status messages
void loop();                                      // loop until secret key found
void generateChildren();                          // randomly generate a new generation of children
void selectParent();                              // select the best child to become the parent of the next generation
void getData();                                   // ask user for a key

// Global Variables
unsigned char children[NUMCHILDREN][LENGTH];      // array holding all childer of current generation
unsigned char  parent[LENGTH];                    // parent of the current generation
unsigned char  delta[LENGTH];                     // diffence between 'current' child and secret key
unsigned char  secret[LENGTH];                    // secret key

int generation = 0;                                 // generation counter
int bestdelta = 9999999;                            // best diffence, compared to secret key
int oldbestdelta = 19999999;                        // to prevent locking
int failures = 0;                                   // to prevent locking
int checksum = 0;                                   // for alternative method (not implemented)
int checksum_secret = 0;                            // for alternative method (not implemented)

int inhibit = 3;                                    // limit mutation frequency
int randomspread = 5;                               // limit mutation distance (3 -> -1,0,1)

int spread;
int rnd;

int main(void) {
  getData();
  setInitialValue(0);
  drawMenu();
  loop();
}

void getData() {
  char item;
  int lengte = LENGTH;
  cout << "Enter secret key: (followed by enter) (maximum key length:" << lengte << ")" << endl;
  for (int i = 0; i < LENGTH; i++) {
    cin >> item;
    secret[i] = item;
  }
}

void loop() {
  while (true) {
    generateChildren();
    selectParent();
    if (bestdelta == 0) {
      cout << "Secret found in generation " << generation <<" : Secret= ";
      for (int i = 0; i < LENGTH; i++) {
        cout << " " << static_cast<char>(parent[i]);
      }
      cout << endl;
      break;
    }
  }
}

void setInitialValue(int initval) {
  srand(time(NULL));
  for (int i = 0; i < LENGTH; i++) {
    rnd = (rand() % 256);
    parent[i] = rnd;
    checksum_secret = checksum_secret+secret[i];
  }
}

void generateChildren() {
  int rnd = 0, rnd2 = 0;
  for (int j = 0; j < NUMCHILDREN; j++) {
    for (int i = 0; i < LENGTH; i++) {
      // rnd = -1 + (rand() % randomspread);
      spread = rand() % 10;
      rnd = (rand() % ((bestdelta/LENGTH)+2) - (((bestdelta/LENGTH)+2)/2) );
      rnd2 = (rand() % inhibit);
      if (rnd2 == 1) {
        children[j][i] = parent[i]+rnd;
      } else {
        children[j][i] = parent[i];
      }
    }
  }
}

void drawMenu() {
  cout.setf(ios::fixed);
  cout << "Secret: ";
  for (int i = 0; i < LENGTH; i++) {
    cout << secret[i] << " ";
  }
  cout <<  "Checksum secret:" << checksum_secret << endl << "Parent: ";
  for (int i = 0; i < LENGTH; i++) {
    cout << parent[i] << " ";
  }
  cout << endl;
}

void selectParent() {
  generation++;
  oldbestdelta = bestdelta;
  for (int j = 0; j < NUMCHILDREN; j++) {
    int deltasum = 0;
    for (int i = 0; i < LENGTH; i++) {
      // Uncomment for position based method
      delta[i] = abs(children[j][i]-secret[i]);
      delta[i] = abs(children[j][i]-secret[i]);
      deltasum = deltasum+delta[i];

      // checksum=checksum+children[j][i];
      // deltasum=abs(checksum_secret-checksum);
    }
    if (deltasum < bestdelta) {
      cout << "Bestdelta: " << bestdelta << " ";
      cout << "Generation: " << generation << " ";
      cout << "Deltasum: " << deltasum << " ";
      cout << "Parent:";
      for (int i = 0; i < LENGTH; i++) {
        parent[i] = children[j][i];
        cout << " "<< parent[i];
      }
      bestdelta = deltasum;
      cout <<" "<< endl;
    }
  }
  if (oldbestdelta == bestdelta) {
    // cout << "Failed generation: " << generation << endl;
    failures++;
    // cout << "Parent:";
    for (int i = 0 ; i < LENGTH; i++) {
      // cout << " "<< parent[i];
    }
    if (failures>1000) {
      cout << endl << "1000 failed generations, resetting parent: ";
      bestdelta = bestdelta+5;
      for (int i = 0; i < LENGTH; i++) {
        int rnd, rnd2;
        rnd = -1 + (rand() % randomspread);
        rnd2 = (rand() % inhibit);
        if (rnd2 == 1) {
          parent[i] = parent[i] + rnd;
        }
        cout << " "<< parent[i];
        failures = 0;
      }
      cout << endl;
    }
  }
}
