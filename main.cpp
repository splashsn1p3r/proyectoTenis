#include <iostream>
//Práctica version 1

#include <iostream>
#include <stdlib.h>
#include <time.h>
// tip para usar los numeros aleatorios: variable = limite_inferior + rand() % (limite_superior +1 - limite_inferior) ;
#include <string>

using namespace std;

const int ANCHO_PISTA = 7;
const int Largo_Pista = 3;
const int LIM_INF_HAB = 1;
const int LIM_SUP_HAB = 2;
const int LIM_INF_VEL = 1;
const int LIM_SUP_VEL = 3;
const bool JUEGO_ALEATORIO = false;
const bool MODO_DEBUG = false;
const int DIM_ARRAY_GOLPES = ANCHO_PISTA + 2;
const int JUEGOS_SET = 3;

typedef enum { NADIE, TENISTA1, TENISTA2 }tTenista;
typedef enum { NADA, QUINCE, TREINTA, CUARENTA, VENTAJA }tPuntosJuego;
typedef int tConteoGolpes[DIM_ARRAY_GOLPES];

string puntosAstring(tPuntosJuego puntuacion);  //HECHA Y FUNCIONAL
int golpeoBola(int posTen, int habilidad); //hecha, sin comprobar(creo que funciona)
int correTen(int posTen, int vel, int posBol); // arreglada
void introducirTenista(string& iniciales, int& habilidad, int& velocidad); //HECHA Y FUNCIONAL
void pintarMarcador(string nombre1, string nombre2, tPuntosJuego puntos1, tPuntosJuego puntos2, int juegos1, int juegos2, tTenista servicio_para);
void pintarPeloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, tTenista bola_jugador, int pos_bola);
tTenista actualizarMarcador(tTenista ganador_punto, tPuntosJuego& puntos1, tPuntosJuego& puntos2, int& juegos1, int& juegos2);      //Comprobar
tTenista lance(tTenista tenista_golpea, string nombre, int habilidad, tConteoGolpes golpes, int& golpes_ganados, int velocidad, int& pos_recibe, int& pos_bola); // he tocado alguna cosa no se como estara
tTenista jugarPunto(tTenista servicio, string nombre1, int habilidad1, int velocidad1, tConteoGolpes golpes1, int& golpes_ganados1, string nombre2,
    int habilidad2, int velocidad2, tConteoGolpes golpes2, int& golpes_ganados2);
tTenista jugarJuego(tTenista servicio, string nombre1, int habilidad1, int velocidad1, int& juegos1, tConteoGolpes golpes1, int& golpes_ganados1,
    string nombre2, int habilidad2, int velocidad2, int& juegos2, tConteoGolpes golpes2, int& golpes_ganados2);

