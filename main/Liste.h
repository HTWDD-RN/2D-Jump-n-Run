#ifndef LINKEDLIST_H
#define LINKEDLIST_H
// Template-Klasse für ein Listenelement
template <typename T>
struct Node {
  T data; // Daten des Elements
  Node* next; // Zeiger auf das nächste Element in der Liste
};

// Template-Klasse für eine generische Liste
template <typename T>
class LinkedList {
public:
  LinkedList() : head(nullptr), current(nullptr) {} // Konstruktor, initialisiert die Liste mit einem leeren Kopfelement

  // Methode zum Hinzufügen eines Elements am Anfang der Liste
  void add(T data) {
    Node<T>* newNode = new Node<T>; // Neues Element erstellen
    newNode->data = data; // Daten setzen
    newNode->next = head; // Neuen Knoten an den Anfang der Liste anhängen
    head = newNode; // Kopfzeiger auf das neue Element setzen
  }

  // Methode zum Zugriff auf das erste Element der Liste
  Node<T>* getFirst() {
    current = head; // Setze current auf head
    return current; // Rückgabe des ersten Elements
  }

  // Methode zum Navigieren zum nächsten Element der Liste
  Node<T>* getNext() {
    if (current != nullptr) {
      current = current->next; // Gehe zum nächsten Element
      return current; // Rückgabe des aktuellen Elements
    } else {
      return nullptr; // Gib nullptr zurück, wenn das Ende der Liste erreicht ist
    }
  }

private:
  Node<T>* head; // Zeiger auf das erste Element in der Liste
  Node<T>* current; // Zeiger auf das aktuelle Element in der Liste
};

#endif
