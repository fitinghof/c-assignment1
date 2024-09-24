#include <assert.h>
#include <stdio.h>

#include "common_defs.h"
#include "linked_list.h"

// Helper to assert node values and report
void assert_node_value(Node *node, uint16_t expected_value,
                       const char *test_name) {
    if (node == NULL || node->data != expected_value) {
        printf_red("FAIL [%s]: Expected %hu, got %hu\n", test_name,
                   expected_value, node ? node->data : 0);
    } else {
        printf_green("PASS [%s]: Expected %hu\n", test_name, expected_value);
    }
}

// Test inserting elements
void test_insert() {
    printf_yellow("Testing list_insert...\n");
    Node *head = NULL;
    list_init(&head);
    list_insert(&head, 10);
    list_insert(&head, 20);
    assert_node_value(head, 20, "test_insert");
    assert_node_value(head->next, 10, "test_insert");

    list_cleanup(&head);
}

// Test inserting elements
void test_insert_loop(int count) {
    printf_yellow("Testing list_insert...\n");
    Node *head = NULL;
    list_init(&head);
    for (int i = 0; i < count; i++) {
        list_insert(&head, i);
    }
    Node *current = head;
    for (int i = count - 1; i >= 0; i--) {
        assert_node_value(current, i, "test_insert");
        current = current->next;
    }

    list_cleanup(&head);
}

// Test inserting after
void test_insert_after() {
    printf_yellow("Testing list_insert_after...\n");
    Node *head = NULL;
    list_init(&head);
    list_insert(&head, 10);
    list_insert(&head, 20);
    Node *node = list_search(&head, 20);
    list_insert_after(node, 15);
    assert_node_value(node->next, 15, "test_insert_after");

    list_cleanup(&head);
}

// Test deletion
void test_delete() {
    printf_yellow("Testing list_delete...\n");
    Node *head = NULL;
    list_init(&head);
    list_insert(&head, 10);
    list_insert(&head, 20);
    list_delete(&head, 10);
    assert_node_value(head, 20, "test_delete");

    list_cleanup(&head);
}

// Test searching
void test_search() {
    printf_yellow("Testing list_search...\n");
    Node *head = NULL;
    list_init(&head);
    list_insert(&head, 10);
    list_insert(&head, 20);
    Node *found = list_search(&head, 10);
    assert_node_value(found, 10, "test_search");

    list_cleanup(&head);
}

void test_show_list() {
    Node *head;
    list_init(&head);

    for (size_t i = 0; i < 10; i++) {
        list_insert(&head, i * 10);
    }
    printf_yellow("Please check manually that this looks good :)\n");
    list_display_range(&head, head, NULL);
    list_cleanup(&head);
}

int main() {
    printf("Needed memory: %ld bytes\n", sizeof(Node[100]));
    test_insert();
    test_insert_loop(100);
    test_insert_after();
    test_delete();
    test_search();
    test_show_list();
    printf("Node size: %ld bytes\n", sizeof(Node));
    return 0;
}
