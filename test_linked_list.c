#include "linked_list.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stddef.h>

#include "common_defs.h"

// Helper to assert node values and report
void assert_node_value(Node *node, uint16_t expected_value, const char *test_name)
{
    if (node == NULL || node->data != expected_value)
    {
        printf_red("FAIL [%s]: Expected %hu, got %hu\n", test_name, expected_value, node ? node->data : 0);
    }
    else
    {
        printf_green("PASS [%s]: Expected %hu\n", test_name, expected_value);
    }
}

// Test inserting elements
void test_insert()
{
    printf_yellow("Testing list_insert...\n");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * 3);
    list_insert(&head, 10);
    list_insert(&head, 20);
    list_insert(&head, 30);

    list_cleanup(&head);
    my_assert(head == NULL);
    printf_green("[PASS].\n");
}

// ********* Stress and edge cases *********

void test_list_insert_loop(int count)
{
    printf_yellow("Testing list_insert...\n");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * count);
    for (int i = 0; i < count; i++)
    {
        list_insert(&head, i);
    }
    Node *current = head;
    my_assert(current->data == 12345);
    current = current->next;

    for (int i = count - 1; i >= 0; i--)
    {
        my_assert(current->data == i);
        current = current->next;
    }

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_list_delete_loop(int count)
{
    printf_yellow("Testing list_insert_after...\n");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * count);
    for (int i = 0; i < count; i++)
    {
        list_insert(&head, i);
    }

    for (int i = 0; i < count; i++)
    {
        list_delete(&head, i);
    }

    my_assert(head == NULL);

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_list_search_loop(int count)
{
    printf_yellow("Testing list_delete...\n");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * count);
    for (int i = 0; i < count; i++)
    {
        list_insert(&head, i);
    }

    for (int i = 0; i < count; i++)
    {
        Node *found = list_search(&head, i);
        my_assert(found->data == i);
    }

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_list_edge_cases()
{
    printf_yellow("Testing list_search...\n");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * 3);

    // Insert at head
    list_insert(&head, 10);
    my_assert(head->data == 10);

    // Insert after
    Node *node = list_search(&head, 10);
    list_insert_after(node, 20);
    my_assert(node->next->data == 20);

    // Insert before
    list_insert_before(&head, node, 15);

    my_assert(head->data == 15);
    my_assert(head->next->data == 10);
    my_assert(head->next->next->data == 20);

    // Delete
    list_delete(&head, 15);
    my_assert(node->next->data == 20);

    // Search
    Node *found = list_search(&head, 20);
    my_assert(found->data == 20);

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

// Main function to run all tests
int main(int argc, char *argv[])
{
    test_insert();
    test_insert_loop(100);
    test_insert_after();
    test_delete();
    test_search();
    return 0;
}