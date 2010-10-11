/*
 * TSingleton.hpp
 *
 *  Created on: 20.07.2010
 *      Author: Martu
 */

#ifndef TSINGLETON_HPP_
#define TSINGLETON_HPP_

template <class T>
class TSingleton
{
protected: // protected da andere klassen von dieser erben sollen
    // Membervariablen
    static T *m_psingleton; // static weil wir nur eine Instanz benoetigen
public:
    // Memberfunktionen

    // Der Destruktor (er bleibt erstmal leer)
    virtual ~TSingleton ()
    {
    }

    // GET-Funktion
    // Es soll, wenn noch nicht vorhanden, ein statisches Objekt erzeugen
    // und einen Zeiger auf diese Zurueckgeben
    inline static T* GET ()
    {
        // if abfrage ob noch keine Instanz des objektes existiert
        if (!m_psingleton)
            m_psingleton = new T; // nein, also erzeugen wir eine

        return (m_psingleton); // Zeiger auf diese instanz zurueckgeben
    }

    // DEL-Funktion
    // Gibt das statische objekt wieder frei wenn es existiert
    static void DEL ()
    {
        // if abfrage ob die instanz existiert
        if (m_psingleton)
        {
            delete (m_psingleton); // ja, also freigeben
            m_psingleton = NULL; // und ja nicht vergessen den zeiger auf NULL zu setzen
        }
    }
};

// Die statische Variable noch erzeugen
template <class T>
T* TSingleton<T>::m_psingleton = 0;

#endif /* TSINGLETON_HPP_ */
