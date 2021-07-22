#include "list_dump.h"



void ListDump(List* list, FILE* log) {
    assert(list);
    assert(log);

    fprintf(log, "digraph List {\n");
    fprintf(log, "\tnode [shape = plaintext];\n");
    fprintf(log, "\tedge [minlen = 3];\n");
    fprintf(log, "\tsplines = ortho;\n\n");
    fprintf(log, "\tsubgraph Stat {\n");
    fprintf(log, "\t\tstat [label = <\n");
    fprintf(log, "\t\t\t<table border = \"1\">\n");
    fprintf(log, "\t\t\t\t<tr><td>n_elems: 4</td></tr>\n");
    fprintf(log, "\t\t\t\t<tr><td>capacity: 8</td></tr>\n");
    fprintf(log, "\t\t\t</table>\n");
    fprintf(log, "\t\t\t>];\n");
    fprintf(log, "\t}\n\n");

    fprintf(log, "\tsubgraph cluster_memory {\n");
    fprintf(log, "\t\tlabel = \"Nodes\";\n\n");
    fprintf(log, "\t\t{rank = same");
    for (size_t id = 0; id < list->capacity; ++id) {
        fprintf(log, "; %zu", id);
    }
    fprintf(log, "};\n");
    fprintf(log, "\t\t{rank = same; used_head; used_tail; free_head; free_tail};\n\n");

    fprintf(log, "\tsubgraph nodes {\n");
    size_t cur_phys_id = list->used_head_phys_id;
    size_t cur_logic_id = 0;
    while (cur_phys_id != LIST_INVALID_ID) {
        fprintf(log, "\t\t\t%zu [label = <\n", cur_phys_id);
        fprintf(log, "\t\t\t\t<table border = \"1\" bgcolor = \"%s\">\n", cur_logic_id >= list->n_elems ? "white" : "yellow");
        fprintf(log, "\t\t\t\t\t<tr><td>%s</td></tr>\n", cur_logic_id >= list->n_elems ? "free" : "used");
        fprintf(log, "\t\t\t\t\t<tr><td>phys_id: %zu</td></tr>\n", cur_phys_id);
        fprintf(log, "\t\t\t\t\t<tr><td>logic_id: %zu</td></tr>\n", cur_logic_id++);
        fprintf(log, "\t\t\t\t</table>\n");
        fprintf(log, "\t\t\t>];\n");
        cur_phys_id = list->elems[cur_phys_id].next_phys_id;
    }
    fprintf(log, "\n");
    fprintf(log, "\t\t\tedge [constraint = true, style = invis];\n\n");

    for (size_t id = 0; id < list->capacity - 1; ++id)
        fprintf(log, "\t\t\t%zu -> %zu;\n", id, id + 1);
    fprintf(log, "\n");

    fprintf(log, "\t\t\tedge [constraint = false, style = \"\"];\n\n");
    cur_phys_id = list->used_head_phys_id;
    while (cur_phys_id != list->free_tail_phys_id) {
        fprintf(log, "\t\t\t%zu -> %zu;\n", cur_phys_id, list->elems[cur_phys_id].next_phys_id);
        cur_phys_id = list->elems[cur_phys_id].next_phys_id;
    }
    fprintf(log, "\n");
    fprintf(log, "\t\t}\n\n");

    fprintf(log, "\t\tsubgraph extreme_elements {\n");
    fprintf(log, "\t\t\tfree_head [label = <\n");
    fprintf(log, "\t\t\t\t<table>\n");
    fprintf(log, "\t\t\t\t\t<tr><td>free_head</td></tr>\n");
    fprintf(log, "\t\t\t\t</table>\n");
    fprintf(log, "\t\t\t>];\n\n");

    fprintf(log, "\t\t\tfree_tail [label = <\n");
    fprintf(log, "\t\t\t\t<table>\n");
    fprintf(log, "\t\t\t\t\t<tr><td>free_tail</td></tr>\n");
    fprintf(log, "\t\t\t\t</table>\n");
    fprintf(log, "\t\t\t>];\n\n");

    fprintf(log, "\t\t\tused_head [label = <\n");
    fprintf(log, "\t\t\t\t<table>\n");
    fprintf(log, "\t\t\t\t\t<tr><td>used_head</td></tr>\n");
    fprintf(log, "\t\t\t\t</table>\n");
    fprintf(log, "\t\t\t>];\n\n");

    fprintf(log, "\t\t\tused_tail [label = <\n");
    fprintf(log, "\t\t\t\t<table>\n");
    fprintf(log, "\t\t\t\t\t<tr><td>used_tail</td></tr>\n");
    fprintf(log, "\t\t\t\t</table>\n");
    fprintf(log, "\t\t\t>];\n");
    fprintf(log, "\t\t}\n");

    fprintf(log, "\t\tedge [dir = back, headlabel = \"\", taillabel = \"\", minlen = \"\"];\n\n");

    fprintf(log, "\t\t%zu -> used_head;\n", list->used_head_phys_id);
    fprintf(log, "\t\t%zu -> used_tail;\n\n", list->used_tail_phys_id);

    fprintf(log, "\t\t%zu -> free_head;\n", list->free_head_phys_id);
    fprintf(log, "\t\t%zu -> free_tail;\n", list->free_tail_phys_id);

    fprintf(log, "\t}\n}\n");
}