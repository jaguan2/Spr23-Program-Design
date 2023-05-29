#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

struct node *insert_head(struct node *list, int x);                             // inserts a node at the head of the list
struct node *insert_tail(struct node *list, int x);                             // inserts a node at the tail of the list
struct node *sorted_insert(struct node *list, int x);                           // inserts a node while maintaining the order of the list
struct node *insert_after(struct node *list, int after_n, int new_x);           // inserts a node after a specified value, 'after_n', contained in the list
struct node *reverse_list(struct node *list);                                   // reverses the order of the list
struct node *delete_head(struct node *list);                                    // deletes the first node of the list
struct node *delete_tail(struct node *list);                                    // deletes the last node of the list
struct node *delete(struct node *list, int x);                                  // deletes the first node containing value 'x' provided as an argument
struct node *delete_all(struct node *list, int x);                              // deletes all nodes containing value 'x' provided as an argument
struct node *append(struct node *list1, struct node *list2);                    // appends list2 to the tail of list1
struct node *replace_matches(struct node *list, int find_n, int replace_x);     // replaces every value containing 'find_n' with 'replace_x' provided as an argument
struct node *find_largest(struct node *list);                                   // returns the node containing the largest value in the list
struct node *clear_list(struct node *list);                                     // deletes all nodes in the list
struct node *remove_duplicate(struct node *list);                               // removes any duplicate value in the list
int search_value(struct node *list, int x);                                     // returns 1 if list contains value 'x', returns 0 if list does not contain value 'x'
int count_matches(struct node *list, int x);                                    // counts the number of times the value 'x' appears in the list
int duplicates(struct node *list);                                              // returns 1 if the list contains any duplicate values, returns 0 if there are no duplicates
void print_list(struct node *list);                                             // prints all the values of the list

int main() {

    struct node *list = NULL;

    exit(EXIT_SUCCESS);

}

struct node *insert_head(struct node *list, int x) {

    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Out of memory\n");
        exit(EXIT_FAILURE);
    }

    new_node->value = x;
    new_node->next = list;
    return new_node;

}

struct node *insert_tail(struct node *list, int x) {

    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Out of memory\n");
        exit(EXIT_FAILURE);
    }

    new_node->value = x;
    new_node->next = NULL;

    if (list == NULL) {
        return new_node;
    }

    struct node *cur;
    for (cur = list; cur->next != NULL; cur = cur->next);
    cur->next = new_node;

    return list;

}

struct node *sorted_insert(struct node *list, int x) {

    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Out of memory\n");
        exit(EXIT_FAILURE);
    }

    new_node->value = x;

    struct node *prev, *cur;
    for (cur = list, prev = NULL; cur != NULL; prev = cur, cur = cur->next) {
        if (cur->value > x) {
            break;
        }
    }

    // if prev is NULL, either the list is empty or the first node already contains a value greater than new node's value
    if (prev == NULL) {
        new_node->next = list;
        return new_node;
    }
    // order of new node's insert is either in the middle or end of the list
    else {
        prev->next = new_node;
        new_node->next = cur;
        return list;
    }

}

struct node *insert_after(struct node *list, int after_n, int new_x) {

    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Out of memory\n");
        exit(EXIT_FAILURE);
    }

    new_node->value = new_x;

    if (list == NULL) {
        new_node->next = list;
        return new_node;
    }

    struct node *cur;
    for (cur = list; cur->next != NULL;) {
        if (cur->value == after_n) {
            new_node->next = cur->next;
            cur->next = new_node;
            return list;
        }
        else {
            cur = cur->next;
        }
    }

}

struct node *reverse_list(struct node *list) {

    if (list == NULL) {
        return NULL;
    }

    struct node *cur, *prev = NULL, *next = NULL;
    for (cur = list; cur != NULL; cur = next) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
    }

    return prev;

}

struct node *delete_head(struct node *list) {

