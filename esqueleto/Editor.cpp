#include "Editor.h"

using std::string;

Editor::Editor(const set<string> & conectivos) {
    _conectivos = conectivos;
    //recorrer con iterador
}

string Editor::texto() const {
    /* Quitar este código y completar */
    return _texto;
}

const set<string>& Editor::vocabulario() const {
    /* Quitar este código y completar */
    return _vocabulario;
}

const set<string>& Editor::conectivos() const {
    /* Quitar este código y completar */
    return _conectivos;
}

int Editor::conteo_palabras() const { 
    /* Quitar este código y completar */
	return _cantidad_palabras; 
}

int Editor::longitud() const { 
    /* Quitar este código y completar */
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
}

void Editor::borrar_posicion(int pos) {
    /* Completar */
}

int Editor::borrar_palabra(const string& palabra) {
    /* Quitar este código y completar */
    return 0;
}

void Editor::reemplazar_palabra(const string& palabra1, const string& palabra2) {
    /* Completar */
}
