#include <iostream>
#include "BinaryTree.h"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

using namespace std;


int main() {

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    BinaryTree<int> tree{};
    tree.remove(5);
    tree.draw();
    tree.insertNode(10);
    tree.insertNode(8);
    tree.insertNode(9);
    tree.insertNode(20);
    tree.insertNode(15);
    tree.insertNode(25);
    tree.insertNode(12);
    tree.draw();
    tree.remove(20);
    tree.draw();
    tree.remove(10);
    tree.draw();
    tree.insertNode(10);
    tree.draw();
}
