//Práctica version 3 por IGNACIO ORTEGO DE LA MATA  y DANIEL MARTIN DEL CASTILLO

#include <iostream>
#include <stdlib.h>
#include <time.h>
// tip para usar los numeros aleatorios: variable = limite_inferior + rand() % (limite_superior +1 - limite_inferior) ;
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

const int ANCHO_PISTA = 7;
const int LARGO_PISTA = 3;
const int LIM_INF_HAB = 1;
const int LIM_SUP_HAB = 2;
const int LIM_INF_VEL = 1;
const int LIM_SUP_VEL = 3;
const bool JUEGO_ALEATORIO = false;
const bool MODO_DEBUG = false;
const int DIM_ARRAY_GOLPES = ANCHO_PISTA + 2;
const int JUEGOS_SET = 3;
const int DIM_ARRAY_TENISTAS = 10;
const string ARCHIVO = "tenista.txt";

typedef enum { NADIE, TENISTA1, TENISTA2 }tTenista;
typedef enum { NADA, QUINCE, TREINTA, CUARENTA, VENTAJA }tPuntosJuego;
typedef int tConteoGolpes[DIM_ARRAY_GOLPES];
struct tDatosPartido {
    int posicion;
    int juegos;
    int golpes_ganadores;
    tPuntosJuego puntos;
    tConteoGolpes golpeos;
};
struct tDatosTenista {
    string iniciales;
    int habilidad;
    int velocidad;
    tDatosPartido datos_partido;
    int partidos_ganados;
    int partidos_perdidos;
};
typedef tDatosTenista tArrayDeTenistas[DIM_ARRAY_TENISTAS];

int menu(); //Hecha, sin comprobar
string puntosAstring(tPuntosJuego puntuacion);  //HECHA Y FUNCIONAL
int golpeoBola(int posTen, int habilidad); //hecha
int correTen(int posTen, int vel, int posBol); // arreglada
void inicializarConteos(tConteoGolpes golpeos);
void mostrarEstadisticas(tTenista tenista, tConteoGolpes golpes, int aciertos, string nombre);
void introducirTenista(string& iniciales, int& habilidad, int& velocidad); //HECHA Y FUNCIONAL
void pintarMarcador(string iniciales1, string iniciales2, const tDatosPartido &datos_t1, const tDatosPartido &datos_t2, tTenista servicio_para);    //Cambiada
void pintarPeloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, tTenista bola_jugador, int pos_bola);
tTenista actualizarMarcador(tTenista ganador_punto, tDatosPartido &datos_t1, tDatosPartido &datos_t2);      //Cambiada
tTenista lance(tTenista bola_para, tDatosTenista &tenista_golpea, tDatosTenista &tenista_recibe, int &pos_bola);        //Actualizada pero falta terminarla (hay error raro operandos)
tTenista jugarPunto(tTenista servicio, tDatosTenista &tenista1, tDatosTenista &tenista2);
tTenista jugarJuego(tTenista servicio, tDatosTenista &tenista1, tDatosTenista &tenista2);
int cargar(tArrayDeTenistas& lista); // usamos una funcion int en vez de un void porque así la aprovechamos y ademas de cargar todos los datos del fichero nos devolvera el número de tenistas que hay en el juego que nos servira para después poderlo usar para acceder al array correctamente
int buscarIniciales(const tArrayDeTenistas& lista, string ini, const int numTenista); //Hecha sin comprobar
void guardar(const tArrayDeTenistas& lista, const int numTenista);
void mostrar(const tArrayDeTenistas& lista);
void mostrarIniciales(const tArrayDeTenistas& listaT);
int buscarIniciales(const tArrayDeTenistas& listaT, string ini);
void eliminarTenista(tArrayDeTenistas& listaT, string iniciales);
void introducirTenista(tArrayDeTenistas& listaT);
tTenista jugarPartido(tDatosTenista& tenista1, tDatosTenista& tenista2);

