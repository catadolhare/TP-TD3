#include "Editor.h"
#include <iostream>
using namespace std;

using std::string;

Editor::Editor(const set<string> & conectivos) {
    //Inicializamos el editor vacio
    _conectivos = conectivos; //O(|conectivos|)
    _texto = {}; //O(1)
    _vocabulario = {}; //O(1)
    _cantidad_palabras = 0; //O(1)
    _longitud = 0; //O(1)
    _posiciones_palabras = {}; //O(1)
}
//Complejidad = O(|conectivos|) + O(1) + O(1) + O(1) + O(1) + O(1)
//            = O(max{|conectivos|, 1})
//            = O(|conectivos|)

string Editor::texto() const {
    string texto_completo = ""; //O(1)

    //Recorremos el vector _texto, hasta la ante ultima palabra, para agregar las palabras a un string sumado a un espacio
    for(int i=0; i<_texto.size()-1; i++){ //O(1), N iteraciones
        texto_completo.append(_texto[i]); //O(1)
        texto_completo.append(" "); //O(1)
    }

    //Agregamos la ultima palabra por separado para no tener un espacio al final del string
    texto_completo.append(_texto[_texto.size()-1]); //O(1)

    return texto_completo; //O(1)
}
//Complejidad = O(1) + N * (O(1) + O(1) + O(1)) + O(1) + O(1)
//            = O(1) + N * O(1)
//            = O(max{1, N})
//            = O(N)


const set<string>& Editor::vocabulario() const {
    return _vocabulario; //O(1)
}
//Complejidad = O(1)

const set<string>& Editor::conectivos() const {
    return _conectivos; //O(1)
}
//Complejidad = O(1)

int Editor::conteo_palabras() const { 
	return _cantidad_palabras; //O(1)
}
//Complejidad = O(1)

int Editor::longitud() const { 
	return _longitud; //O(1)
}
//Complejidad = O(1)

//Funcion auxiliar usada en las proximas funciones
vector<string> Editor::separar_oracion(const string& oracion){
    //Usamos un string para almacenar las palabras separadas y un vector auxiliar para ir guardandolas
    string palabra = ""; //O(1)
    vector<string> aux; //O(1)

    int j = 0; //O(1)
    //Recorremos la oracion pasada por parametro
    while(j<oracion.size()+1){ // O(1), |oracion| iteraciones
        if(oracion[j] == ' ' || j==oracion.size()){ //O(1)
            //Si se encuentra un espacio o esta al final de la oracion, se guarda la palabra en el vector auxiliar
            aux.push_back(palabra); //O(1)
            palabra = ""; //O(1)
        } else if (oracion[j] != ' ') { //O(1)
            //Si no es un espacio, es decir, es un caracter, se guarda el caracter en el string
            palabra.push_back(oracion[j]); //O(1)
        }
        j++; //O(1)
    }
    return aux;
}
//Complejidad = O(1) + O(1) + O(1) + |oracion| * (O(1) + O(1) +O(1)) + O(1)
//            = O(1) + |oracion| * O(1)
//            = O(1) + O(|oracion|)
//            = O(max{1, |oracion|})
//            = O(|oracion|)

void Editor::agregar_atras(const string& oracion) {
    //Separamos la oracion en palabras
    vector<string> oracion_separada = separar_oracion(oracion); //O(|oracion|)

    //Recorremos el vector con las palabras separadas
    for(int i=0; i<oracion_separada.size(); i++){ //O(1), |oracion| iteraciones
        //Agregamos cada palabra al final del texto
        _texto.push_back(oracion_separada[i]); //O(1)
        _longitud++; //O(1)

        //Verficamos si la palabra es un conectivo, si no lo es modificamos los valores de _cantidad_palabras y lo agregamos a vocabulario
        if(_conectivos.count(oracion_separada[i]) == 0){ //O(log M)
            _cantidad_palabras++; //O(1)
            _vocabulario.insert(oracion_separada[i]); //O(log M)
        }

        //Verificamos si la palabra tiene una clave en _posicinoes_palabras, si lo tiene, insertamos la posicion a su respectivos set, si no, creamos la clave asignandole un set con la respectiva posicion
        if(_posiciones_palabras.count(oracion_separada[i]) == 1){ //O(log M)
            _posiciones_palabras[oracion_separada[i]].insert(_longitud-1); //O(log P)
        } else {
            _posiciones_palabras[oracion_separada[i]] = {_longitud-1}; //O(log P)
        }
    }
}
//Complejidad = O(|oracion|) + |oracion| * (O(1) + O(1) + O(log M) + O(1) + O(log M) + O(log M) + O(log P))
//            = O(|oracion|) + |oracion| * (O(1) +  O(log M) + O(log P)) por regla de logaritmos, log M + log P = log M*P
//            = O(|oracion|) + |oracion| * (O(1) +  O(log M * P))
//            = O(|oracion|) + |oracion| * O(max{1, log M * P}) 
//            = O(|oracion|) + |oracion| * O(log (M * P))
//            = O(|oracion|) + O(|oracion| * log (M * P))
//            = O(|oracion|(1 + log (M*P))) sacando factor comun |oracion|
//            = O(|oracion| * max{1, log (M*P)})
//            = O(|oracion| * log (M*P))

