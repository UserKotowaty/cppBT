#pragma once
#include "TreeNode.h"
#include <concepts>
#include <iostream>
template <typename T> concept treeType = requires (T a, T b) {
	requires std::copy_constructible<T>;
	requires std::copyable<T>;
	{a == b} -> std::same_as<bool>;
	{a > b} -> std::same_as<bool>;
	{a < b} -> std::same_as<bool>;

};

template <treeType T> class BinaryTree {
public:
	BinaryTree();
	~BinaryTree();
	void insertNode(const T&);
	bool searchNode(const T&);
	void remove(const T&);
	void draw();
private:
	TreeNode<T>* root;
	void insert(TreeNode<T>*&, TreeNode<T>*&);
	void destroySubTree(TreeNode<T>*);
	void deleteNode(const T&, TreeNode<T>*&);
	void makeDeletion(TreeNode<T>*&);
	bool recursive(TreeNode<T>*, const T& value);
};

template <treeType T>
BinaryTree<T>::BinaryTree() : root(nullptr) {

}

template <treeType T>
BinaryTree<T>::~BinaryTree() {
	destroySubTree(root);
}

template <treeType T>
void BinaryTree<T>::insert(TreeNode<T>*& nodePtr, TreeNode<T>*& newNode)
{
	if (nodePtr == nullptr)
	{
		// Insert the node.
		nodePtr = newNode;
	}
	else if (newNode->value < nodePtr->value)
	{
		// Search the left branch
		insert(nodePtr->left, newNode);
	}
	else
	{
		// Search the right branch
		insert(nodePtr->right, newNode);
	}
}

template <treeType T>
void BinaryTree<T>::insertNode(const T& num)
{
	TreeNode<T>* newNode = nullptr; // Pointer to a new node.
	// Create a new node and store num in it.
	newNode = new TreeNode<T>;
	newNode->value = num;
	newNode->left = newNode->right = nullptr;
	// Insert the node.
	insert(root, newNode);
}

template <treeType T>
void BinaryTree<T>::destroySubTree(TreeNode<T>* nodePtr) {
	if (nodePtr->left)
	{
		destroySubTree(nodePtr->left);
	}
	if (nodePtr->right)
	{
		destroySubTree(nodePtr->right);
	}
	delete nodePtr;
}

template <treeType T>
bool BinaryTree<T>::searchNode(const T& num) {
	return recursive(root, num);
}

template <treeType T>
void BinaryTree<T>::remove(const T& num) {
	deleteNode(num, root);
}

template <treeType T>
void BinaryTree<T>::deleteNode(const T& num, TreeNode<T>*& nodePtr) {
if(root==nullptr) {
	return;
}

	if (num < nodePtr->value)
	{
		deleteNode(num, nodePtr->left);
	}
	else if (num > nodePtr->value)
	{
		deleteNode(num, nodePtr->right);
	}
	else
	{
		makeDeletion(nodePtr);
	}
}

template <treeType T>
void BinaryTree<T>::makeDeletion(TreeNode<T>*& nodePtr)
{


	// Temporary pointer, used in reattaching the left subtree.
	TreeNode<T>* tempNodePtr = nullptr;
	if (nodePtr == nullptr)
	{
		
	}
	else if (nodePtr->right == nullptr)
	{
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->left; // Reattach the left child
		delete tempNodePtr;
	}
	else if (nodePtr->left == nullptr)
	{
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right; // Reattach the right child
		delete tempNodePtr;
	}
	// If the node has two children.
	else
	{
		// Move one node the right.
		tempNodePtr = nodePtr->right;
		// Go to the end left node.
		while (tempNodePtr->left)
		{
			tempNodePtr = tempNodePtr->left;
		}
		// Reattach the left subtree.
		tempNodePtr->left = nodePtr->left;
		tempNodePtr = nodePtr;
		// Reattach the right subtree.
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	}
}

template <treeType T>
bool BinaryTree<T>::recursive(TreeNode<T>* current, const T& value) {
	if (current == nullptr) {
		return false;
	}
	if (value == current->value) {
		return true;
	}
	return value < current->value
		? recursive(current->left, value)
		: recursive(current->right, value);
}

template <treeType T>
void BinaryTree<T>::draw() {
	printBT(root);
}

template <typename T>  void printBT(const TreeNode<T>* node)
{
	printBT("", node, false);
}

template <typename T> void printBT(const std::string& prefix, const TreeNode<T>* root, bool isLeft)
{
	if (root != nullptr)
	{
		//
		std::cout << prefix;

		std::cout << (isLeft ? "|--" : "^--");

		// print the value of the node
		std::cout << root->value << std::endl;

		// enter the next tree level - left and right branch
		printBT(prefix + (isLeft ? "|   " : "    "), root->left, true);
		printBT(prefix + (isLeft ? "|   " : "    "), root->right, false);
	}
}