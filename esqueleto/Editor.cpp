#include "Editor.h"

using std::string;

Editor::Editor(const set<string> & conectivos) {
    for(set<string>::iterator it=conectivos.begin(); it != conectivos.end(); it++){
        _conectivos.insert(*it);
    }
}

string Editor::texto() const {
    string texto_completo;
    for(int i=0; i<_texto.size(); i++){
        texto_completo.append(_texto[i]);
        texto_completo.append(" ");
    }
    return texto_completo;
}

const set<string>& Editor::vocabulario() const {
    return _vocabulario;
}

const set<string>& Editor::conectivos() const {
    return _conectivos;
}

int Editor::conteo_palabras() const { 
	return _cantidad_palabras; 
}

int Editor::longitud() const { 
	return _longitud; 
}

void Editor::agregar_atras(const string& oracion) {
    /* Completar */
}

const set<int> & Editor::buscar_palabra(const string& palabra) const {
    /* Quitar este código y completar */

    return set_int_vacio;
}

void Editor::insertar_palabras(const string& oracion, int pos) {
    /* Completar */
    /*vector<string> aux ={};
    string palabra;
    int i=0;
    while(i<oracion.size()){
        if(oracion[i] != ' '){
            palabra[i] = oracion[i]; //chequear
        } else {
            aux.append(palabra); //chequear
        }
        i++;
    }*/
    int largo_anterior = _texto.size();
    agregar_atras(oracion);
    int largo_oracion = _texto.size() - largo_anterior;
    for(int i=pos; i<_texto.size() - largo_oracion; i++){
        swap(_texto[i], _texto[_texto.size() - largo_oracion+i]);
    }
    
}

void Editor::borrar_posicion(int pos) {
    string palabra = _texto[pos];
    for(int i=pos; i<_texto.size()-1; i++){
        swap(_texto[i], _texto[i+1]);
    }
    _texto.pop_back();
    //faltaria borrar la palabra de texto
    //mover todas las palabras a la izquierda de pos un pos a la derecha, dejando la palabra de pos al final y hacer ´pop_back
    _vocabulario.erase(palabra);
    _longitud = _longitud - 1;
    if(_conectivos.count(palabra) == 0){
        _cantidad_palabras = _cantidad_palabras - 1;
    }
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
    /* Completar */
}
