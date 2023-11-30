#ifndef GRAPH_QL_REQUEST_H
#define GRAPH_QL_REQUEST_H

#define MAX_REQUEST_SIZE 1024
#define MAX_STRING_SIZE 64
#define TAB "    "

struct attribute {
    char *left;
    char *right;
    char *condition;
    struct attribute *next_attribute;
    char *combined_condition;
};

struct request {
    char *operation;
    struct attribute *attributes;
};

#endif //GRAPH_QL_REQUEST_H
