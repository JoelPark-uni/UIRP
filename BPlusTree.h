#ifndef BPlusTree_H
#define BPlusTree_H

#include <iostream>

template <typename T>
struct Node {
    bool is_leaf;
    std::size_t degree; // maximum number of children
    std::size_t size; // current number of children
    T* item;
    Node<T>** children;

    // You may add variables if needed.

public:
    Node(std::size_t _degree) {
        // Constructor
        is_leaf = false;
        degree = _degree;
        size = 1;
        item = new T[_degree+1]; // The last element is to make easier when overflow occurred.
        children = new Node<T>*[_degree+2];
    }

    // You may add a destructor if needed.
};

template <typename T>
class BPlusTree {
    Node<T>* root;
    std::size_t degree;

public:
    BPlusTree(std::size_t _degree) {
        // Constructor
        root = NULL;
        degree = _degree;

    }

    ~BPlusTree() {
        // Destructor
        BPlusTree_clear(root);

    }

    bool search(T data) {
        // Return true if the item exists. Return false if it does not.
        Node<T>* tmp = root;
        if(tmp == NULL)     return false;

        while(tmp->is_leaf != true)
        {
            for(int i = 0; i < tmp->size-1; i++)
            {
                if(tmp->item[i] > data)
                {

                    tmp = tmp->children[i];
                    break;
                }

                if(i == tmp->size-2)
                {
                    tmp = tmp->children[i+1];
                    break;
                }
            }
        }


        for(int i = 0; i < tmp->size-1; i++)
        {
            if(tmp->item[i] == data)    return true;
        }

        return false;

    }

    void insert(T data) {
        // Insert new item into the tree.


        if(root == NULL)
        {
            root = new Node<T>(degree);

            root->item[0] = data;
            root->is_leaf = true;
            root->size++;

            return;
        }

        Node<T>* tmp = root;
        Node<T>* tmp_parent;

        // Using similar algorithm with search to find appropriate position
        while(tmp->is_leaf != true)
        {
            tmp_parent = tmp;
            for(int i = 0; i < tmp->size-1; i++)
            {
                if(tmp->item[i] > data)
                {

                    tmp = tmp->children[i];
                    break;
                }

                if(i == tmp->size-2)
                {
                    tmp = tmp->children[i+1];
                    break;
                }
            }
        }




        if(tmp->size < degree)
        {
            tmp->item[tmp->size-1] = data;
            sort_item(tmp->item, tmp->size);
            tmp->size++;

            // Last pointer should point the next node
            tmp->children[tmp->size] = tmp->children[tmp->size-1];
            tmp->children[tmp->size-1] = NULL;
        }

        else
        {
            tmp->item[tmp->size-1] = data;
            sort_item(tmp->item, tmp->size);
            tmp->size++;
            tmp->size = degree/2;

            Node<T>* newNode = new Node<T>(degree);

            newNode->is_leaf = true;
            newNode->degree = degree;
            newNode->size = degree - degree/2 + 1;
            for(int i = 0; i < newNode->size-1; i++)
            {
                newNode->item[i] = tmp->item[tmp->size + i];
            }

            // Last children should point to next node.
            tmp->children[tmp->size] = newNode;
            newNode->children[newNode->size] = tmp->children[degree-1];
            tmp->children[degree-1] = NULL;

            if(tmp == root)
            {
                Node<T>* newRoot = new Node<T>(degree);
                root = newRoot;

                newRoot->is_leaf = false;
                newRoot->size = 2;

                newRoot->item[0] = newNode->item[0];
                newRoot->children[0] = tmp;
                newRoot->children[1] = newNode;
            }

            else
            {
                insert_internal(newNode->item[0], tmp_parent, newNode);
            }

        }
    }

