/*
  for self-education to learn algotirhm.
  
  bsearch - binary search of a sorted array
 */

#include <stdlib.h>
#include <stdio.h>

/*
  define node
*/ 
typedef struct node {
  int item;
  struct node *left;
  struct node *right;
}Node;


/*
  generate node
*/ 
static Node *make_node(int x)
{
  Node *node = malloc(sizeof(Node));
  if (node != NULL){
    node->item = x;
    node->left = NULL;
    node->right = NULL;
  }
  return node;
}


/*
  search data
*/ 
static int search_node(int x, Node *node)
{
  while (node != NULL){
    if (node->item == x){
      return 0;
    }else if (x < node->item){
      node = node->left;
    }else{
      node = node->right;
    }
  }
  return -1;
}


/*
  if node does not exist, make new node.
*/ 
static Node *insert_node(int x, Node *node)
{
  if (node == NULL){
    return make_node(x);
  }else if (x < node->item){
    node->left = insert_node(x, node->left);
  }else if (x > node->item){
    node->right = insert_node(x, node->right);
  }
  return node;
}


/*
  search minimun number in  tree
*/
static int search_min(Node *node)
{
  while (node->left != NULL){
    node = node->left;
  }
  return node->item;
}


/*
  delete node of minimun number in tree, whose root is 'node'.
*/ 
static Node *delete_min(Node *node)
{
  if (node->left == NULL){
    Node *tmp = node->right;
    free(node);
    return tmp;
  }
  node->left = delete_min(node->left);
  return node;
}


/*
  search data and delete its node
*/
static Node *delete_node(int x, Node *node)
{
  if (node == NULL){
    return NULL;
  }
  if (x == node->item){
    if(node->left == NULL){
      Node *tmp = node->right;
      free(node);
      return tmp;
    }
    if (node->right == NULL){
      Node *tmp = node->left;
      free(node);
      return tmp;
    }
    node->item = search_min(node->right);
    node->right = delete_min(node->right);
  }else if (x < node->item){
    node->left= delete_node(x, node->left);
  }else{
    node->right = delete_node(x, node->right);
  }
  return node;
}


/*
  traverse
 */
static void foreach_node(void (*func)(int), Node *node)
{
  if (node != NULL){
    foreach_node(func, node->left);
    func(node->item);
    foreach_node(func, node->right);
  }
}


/*
  output item
*/
void print_item(int x)
{
  printf("%d", x);
}


/*
  define tree and function to opearate them.
 */


/*
  define Tree
 */
typedef struct {
  Node *root;
}Tree;


/*
  make Tree
*/
Tree *make_tree(void)
{
  Tree *tree = malloc(sizeof(Tree));
  if (tree != NULL){
    tree->root = NULL;
  }
  return tree;
}


/*
  search data from Tree
*/
int search_tree(int x, Tree *tree)
{
  return search_node(x, tree->root);
}


/*
  insert data to Tree
*/
void insert_tree(int x, Tree *tree)
{
  tree->root = insert_node(x, tree->root);
}


/*
  delete data from Tree
*/
void delete_tree(int x, Tree *tree)
{
  tree->root = delete_node(x, tree->root);
}


/*
  destroy node
*/
static void destroy_node(Node *node)
{
  if (node != NULL){
    destroy_node(node->left);
    destroy_node(node->right);
    free(node);
  }
}


/*
  destroy Tree
*/
void destroy_tree(Tree *tree)
{
  destroy_node(tree->root);
  free(tree);
}


/*
  traverse tree
 */
void foreach_tree(void (*func)(int), Tree *tree)
{
  foreach_node(func, tree->root);
}

/*
  TEST
*/
void print_tree(Tree *tree)
{
  foreach_tree(print_item, tree);
  printf("\n");
}

int main(int argc, char *argv[])
{
  if (argc < 1){
    perror("[!] usage: ./bsearch [num1 [num2 [...]]]");
    exit(1);
  }

  int a[argc-1];

  for (int i = 1; i < argc; i ++){
    a[i-1] = atoi(argv[i]);
  }

  Tree *tree = make_tree();
  
  for (int i = 0; i < argc-1; i ++){
    insert_tree(a[i], tree);
    print_tree(tree);
  }

  for (int i = -1; i < argc; i ++){
    printf("%d\n", search_tree(i, tree));
  }

  for (int i = 0; i < argc-1; i++){
    delete_tree(a[i], tree);
    print_tree(tree);
  }
  destroy_tree(tree);
}


