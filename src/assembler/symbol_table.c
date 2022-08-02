#include "symbol_table.h"

// symbol table data structure based on a binary tree

// allocates memory for a tree element
stElem *st_alloc_elem(void){
    stElem *elem = malloc(sizeof(stElem));
    if (elem == NULL) errorAndExit("Unable to allocate memory at \"symbol_table.c::st_alloc_elem\".");
    return elem;
}

// frees the memory for a tree element and all children trees recursively
void st_free_elem(stElem *elem){
    if (elem == NULL) return;
    st_free_elem(elem->left);
    st_free_elem(elem->right);
    free(elem);
}

// frees the memory for a symbol table (binary tree) by calling the recursive method
void st_free(symbolTable *table){
    st_free_elem(table -> root);
    free(table);
}

// initializes symbol table
void st_init(symbolTable *handle){
    handle -> root = NULL;
}

// inserts a node into the tree, containing a label and address
stElem *st_insert_elem(stElem *root, const char *label, u_address address){
    if (root == NULL) {
        // if tree is empty
        stElem *newElem = st_alloc_elem();
        newElem -> label = label;
        newElem -> address = address;
        newElem -> left = newElem -> right = NULL;
        return newElem;
    } else {
        // if tree isn't empty add to the first free node
        const int comparison = strcmp(label, root -> label);
        if (comparison < 0) {
            root->left = st_insert_elem(root->left, label, address);
        } else if (comparison > 0) {
            root->right = st_insert_elem(root->right, label, address);
        }
        return root;
    }
}

// calls the recursive st_insert_elem method
void st_insert(symbolTable *handle, const char label[], u_address address){
    handle -> root = st_insert_elem(handle -> root, label, address);
}

// searches for and returns the address corresponding to the provided label
u_address st_lookup(symbolTable *handle, char *label){
    stElem *elem = handle->root;
    while (elem != NULL) {
        const int comparison = strcmp(label, elem -> label);
        if (comparison == 0) {
            return elem -> address;
        } else if (comparison < 0) {
            elem = elem -> left;
        } else {
            elem = elem -> right;
        }
    }
    return 4;
}

// mallocs space for the table and initializes
symbolTable *create_table(void) {
  symbolTable *table = malloc(sizeof(symbolTable));
  if (table == NULL) errorAndExit("Unable to allocate memory for the table at \"symbol_table.c::create_table\".");
  st_init(table);
  return table;
}
