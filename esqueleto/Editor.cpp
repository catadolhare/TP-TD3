#include "Editor.h"
#include <iostream>
using namespace std;

using std::string;

Editor::Editor(const set<string> & conectivos) {
    _conectivos = conectivos; //O(|conectivos|) o O(1) PREGUNTAR
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
    for(int i=0; i<_texto.size()-1; i++){ //O(1), N iteraciones
        texto_completo.append(_texto[i]); //O(1)
        texto_completo.append(" "); //O(1)
    }
    texto_completo.append(_texto[_texto.size()-1]); //O(1)
    return texto_completo; //O(1)
}
//Complejidad = O(1) + N * (O(1) + O(1) + O(1)) + O(1) + O(1)
//            = O(1) + N * ((1) + O(1)
//            = O(max{O(1), N, O(1)})
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

vector<string> Editor::separar_oracion(const string& oracion){
    string palabra = ""; //O(1)
    vector<string> aux; //O(1)
    int j = 0; //O(1)
    while(j<oracion.size()+1){ // O(1), |oracion| iteraciones
        if(oracion[j] == ' ' || j==oracion.size()){ //O(1)
            aux.push_back(palabra); //O(1)
            palabra = ""; //O(1)
        } else if (oracion[j] != ' ') { //O(1)
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
    string palabra = ""; //O(1)
    int i=0; //O(1)
    vector<string> oracion_separada = separar_oracion(oracion); //O(|oracion|)
    for(int i=0; i<oracion_separada.size(); i++){ //O(1), |oracion| iteraciones
        _texto.push_back(oracion_separada[i]); //O(1)
        _longitud++; //O(1)
        if(_conectivos.count(oracion_separada[i]) == 0){ //O(log M)
            _cantidad_palabras++; //O(1)
            _vocabulario.insert(oracion_separada[i]); //O(log M)
        }
        if(_posiciones_palabras.count(oracion_separada[i]) == 1){ //O(1)
            _posiciones_palabras[oracion_separada[i]].insert(_longitud-1); //O(log P)
        } else {
            _posiciones_palabras[oracion_separada[i]] = {_longitud-1}; //O(log P)
        }
    }
}
//Complejidad = O(1) + O(1) + O(|oracion|) + |oracion| * (O(1) + O(1) + O(log M) + O(1) + O(log M) + O(1) + O(log P) + O(log P))
//            = O(1) + O(|oracion|) + |oracion| * O(max{1, log M, log P}) 
//            = O(1) + O(|oracion|) + |oracion| * O(log M + log P) por regla de logaritmos, log M + log P = log M*P
//            = O(1) + O(|oracion|) + O(|oracion| * log (M*P))
//            = O(max{1, |oracion|, |oracion| * log (M*P)})
//            = O(|oracion| + |oracion| * log (M*P))
//            = O(|oracion|(1 + log M*P)) sacando factor comun |oracion|
//            = O(|oracion| * max{1, log M*P})
//            = O(|oracion| * log (M*P))

const set<int> & Editor::buscar_palabra(const string& palabra) const {
    auto it_posiciones_palabras = _posiciones_palabras.find(palabra); //O(log M)
    if(it_posiciones_palabras != _posiciones_palabras.end()){ //O(1)
        return _posiciones_palabras.at(palabra); //O(log M)
    } else {
        return set_int_vacio; //O(1)
    }
}
//Complejidad = O(log M) + O(1) + O(log M)
//            = O(max{log M, 1, log M})
//            = O(log M)

void Editor::insertar_palabras(const string& oracion, int pos) {
    //separamos la oracion en palabras
    vector<string> oracion_separada = separar_oracion(oracion); //O(|oracion|)

    //actualizamos las variables
    for(int j=0; j<oracion_separada.size(); j++){ //O(1), |oracion_separada| iteraciones
        _longitud++; //O(1)
        if(_conectivos.count(oracion_separada[j]) == 0){ //O(1)
            _cantidad_palabras++; //O(1)
            _vocabulario.insert(oracion_separada[j]); //O(log M)
        }
        if(_posiciones_palabras.count(oracion_separada[j]) == 1){ //O(1)
            _posiciones_palabras[oracion_separada[j]].insert(pos+j); //O(log P)
        } else {
            _posiciones_palabras[oracion_separada[j]] = {pos+j}; //O(log P)
        }
    }

    for(int i = pos; i < _texto.size(); i++){ //O(1), |_texto| - pos iteraciones
        _posiciones_palabras[_texto[i]].erase(i); //O(log M)
        _posiciones_palabras[_texto[i]].insert(i+oracion_separada.size()); //O(log M)
    }

    _texto.insert(_texto.begin() + pos, oracion_separada.begin(), oracion_separada.end()); ///O(N)
}
//Complejidad = O(|oracion|) + |oracion_separada|*(O(1) + O(1) + O(1) + O(log M) + O(1) + O(log P ??????))
//            = O(|oracion|) + |oracion_separada|*(O(max{1, log (M*P)})
//            = O(|oracion|) + |oracion_separada|*(O(log (M*P))
//            = O(|oracion|) + O(|oracion_separada|*log (M*P)
//            = O(|oracion| + |oracion_separada|*log (M*P))

void Editor::borrar_posicion(int pos) {
    string palabra = _texto[pos]; //O(1)

    if(_conectivos.count(palabra) == 0){ //O(log M)
        _cantidad_palabras = _cantidad_palabras - 1; //O(1)
        _vocabulario.erase(palabra); //O(log M)
    }
    _longitud = _longitud - 1; //O(1)

    _texto.erase(_texto.begin() + pos); //O(N)

    _posiciones_palabras[palabra].erase(pos); //O(log M)

    if(_posiciones_palabras[palabra].empty()){ //O(1)
        _posiciones_palabras.erase(palabra); //(log M)
        _vocabulario.erase(palabra); //O(log M)
    }

    for(int j=0; j<_longitud; j++){ //O(1), N iteraciones
        for(set<int>::iterator it = _posiciones_palabras[_texto[j]].begin(); it != _posiciones_palabras[_texto[j]].end(); it++){ //|_posiciones_palabras[_texto[j]]| iteraciones -> creo que esto es P
            if(*it>pos){ //O(1)
                int pos_nueva = *it-1; //O(1)
                _posiciones_palabras[_texto[j]].erase(*it); //O(log M)
                _posiciones_palabras[_texto[j]].insert(pos_nueva); //O(log M)
            }
        }
    }
}
//Complejidad = O(1) + O(log M) + O(1) + O(log M) + O(1) + O(N) + O(log M) + O(1) + O(log M) + O(log M) + N * (O(1) + P*(O(1) + O(1) + O(log M) + O(log M)))
//            = O(log M + N) + O(N*P*log M)
//            = O(log M + N + N*P*log M) -> no se si se puede seguir simplificando
//            = O(log M + N*(1+P log M)) sacando factor comun N
//            = O(log M + N*(max{1+P log M}))
//            = O(log M + N P log M))
//            = O(log M * (1 + N*P))) sacando factor comun log M
//            = O(log M * (max{1 + N*P})))
//            = O(log M * N * P)

int Editor::borrar_palabra(const string& palabra) {
    auto it_encontrar_palabra = _posiciones_palabras.find(palabra);
    if(it_encontrar_palabra == _posiciones_palabras.end()){
        return 0;
    }

    int cantidad_borradas = 0;
    vector<int> posiciones_borrar;

    for(auto it_posiciones_borrar = _posiciones_palabras[palabra].begin(); it_posiciones_borrar != _posiciones_palabras[palabra].end(); it_posiciones_borrar++){
        posiciones_borrar.push_back(*it_posiciones_borrar);
        cout<<*it_posiciones_borrar<<endl;
    }

    for(int i=posiciones_borrar.size()-1; i>=0; i--){
        cout<<posiciones_borrar[i]<<endl;
        borrar_posicion(posiciones_borrar[i]);
        cantidad_borradas++;
        cout<<cantidad_borradas<<endl;
    }

    return cantidad_borradas;
}

void Editor::reemplazar_palabra(const string& palabra1, const string& palabra2) {
    int cantidad_reemplazadas = 0; //O(1)

    for(set<int>::iterator it = _posiciones_palabras[palabra1].begin(); it != _posiciones_palabras[palabra1].end(); it++){ // P iteraciones
        _texto[*it] = palabra2; //O(1)
        cantidad_reemplazadas++; //O(1)
        if(_posiciones_palabras.count(palabra2) == 1){ //O(log P)
            _posiciones_palabras[palabra2].insert(*it); //O(log P)
        } else {
            _posiciones_palabras[palabra2] = {*it}; //O(log P)
        }
    }
    if(_posiciones_palabras[palabra1].empty()){ //O(1)
        _posiciones_palabras.erase(palabra1); //O(log M)
    }
    
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
//Complejidad= O(1) + P*(O(1) + O(1) + O(log P) + O(log P)) + O(1) + O(log M) + O(log M) + O(log M) + O(log M) + O(log M)
//           = O(1) + P*(O(max{1, log P})) + O(max{1, log M})
//           = O(1) + P*O(log P) + O(log M)
//           = O(max{1, P log P, log M})
//           = O(P log P + log M)