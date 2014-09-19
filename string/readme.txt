string is anything enclosed in double quotation marks, and terminating by '\0' automatically by compiler.

If wanna use quotation in string: \"xxxx\"

char *p="strings";
the content cannot be changed, cause compiler choose to repsent all identical string with a single copy in memory.
so p[1]=m is not allowed.

but p[]="strings"; p[1]=m is allowed cause array gets a copy of the original string!

