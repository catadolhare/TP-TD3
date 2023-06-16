#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <set>
#include <string>
#include <vector>
#include <map>
/* agregar includes que sean necesarios */

using namespace std;

class Editor {
public:
    // Dimensiones:
    // N: cantidad total de palabras del texto (incluyendo repetidas)
    // M: cantidad de palabras diferentes del texto (conectivas o no)
    // cardinal del conjunto de conectivos -> se puede asumir que es constante K
    // P: cantidad de repeticiones de la palabra más repetida

    // Crea un editor de texto vacío y registra qué conectivos considerará
    Editor(const set<string> & conectivos);                     // O(1)

    // Obtiene el texto completo
    string texto() const;                                       // O(N)

    const set<string>& vocabulario() const;                     // O(1)
    const set<string>& conectivos() const;                      // O(1)

    //  cuántas palabras no conectivas tiene el texto
    int conteo_palabras() const;                                // O(1)
    // cantidad de palabras del texto               
    int longitud() const;                                       // O(1)

    // obtiene posiciones de la palabra en el texto
    const set<int> & buscar_palabra(const string& palabra) const;               // O(log M)

    // agrega una palabra en una posición, desplazando a las restantes
    void insertar_palabras (const string& oracion, int posicion);               // sin requerimiento
    // elimina la palabra de una posición
    void borrar_posicion (int posicion);                                        // sin requerimiento
    // borra todas las apariciones de la palabra del texto y devuelve la cantidad borrada 
    int borrar_palabra (const string& palabra);                                 // sin requerimiento

    // agrega varias palabras al final del texto (separadas por espacios)
    void agregar_atras (const string& oracion);                                 // O(|oracion| * log(M))
    // reemplaza una palabra por otra    
    void reemplazar_palabra(const string& palabra, const string& reemplazo);    // O(log M + P * log(P))

private:
    set<string> _conectivos;
    vector<string> _texto;
    set<string> _vocabulario;
    int _cantidad_palabras;
    int _longitud;
    map<string, set<int>> _posiciones_palabras;

    //Invariante de Representacion:
    //  -_texto son strings solo con letras del alfabeto
    //  -_cantidad_palabras mayor o igual a cero
    //  -_longitud igual al tamaño de _texto
    //  -la clave de _posiciones_palabras (string) tiene que pertencer a _texto
    //  -los valores en el set de _posiciones_palabras son numeros entre 0 y _longitud-1
    //  -relaciones entre texto conectivos y vocabulario

    //Rep(e:estr) = 
    // _cantidad_palabras >= 0
    // _longitud >= 0
    // (for all)(int i)(0<=i<|_posiciones_palabras|)=>e._posiciones_palabras[i]
    
};


#endif // __EDITOR_H__
