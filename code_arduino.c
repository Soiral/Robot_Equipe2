char val;

void setup()
{
 // begin the serial communication
 Serial.begin(9600);
 // Vitesse moteur gauche
 pinMode(9, OUTPUT);
 // Direction moteur gauche
 pinMode(7, OUTPUT);
 // Vitesse moteur droite
 pinMode(10, OUTPUT);
 // Direction moteur droite
 pinMode(8, OUTPUT);
}

boolean is_a_number(int n)
{
  return n >= 48 && n <= 57;
}

int ascii2int(int n, int byte_read)
{
  return n*10 + (byte_read - 48);
}

void roue_gauche(int puissance, String sens) {
  if (sens == "avant") {
    digitalWrite(7, HIGH);    
  } else {
    digitalWrite(7, LOW); 
  }
  analogWrite(9, puissance);
}

void roue_droite(int puissance, String sens) {
  if (sens == "avant") {
    digitalWrite(8, HIGH);   
  } else {
    digitalWrite(8, LOW);
  }
  analogWrite(10, puissance);
}

void tourner_gauche(int puissance, String sens, int rapidite) {
  if (rapidite == 1) {
    if (puissance + 50 >= 255) {
    puissance -= 50; 
    }
    roue_gauche(puissance, sens);
    roue_droite(puissance + 50, sens);
  } else if (rapidite == 2) {
    if (puissance + 100 >= 255) {
    puissance -= 100; 
    }
    roue_gauche(puissance, sens);
    roue_droite(puissance + 100, sens);
  }  
}

void tourner_droite(int puissance, String sens, int rapidite) {
 if (rapidite == 1) {
    if (puissance + 50 >= 255) {
    puissance -= 50; 
    }
    roue_droite(puissance, sens);
    roue_gauche(puissance + 50, sens);
  } else if (rapidite == 2) {
    if (puissance + 100 >= 255) {
    puissance -= 100; 
    }
    roue_droite(puissance, sens);
    roue_gauche(puissance + 100, sens);
  }  
}
//0 -> arret
//1 -> avancer
//2 -> avancer rapidement
//3 -> reculer
//4 -> reculer rapidement
//5 -> tourner gauche normal
//6 -> tourner gauche rapidement
//7 -> tourner droite normal
//8 -> tourner droite rapidement
//9 -> tourner gauche arriere normal
//a -> tourner gauche arriere rapidement
//b -> tourner droite arriere normal
//c -> tourner droite arriere rapidement

void loop()
{
  
 // regarde si quelque chose se trouve dans le buffer
 if (Serial.available()) {
   // lit le premier byte dans la pile (valeur entre 0 to 255)
   val = Serial.read();
   Serial.println(val);

  switch(val) {
    case '0':
      roue_droite(0, "avant");
      roue_gauche(0, "avant");
      break;
    case '1':
      roue_droite(70, "avant");
      roue_gauche(70, "avant");
      break;
    case '2':
      roue_droite(200, "avant");
      roue_gauche(200, "avant");
      break;
    case '3':
      roue_droite(70, "arriere");
      roue_gauche(70, "arriere");
      break;
    case '4':
      roue_droite(200, "arriere");
      roue_gauche(200, "arriere");
      break; 
    case '5':
      tourner_gauche(100, "avant", 1);
      break; 
    case '6':
      tourner_gauche(100, "avant", 2);
      break;   
    case '7':
      tourner_droite(100, "avant", 1);
      break; 
    case '8':
      tourner_droite(100, "avant", 2);
      break; 
    case '9':
      tourner_gauche(100, "arriere", 1);
      break; 
    case 'a':
      tourner_gauche(100, "arriere", 2);
      break; 
    case 'b':
      tourner_droite(100, "arriere", 1);
      break; 
    case 'c':
      tourner_droite(100, "arriere", 2);
      break;       
  }  
 }
}
