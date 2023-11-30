#include "../include/parser.h"
#include "../include/view.h"

int main(int argc, char **argv) {

    FILE *file;
    file = fopen("request.txt", "r");
    char *req = calloc(MAX_REQUEST_SIZE, sizeof(char));
    fread(req, sizeof(char), MAX_REQUEST_SIZE, file);

    printf("Your request:\n%s\n\n", req);

    struct request *request = malloc(sizeof(struct request));
    enum parser_status status = parse_request(req, request);
    if (status == PARSE_OK) get_request_view(request);

    fclose(file);
    free(req);
    free(request);

    return 0;
}
