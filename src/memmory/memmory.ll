define i32 @main(i32 %argc, i8** %argv) {
    %is_valid_args = icmp eq i32 %argc, 2
    br i1 %is_valid_args, label %exit_success, label %invalid_args

exit_success:
    ret i32 0

invalid_args:
    %str = getelementptr [75 x i8], [75 x i8]* @err_invalid_args_msg, i32 0, i32 0
    call i32 @puts(i8* %str) nounwind
    br label %exit_error

exit_error:
    ret i32 1
}

@err_invalid_args_msg = private unnamed_addr constant [75 x i8] c"ERROR: Incorrect number of arguments.\0AUSAGE: [program] [size in kilobytes]\00"
declare i32 @puts(i8*) nounwind
