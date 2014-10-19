#include <check.h>
#include "../src/confuse.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void suppress_errors(cfg_t *cfg, const char *fmt, va_list ap);

static cfg_t *cfg = 0;
static int func_alias_called = 0;

int func_alias(cfg_t *cfg, cfg_opt_t *opt, int argc, const char **argv)
{
    func_alias_called = 1;

    fail_unless(cfg != 0, 0);
    fail_unless(opt != 0, 0);
    fail_unless(strcmp(opt->name, "alias") == 0, 0);
    fail_unless(opt->type == CFGT_FUNC, 0);
    fail_unless(argv != 0, 0);
    fail_unless(strcmp(argv[0], "ll") == 0, 0);
    fail_unless(strcmp(argv[1], "ls -l") == 0, 0);

    if(argc != 2)
        return -1;

    return 0;
}

void func_setup(void)
{
    cfg_opt_t opts[] = 
    {
        CFG_FUNC("alias", func_alias),
        CFG_END()
    };

    cfg = cfg_init(opts, 0);
    cfg_set_error_function(cfg, suppress_errors);
}

void func_teardown(void)
{
    cfg_free(cfg);
}

START_TEST(func_test)
{
    char *buf;

    func_alias_called = 0;
    buf = "alias(ll, 'ls -l')";
    fail_unless(cfg_parse_buf(cfg, buf) == CFG_SUCCESS, 0);
    fail_unless(func_alias_called == 1, "alias() function not called");

    func_alias_called = 0;
    buf = "alias(ll, 'ls -l', 2)";
    fail_unless(cfg_parse_buf(cfg, buf) == CFG_PARSE_ERROR, 0);
    fail_unless(func_alias_called == 1, "alias() function not called");

    buf = "unalias(ll, 'ls -l')";
    fail_unless(cfg_parse_buf(cfg, buf) == CFG_PARSE_ERROR, 0);
}
END_TEST

Suite *func_suite(void) 
{ 
    Suite *s = suite_create("functions"); 

    TCase *tc_func = tcase_create("functions");
    suite_add_tcase(s, tc_func);
    tcase_add_checked_fixture(tc_func, func_setup, func_teardown);
    tcase_add_test(tc_func, func_test); 

    return s; 
}