    if (list == NULL) {
        return NULL;
    }

    if (list->next == NULL) {
        free(list);
        return NULL;
    }

    struct node *new_head = list->next;
    free(list);

    return new_head;

}

struct node *delete_tail(struct node *list) {

    if (list == NULL) {
        return NULL;
    }

    if (list->next == NULL) {
        free(list);
        return NULL;
    }

    struct node *prev, *cur;
    for (cur = list, prev = NULL; cur->next != NULL; prev = cur, cur = cur->next);
    prev->next = NULL;
    free(cur);

    return list;

}

struct node *delete(struct node *list, int x) {

    if (list == NULL) {
        return NULL;
    }

    if (list->value == x && list->next == NULL) {
        free(list);
        return NULL;
    }

    if (list->value == x) {
        struct node *new_head = list->next;
        free(list);
        return new_head;
    }

    struct node *prev, *cur;
    for (cur = list, prev = NULL; cur != NULL && cur->value != x; prev = cur, cur = cur->next);
    prev->next = cur->next;
    free(cur);

    return list;

}

struct node *delete_all(struct node *list, int x) {

    if (list == NULL) {
        return NULL;
    }

    struct node *cur, *temp;
    for (cur = list; cur != NULL && cur->value == x; cur = temp) {
        temp = cur->next;
        free(cur);
    }

    if (cur == NULL) {
        return NULL;
    }

    struct node *new_list = cur;

    while (cur->next != NULL) {
        if (cur->next->value == x) {
            temp = cur->next;
            cur->next = cur->next->next;
            free(temp);
        }
        else {
            cur = cur->next;
        }
    }

    return new_list;

}

struct node *append(struct node *list1, struct node *list2) {

    if (list1 == NULL) {
        return list2;
    }

    if (list2 == NULL) {
        return list1;
    }

    struct node *cur;
    for (cur = list1; cur->next != NULL; cur = cur->next);
    cur->next = list2;

    return list1;

}

struct node *replace_matches(struct node *list, int find_n, int replace_x) {

    if (list == NULL) {
        return NULL;
    }

    struct node *cur;
    for (cur = list; cur != NULL; cur = cur->next) {
        if (cur->value == find_n) {
            cur->value = replace_x;
        }
    }

    return list;

}

struct node *find_largest(struct node *list) {

    struct node *p, *largest = list;
    for (p = list->next; p != NULL; p = p->next) {
        if (p->value > largest->value) {
            largest = p;
        }
    }

    return largest;

}

struct node *clear_list(struct node *list) {

    if (list != NULL) {
        clear_list(list->next);
        free(list);
    }

    return NULL;

}

struct node *remove_duplicate(struct node *list) {

    if (list == NULL) {
        return NULL;
    }

    struct node *p, *q, *temp;
    for (p = list; p != NULL; p = p->next) {
        for (q = p; q->next != NULL;) {
            if (p->value == q->next->value) {
                temp = q->next;
                q->next = q->next->next;
                free(temp);
            }
            else {
                q = q->next;
            }
        }
    }

    return list;

}

int search_value(struct node *list, int x) {

    if (list == NULL) {
        return 0;
    }

    if (list->value == x) {
        return 1;
    }

    return search_value(list->next, x);

}

int count_matches(struct node *list, int x) {

    if (list == NULL) {
        return 0;
    }

    if (list->value == x) {
        return 1 + count_matches(list->next, x);
    }

    return count_matches(list->next, x);

}

int duplicates(struct node *list) {

    struct node *p, *q;
    for (p = list; p->next != NULL; p = p->next) {
        for (q = p->next; q != NULL; q = q->next) {
            if (p->value == q->value) {
                return 1;
            }
        }
    }

    return 0;

}

void print_list(struct node *list) {

    if (list != NULL) {
        for (struct node *p = list; p != NULL; p = p->next) {
            printf("%d ", p->value);
        }
        printf("\n");
    }

}