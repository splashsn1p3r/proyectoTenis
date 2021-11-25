#include <iostream>
//Práctica version 1

#include <iostream>
#include <stdlib.h>
#include <time.h>
// tip para usar los numeros aleatorios: variable = limite_inferior + rand() % (limite_superior +1 - limite_inferior) ;
#include <string>

using namespace std;

const int ANCHO_PISTA = 7;
const int LIM_INF_HAB = 1;
const int LIM_SUP_HAB = 2;
const int LIM_INF_VEL = 1;
const int LIM_SUP_VEL = 3;
const bool JUEGO_ALEATORIO = true;
const bool MODO_DEBUG = false;

string marcador(int puntuacion); //hecha
int golpeoBola(int posTen, int habilidad); //hecha, sin comprobar(creo que funciona)
int correTen(int posTen, int vel, int posBol); // arreglada



int main() {
    string nombre1, nombre2, marcador1, marcador2;
    int hab1, hab2, vel1, vel2, empieza, puntos1 = 0, puntos2 = 0, posTen1 = 4, posTen2 = 4;
    int posBola = 0, posTenGolp = 0, habTenGolp = 0, posTen = 0, velTen = 0;
    bool juego = false, turno1;

    cout << "Bienvenido al simulador de partidos de tenis" << endl;
    cout << "Datos del tenista 1" << endl;
    cout << "Introduce sus iniciales: ";
    cin >> nombre1;
    cout << "Introduzca su habilidad (1 o 2): ";
    cin >> hab1;
    cout << "Introduzca su velocidad (1 al 3): ";
    cin >> vel1;
    cout << "Datos del tenista 2" << endl;
    cout << "Introduce sus iniciales: ";
    cin >> nombre2;
    cout << "Introduzca su habilidad (1 o 2): ";
    cin >> hab2;
    cout << "Introduzca su velocidad (1 al 3): ";
    cin >> vel2;
    srand(time(NULL));


    if (JUEGO_ALEATORIO == true) {      //Modo de juego teclado
        empieza = 1 + rand() % (2);

        if (empieza == 1){
            cout << "Comienza " << nombre1 << endl;
            posTenGolp = posTen1;
            habTenGolp = hab1;
            posTen = posTen2;
            velTen = vel2;
            turno1 = true;
        }
        else if (empieza == 2) { //esto que parece una cosa que no tiene sentido nos ffacilita mucho la creación del bucle while de jugada ya que las funciones seran siempre las mismas
//            string aux = nombre1;
//            int auxiliar = hab1;
//            nombre1 = nombre2;
//            nombre2 = nombre1;
//            hab1 = hab2;
//            hab2 = auxiliar;
//            auxiliar = vel1;
//            vel1 = vel2;
//            vel2 = auxiliar;
             cout << "Comienza " << nombre2 << endl;
             posTenGolp = posTen2;
             habTenGolp = hab2;
             posTen = posTen1;
             velTen = vel1;
             turno1 = false;
         }

        while (!juego) {
            // la posicion del gopeo de la bola y del tenista una vez han corrido, y de la velocidad y habilidad del tenista al que le toca
            bool jugada = false;
            while (!jugada){
                posBola = golpeoBola(posTenGolp, habTenGolp);
                if(posBola <= 7 && posBola > 0) {
                    posTen = correTen(posTen, velTen, posBola);
                    if (posBola == posTen) {
                        if(turno1){
                            posTenGolp = posTen2;
                            habTenGolp = hab2;
                            posTen = posTen1;
                            velTen = vel1;
                            turno1 = false;
                        }
                        else {
                            posTenGolp = posTen1;
                            habTenGolp = hab1;
                            posTen = posTen2;
                            velTen = vel2;
                            turno1 = true;
                        }
                    }
                    else{
                        if (turno1) {
                            puntos1++;
                            posTenGolp = posTen2;
                            habTenGolp = hab2;
                            posTen = posTen1;
                            velTen = vel1;
                            turno1 = false;
                            jugada = true;
                        }
                        else {
                            puntos2++;
                            posTenGolp = posTen1;
                            habTenGolp = hab1;
                            posTen = posTen2;
                            velTen = vel2;
                            turno1 = true;
                            jugada = true;
                        }
                    }
                }
                else { // punto para quien no golpea la bola
                    if (turno1) {
                        puntos2++;
                        posTenGolp = posTen2;
                        habTenGolp = hab2;
                        posTen = posTen1;
                        velTen = vel1;
                        turno1 = false;
                        jugada = true;
                    }
                    else {
                        puntos1++;
                        posTenGolp = posTen1;
                        habTenGolp = hab1;
                        posTen = posTen2;
                        velTen = vel2;
                        turno1 = true;
                        jugada = true;
                    }
                }
            }


            marcador1 = marcador(puntos1);      //Actualiza y enseña marcador
            marcador2 = marcador(puntos2);
            // casos en los que no se produce ventaja
            if (puntos1 == 4 && puntos2 < 3) {

                cout << "El ganador del juego es " << nombre1;
                juego = true;
            } else if (puntos2 == 4 && puntos1 < 3) {

                cout << "El ganador del juego es " << nombre2;
                juego = true;

            }
                // resto de casos
            else {
                //Casos en los que hay que jugar con ventaja
                if ((puntos1 == 4 && puntos2 == 3) || (puntos2 == 4 && puntos1 == 3)) {

                    // se comprueba que no haya que reducir la ventaja de uno de los jugadores
                    if (puntos1 == 4 && puntos2 == 4) {
                        puntos1 = 3;
                        puntos2 = 3;
                    }
                }
                cout << nombre1 << "  " << marcador1 << " - " << marcador2 << "  " << nombre2 << endl;
            }


        }
    }
//    else {  //Modo de juego aleatorio
//    }


        return 0;
}

