#include <stdio.h>
#include <stdlib.h>
struct node {
    int key;
    int type;
    void *data;
    struct node *left;
    struct node *right;
};

struct newtype {
    int num;
    float score;
    char grade;
};

struct node *tree = NULL;

struct node *create(int key, void *data, int type) {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->key = key;
    newnode->type = type;
    newnode->data = data;
    newnode->left = newnode->right = NULL;
    return newnode;
}

struct node *insert(struct node *root, int key, void *data, int type) {
    if (root == NULL)
        return create(key, data, type);
    else if (key < root->key)
        root->left = insert(root->left, key, data, type);
    else if (key > root->key)
        root->right = insert(root->right, key, data, type);
    return root;
}

void print(void *data, int type) {
    switch (type) {
    case 1:
        printf("%d ", *(int *)data);
        break;
    case 2:
        printf("%.2f ", *(float *)data);
        break;
    case 3:
        printf("%c ", *(char *)data);
        break;
    case 4:
        struct newtype *nt = (struct newtype *)data;
        printf("{num: %d, score: %.2f, grade: %c}", nt->num, nt->score, nt->grade);
        break;
    default:
        break;
    }
}

void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("Key: %d, Data: ", root->key);
        print(root->data, root->type);
        printf("\n");
        inorder(root->right);
    }
}


void preorder(struct node *root) {
    if (root != NULL) {
        printf("Key: %d, Data: ", root->key);
        print(root->data, root->type);
        printf("\n");
        preorder(root->left);
        preorder(root->right);
    }
}


void postorder(struct node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("Key: %d, Data: ", root->key);
        print(root->data, root->type);
        printf("\n");
    }
}

int main() {
    while (1) {
        printf("Enter operation you want to perform\n");
        printf("1: Insert\n");
        printf("2: Inorder Traversal\n");
        printf("3: Preorder Traversal\n");
        printf("4: Postorder Traversal\n");
        printf("5: Exit\n");

        int ch;
        scanf("%d", &ch);

        switch (ch) {
        case 1: {
            int key;
            printf("Insert key for maintaining bst property: ");
            scanf("%d", &key);

            int k;
            printf("Choose data type to insert:\n");
            printf("1: int\n");
            printf("2: float\n");
            printf("3: char\n");
            printf("4: structure (int, float, char)\n");
            scanf("%d", &k);

            void *data;
            switch (k) {
            case 1: {
                data = malloc(sizeof(int));
                printf("Enter an integer: ");
                scanf("%d", (int *)data);
                tree = insert(tree, key, data, 1);
                break;
            }
            case 2: {
                data = malloc(sizeof(float));
                printf("Enter a float: ");
                scanf("%f", (float *)data);
                tree = insert(tree, key, data, 2);
                break;
            }
            case 3: {
                data = malloc(sizeof(char));
                printf("Enter a character: ");
                scanf(" %c", (char *)data);
                tree = insert(tree, key, data, 3);
                break;
            }
            case 4: {
                data = malloc(sizeof(struct newtype));
                printf("Enter data for struct (int float char): ");
                struct newtype *nt = (struct newtype *)data;
                scanf("%d %f %c", &nt->num, &nt->score, &nt->grade);
                tree = insert(tree, key, data, 4);
                break;
            }
            default:
                printf("Please enter a valid data type.\n");
                break;
            }
            break;
        }
        case 2:
            inorder(tree);
            break;
        case 3:
            preorder(tree);
            break;
        case 4:
            postorder(tree);
            break;
        case 5:
            return 0;
        default:
            printf("Please enter a correct choice\n");
            break;
        }
    }
}