    void insert_internal(T data, Node<T>* tmp, Node<T>* child)
    {
        if(tmp->size < degree)
        {
            tmp->item[tmp->size-1] = data;
            sort_item(tmp->item, tmp->size);
            tmp->size++;

            for(int i = 0; i < tmp->size-1; i++)
            {
                if(tmp->item[i] == data)
                {
                    shift_children(tmp->children, tmp->size, i);
                    tmp->children[i+1] = child;
                    break;
                }
            }
        }

        else // Overflow
        {
            tmp->item[tmp->size-1] = data;
            sort_item(tmp->item, tmp->size);
            tmp->size++;

            for(int i = 0; i< tmp->size-1; i++)
            {
                if(tmp->item[i] == data)
                {
                    shift_children(tmp->children, tmp->size, i);
                    tmp->children[i+1] = child;
                    break;
                }
            }

            tmp->size = tmp->size/2;

            Node<T>* newNode = new Node<T>(degree);
            newNode->is_leaf = false;
            newNode->degree = degree;
            newNode->size = degree - degree/2 + 1;
            for(int i = 0; i < newNode->size-1; i++)
            {
                newNode->item[i] = tmp->item[tmp->size - 1 + i];
                newNode->children[i] = tmp->children[tmp->size - 1 + i];
            }
            newNode->children[newNode->size-1] = tmp->children[tmp->size];

            if(tmp == root)
            {
                //std::cout<<"tmp";

                Node<T>* newRoot = new Node<T>(degree);
                newRoot->is_leaf = false;
                newRoot->size = 2;
                newRoot->item[0] = tmp->item[tmp->size-1];
                newRoot->children[0] = tmp;
                newRoot->children[1] = newNode;
                root = newRoot;
            }
            else
            {
                //std::cout <<"!";
                insert_internal(tmp->item[tmp->size-1], search_parent(root, tmp), newNode);
            }

        }
    }

    void shift_children(Node<T>** children, size_t size, int n)
    {
        for(int i = size; i > n+1; i--)
        {
            children[i] = children[i-1];
        }
    }

    Node<T>* search_parent(Node<T>* tmp, Node<T>* aim)
    {
        //std::cout << "search";
        Node<T>* parent;
        for(int i = 0; i < tmp->size; i++)
        {
            if(tmp->is_leaf || tmp->children[0]->is_leaf)
                return NULL;
            if(tmp->children[i] == aim)
            {
                parent = tmp;
                //std::cout <<"SUC";
                return parent;
            }
            else
            {
                //std::cout <<"SUC";
                parent = search_parent(tmp->children[i], aim);
                if(parent != NULL)
                    return parent;
            }
        }

        return parent;

    }


    void remove(T data) {
        // Remove an item from the tree.
    }

    /* ------ int range_search() ------
     * Find for items with data between start and end, inclusive.
     * result_data is an array with the length of arr_length.
     * If the number of matching data exceeds the length, abort and return -1.
     * Otherwise, fill it with the matching data and return the number of them.
     *
     * For example, if tree is currently [1, 2, 3, 4, 5]
     * and range_search(2, 4, arr, 3) is called,
     * fill arr to make arr == {2, 3, 4} and return 3.
     *
     * You can assume result_data is safe to use for at least arr_length
     * elements.
     */

    int range_search(T start, T end, T* result_data, int arr_length) {
        // Implement here
    }

    void print(Node<T>* cursor) {
        // You must NOT edit this function.
        if (cursor != NULL) {
            for (int i = 0; i < cursor->size; ++i) {
                std::cout << cursor->item[i] << " ";
            }
            std::cout << "\n";

            if (cursor->is_leaf != true) {
                for (int i = 0; i < cursor->size + 1; ++i) {
                    print(cursor->children[i]);
                }
            }
        }
    }

    void _print(Node<T>* tmp)
    {

        if(tmp == NULL)     return;
        if(tmp->is_leaf)
        {
            for(int i = 0; i < tmp->size-1; i++)
            {
                std::cout << tmp->item[i];
            }
        }
        else
        {
            for(int i = 0; i < tmp->size; i++)
                BPlusTree_clear(tmp->children[i]);
        }
    }

    Node<T>* getRoot()
    {
        return root;
    }

    void BPlusTree_clear(Node<T>* tmp)
    {
        if(tmp == NULL)     return;
        if(tmp->is_leaf)
        {
            delete[] tmp->item;
            delete[] tmp->children;
            delete tmp;
        }
        else
        {
            for(int i = 0; i < tmp->size; i++)
                BPlusTree_clear(tmp->children[i]);
        }
    }

    void sort_item(T* arr, int size) // Using Bubble sort
    {
        T temp;
        for(int i = 0; i < size; i++)
        {

            for(int j = i; j < size; j++)
            {
                if(arr[i] > arr[j])
                {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }

            }
        }
    }
};

#endif
