struct grupo_ojos { // un struct es como una variable que contiene otras
                    // variables
  short fila1;
  short fila2;
  short fila3;
  bool estado; // true = prendido, false = apagado
}; // se explica solo el que contiene, es mas facil trabajar con esto
#define tiempo 900

short aleatorio; // declaaracion de variable aleatorio

// declaracion de los grupos
struct grupo_ojos grupo1 = {17, 18, 23, false};
struct grupo_ojos grupo2 = {22, 21, 19, false};
struct grupo_ojos grupo3 = {16, 15, 32, false};
struct grupo_ojos grupo4 = {33, 25, 26, false};
struct grupo_ojos grupo5 = {27, 14, 13, false};

void prender_progresivamente(short pin) {
  for (short brillo = 0; brillo < 256; brillo++) {
    analogWrite(pin, brillo);
    delayMicroseconds(tiempo);
    // Serial.print(pin);Serial.print(" ");Serial.println(brillo);
  }
}
void apagar_progresivamente(short pin) {
  for (short brillo = 255; brillo > -1; brillo--) {
    analogWrite(pin, brillo);
    delayMicroseconds(tiempo);
    // Serial.print(pin);Serial.print(" ");Serial.println(brillo);
  }
}
// void prender_ojo(short fila1, short fila2, short fila3) {
//   prender_progresivamente(fila1);
//   prender_progresivamente(fila2);
//   prender_progresivamente(fila3);
// }
// void apagar_ojo(short fila1, short fila2, short fila3) {
//   apagar_progresivamente(fila3);
//   apagar_progresivamente(fila2);
//   apagar_progresivamente(fila1);
// }
/*
5 grupos de ojos, prendido aleatorio al inicio
cuando uno se apaga elegido al azar, esperar  hasta que se prenda completamente
para que se elija otro ojo (+ un pequeño tiempo aleatorio si se puede)
*/
void prender_grupo_si_apagado(struct grupo_ojos *ojo) {
  if (!ojo->estado) {
    ojo->estado = true;
    prender_progresivamente(ojo->fila1);
    prender_progresivamente(ojo->fila2);
    prender_progresivamente(ojo->fila3);
    Serial.println("prender");
  }
} // aqui ya hay punteros, solo hay que saber que para acceder a una variable
  // dentro del struct apuntado se usa '->'

void apagar_grupo_si_prendido(struct grupo_ojos *ojo) {
  if (ojo->estado) {
    ojo->estado = false;
    apagar_progresivamente(ojo->fila3);
    apagar_progresivamente(ojo->fila2);
    apagar_progresivamente(ojo->fila1);
    Serial.println("apagar");
  }
}

void setup() {
  Serial.begin(115200);

  short pines[15] = {17, 18, 23, 22, 21, 19, 16, 15,
                     32, 33, 25, 26, 27, 14, 13};
  // declaracion de pines a usar

  for (int index = 0; index < (sizeof(pines) / 2); index++) {
    pinMode(pines[index], OUTPUT);
    // Serial.println(pines[ index ]);
  } // NOTE: Funciona, solo se tiene que reiniciar una vez despues de flashear
    // deberia servir para cualquier longitud de lista de pines validos

  // solo en caso de no andar dejo esto comentado
  //  pinMode(23, OUTPUT);
  //  pinMode(22, OUTPUT);
  //  pinMode(21, OUTPUT);
  //  pinMode(19, OUTPUT);
  //  pinMode(16, OUTPUT);
  //  pinMode(15, OUTPUT);
  //  pinMode(32, OUTPUT);
  //  pinMode(33, OUTPUT);
  //  pinMode(25, OUTPUT);
  //  pinMode(26, OUTPUT);
  //  pinMode(27, OUTPUT);
  //  pinMode(14, OUTPUT);
  //  pinMode(13, OUTPUT);
  //  pinMode(12, OUTPUT);
  //  pinMode(17, OUTPUT);
  //  pinMode(18, OUTPUT);

  // solo tiene que correr una vez asique lo pongo aqui:
  while (!(grupo1.estado && grupo2.estado && grupo3.estado && grupo4.estado &&
           grupo5.estado)) {
    aleatorio = random(1, 6);
    Serial.println(aleatorio);
    switch (aleatorio) {
    case 1: {
      prender_grupo_si_apagado(&grupo1);
      // es necesario usar un puntero para cambiar la variable de estado
      break;
    };
    case 2: {
      prender_grupo_si_apagado(&grupo2);
      break;
    };
    case 3: {
      prender_grupo_si_apagado(&grupo3);
      break;
    };
    case 4: {
      prender_grupo_si_apagado(&grupo4);
      break;
    };
    case 5: {
      prender_grupo_si_apagado(&grupo5);
      break;
    }
    }
  }
}
void loop() {

  aleatorio = random(1, 6);
  Serial.println(aleatorio);
  switch (aleatorio) {
  case 1: {
    apagar_grupo_si_prendido(&grupo1);
    prender_grupo_si_apagado(&grupo1);
    break;
  };
  case 2: {
    apagar_grupo_si_prendido(&grupo2);
    prender_grupo_si_apagado(&grupo2);
    break;
  };
  case 3: {
    apagar_grupo_si_prendido(&grupo3);
    prender_grupo_si_apagado(&grupo3);
    break;
  };
  case 4: {
    apagar_grupo_si_prendido(&grupo4);
    prender_grupo_si_apagado(&grupo4);
    break;
  };
  case 5: {
    apagar_grupo_si_prendido(&grupo5);
    prender_grupo_si_apagado(&grupo5);
    break;
  }
  }
  delayMicroseconds(50 + random(1, 100));
  //hay una forma de hacer simultaneo el prendido y apagado con millis()
  //pero eso seria reescribir una buena parte del codigo 
  //tambien se puede usar el otro nucleo pero yo nose hacer eso
}
