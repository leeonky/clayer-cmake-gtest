#include "gtest/gtest.h"

extern "C" {
#include <fcntl.h>
#include <semaphore.h>
#include <stdarg.h>
#include "fff.h"
#include "../sysport.h"

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC_VARARG(sem_t *, __wrap_sem_open, const char *, int, ...);
FAKE_VALUE_FUNC4(sem_t *, sem_open_4_args, const char *, int, int, int);
FAKE_VALUE_FUNC2(sem_t *, sem_open_2_args, const char *, int);
FAKE_VALUE_FUNC1(int, __wrap_sem_unlink, const char *);

}

sem_t *sem_open_4_args_delegator(const char *name, int flag, va_list ap){
    int value3 = va_arg(ap, int);
    int value4 = va_arg(ap, int);
    return sem_open_4_args(name, flag, value3, value4);
}

sem_t *sem_open_2_args_delegator(const char *name, int flag, va_list ap){
    return sem_open_2_args(name, flag);
}

class sem_new_with_id_test : public testing::Test {
    void SetUp() {
        RESET_FAKE(__wrap_sem_open);
        RESET_FAKE(sem_open_4_args);
        __wrap_sem_open_fake.custom_fake = sem_open_4_args_delegator;
    }
};

class sem_load_with_id_test : public testing::Test {
    void SetUp() {
        RESET_FAKE(__wrap_sem_open);
        RESET_FAKE(sem_open_2_args);
        __wrap_sem_open_fake.custom_fake = sem_open_2_args_delegator;
    }
};

class sem_unlink_with_id_test : public testing::Test {
    void SetUp() {
        RESET_FAKE(__wrap_sem_unlink);
    }
};

TEST_F(sem_new_with_id_test, should_invoke_sem_open_with_correct_args) {
    sem_t result_sem;
    sem_open_4_args_fake.return_val = &result_sem;

    sem_t *result = sem_new_with_id(100, 200);

    ASSERT_EQ(1, sem_open_4_args_fake.call_count);
    ASSERT_STREQ("100", sem_open_4_args_fake.arg0_val);
    ASSERT_EQ(O_CREAT|O_EXCL, sem_open_4_args_fake.arg1_val);
    ASSERT_EQ(0644, sem_open_4_args_fake.arg2_val);
    ASSERT_EQ(200, sem_open_4_args_fake.arg3_val);
    ASSERT_EQ(result, sem_open_4_args_fake.return_val);
}

TEST_F(sem_load_with_id_test, should_invoke_sem_open_with_correct_args) {
    sem_t result_sem;
    sem_open_2_args_fake.return_val = &result_sem;

    sem_t *result = sem_load_with_id(100);

    ASSERT_EQ(1, sem_open_2_args_fake.call_count);
    ASSERT_STREQ("100", sem_open_2_args_fake.arg0_val);
    ASSERT_EQ(0, sem_open_2_args_fake.arg1_val);
    ASSERT_EQ(result, sem_open_2_args_fake.return_val);
}

TEST_F(sem_unlink_with_id_test, should_invoke_sem_unlink_with_correct_args) {
    __wrap_sem_unlink_fake.return_val = 1;

    int result = sem_unlink_with_id(100);

    ASSERT_EQ(1, __wrap_sem_unlink_fake.call_count);
    ASSERT_STREQ("100", __wrap_sem_unlink_fake.arg0_val);
    ASSERT_EQ(result, 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