const set<int> & Editor::buscar_palabra(const string& palabra) const {
    //Verificamos si la palabra es una clave en _posiciones_palabras, si lo es devuelte el set asociado, si no, devuelve un set vacio
    auto it_posiciones_palabras = _posiciones_palabras.find(palabra); //O(log M)
    if(it_posiciones_palabras != _posiciones_palabras.end()){ //O(1)
        return _posiciones_palabras.at(palabra); //O(log M)
    } else {
        return set_int_vacio; //O(1)
    }
}
//Complejidad = O(log M) + O(1) + O(log M) en el peor caso entra en la primra rama del condicional
//            = O(max{log M, 1, log M})
//            = O(log M)

void Editor::insertar_palabras(const string& oracion, int pos) {
    //separamos la oracion en palabras
    vector<string> oracion_separada = separar_oracion(oracion); //O(|oracion|)

    //Recorremos el vector de la oracion separada, actualizando las variables donde corresponda
    for(int j=0; j<oracion_separada.size(); j++){ //O(1), |oracion_separada| iteraciones
        _longitud++; //O(1)
        if(_conectivos.count(oracion_separada[j]) == 0){ //O(1)
            _cantidad_palabras++; //O(1)
            _vocabulario.insert(oracion_separada[j]); //O(log M)
        }

        _posiciones_palabras[oracion_separada[j]].insert(pos+j); //O(log P)
    }

    //Recorremos texto a partir de pos, borrando las posiciones originales de cada palabra despues de la posicion y agregando la posicion que quedaria luego de insertar la oracion
    for(int i = pos; i < _texto.size(); i++){ //O(1), |_texto| - pos iteraciones
        _posiciones_palabras[_texto[i]].erase(i); //O(log P)
        _posiciones_palabras[_texto[i]].insert(i+oracion_separada.size()); //O(log P)
    }

    //Insertamos las palabras en oracion_separada a _texto
    _texto.insert(_texto.begin() + pos, oracion_separada.begin(), oracion_separada.end()); ///O(N)
}
//Complejidad = O(|oracion|) + |oracion_separada|*(O(1) + O(1) + O(1) + O(1) + O(log M) + O(log P) + (|_texto| - pos) * (O(1) + O(log M)) + O(N)
//            = O(|oracion|) + |oracion_separada|*(O(1) + O(log (M * P)) + (|_texto| - pos) * (max{1, log M}) + O(N) por regla de logaritmos
//            = O(|oracion|) + |oracion_separada|*(O(max{1, log (M*P)}) + (|_texto| - pos) * (log M) + O(N)
//            = O(|oracion|) + |oracion_separada|*(O(log (M*P)) + (|_texto| - pos) * (log M) + O(N)
//            = O(|oracion|) + O(|oracion_separada|*log (M*P)) + (|_texto| - pos) * (log M) + O(N)
//            = O(|oracion| + |oracion_separada|*log (M*P) + (|_texto| - pos) * (log M) + O(N))

void Editor::borrar_posicion(int pos) {
    //Guardamos la palabra en la posicion a borrar
    string palabra = _texto[pos]; //O(1)

    //Actualizamos las variables correspondientes dependiendo de la palabra en la posicion a borrar
    if(_conectivos.count(palabra) == 0){ //O(log M)
        _cantidad_palabras = _cantidad_palabras - 1; //O(1)
        _vocabulario.erase(palabra); //O(log M)
    }
    _longitud = _longitud - 1; //O(1)

    //Borramos la palabra de _texto
    _texto.erase(_texto.begin() + pos); //O(N)

    //Borramos la posicion del set correspondiente a la palabra en _posiciones_palabras
    _posiciones_palabras[palabra].erase(pos); //O(log P)

    //Verificamos si el set correspondiente a la palabra en _posiciones_palabras esta vacio, si es asi, borramos la clave
    if(_posiciones_palabras[palabra].empty()){ //O(1)
        _posiciones_palabras.erase(palabra); //(log M)
        _vocabulario.erase(palabra); //O(log M)
    }

    //Actualizamos las posiciones disminuyendo en 1 las posiciones de las palabras siguientes a las borradas
    for(int j=0; j<_longitud; j++){ //O(1), N iteraciones
        for(set<int>::iterator it = _posiciones_palabras[_texto[j]].begin(); it != _posiciones_palabras[_texto[j]].end(); it++){ //P iteraciones
            if(*it>pos){ //O(1)
                int pos_nueva = *it-1; //O(1)
                _posiciones_palabras[_texto[j]].erase(*it); //O(log P)
                _posiciones_palabras[_texto[j]].insert(pos_nueva); //O(log P)
            }
        }
    }
}
//Complejidad = O(1) + O(log M) + O(1) + O(log M) + O(1) + O(N) + O(log P) + O(1) + O(log M) + O(log M) + N * (O(1) + P*(O(1) + O(1) + O(log P) + O(log P)))
//            = O(1) + O(log M) + O(N) + O(log P) + N * (O(1) + P*(O(1) + O(1) + O(log P)))
//            = O(max{1, log M, N, log P) + N * (O(1) + P*(O(max{1, log P}))
//            = O(log M + N + log P) + N * (O(1) + O(P log P)
//            = O(log M + N + log P) + N * O(max{1,P log P})
//            = O(log M + N + log P) + N * O(P log P)
//            = O(log M + N + log P) + O(N * P * log P)
//            = O(log M + N + log P + N * P * log P)
//            = O(log M + N + log P (1 + N * P)) sacando factor comun log P para los ultimos dos terminos
//            = O(log M + N + log P (max{1 + N * P}))
//            = O(log M + N + log P * N * P)
//            = O(log M + N(1 + log P * P)) sacando factor comun N para los dos ultimos terminos
//            = O(log M + N(max{1 + log P * P}))
//            = O(log M + N * log P * P)

