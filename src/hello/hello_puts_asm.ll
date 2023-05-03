; Definition of the main function
define i32 @main() {
  ; Load the "Hello, world!" string into memory
  %hello_str = alloca [14 x i8], align 1
  store [14 x i8] c"Hello, world!\00", [14 x i8]* %hello_str, align 1
  
  ; Call the puts function to display the string on the screen
  %hello_str_cast = bitcast [14 x i8]* %hello_str to i8*
  %puts_func = tail call i32 @puts(i8* %hello_str_cast) nounwind
  ret i32 0
}

; Definition of the puts function from the C standard library
declare i32 @puts(i8*) nounwind
