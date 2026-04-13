#include <assert.h>
#include <stdlib.h>

#include "hash_table.h"
#include "list.h"
#include "font.h"

list_t create_list(const char* word)
{
    list_t list = {};

    list.head = create_node(word);
    list.current = list.head;
    list.tail = list.head;

    return list;
}

node_t* create_node(const char* word)
{
    node_t node = {};

    node.word = word;
    node.next = nullptr;

    return &node;
}

node_t* list_push_back(const char* word, list_t* const list)
{
    assert(list);

    node_t* const node = create_node(word);

    list->tail->next = node;
    list->tail = node;

    return node;
}

void list_destroy(list_t* list)
{
    node_t* current = list->head;

    while (current)
    {
        node_t* next = current->next;
        free(current);
        current = next;
    }
}

bool list_verify(list_t* const list)
{
    if (!list) return false;

    if (!list->head)
        return (list->tail == nullptr && list->current == nullptr);
        
    if (!list->tail) return false;

    node_t* node = list->head;
    node_t* last = nullptr;
    bool current_found = (list->current == nullptr);

    while (node)
    {
        if (node == list->current)
            current_found = true;

        last = node;
        node = node->next;
    }

    if (last != list->tail) return false;
    if (list->tail->next != nullptr) return false;
    if (!current_found) return false;

    return true;
}

void list_dump(list_t* const list, const char* const txt_file_name, const char* const png_file_name)
{
    assert(list);
    assert(txt_file_name);
    assert(png_file_name);

    FILE* txt_file = fopen(txt_file_name, "w");
    fprintf(txt_file, "digraph structs\n{\nrankdir = LR;\ngraph[bgcolor=\"#e0e0e9ff\"];\n");

    int node_number = 1;
    for (list->current = list->head; ; node_number++)
    {
        fprintf(txt_file, "node_%d [style=filled, penwidth = 3, fillcolor=\"#b7e5f3ff\","
                "color = \"#3f6969ff\", shape=record, label= \" ", node_number);
        fprintf(txt_file, "WORD = %s | ", list->current->word);
        fprintf(txt_file, "ADDRESS = %p |\n", list->current);
        fprintf(txt_file, "{next = %p}\" ];\n", list->current->next);

        if (list->current == list->tail)
            break;
        list->current = list->current->next;
    }

    int list_capacity = node_number;
    fprintf(txt_file, "{\nedge[color = \"#149b5aff\", weight = 1000];\n");
    for (node_number = 1; node_number < list_capacity; node_number++)
    {
        fprintf(txt_file, "node_%d -> node_%d\n", node_number, node_number + 1);
    }

    fprintf(txt_file, "}\n");
    fprintf(txt_file, "}");
    fclose(txt_file);

    char command[1000];
    sprintf(command, "dot %s -T png -o %s", txt_file_name, png_file_name);
    system(command);

    printf(MAKE_BOLD_GREEN("List visualization saved to %s\n"), LIST_DUMP_PNG);
}