int Editor::borrar_palabra(const string& palabra) {
    //Verficamos si la palabra si la palabra pertence al texto o no buscandola en _posiciones_palabras, si no la encuentra devuelve 0
    auto it_encontrar_palabra = _posiciones_palabras.find(palabra); //O(log M)
    if(it_encontrar_palabra == _posiciones_palabras.end()){ //O(1)
        return 0; //O(1)
    }

    int cantidad_borradas = 0; //O(1)
    vector<int> posiciones_borrar; //O(1)

    //Guardamos en un vector las posiciones de la palabra a borrar
    for(auto it_posiciones_borrar = _posiciones_palabras[palabra].begin(); it_posiciones_borrar != _posiciones_palabras[palabra].end(); it_posiciones_borrar++){ //O(1), P iteraciones
        posiciones_borrar.push_back(*it_posiciones_borrar); //O(1)
    }

    //Recorremos el vector con las posiciones a borrar, llamando a borrar_posicion por cada posicion
    for(int i=posiciones_borrar.size()-1; i>=0; i--){ //P iteraciones
        borrar_posicion(posiciones_borrar[i]); //O(log M + N * log P * P)
        cantidad_borradas++; //O(1)
    }

    return cantidad_borradas; //O(1)
}
//Complejidad = O(log M) + O(1) + O(1) + O(1) + P * (O(1) + O(1)) + P * (O(log M + N * log P * P) + O(1)) + O(1)
//            = O(log M) + O(1) + P * O(1) + P * (O(log M + N * log P * P) + O(1)) sacando factor comun P para los ultimos terminos
//            = O(log M) + O(1) + P * (O(1) + O(log M + N * log P * P) + O(1))
//            = O(max{log M, 1}) + P * (O(max{1, (log M + N * log P * P), 1})
//            = O(log M) + P * (O(log M + N * log P * P))
//            = O(log M) +  (O(P*(log M + N * log P * P)))
//            = O(log M + P*(log M + N * log P * P))
//            = O(log M + P*log M + N * log P * P²)

void Editor::reemplazar_palabra(const string& palabra1, const string& palabra2) {
    int cantidad_reemplazadas = 0; //O(1)

    //Recorremos el set asociado a la palabra 1 en _posiciones_palabras
    for(set<int>::iterator it = _posiciones_palabras[palabra1].begin(); it != _posiciones_palabras[palabra1].end(); it++){ // P iteraciones
        //Cambiamos en _texto palabra1 por palabra2
        _texto[*it] = palabra2; //O(1)
        cantidad_reemplazadas++; //O(1)

        //Modificamos las posiciones de palabra2 en _posiciones_palabras
        _posiciones_palabras[palabra2].insert(*it); //O(log P)
    }

    //Como se reemplazan todas las palabra1 por palabra2, no quedarian palabra1 en el _texto, por lo que borramos esa clave de _posicines_palabras
    _posiciones_palabras.erase(palabra1); //O(log M)

    //Actualizamos las variables correspondientes dependiendo de si palabra1 y palabra2 son conectivos o no
    if(_conectivos.count(palabra1) == 1 && _conectivos.count(palabra2) == 0){//O(log M)
        _vocabulario.insert(palabra2);//O(log M)
        _cantidad_palabras += cantidad_reemplazadas; //O(1)
    }
    if(_conectivos.count(palabra1) == 0 && _conectivos.count(palabra2) == 1){//O(log M)
        _vocabulario.erase(palabra1);//O(log M)
        _cantidad_palabras -= cantidad_reemplazadas; //O(1)
    }
    if(_conectivos.count(palabra1) == 0 && _conectivos.count(palabra2) == 0){ //O(log M)
        _vocabulario.erase(palabra1);//O(log M)
        _vocabulario.insert(palabra2); //O(log M)
    }
}
//Complejidad= O(1) + P*(O(1) + O(1) + O(log P)) + O(log M) + O(log M) + O(log M) + O(log M) + O(log M) + O(log M) (verifica las condiciones de los tres if y en el peor caso entra en el ultimo if)
//           = O(1) + P*(O(max{1, log P})) + O(log M)
//           = O(1) + P*O(log P) + O(log M)
//           = O(1) + O(P * log P) + O(log M)
//           = O(P log P + log M)