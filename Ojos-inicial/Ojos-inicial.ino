// NOTE: esto es ejemplo dado
//  #define fila1 10
//  #define fila2 9
//  #define fila3 6
//  #define fila4 3
//  #define tira 11

// int cont;
#define tiempo 300
// NOTE:
//  Tengo 5 ojos, con 3 filas  de leds cada uno que se deben encender
//  progresivamente desde abajo hacia arriba pines disponibles:
//  17_18_23_22_21_19_16_15_32_33_25_26_27_14_13_12_

// unsigned long t0;
void setup() {
  short pines[15] = {17, 18, 23, 22, 21, 19, 16, 15,
                     32, 33, 25, 26, 27, 14, 13};
  for (short cuenta = 0; cuenta < 15;
       cuenta++) { // NOTE: declarar cada pin a usar como pin de salida
    pinMode(pines[cuenta], OUTPUT);
    digitalWrite(pines[cuenta], LOW); // setear cada salida como apagado
  }
}
void prender_ojo(short fila1, short fila2, short fila3) {
  prender_progresivamente(fila1);
  prender_progresivamente(fila2);
  prender_progresivamente(fila3);
}
void prender_progresivamente(short pin) {
  for (short brillo = 0; brillo <= 253; brillo++) {
    analogWrite(pin, brillo);
    delayMicroseconds(tiempo);
  }
}

void loop() {
  for (short ojonumero = 1; ojonumero <= 5; ojonumero++) {
    switch
      (ojonumero) {
      case 1: {
        prender_ojo(17, 18, 23);
        break;
      };
      case 2: {
        prender_ojo(22, 21, 19);
        break;
      };
      case 3: {
        prender_ojo(16, 15, 32);
        break;
      };
      case 4: {
        prender_ojo(33, 25, 26);
        break;
      };
      case 5: {
        prender_ojo(27, 14, 13);
        break;
      };
      default:
        break;
      }
  }
}
