#ifndef GRAPH_QL_PARSER_H
#define GRAPH_QL_PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "request.h"
#include "malloc.h"

enum parser_status parse_request(char * req, struct request *request);

enum parser_status {
    PARSE_OK = 0,
    PARSE_INCORRECT_REQUEST = 1,
    PARSE_ERROR = 2
};

#endif //GRAPH_QL_PARSER_H
