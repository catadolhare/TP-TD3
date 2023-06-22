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

    // conjuntos vacíos para devolver por referncia
    const set<int> set_int_vacio = {};
    const set<string> set_string_vacio = {};

    vector<string> separar_oracion(const string& oracion);

/*

    //Invariante de Representacion:
    //  -_texto son strings solo con letras del alfabeto
    //  -_cantidad_palabras mayor o igual a cero
    //  -_longitud igual al tamaño de _texto
    //  -la clave de _posiciones_palabras (string) tiene que pertencer a _texto
    //  -si una palabra pertence a texto, es una clave en _posiciones_palabras
    //  -los valores en el set de _posiciones_palabras son numeros entre 0 y _longitud-1
    //  -si una palabra pertence a _vocabulario, no pertence a _conectivos
    //  -si una palabra pertenece a _conectivos, no pertence a _vocabulario
    //  -todas las palabras en _texto, estan en _conectivos o en _vocabulario, no en ambas
    //  -si una palabra esta en _vocabulario, esta en _texto

    Ejemplo que cumple invariante:
        - _texto = [me, presento, ante, usted]
        - _conectivos = {me, ante}
        - _vocabulario = {presento, usted}
        - _cant_palabras = 2
        - _longitud = 4
        - _posiciones_palabras = {[me,{0}], [presento,{1}], [ante,{2}], [usted,{3}]}
        - set_int_vacio = {};
        - set_string_vacio = {};

    Ejemplo que no cumple invariante:
        - _texto = [me, presento, ante, usted]
        - _conectivos = {me, ante}
        - _vocabulario = {me, presento, ante, usted}
        - _cant_palabras = 4
        - _longitud = 4
        - _posiciones_palabras = {[me,{0}], [presento,{1}], [ante,{2}], [usted,{3}]}
        - set_int_vacio = {};
        - set_string_vacio = {};

    //Rep(e:estr) = 
    // (for all)(int i, j)(0<=i<|e._texto| and 0<=j<=|e._texto[i]|)=>esLetra(e._texto[i][j])
    // e._cantidad_palabras >= 0
    // e._longitud == |_texto|
    // (for all)(string s)(s ∈ claves(e._posiciones_palabras))=> s ∈ e._texto
    // (for all)(int j)(0<=j<|_texto|) => e._texto[j] ∈ claves(e._posiciones_palabras)
    // (for all)(int k, l)(0<=k<|_texto| and 0<=l<|e._posiciones_palabras[k]) => 0<=e._posiciones_palabras[k][l]<=_longitud-1
    // (for all)(string m)(m ∈ |e._vocabulario|)=> m ∉ e._conectivos
    // (for all)(string n)(n ∈ |e._conectivos|)=> n ∉ e._vocabulario
    // (for all)(int p)(0<=p<|e._texto|)=>e._texto[p] ∈ e._conectivos ⊻ e._texto[p] ∈ e._vocabulario
    // (for all)(string q)(q ∈ |e._vocabulario|) => q ∈ e._texto

    //esLetra(c:char): c es letra del alfabeto

    */
};


#endif // __EDITOR_H__