string marcador(int puntuacion) { //Muestra el marcador
    string res = "0";
    switch (puntuacion) {
        case 0:
            res = "00";
            break;
        case 1:
            res = "15";
            break;
        case 2:
            res = "30";
            break;
        case 3:
            res = "40";
            break;
        case 4:
            res = "Ad";
            break;
    }

    return res;
}

int golpeoBola(int posTen, int habilidad) {
    int destBolDeseado, destBolAlcanzado;
    //primero inicializamos los numeros aleatorios que vamos a usar en la función
    srand(time(NULL));

    if (!JUEGO_ALEATORIO) {//si NO recibe los valores por teclado
        cin >> destBolDeseado;
    }
    else {// si recibe los valores por teclado
        destBolDeseado = 1 + rand() % 7;
    }
    if (destBolDeseado <= habilidad) {//si tiene habilidad suficiente
        destBolAlcanzado = destBolDeseado;
    }
    else {
        // calcular la probabilidad de acierto si el jugador no tiene suficiente habilidad
        int probAcierto = 100 - (((destBolDeseado - habilidad) / (ANCHO_PISTA - 1 - LIM_INF_HAB)) * 100);
        int probReal = rand() % 100;
        if (probAcierto < probReal) {
            destBolAlcanzado = destBolDeseado;
        }
        else {
            destBolAlcanzado = destBolDeseado - 1 + rand() % (1);
        }
    }
    return destBolAlcanzado;
}

int correTen(int posTen, int vel, int posBol) {
    int distancia;

    distancia = abs(posTen - posBol);
    if (distancia < vel) {                                        //Si la distancia es menor entonces llega.
        posTen = posBol;
    }
    else if (distancia > vel && posTen > posBol) {                //La distancia es mayor y corre izquierda.
        posTen = posTen - vel;
    }
    else if (distancia > vel && posTen < posBol) {                //La distancia es mayor y corre derecha.
        posTen = posTen + vel;
    }

    return posTen;
}