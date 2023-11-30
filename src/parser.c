#include "../include/parser.h"

void print_error() {
    printf("The request is incorrectly written\n");
    exit(EXIT_FAILURE);
}

void check_path(char *req, int *path_length) {
    int bracket = 0;

    for (int i = 0; i < *path_length; i++) {
        if (req[i] == '{') bracket++;
        if (req[i] == '}') bracket--;
    }

    if (bracket != 0) {
        print_error();
    }
}

void remove_char(int *size, char **request_path) {
    (*size)--;
    (*request_path)++;
}

void new_line(char **req, int *path_length) {
    int i;
    for (i = 0; i < *path_length; i++) {
        if ((*req)[i] == '\n') break;
    }
    i++;
    for (; i < *path_length; i++) {
        if ((*req)[i] != ' ') break;
    }

    for (int j = 0; j < i; j++) {
        remove_char(path_length, req);
    }
}

char *read_word(char **req, int *path_length) {

    char *word = calloc(MAX_STRING_SIZE, sizeof(char));

    int i;
    for (i = 0; i < *path_length; i++) {
        if ((*req)[i] == ' ' || (*req)[i] == ',') {
            if ((*req)[i] == ',') i--;
            break;
        }
        word[i] = (*req)[i];
    }
    i++;

    for (int j = 0; j < i; j++) {
        remove_char(path_length, req);
    }
    return word;
}

void read_attributes(char **req, int *path_length, struct attribute *attribute) {

    if ((*req)[0] != '|' && (*req)[0] != '&') {
        char *left = read_word(req, path_length);
        char *condition = read_word(req, path_length);
        char *right = read_word(req, path_length);

        attribute->left = left;
        attribute->condition = condition;
        attribute->right = right;
    }

    if ((*req)[0] == ',') {

        new_line(req, path_length);
        struct attribute *new_attribute = malloc(sizeof(struct attribute));
        read_attributes(req, path_length, new_attribute);
        attribute->next_attribute = new_attribute;
    } else if ((*req)[0] == '|' || (*req)[0] == '&') {

        char *combined_condition = read_word(req, path_length);
        attribute->combined_condition = combined_condition;
        new_line(req, path_length);
        read_attributes(req, path_length, attribute);
    }
    remove_char(path_length, req);
}

enum parser_status parse_request(char *req, struct request *request) {

    int path_length = strlen(req);

    check_path(req, &path_length);

    char *query = read_word(&req, &path_length);
    if (strcmp("query", query) != 0) print_error();

    new_line(&req, &path_length);

    char *operation = read_word(&req, &path_length);
    if (!(
            strcmp("add", operation) == 0 ||
            strcmp("find", operation) == 0 ||
            strcmp("delete", operation) == 0 ||
            strcmp("update", operation) == 0 ||
            strcmp("connect", operation) == 0
    ))
        print_error();

    request->operation = operation;

    new_line(&req, &path_length);

    struct attribute *attribute = malloc(sizeof(struct attribute));
    request->attributes = attribute;
    read_attributes(&req, &path_length, attribute);

    new_line(&req, &path_length);
    new_line(&req, &path_length);

    return PARSE_OK;
}