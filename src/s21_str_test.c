#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include <time.h>

#include "s21_string.h"
#include "s21_sprintf.h"

/*


    fail_unless(t_s21_strcpy(str, supp_str) == strcpy(str, supp_str));
    fail_unless(t_s21_strncpy(str, supp_str, 10) == strncpy(str, supp_str, 10));
    fail_unless(t_s21_strcspn(str, supp_str) == strcspn(str, supp_str));
    fail_unless(t_s21_strlen(str) == strlen(str));
    fail_unless(t_s21_strpbrk(str, supp_str) == strpbrk(str, supp_str));
    fail_unless(t_s21_strrchr(str, 'h') == strrchr(str, 'h'));
    fail_unless(t_s21_strspn(str, supp_str) == strspn(str, supp_str));
    fail_unless(t_s21_strstr(str, supp_str) == strstr(str, supp_str));
    fail_unless(t_s21_strtok(str, "\n") == strtok(str, "\n"));

*/

START_TEST(t_s21_memchr) {
    char str[1024];
    strcat(str, "Simple text.");
    fail_unless(s21_memchr(str, 'S', 30) == memchr(str, 'S', 30));
    fail_unless(s21_memchr(str, '\0', 20) == memchr(str, '\0', 20));
    fail_unless(s21_memchr(str, '\n', 15) == memchr(str, '\n', 15));
    fail_unless(s21_memchr(str, '\t', 10) == memchr(str, '\t', 10));
    fail_unless(s21_memchr(str, '7', 20) == memchr(str, '7', 20));
    fail_unless(s21_memchr(str, '4', 15) == memchr(str, '4', 15));
}
END_TEST

START_TEST(t_s21_memcmp) {
    char str[1024];
    char supp_str[256] = "text";
    strcat(str, "Simple text.");
    fail_unless(s21_memcmp(str, supp_str, 13) == memcmp(str, supp_str, 13));
    fail_unless(s21_memcmp(str, supp_str, 1) == memcmp(str, supp_str, 1));
    fail_unless(s21_memcmp(str, supp_str, 3) == memcmp(str, supp_str, 3));
    fail_unless(s21_memcmp(str, supp_str, 5) == memcmp(str, supp_str, 5));
    fail_unless(s21_memcmp(str, supp_str, 7) == memcmp(str, supp_str, 7));
    fail_unless(s21_memcmp(str, supp_str, 8) == memcmp(str, supp_str, 8));
}
END_TEST

START_TEST(t_s21_memcpy) {
    char str[1024];
    char supp_str[256] = "text";
    strcat(str, "Simple text.");
    fail_unless(s21_memcpy(str, supp_str, 10) == memcpy(str, supp_str, 10));
    fail_unless(s21_memcpy(str, supp_str, 5) == memcpy(str, supp_str, 5));
    fail_unless(s21_memcpy(str, supp_str, 0) == memcpy(str, supp_str, 0));
    fail_unless(s21_memcpy(str, supp_str, 23) == memcpy(str, supp_str, 23));
    fail_unless(s21_memcpy(str, supp_str, 45) == memcpy(str, supp_str, 45));
    fail_unless(s21_memcpy(str, supp_str, 10) == memcpy(str, supp_str, 10));
}
END_TEST

// TODO MEMMOVE
START_TEST(t_s21_memmove) {
    char str[1024];
    char supp_str[256] = "text";
    
    strcat(str, "Simple text.");
    fail_unless(((char*)s21_memmove(str, supp_str, 10) == (char*)memmove(str, supp_str, 10)));
    fail_unless(((char*)s21_memmove(str, supp_str, 0) == (char*)memmove(str, supp_str, 0)));
    fail_unless(((char*)s21_memmove(str, supp_str, 13) == (char*)memmove(str, supp_str, 13)));
    fail_unless(((char*)s21_memmove(str, supp_str, 0) == (char*)memmove(str, supp_str, 0)));
    fail_unless(((char*)s21_memmove(str, supp_str, 1) == (char*)memmove(str, supp_str, 1)));
    fail_unless(((char*)s21_memmove(str, supp_str, 7) == (char*)memmove(str, supp_str, 7)));
}
// END_TEST

