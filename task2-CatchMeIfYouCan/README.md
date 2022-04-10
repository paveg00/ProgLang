Tests output:
```|------------------Test_easy_test------------------|
TRY
Do smthing before throw
THROW
Clear stack CATCH
CATCH
Do smthing on catch
|------------------TestEnd------------------|
|------------------Test_easy_test_destructor------------------|
TRY
Construct A
Do smthing before throw
THROW
Clear stack CATCH
Destruct A
CATCH
Do smthing on catch
|------------------TestEnd------------------|
|------------------Test_long_jump_exception------------------|
TRY
Do smthing before throw
TRY
Do smthing before throw in throwable_func
Construct A
Construct B
THROW
Clear stack CATCH
Destruct B
Destruct A
CATCH
Clear stack CATCH
CATCH
Do smthing on catch
|------------------TestEnd------------------|
|------------------Test_not_caught_exception------------------|
TRY
Construct A
Do smthing before throw
THROW
Clear stack CATCH
Destruct A
CATCH
CATCH failed - exit(1)

Process finished with exit code 1
```
