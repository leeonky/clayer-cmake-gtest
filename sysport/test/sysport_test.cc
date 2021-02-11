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

}

sem_t *sem_open_4_args_delegator(const char *name, int flag, va_list ap){
    int value3 = va_arg(ap, int);
    int value4 = va_arg(ap, int);
    return sem_open_4_args(name, flag, value3, value4);
}

TEST(sem_new_with_id, should_invoke_sem_open_with_id_and_value) {
    sem_t result_sem;
    RESET_FAKE(__wrap_sem_open);
    RESET_FAKE(sem_open_4_args);
    __wrap_sem_open_fake.custom_fake = sem_open_4_args_delegator;
    sem_open_4_args_fake.return_val = &result_sem;

    sem_new_with_id(100, 200);

    ASSERT_EQ(1, sem_open_4_args_fake.call_count);

    ASSERT_STREQ("100", sem_open_4_args_fake.arg0_val);
    ASSERT_EQ(O_CREAT|O_EXCL, sem_open_4_args_fake.arg1_val);
    ASSERT_EQ(0644, sem_open_4_args_fake.arg2_val);
    ASSERT_EQ(200, sem_open_4_args_fake.arg3_val);
    ASSERT_EQ(&result_sem, sem_open_4_args_fake.return_val);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