START_TEST(t_s21_memset) {
    char str[1024];
    strcat(str, "Simple text.");
    fail_unless(s21_memset(str, '6', 10) == memset(str, '6', 10));
    fail_unless(s21_memset(str, '\t', 5) == memset(str, '\t', 5));
    fail_unless(s21_memset(str, '\0', 10) == memset(str, '\0', 10));
    fail_unless(s21_memset(str, 'G', 2) == memset(str, 'G', 2));
    fail_unless(s21_memset(str, 'J', 10) == memset(str, 'J', 10));
    fail_unless(s21_memset(str, '`', 10) == memset(str, '`', 10));
}
END_TEST

START_TEST(t_s21_strcat) {
    char s21_str[256];
    char str[256];
    memset(s21_str, '\0', 256);
    memset(str, '\0', 256);
    char rand_str[5];
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 4; j++) {
            rand_str[j] = (char)rand() % 125 + 2;
        }
        strcat(str, rand_str);
        s21_strcat(s21_str, rand_str);
        fail_unless(!strcmp(str, s21_str));
    }
}
END_TEST

START_TEST(t_s21_strncat) {
    char str[1024];
    char supp_str[256] = "text";
    strcat(str, "Simple text.");
    fail_unless(!strcmp(s21_strncat(str, supp_str, 15), strncat(str, supp_str, 15)));
    memset(supp_str, '\0', 256);
    strcat(supp_str, "\0");
    fail_unless(!strcmp(s21_strncat(str, supp_str, 0), strncat(str, supp_str, 0)));
    memset(supp_str, '\0', 256);
    strcat(supp_str, "\t");
    fail_unless(!strcmp(s21_strncat(str, supp_str, 20), strncat(str, supp_str, 20)));
    memset(supp_str, '\0', 256);
    strcat(supp_str, "O02RKEWLF;");
    fail_unless(!strcmp(s21_strncat(str, supp_str, 14), strncat(str, supp_str, 14)));
    memset(supp_str, '\0', 256);
    strcat(supp_str, "JI934 K3NNO3NI34 3FF 3 3 4 F3K ;");
    fail_unless(!strcmp(s21_strncat(str, supp_str, 1), strncat(str, supp_str, 1)));
    memset(supp_str, '\0', 256);
    strcat(supp_str, "__________________________\0\n");
    fail_unless(!strcmp(s21_strncat(str, supp_str, 29), strncat(str, supp_str, 29)));
}
END_TEST

START_TEST(t_s21_strchr) {
    char str[128];
    strcat(str, "Simple text.");
    fail_unless (strchr(str, ' ') == strchr(str, ' '));
    fail_unless (strchr(str, 'q') == strchr(str, 'q'));
    fail_unless (strchr(str, '%') == strchr(str, '%'));
    fail_unless (strchr(str, '?') == strchr(str, '?'));
    fail_unless (strchr(str, '\t') == strchr(str, '\t'));
    fail_unless (strchr(str, '\n') == strchr(str, '\n'));
}
END_TEST

START_TEST(t_s21_strcmp) {
    char str[1024];
    char supp_str[256] = "text";
    strcat(str, "Simple text.");
    fail_unless(s21_strcmp(str, supp_str) == strcmp(str, supp_str));
    fail_unless(s21_strcmp(str, "\0\0\0\0\0") == strcmp(str, "\0\0\0\0\0"));
    fail_unless(s21_strcmp(str, "U83HREBRH") == strcmp(str, "U83HREBRH"));
    fail_unless(s21_strcmp(str, "tex") == strcmp(str, "tex"));
    fail_unless(s21_strcmp(str, ".") == strcmp(str, "."));
    fail_unless(s21_strcmp(str, "\n") == strcmp(str, "\n"));
}
END_TEST

START_TEST(t_s21_strncmp) {
    char str[1024];
    strcat(str, "Simple text.");
    fail_unless(s21_strncmp(str, "hel", 3) == strncmp(str, "hel", 3));
    fail_unless(s21_strncmp(str, "\0\0\0\0\0", 7) == strncmp(str, "\0\0\0\0\0", 7));
    fail_unless(s21_strncmp(str, "U83HREBRH", 3) == strncmp(str, "U83HREBRH", 3));
    fail_unless(s21_strncmp(str, "tex", 3) == strncmp(str, "tex", 3));
    fail_unless(s21_strncmp(str, ".", 1) == strncmp(str, ".", 1));
    fail_unless(s21_strncmp(str, "\n", 1) == strncmp(str, "\n", 1));
}
END_TEST

