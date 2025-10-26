#include <iostream>
#include <windows.h>
#include "RB_tree.h"

int main() {
    // Habilitar UTF-8 en consola de Windows
    SetConsoleOutputCP(CP_UTF8);

    RB_tree<int> tree;

    // Insertando elementos
    tree.add_leaf(10);
    tree.add_leaf(20);
    tree.add_leaf(30);
    tree.add_leaf(15);
    tree.add_leaf(25);
    tree.add_leaf(5);

    std::cout << "Árbol después de inserciones:" << std::endl;
    tree.print_tree();

    std::cout << "\n¿Existe 15? " << (tree.find(15) ? "Sí" : "No") << std::endl;
    std::cout << "¿Existe 100? " << (tree.find(100) ? "Sí" : "No") << std::endl;

    std::cout << "\nSucesor de 15: " << tree.sucesor(15) << std::endl;
    std::cout << "Predecesor de 20: " << tree.predecesor(20) << std::endl;

    std::cout << "\nEliminando 20..." << std::endl;
    tree.delete_leaf(20);
    tree.print_tree();

    return 0;
}