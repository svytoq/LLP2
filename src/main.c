#include "../include/parser.h"
#include "../include/view.h"

int main(int argc, char **argv) {

    char *req;

    // TODO read req from console or from file

    struct request *request = malloc(sizeof(struct request *));

    parse_request(req, request);

    get_request_view(request);

    return 0;
}