int main() {
    string nombre1, nombre2, marcador1, marcador2;
    int hab1, hab2, vel1, vel2, empieza, posTen1 = 4, posTen2 = 4;
    tPuntosJuego puntos1 = NADA, puntos2 = NADA;
    int posBola = 0, posTenGolp = 0, habTenGolp = 0, posTen = 0, velTen = 0;
    bool juego = false, turno1;
    srand(time(NULL));        //Primero inicializamos los numeros aleatorios que vamos a usar en la función

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

        if (empieza == 1) {
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
            while (!jugada) {
                posBola = golpeoBola(posTenGolp, habTenGolp);
                if (posBola <= 7 && posBola > 0) {
                    posTen = correTen(posTen, velTen, posBola);
                    if (posBola == posTen) {
                        if (turno1) {
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
                    else { //hay que actualizar los marcadores
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


            marcador1 = puntosAstring(puntos1);      //Actualiza y enseña marcador
            marcador2 = puntosAstring(puntos2);
            // casos en los que no se produce ventaja


        }
    }
    //    else {  //Modo de juego aleatorio
    //    }


    return 0;
}

/*
funcion que usabamos antes de puntos a String
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
*/

string puntosAstring(tPuntosJuego puntuacion) {
    string res = "0";
    switch (puntuacion) {
    case NADA:
        res = "00";
        break;
    case QUINCE:
        res = "15";
        break;
    case TREINTA:
        res = "30";
        break;
    case CUARENTA:
        res = "40";
        break;
    case VENTAJA:
        res = "Ad";
        break;
    }
    return res;
}

void introducirTenista(string& iniciales, int& habilidad, int& velocidad) {
    cout << "Bienvenido al simulador de partidos de tenis" << endl;
    cout << "Datos del tenista" << endl;
    cout << "Introduce sus iniciales: ";
    cin >> iniciales;
    cout << "Introduzca su habilidad (1 o 2): ";
    cin >> habilidad;
    cout << "Introduzca su velocidad (1 al 3): ";
    cin >> velocidad;
}

tTenista actualizarMarcador(tTenista ganador_punto, tPuntosJuego& puntos1, tPuntosJuego& puntos2, int& juegos1, int& juegos2) {
    tTenista gana = NADIE;
    if (ganador_punto == TENISTA1) {
        if (puntos1 = NADA) {
            puntos1 = QUINCE;
        }
        else if (puntos1 == QUINCE) {
            puntos1 = TREINTA;
        }
        else if (puntos1 == TREINTA) {
            puntos1 = CUARENTA;
        }
        else if (puntos1 == CUARENTA && puntos2 == CUARENTA) { //no usamos el switch para poder poner este caso en especifico en vez de ensuciar el case 40
            puntos1 = VENTAJA;
        }
        else if (puntos1 == CUARENTA && puntos2 < TREINTA) {
            puntos1 = NADA;
            puntos2 = NADA;
            juegos1++;                      //Juego
        }
        else if (puntos1 == VENTAJA) {
            puntos1 = NADA;
            puntos2 = NADA;
            juegos1++;                      //Juego
        }
    }
    else if (ganador_punto = TENISTA2) {
        if (puntos2 = NADA) {
            puntos2 = QUINCE;
        }
        else if (puntos2 == QUINCE) {
            puntos2 = TREINTA;
        }
        else if (puntos2 == TREINTA) {
            puntos2 = CUARENTA;
        }
        else if (puntos2 == CUARENTA && puntos1 == CUARENTA) {
            puntos1 = VENTAJA;
        }
        else if (puntos2 == CUARENTA && puntos1 < TREINTA) {
            puntos2 = NADA;
            puntos1 = NADA;
            juegos2++;                      //Juego
        }
        else if (puntos2 == VENTAJA) {
            puntos2 = NADA;
            puntos1 = NADA;
            juegos2++;                      //Juego
        }
    }

    if (juegos1 == JUEGOS_SET) {            //Si gana tenista 1
        gana = TENISTA1;
    }
    else if (juegos2 == JUEGOS_SET) {       //Si gana tenista 2
        gana = TENISTA2;
    }

    return gana;
}

void pintarMarcador(string nombre1, string nombre2, tPuntosJuego puntos1, tPuntosJuego puntos2, int juegos1, int juegos2, tTenista servicio_para) {
    string p1String, p2String;

    p1String = puntosAstring(puntos1);       //Duda
    p2String = puntosAstring(puntos2);
    if (servicio_para == TENISTA1) {
        cout << nombre1 << " " << juegos1 << " : " << p1String << "*" << endl;           //Marcador si saca tenista 1
        cout << nombre2 << " " << juegos2 << " : " << p2String << endl;
    }
    else if (servicio_para == TENISTA2) {                                               //Marcador si saca tenista 2
        cout << nombre1 << " " << juegos1 << " : " << puntos1 << endl;
        cout << nombre2 << " " << juegos2 << " : " << puntos2 << "*" << endl;
    }
}

void pintarPeloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, tTenista bola_jugador, int pos_bola) {
    int i = 1, u = 1, cont = 0, v = 1, cont2 = 0, x = 1, p = 1, z = 1;

    cout << "  ";
    for (i = 1; i < ANCHO_PISTA +2; i++) {     //Tenista de arriba en su posicion
         if (i != pos_t1) {
             cout << "  ";
         }
         else {
            cout << nombre1;
         }
    }
    cout << endl;
    cout << "  ";

    for (u = 0; u < ANCHO_PISTA + 2; u++) {       //Linea de fondo
        cout << " -";
    }
    cout << endl;
    cout << "  ";

    while (cont != LARGO_PISTA) {                                   //Campo tenista 1 
        for (v = 1; v < ANCHO_PISTA + 4; v++) {
            if (v != pos_bola) {       
                cout << "| ";
            }
            else if (cont != 0) {
                cout << "| ";
            }
            else if (pos_bola = v){
                if (bola_jugador == TENISTA1) {
                    cout << "|o";
                }
            }
            else {
                cout << "| ";
            }
        }
        cout << endl;
        cout << "  ";
        cont++;
    }

    cout << "-1-2-3-4-5-6-7-8-9-" << endl;
    cout << "  ";

    while (cont2 != LARGO_PISTA) {                                   //Campo tenista 2
        for (x = 1; x < ANCHO_PISTA + 4; x++) {
            if (x != pos_bola) {
                cout << "| ";
            }
            else if (cont2 != 2) {
                cout << "| ";
            }
            else if (pos_bola = x) {
                if (bola_jugador == TENISTA2) {
                    cout << "|o";
                }
            }
            else {
                cout << "| ";
            }
        }
        cout << endl;
        cout << "  ";
        cont2++;
    }
   

    for (p = 1; p < ANCHO_PISTA + 3; p++) {       //Linea de fondo
        cout << " -";
    }
    cout << endl;

    cout << "  ";
    for (z = 1; z < ANCHO_PISTA + 2; z++) {     //Tenista de abajo en su posicion
        if (z != pos_t2) {
            cout << "  ";
        }
        else {
            cout << nombre2;
        }
    }
    cout << endl;
}

tTenista lance(tTenista tenista_golpea, string nombre, int habilidad, tConteoGolpes golpes, int& golpes_ganados, int velocidad, int& pos_recibe, int& pos_bola) {
    tTenista gana;

    pos_bola = golpeoBola(pos_recibe, habilidad);                     //No deberia darte la posicion del que lanza para esta funcion en vez de el que recive?
    if (2 <= pos_bola <= 8) {
        pos_recibe = correTen(pos_recibe, velocidad, pos_bola);
        if (pos_bola != pos_recibe) {                 //No llega a la pelota, punto
            if (tenista_golpea == TENISTA1) {           //Fuera
                gana = TENISTA1;
            }
            else {
                gana = TENISTA2;
            }
        }
        else if (pos_bola == pos_recibe) {          //Llega por lo tanto no gana nadie
            gana = NADIE;
        }
    }
    else {
        if (tenista_golpea == TENISTA1) {           //Fuera
            gana = TENISTA2;
        }
        else {
            gana = TENISTA1;
        }
    }
    //Falta conteo de golpes que no encuentro como se hace (guardar en el array supongo)
    
    return gana;
}

tTenista jugarPunto(tTenista servicio, string nombre1, int habilidad1, int velocidad1, tConteoGolpes golpes1,
    int& golpes_ganados1, string nombre2, int habilidad2, int velocidad2, tConteoGolpes golpes2, int& golpes_ganados2) {
    tTenista gana;


    return gana;
}

tTenista jugarJuego(tTenista servicio, string nombre1, int habilidad1, int velocidad1, int& juegos1, tConteoGolpes golpes1, int& golpes_ganados1,
    string nombre2, int habilidad2, int velocidad2, int& juegos2, tConteoGolpes golpes2, int& golpes_ganados2) {
    tTenista d;



    return d;
}



int golpeoBola(int posTen, int habilidad) {
        int destBolDeseado = 0, destBolAlcanzado = 0, distancia, probAcierto, probReal, desvio;


        if (MODO_DEBUG == true) {//si recibe los valores por teclado
            cout << "Introduce el destino deseado de la bola: ";
            cin >> destBolDeseado;
        } else {// si recibe los valores por teclado
            destBolDeseado = 1 + rand() % 7;
            cout << "Destino aleatorio " << destBolDeseado << endl;
        }

        distancia = abs(destBolDeseado - habilidad);        //Calculamos distancia a recorrer
        cout << "Distanica a recorrer " << distancia << endl;

        if (distancia <= habilidad) {        //Si tiene habilidad suficiente
            cout << "Suficiente habilidad. " << endl;
            destBolAlcanzado = destBolDeseado;
        } else if (distancia >
                   habilidad) {        //Calcular la probabilidad de acierto si el jugador no tiene suficiente habilidad
            probAcierto = 100 - (((distancia - habilidad) / ((ANCHO_PISTA - 1) - LIM_INF_HAB)) * 100);
            probReal = rand() % 100;
            cout << "Probabilidad de acierto " << probAcierto << " y probabilidad real " << probReal << endl;
            if (probAcierto > probReal) {
                destBolAlcanzado = destBolDeseado;
            } else if (probAcierto < probReal) {
                desvio = rand() % 1;
                if (desvio == 0) {
                    destBolAlcanzado = destBolDeseado - 1;
                } else if (desvio == 1) {
                    destBolAlcanzado = destBolDeseado + 1;
                }
            }
        }
        cout << "Destino final " << destBolAlcanzado;

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