START_TEST(t_s21_strcpy) {
    char str[1024];
    char s21_str[1024];
    char supp_str[256] = "text";
    strcat(str, "Simple text.");

    time_t t;
    srand((unsigned)time(&t));

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            supp_str[i] = (char)rand() % 127;
        }
        fail_unless(!strcmp(s21_strcpy(s21_str, supp_str), strcpy(str, supp_str)));
        memset(supp_str, '\0', 256);
    }
}
END_TEST

START_TEST(t_s21_strncpy) {
    char str[256];
    char s21_str[256];
    char supp_str[32] = "text";
    strcat(str, "Simple text.");

    time_t t;
    srand((unsigned)time(&t));

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            supp_str[j] = (char)rand() % 96 + 32;
        }
        int rand_value = rand() % 5 + 1;
        s21_strncpy(s21_str, supp_str, (s21_size_t)rand_value);
        strncpy(str, supp_str, (size_t)rand_value);
        memset(supp_str, '\0', 32);
        memset(s21_str, '\0', 256);
        memset(str, '\0', 256);
    }
}
END_TEST

START_TEST(t_s21_strcspn) {
    char str[1024];
    strcat(str, "Simple text.");
    fail_unless(s21_strcspn(str, "hel") == strcspn(str, "hel"));
    fail_unless(s21_strcspn(str, "qwef") == strcspn(str, "qwef"));
    fail_unless(s21_strcspn(str, "Sim") == strcspn(str, "Sim"));
    fail_unless(s21_strcspn(str, "txet elpmiS") == strcspn(str, "txet elpmiS"));
    fail_unless(s21_strcspn(str, "iqwertyuiopasdfghjklzxcvbnm") == strcspn(str, "iqwertyuiopasdfghjklzxcvbnm"));
    fail_unless(s21_strcspn(str, "sd") == strcspn(str, "sd"));

}
END_TEST

START_TEST(t_s21_strlen) {
    char supp_str[256];
    time_t t;
    srand((unsigned)time(&t));

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            supp_str[i] = (char)rand() % 127;
        }
        fail_unless(s21_strlen(supp_str) == strlen(supp_str));
        memset(supp_str, '\0', 256);
    }
}
END_TEST

START_TEST(t_s21_strpbrk) {
    char str[1024];
    char supp_str[10];
    strcat(str, "Simple text. It's a template for search a chars.");

    time_t t;
    srand((unsigned)time(&t));

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) supp_str[i] = (char)rand() % 127;
        fail_unless(s21_strpbrk(str, supp_str) == strpbrk(str, supp_str));
        memset(supp_str, '\0', 10);
    }
}
END_TEST

START_TEST(t_s21_strrchr) {
    char str[1024];
    char supp_str[10];
    strcat(str, "Simple text. It's a template for search a chars.");

    time_t t;
    srand((unsigned)time(&t));

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) supp_str[i] = (char)rand() % 127;
        char rand_value = rand() % 96 + 32;
        fail_unless(s21_strrchr(str, rand_value) == strrchr(str, rand_value));
        memset(supp_str, '\0', 10);
    }
}
END_TEST

START_TEST(t_s21_strspn) {
    char str[1024];
    char supp_str[10];
    strcat(str, "Simple text. It's a template for search a chars.");

    time_t t;
    srand((unsigned)time(&t));

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) supp_str[i] = (char)rand() % 127;
        fail_unless(s21_strspn(str, supp_str) == strspn(str, supp_str));
        memset(supp_str, '\0', 10);
    }
}
END_TEST

START_TEST(t_s21_strstr) {
    char str[512];
    char supp_str[2];
    strcat(str, "Some Flood text for testing strstr function. qwertyuioasdfghjklzxcvbnm");

    time_t t;
    srand((unsigned)time(&t));

    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 1; j++) {
            int rand_value = rand() % 127;
            if (!rand_value) rand_value++;
            supp_str[j] = (char)rand_value;
        }
        fail_unless(s21_strstr(str, supp_str) == strstr(str, supp_str));
        memset(supp_str, '\0', 2);
    }
}
END_TEST

