#include "../includes/libasm.h"

static int passed = 0, failed = 0;
#define CHECK(label, condition) do { \
    if (condition) { printf("[PASS] %s\n", label); ++passed; } \
    else { printf("[FAIL] %s (line %d)\n", label, __LINE__); ++failed; } \
} while (0)

/*Tests*/

static void test_strlen(void)
{
    printf("\n-- ft_strlen --");
    const char *cases[] = {"", "Hello", "a", "embedded systems", "Hello\nWorld!"};
    for (size_t i = 0; i < sizeof cases / sizeof cases[0]; ++i)
        CHECK("matches strlen", ft_strlen(cases[i]) == strlen(cases[i]));
}

static void test_strcpy(void)
{
    printf("\n-- ft_strcpy --\n");
    char dst[64];
    char *ret = ft_strcpy(dst, "Hello, assembly!");
    CHECK("copies string", strcmp(dst, "Hello, assembly!") == 0);
    CHECK("returns destination", ret == dst);
    memset(dst, 0x5a, sizeof dst);
    ret = ft_strcpy(dst, "");
    CHECK("copies empty string", ret == dst && dst[0] == '\0' && dst[1] == 'Z');
}

static void test_strcmp(void)
{
    printf("\n-- ft_strcmp --\n");
    const char *pairs[][2] = {
        {"", ""}, {"abc", "abc"}, {"abc", "abd"},
        {"abd", "abc"}, {"abc", "abcd"}, {"abcd", "abc"},
        {"", "x"}, {"x", ""}, {"A", "a"}
    };
    for (size_t i = 0; i < sizeof pairs / sizeof pairs[0]; ++i) {
        int a = ft_strcmp(pairs[i][0], pairs[i][1]);
        int b = strcmp(pairs[i][0], pairs[i][1]);
        CHECK("strcmp sign matches", (a > 0) == (b > 0) &&
                (a < 0) == (b < 0));
    }
    const char high[] = {(char)0xff, '\0'};
    const char low[] = {(char)0x01, '\0'};
    CHECK("unsigned byte comparison", ft_strcmp(high, low) > 0);
}

static void test_write(void) 
{
    printf("\n-- ft_write --\n");
    int fd[2];
    if (pipe(fd) != 0) { perror("pipe"); ++failed; return; }
    const char msg[] = "Hello";
    errno = 0;
    ssize_t n = ft_write(fd[1], msg, sizeof msg -1);
    char buf[16] = {0};
    ssize_t got = read(fd[0], buf, sizeof msg - 1);
    CHECK("writes expected bytes", n ==5 && got == 5 && memcmp(buf, msg, 5) == 0);
    close(fd[0]); close(fd[1]);
    errno = 0;
    n = ft_write(-1, msg, 5);
    CHECK("invalid fd returns -1", n == -1);
    CHECK("invalid fd sets EBADF", errno == EBADF);
}

static void test_read(void)
{
    printf("\n-- ft_read --\n");
    int fd[2];
    if (pipe(fd) != 0) { perror("pipe"); ++failed; return; }
    const char msg[] = "Read test";
    if (write(fd[1], msg, sizeof msg - 1) != (ssize_t)(sizeof msg - 1)) {
        perror("write setup"); ++failed; close(fd[0]); close(fd[1]); return;
    }
    close(fd[1]);
    char buf[32] = {0};
    ssize_t n = ft_read(fd[0], buf, sizeof buf);
    CHECK("reads expected bytes", n == (ssize_t)(sizeof msg - 1) &&
            memcmp(buf, msg, sizeof msg - 1) == 0);
    CHECK("EOF returns zero", ft_read(fd[0], buf, sizeof buf) == 0);
    close(fd[0]);
    errno = 0;
    n = ft_read(-1, buf, sizeof buf);
    CHECK("invalid fd returns -1", n == -1);
    CHECK("invalid fd stes EBADF", errno == EBADF);
}

static void test_strdup(void) 
{
    printf("\n-- ft_strdup --\n");
    const char *cases[] = {"", "Hello", "longer string with spaces"};
    for (size_t i = 0; i < sizeof cases / sizeof cases[0]; ++i) {
        char *copy = ft_strdup(cases[i]);
        CHECK("duplcates contents", copy && strcmp(copy, cases[i]) == 0);
        CHECK("allocates independent memory", copy && copy != cases[i]);
        free(copy);
    }
}

static void test_calloc(void)
{
    printf("\n-- ft_calloc --\n");
    const size_t n = 32;
    unsigned char *p = ft_calloc(n, sizeof *p);
    int zero = (p != NULL);
    if (p) for (size_t i = 0; i < n; ++i) if (p[i] != 0) zero = 0;
    CHECK("32 bytes initialized to zero", zero);
    if (p) { p[0] = 42; p[n - 1] = 99; }
    CHECK("allocated memory is writable", p && p[0] == 42 && p[n - 1] == 99);
    free(p);

    p = ft_calloc(1, 1);
    CHECK("one byte initialized to zero", p && p[0] == 0);
    free(p);
    
    errno = 0;
    void *q = ft_calloc(SIZE_MAX, 2);
    CHECK("multiplication overflow returns NULL", q == NULL);
    CHECK("multiplication overflow sets ENOMEM", errno == ENOMEM);
    free(q);

    errno = 0;
    q = ft_calloc(SIZE_MAX, SIZE_MAX);
    CHECK("large multiplication overflow returns NULL", q == NULL);
    CHECK("large multiplication overflow sets ENOMEM", errno == ENOMEM);
    free(q);

    q = ft_calloc(0, 10);
    printf("[INFO] zero elements: results may be NULL or freeable pointer\n");
    free(q);
    q = ft_calloc(10, 0);
    printf("[INFO] zero element size: result may be NULL or freeable pointer\n");
    free(q);

    errno = 0;
    void *ptr = ft_calloc(SIZE_MAX, 1);
    int saved_errno = errno;
    CHECK("huge allocation without multiplication overflow returs NULL", ptr == NULL);
    CHECK("malloc failure preservers ENOMEM", saved_errno == ENOMEM);
    free(ptr);
}

static void test_list_size(void)
{
    printf("\n-- ft_list_size --");
    
    t_list node3 = {(void *)"C", NULL};
    t_list node2 = {(void *)"B", &node3};
    t_list node1 = {(void *)"A", &node2};

    CHECK("empty_list", ft_list_size(NULL) == 0);
    CHECK("one node", ft_list_size(&node3) == 1);
    CHECK("three nodes", ft_list_size(&node1) == 3);
}

int main(void) 
{
    test_strlen();
    test_strcpy();
    test_strcmp();
    test_write();
    test_read();
    test_strdup();
    test_calloc();
    test_list_size();

    printf("\nResults: %d passed, %d failed\n", passed, failed);
    return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
