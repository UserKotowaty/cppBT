#pragma once
template <typename T> struct TreeNode {
	T value;
	TreeNode<T>* left;
	TreeNode<T>* right;
};