START_TEST(t_s21_sprintf) {
    


    time_t t;
    srand((unsigned)time(&t));


    const char pattern_1[] = "new int is %d";
    const char pattern_2[] = "new string is %s";
    const char pattern_3[] = "new invisible char is %c";
    const char pattern_4[] = "new int is %d new string is %s new inv char is %c";
    const char pattern_5[] = "new special char is %c";
    



    for (int i = 0; i < 50; i++) {
        char str[512] = {0};
        char s21_str[512] = {0};
        char tmp[56] = {0};
        int n = i % 5;
        if (n == 0) {
            int rand_value = rand() % 256;
            sprintf(str, pattern_1, rand_value);
            s21_sprintf(s21_str, pattern_1, rand_value);
        }
        if (n == 1) {
            for (int j = 0; j < 54; j++) {
                tmp[j] = (char)(rand() % 26 + 97);
            }
            sprintf(str, pattern_2, tmp);
            s21_sprintf(s21_str, pattern_2, tmp);
        }
        if (n == 2) {
            char inv_char = rand() % 31 + 1;
            sprintf(str, pattern_3, inv_char);
            s21_sprintf(s21_str, pattern_3, inv_char);
        }
        if (n == 3) {
            int rand_value = rand() % 256;
            for (int j = 0; j < 54; j++) {
                tmp[j] = (char)(rand() % 26 + 97);
            }
            char inv_char = (char)rand() % 30 + 1;
            sprintf(str, pattern_4, rand_value, tmp, inv_char);
            s21_sprintf(s21_str, pattern_4, rand_value, tmp, inv_char);
        }
        if (n == 4) {
            char spec_char;
            spec_char = rand() % 20 + 1;
            printf("SPEC CHAR IS '%d'\n", spec_char);
            sprintf(str, pattern_5, spec_char);
            s21_sprintf(s21_str, pattern_5, spec_char);
        }
        printf("ITERATION IS %d\n", n);
        fail_unless(!strcmp(str, s21_str));
        resetBuffer(str, 512);
        resetBuffer(s21_str, 512);
        resetBuffer(tmp, 56);
    }

}
END_TEST



// Функция создания набора тестов.
Suite *example_suite_create(void)
{
    Suite *suite = suite_create("Example");
    // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
    TCase *tcase_core = tcase_create("Core of example");


    tcase_add_test(tcase_core, t_s21_memchr);
    tcase_add_test(tcase_core, t_s21_memcmp);
    tcase_add_test(tcase_core, t_s21_memcpy);
    tcase_add_test(tcase_core, t_s21_memmove);
    tcase_add_test(tcase_core, t_s21_memset);
    tcase_add_test(tcase_core, t_s21_strcat);
    tcase_add_test(tcase_core, t_s21_strncat);
    tcase_add_test(tcase_core, t_s21_strchr);
    tcase_add_test(tcase_core, t_s21_strcmp);
    tcase_add_test(tcase_core, t_s21_strncmp);
    tcase_add_test(tcase_core, t_s21_strcpy);
    tcase_add_test(tcase_core, t_s21_strncpy);
    tcase_add_test(tcase_core, t_s21_strcspn);
    tcase_add_test(tcase_core, t_s21_strlen);
    tcase_add_test(tcase_core, t_s21_strpbrk);
    tcase_add_test(tcase_core, t_s21_strrchr);
    tcase_add_test(tcase_core, t_s21_strspn);
    tcase_add_test(tcase_core, t_s21_strstr);
    tcase_add_test(tcase_core, t_s21_sprintf);


    suite_add_tcase(suite, tcase_core);
    

    

    return suite;
}

int main(void)
{
    Suite *suite = example_suite_create();
    SRunner *suite_runner = srunner_create(suite);
    
    srunner_run_all(suite_runner, CK_NORMAL);
    int failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
    
    if (failed_count != 0) {
        printf("ERROR: FAILED COUNT: %d\n", failed_count);
        return EXIT_FAILURE;
    } else {
        printf("INFO: ALL TESTS ARE SUCCESS\n");
    }



    return EXIT_SUCCESS;
}