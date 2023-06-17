#include "Editor.h"
#include <iostream>
using namespace std;

using std::string;

Editor::Editor(const set<string> & conectivos) {
    for(set<string>::iterator it=conectivos.begin(); it != conectivos.end(); it++){ //|conectivos| iteraciones
        _conectivos.insert(*it); //O(log n)
    }
    _texto = {}; //O(1)
    _vocabulario = {}; //O(1)
    _cantidad_palabras = 0; //O(1)
    _longitud = 0; //O(1)
    _posiciones_palabras = {}; //O(1)
}

string Editor::texto() const {
    string texto_completo = ""; //O(1)
    for(int i=0; i<_texto.size()-1; i++){
        texto_completo.append(_texto[i]);
        texto_completo.append(" ");
    }
    texto_completo.append(_texto[_texto.size()-1]);
    return texto_completo; //O(1)
}

const set<string>& Editor::vocabulario() const {
    return _vocabulario; //O(1)
}

const set<string>& Editor::conectivos() const {
    return _conectivos; //O(1)
}

int Editor::conteo_palabras() const { 
	return _cantidad_palabras; //O(1)
}

int Editor::longitud() const { 
	return _longitud; //O(1)
}

void Editor::agregar_atras(const string& oracion) {
    string palabra = ""; //O(1)
    int i=0; //O(1)
    while(i<oracion.size()+1){ // |oracion| iteraciones
        if(oracion[i] == ' ' || i==oracion.size()){ //O(1)
            _texto.push_back(palabra); //O(1)
            _longitud++; //O(1)
            if(_conectivos.count(palabra) == 0){ //O(1)
                _cantidad_palabras++; //O(1)
                _vocabulario.insert(palabra); //O(log M)
            }
            if(_posiciones_palabras.count(palabra) == 1){
                _posiciones_palabras[palabra].insert(_longitud-1); //O(log P)
            } else {
                _posiciones_palabras[palabra] = {_longitud-1}; //O(log P)
            }
            palabra = ""; //O(1)
        } else if (oracion[i] != ' ') {
            palabra.push_back(oracion[i]); //porque no es append? //O(1)
        }
        i++; //O(1)
    }
}
//Complejidad: O(1) + O(1) + |oracion|*(O(1)+O(1)+O(1)+O(log M)+O(log P)+O(1))
            // = O(1) + |oracion|*(O(1)+O(log M*P)) por regla de logaritmos
            // = O(max{O(1), |oracion|*(max{O(1), O(log M P)})})
            // =O(|oracion|*log MP)
            //CHEQUEAR

const set<int> & Editor::buscar_palabra(const string& palabra) const {
    //devolver el map que tenga esa palabra
    return _posiciones_palabras.at(palabra); //O(log M)
}

void Editor::insertar_palabras(const string& oracion, int pos) {
    int largo_anterior = _longitud; //O(1)
    agregar_atras(oracion); //O(|oracion|*log MP) //ya modifica lognitud, vocabulario y conteo de palabras
    int largo_oracion = _longitud - largo_anterior; //O(1)
    for(int i=0; i<largo_oracion; i++){ //largo_oracion iteraciones
        _posiciones_palabras[_texto[pos+i]].erase(pos+i);
        _posiciones_palabras[_texto[_longitud - largo_oracion+i]].erase(_longitud - largo_oracion+i);
        swap(_texto[pos+i], _texto[_longitud - largo_oracion+i]); //O(1)
        //_posiciones_palabras[_texto[pos+i]].insert(pos+i);
        //_posiciones_palabras[_texto[_longitud - largo_oracion+i]].insert(_longitud - largo_oracion+i);
    }
    for(int j=pos; j<_longitud; j++){
        _posiciones_palabras[_texto[j]].insert(j);
    }
}

void Editor::borrar_posicion(int pos) {
    string palabra = _texto[pos];
    for(int i=pos; i<_texto.size()-1; i++){
        swap(_texto[i], _texto[i+1]);
        
    }
    _texto.pop_back();
    _longitud = _longitud - 1;
    for(int j=0; j<_longitud; j++){
        for(set<int>::iterator it = _posiciones_palabras[_texto[j]].begin(); it != _posiciones_palabras[_texto[j]].end(); it++){
            if(*it>pos){
                int pos_nueva = *it-1;
                _posiciones_palabras[_texto[j]].erase(*it);
                _posiciones_palabras[_texto[j]].insert(pos_nueva);
            }
        }
    }
    if(_conectivos.count(palabra) == 0){
        _cantidad_palabras = _cantidad_palabras - 1;
        _vocabulario.erase(palabra);
    }
    _posiciones_palabras[palabra].erase(pos);
}

int Editor::borrar_palabra(const string& palabra) {
    int cantidad_borradas = 0;
    for(int i=0; i<_texto.size(); i++){
        if(_texto[i] == palabra){
            for(int j=i; j<_texto.size(); j++){
                swap(_texto[j], _texto[j+1]);
            }
            _texto.pop_back();
            cantidad_borradas++;
        }
    }
    _vocabulario.erase(palabra);
    _longitud = _longitud - cantidad_borradas;
    if(_conectivos.count(palabra) == 0){
        _cantidad_palabras = _cantidad_palabras - cantidad_borradas;
    }
    return cantidad_borradas;
}

void Editor::reemplazar_palabra(const string& palabra1, const string& palabra2) {
    int cantidad_reemplazadas = 0;
    _posiciones_palabras[palabra2] = _posiciones_palabras[palabra1];
    _posiciones_palabras.erase(palabra1);
    for(set<int>::iterator it = _posiciones_palabras[palabra2].begin(); it != _posiciones_palabras[palabra2].end(); it++){
        _texto[*it] = palabra2;
        cantidad_reemplazadas++;
    }
    if(_conectivos.count(palabra1) == 1 && _conectivos.count(palabra2) == 0){
        _vocabulario.insert(palabra2);
        _cantidad_palabras += cantidad_reemplazadas;
    }
    if(_conectivos.count(palabra1) == 0 && _conectivos.count(palabra2) == 1){
        _vocabulario.erase(palabra1);
        _cantidad_palabras -= cantidad_reemplazadas;
    }
    if(_conectivos.count(palabra1) == 0 && _conectivos.count(palabra2) == 0){
        _vocabulario.erase(palabra1);
        _vocabulario.insert(palabra2);
    }
    
    
}
