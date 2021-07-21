#include "list_dump.h"


void ListDump(List* list, FILE* log) {
    assert(list);
    assert(log);

    fprintf(log, "digraph List {\n");
    fprintf(log, "\tnode [shape = record, style = filled, fillcolor = yellow];\n");
    fprintf(log, "\tedge [constraint = false];\n");
    fprintf(log, "\trankdir = LR;\n\n");
    
    fprintf(log, "\tsubgraph Stat {\n");
    fprintf(log, "\t\tnode [fillcolor = white];\n");
    fprintf(log, "\t\tstat [label = \"n_elems: %zu|capacity: %zu\"];\n", list->n_elems, list->capacity);
    
    fprintf(log, "\t}\n");

    fprintf(log, "\tsubgraph cluster_memory {\n");
}