int main() {
    string nombre1, nombre2, marcador1, marcador2;// variables que probablemente se eliminen porque ahora se usa un array
    int hab1, hab2, vel1, vel2, juegos1 = 0, juegos2 = 0; // variables que probablemente se eliminen porque ahora se usa un array
    int golpes_ganadores1 = 0, golpes_ganadores2 = 0;// variables que probablementye se eliminen porque ahora se usa un array
    tArrayDeTenistas lista;
    int opcion, numTenistas = cargar(lista);

    tTenista ganador_set = NADIE, servicio_para;
    tConteoGolpes golpeos1, golpeos2;
    srand(time(NULL));        //Primero inicializamos los numeros aleatorios que vamos a usar en la función
    inicializarConteos(golpeos1);
    inicializarConteos(golpeos2);

    cout << "Bienvenido al simulador de partidos de tenis" << endl;
    servicio_para = tTenista(rand() % 2 + 1);
    opcion = menu();
    while (opcion != 0) {
        switch (opcion) {
        case 1:

            break;
        case 2:
            if (numTenistas < DIM_ARRAY_TENISTAS) {
                introducirTenista(lista[numTenistas].iniciales, lista[numTenistas].habilidad,
                    lista[numTenistas].velocidad);
                numTenistas++;
            }
            else {
                cout << "ERROR : No se pueden añadir más tenistas, memoria llena" << endl;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        }
        opcion = menu();
    }
    cout << "Programa finalizado" << endl;


    while (ganador_set == NADIE) {
        tTenista ganadorPunto = NADIE;
        cout << "Servicio para: " << servicio_para;
        ganadorPunto = jugarPunto(servicio_para, nombre1, hab1, vel1, golpeos1, golpes_ganadores1, nombre2, hab2, vel2, golpeos2, golpes_ganadores2);
        if (ganadorPunto == TENISTA1) {
            juegos1++;
            cout << nombre1 << "Ha ganado el punto." << endl;
        }
        else if (ganadorPunto == TENISTA2) {
            juegos2++;
            cout << nombre2 << "Ha ganado el punto." << endl;
        }
        if (juegos1 == JUEGOS_SET || juegos2 == JUEGOS_SET) {
            ganador_set = ganadorPunto;
        }
        else {
            servicio_para = tTenista(servicio_para % 2 + 1);
        }
    }
    cout << ganador_set << "ha ganado el set!!" << endl;
    mostrarEstadisticas(TENISTA1, golpeos1, golpes_ganadores1, nombre1);
    mostrarEstadisticas(TENISTA2, golpeos2, golpes_ganadores2, nombre2);
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

int menu() {
    int op;

    cout << "\033[5m, Juego de tenis: \033[0m," << endl;
    cout << "[1] Ver datos tenistas" << endl;
    cout << "[2] Nuevo tenista" << endl;
    cout << "[3] Eliminar tenista" << endl;
    cout << "[4] Jugar partido" << endl;
    cout << "[5] Torneo semifinales/final" << endl;
    cout << "[6] Torneo top-4" << endl;
    cout << "[0] Salir" << endl << endl;
    cout << "Opción: ";
    cin >> op;

    while (op < 0 || op > 6) {
        cout << "Opción no valida, por favor seleccione una opción correcta" << endl;

        cout << "\033[5m, Juego de tenis: \033[0m," << endl;
        cout << "[1] Ver datos tenistas" << endl;
        cout << "[2] Nuevo tenista" << endl;
        cout << "[3] Eliminar tenista" << endl;
        cout << "[4] Jugar partido" << endl;
        cout << "[5] Torneo semifinales/final" << endl;
        cout << "[6] Torneo top-4" << endl;
        cout << "[0] Salir" << endl << endl;
        cout << "Opción: ";
        cin >> op;
    }

    return op;
}

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

    cout << "Datos del tenista" << endl;
    cout << "Introduce sus iniciales: ";
    cin >> iniciales;
    cout << "Introduzca su habilidad (1 al 3): ";
    cin >> habilidad;
    cout << "Introduzca su velocidad (1 al 4): ";
    cin >> velocidad;
    cout << "Tenista creado con éxito";
}

void mostrarEstadisticas(tTenista tenista, tConteoGolpes golpes, int aciertos, string nombre) {
    int a = 0;
    for (int i = 1; i < DIM_ARRAY_GOLPES - 1; i++) {
        a = a + golpes[i];
    }
    cout << "Estadisticas de " << nombre << endl;
    cout << setw(20) << "Golpes Totales: " << a << endl;
    cout << setw(22) << "Golpes Ganadores: " << aciertos << endl;
    cout << setw(26) << "Errores no forzadose: " << golpes[DIM_ARRAY_GOLPES - 1] << endl;
    cout << setw(9) << "Calle: ";
    for (int i = 0; i < 9; i++) {
        cout << setw(5) << i;
    }
    cout << endl << setw(12) << "%";
    for (int i = 0; i < DIM_ARRAY_GOLPES; i++) {
        cout << setw(5) << golpes[i] / a * 100;
    }
    cout << endl;
}

tTenista actualizarMarcador(tTenista ganador_punto, tDatosPartido& datos_t1, tDatosPartido& datos_t2) {
    tTenista gana = NADIE;
    if (ganador_punto == TENISTA1) {
        if (datos_t1.puntos == NADA) {
            datos_t1.puntos = QUINCE;
        }
        else if (datos_t1.puntos == QUINCE) {
            datos_t1.puntos = TREINTA;
        }
        else if (datos_t1.puntos == TREINTA) {
            datos_t1.puntos = CUARENTA;
        }
        else if (datos_t1.puntos == CUARENTA && datos_t2.puntos == CUARENTA) { //no usamos el switch para poder poner este caso en especifico en vez de ensuciar el case 40
            datos_t1.puntos = VENTAJA;
        }
        else if (datos_t1.puntos == CUARENTA && datos_t2.puntos < TREINTA) {
            datos_t1.puntos = NADA;
            datos_t2.puntos = NADA;
            datos_t1.juegos++;                      //Juego
        }
        else if (datos_t1.puntos == VENTAJA) {
            datos_t1.puntos = NADA;
            datos_t2.puntos;
            datos_t1.juegos++;                      //Juego
        }
    }
    else if (ganador_punto == TENISTA2) {
        if (datos_t2.puntos == NADA) {
            datos_t2.puntos = QUINCE;
        }
        else if (datos_t2.puntos == QUINCE) {
            datos_t2.puntos = TREINTA;
        }
        else if (datos_t2.puntos == TREINTA) {
            datos_t2.puntos = CUARENTA;
        }
        else if (datos_t2.puntos == CUARENTA && datos_t1.puntos == CUARENTA) {
            datos_t1.puntos = VENTAJA;
        }
        else if (datos_t2.puntos == CUARENTA && datos_t1.puntos < TREINTA) {
            datos_t2.puntos = NADA;
            datos_t1.puntos = NADA;
            datos_t2.juegos++;                      //Juego
        }
        else if (datos_t2.puntos == VENTAJA) {
            datos_t2.puntos = NADA;
            datos_t1.puntos = NADA;
            datos_t2.juegos++;                      //Juego
        }
    }

    if (datos_t1.juegos == JUEGOS_SET) {            //Si gana tenista 1
        gana = TENISTA1;
    }
    else if (datos_t2.juegos == JUEGOS_SET) {       //Si gana tenista 2
        gana = TENISTA2;
    }

    return gana;
}

void pintarMarcador(string iniciales1, string iniciales2, const tDatosPartido& datos_t1, const tDatosPartido& datos_t2, tTenista servicio_para) {
    string p1String, p2String;

    p1String = puntosAstring(datos_t1.puntos);       //Duda
    p2String = puntosAstring(datos_t1.puntos);
    if (servicio_para == TENISTA1) {
        cout << iniciales1 << " " << datos_t1.juegos << " : " << p1String << "*" << endl;           //Marcador si saca tenista 1
        cout << iniciales2 << " " << datos_t2.juegos << " : " << p2String << endl;
    }
    else if (servicio_para == TENISTA2) {                                               //Marcador si saca tenista 2
        cout << iniciales1 << " " << datos_t1.juegos << " : " << p1String << endl;
        cout << iniciales2 << " " << datos_t1.juegos << " : " << p2String << "*" << endl;
    }
}

void pintarPeloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, tTenista bola_jugador, int pos_bola) {
    int i = 1, u = 1, cont = 0, v = 1, cont2 = 0, x = 1, p = 1, z = 1;

    cout << "  ";
    for (i = 1; i < ANCHO_PISTA + 2; i++) {     //Tenista de arriba en su posicion
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
            else if (pos_bola == v) {
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
            else if (pos_bola == x) {
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

tTenista lance(tTenista bola_para, tDatosTenista& tenista_golpea, tDatosTenista& tenista_recibe, int& pos_bola) {
    tTenista gana = NADIE;
    cout << tenista_golpea << "Golpea la bola." << endl;
    pos_bola = golpeoBola(pos_bola, tenista_golpea.habilidad);                     //No deberia darte la posicion del que lanza para esta funcion en vez de el que recive?
    //golpes[pos_bola] = golpes[pos_bola] + 1;
    if (1 <= pos_bola && pos_bola <= 7) {
        tenista_recibe.datos_partido.posicion = correTen(tenista_recibe.datos_partido.posicion, tenista_recibe.velocidad, pos_bola);
        if (pos_bola != tenista_recibe.datos_partido.posicion) {                 //No llega a la pelota, punto
            if (tenista_golpea == TENISTA1) {           //Fuera
                gana = TENISTA1;
            }
            else {
                gana = TENISTA2;
            }
        }
        else if (pos_bola == tenista_recibe.datos_partido.posicion){          //Llega por lo tanto no gana nadie
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

tTenista jugarPunto(tTenista servicio, tDatosTenista& tenista1, tDatosTenista& tenista2) {//tTenista jugarPunto(tTenista servicio, tDatosTenista &tenista1, tDatosTenista &tenista2){
    tTenista gana = NADIE, bolaPara = servicio;
    int pos1 = ANCHO_PISTA / 2 + 1;
    int pos2 = pos1;
    int posBola = 0;

    posBola = (servicio == TENISTA1) ? pos1 : pos2;
    tenista1.datos_partido.posicion = pos1;
    tenista2.datos_partido.posicion = pos2;

    pintarPeloteo(tenista1.iniciales, tenista2.iniciales, tenista1.datos_partido.posicion, tenista2.datos_partido.posicion, bolaPara, posBola);
    while (gana == NADIE) {
        if (bolaPara == TENISTA1) {
            gana = lance(TENISTA1, tenista1, tenista2, posBola);
        }
        if (bolaPara == TENISTA2) {
            gana = lance(TENISTA2, tenista2, tenista1, posBola);
        }
        bolaPara = tTenista(3 - bolaPara);
        pintarPeloteo(tenista1.iniciales, tenista2.iniciales, tenista1.datos_partido.posicion, tenista2.datos_partido.posicion, bolaPara, posBola);
    }

    return gana;
} 

tTenista jugarJuego(tTenista servicio, tDatosTenista& tenista1, tDatosTenista& tenista2) { //tTenista jugarJuego(tTenista servicio, tDatosTenista &tenista1, tDatosTenista &tenista2){
    tTenista gana = NADIE, ganaPunto = NADIE;
    tPuntosJuego puntos1 = NADA, puntos2 = NADA;

    while (gana == NADIE) {
        ganaPunto = NADIE;
        pintarMarcador(tenista1.iniciales, tenista2.iniciales, tenista1.datos_partido, tenista2.datos_partido, servicio);        
        ganaPunto = jugarPunto(servicio, tenista1, tenista2);
        gana = actualizarMarcador(ganaPunto, tenista1.datos_partido, tenista2.datos_partido);
    }

    return gana;
}

int golpeoBola(int posTen, int habilidad) {
    int destBolDeseado = 0, destBolAlcanzado = 0, distancia, probAcierto, probReal, desvio;


    if (MODO_DEBUG == true) {//si recibe los valores por teclado
        cout << "Introduce el destino deseado de la bola: ";
        cin >> destBolDeseado;
    }
    else {// si recibe los valores por teclado
        destBolDeseado = 1 + rand() % 7;
        cout << "Destino aleatorio " << destBolDeseado << endl;
    }

    distancia = abs(destBolDeseado - habilidad);        //Calculamos distancia a recorrer
    if (MODO_DEBUG) {
        cout << "Distanica a recorrer " << distancia << endl;
    }
    if (distancia <= habilidad) {        //Si tiene habilidad suficiente
        if (MODO_DEBUG) {
            cout << "Suficiente habilidad. " << endl;
        }
        destBolAlcanzado = destBolDeseado;
    }
    else if (distancia >
        habilidad) {        //Calcular la probabilidad de acierto si el jugador no tiene suficiente habilidad
        probAcierto = 100 - (((distancia - habilidad) / ((ANCHO_PISTA - 1) - LIM_INF_HAB)) * 100);
        probReal = rand() % 100;
        if (MODO_DEBUG) {
            cout << "Probabilidad de acierto " << probAcierto << " y probabilidad real " << probReal << endl;
        }
        if (probAcierto > probReal) {
            destBolAlcanzado = destBolDeseado;
        }
        else if (probAcierto < probReal) {
            desvio = rand() % 1;
            if (desvio == 0) {
                destBolAlcanzado = destBolDeseado - 1;
            }
            else if (desvio == 1) {
                destBolAlcanzado = destBolDeseado + 1;
            }
        }
    }
    if (MODO_DEBUG) {
        cout << "Destino final " << destBolAlcanzado;
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

void inicializarConteos(tConteoGolpes golpeos) {
    for (int i = 0; i < DIM_ARRAY_GOLPES; i++) {
        golpeos[i] = 0;
    }
}

int cargar(tArrayDeTenistas& lista) {
    int numTenistas = 0;
    ifstream archivo(ARCHIVO);
    if (archivo.is_open()) {
        while (!archivo.eof() && numTenistas < DIM_ARRAY_TENISTAS) {
            archivo >> lista[numTenistas].iniciales;
            archivo >> lista[numTenistas].habilidad;
            archivo >> lista[numTenistas].velocidad;
            archivo >> lista[numTenistas].partidos_ganados;
            archivo >> lista[numTenistas].partidos_perdidos;
            numTenistas++;
        }

        archivo.close();
    }
    else {
        cout << "ERROR al abrir el archivo" << endl;
    }
    return numTenistas;
}

int buscarIniciales(const tArrayDeTenistas& lista, string ini, const int numTenista) {
    int pos = -1;
    bool encontrado = false;

    while (!encontrado && pos < numTenista) {
        pos++;
        if (ini == lista[pos].iniciales) {
            encontrado = true;
        }
    }
    if (!encontrado) {
        pos = -1;
    }
    return pos;

}

void guardar(const tArrayDeTenistas& lista, const int numTenistas) {
    ofstream archivo(ARCHIVO);
    if (archivo.is_open()) {
        for (int i = 0; i < numTenistas; i++) {
            cout << lista[numTenistas].iniciales << " ";
            cout << lista[numTenistas].habilidad << " ";
            cout << lista[numTenistas].velocidad << " ";
            cout << lista[numTenistas].partidos_ganados << " ";
            cout << lista[numTenistas].partidos_perdidos << endl;
        }
        archivo.close();
    }
    else {
        cout << "ERROR al abrir el archivo." << endl;
    }
}

void mostrar(const tArrayDeTenistas& listaT) {

}

void mostrarIniciales(const tArrayDeTenistas& listaT) {

}

int buscarIniciales(const tArrayDeTenistas& listaT, string ini) {
    int d;

    return d;
}

void eliminarTenista(tArrayDeTenistas& listaT, string iniciales) {

}

void introducirTenista(tArrayDeTenistas& listaT) {

}

tTenista jugarPartido(tDatosTenista& tenista1, tDatosTenista& tenista2) {
    tTenista gana = NADIE, jugar, servi;
    int juegos1 = 0, juegos2 = 0, servicio;

    while (gana = NADIE) {         //Mientras no llegue ninguno a 2 set se jugarJuego

        servicio = rand() % 1;      //Sorteo de saque
        if (servicio == 0) {
            servi = TENISTA1;
        }
        else if (servicio == 1) {
            servi = TENISTA2;
        }

        jugar = jugarJuego(servi, tenista1, tenista2);
        if (jugar = TENISTA1) {
            juegos1++;
        }
        else if (jugar = TENISTA2) {
            juegos2++;
        }
        if (juegos1 == 2) {
            gana = TENISTA1;
        }
        else if (juegos2 == 2) {
            gana = TENISTA2;
        }
    }
    
    if (gana == TENISTA1) {
        tenista1.partidos_ganados++;
        tenista2.partidos_perdidos++;
    }
    else if (gana == TENISTA2) {
        tenista2.partidos_ganados++;
        tenista1.partidos_perdidos++;
    }

    return gana;
}

