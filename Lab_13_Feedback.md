### Feedback for Lab 13

Run on April 30, 21:25:38 PM.

+ :heavy_check_mark:  Run git ls-remote to check for existence of specific branch- Branch devel found

+ :heavy_check_mark:  Checkout devel branch.




#### Necessary Files and Structure

+ :heavy_check_mark:  Check that directory "project" exists.

+ :heavy_check_mark:  Check that directory "project/bin" exists.

+ :heavy_check_mark:  Check that directory "project/docs" exists.

+ :heavy_check_mark:  Check that directory "project/src" exists.

+ :heavy_check_mark:  Check that directory "project/tests" exists.

+ :heavy_check_mark:  Check that directory "project/web" exists.

+ :heavy_check_mark:  Check that file "project/Makefile" exists.

---


#### Compile Simulation and Tests

+ :heavy_check_mark:  Change into directory "project".

+ :heavy_check_mark:  Copy directory "Files for correct version".



+ :heavy_check_mark:  Check that make  compiles.



+ :x:  Check that make test compiles.

    Make compile fails with errors:.
<pre>cd tests; make
make[1]: Entering directory '/project/grades/Spring-2021/csci3081/student-repos/Lab_13_Feedback/repo-iter3-01-22/project/tests'
mkdir -p /project/grades/Spring-2021/csci3081/student-repos/Lab_13_Feedback/repo-iter3-01-22-build/test
/soft/gcc/7.1.0/Linux_x86_64/bin/g++ -std=c++11 -fPIC  -Wl,-rpath,/project/grades/Spring-2021/csci3081/student-repos/Lab_13_Feedback/repo-iter3-01-22-build/lib -I/project/grades/Spring-2021/csci3081/dependencies/include -I../src -I../include -I. -I.. -L/project/grades/Spring-2021/csci3081/dependencies/lib -L/project/grades/Spring-2021/csci3081/student-repos/Lab_13_Feedback/repo-iter3-01-22-build/lib *.cc -lgtest_main -lgtest -lgmock -pthread -lcsci3081proj -lEntityProject -lCppWebServer -lwebsockets -lssl -lcrypto -lz -o /project/grades/Spring-2021/csci3081/student-repos/Lab_13_Feedback/repo-iter3-01-22-build/test/csci3081tests
robot_test.cc:9:10: fatal error: Robot.h: No such file or directory
 #include "Robot.h"
          ^~~~~~~~~
compilation terminated.
make[1]: *** [Makefile:16: /project/grades/Spring-2021/csci3081/student-repos/Lab_13_Feedback/repo-iter3-01-22-build/test/csci3081tests] Error 1
make[1]: Leaving directory '/project/grades/Spring-2021/csci3081/student-repos/Lab_13_Feedback/repo-iter3-01-22/project/tests'
make: *** [Makefile:68: test] Error 2
</pre>



+ :leftwards_arrow_with_hook:  Dynamic Check that file exists. (Test not run because of an earlier failing test)

+ :leftwards_arrow_with_hook:  Dynamic Check that file exists. (Test not run because of an earlier failing test)

---

+ :heavy_check_mark:  Check that make clean compiles.



+ :heavy_check_mark:  Change into directory "..".


#### Checkout to branch

+ :heavy_check_mark:  Run git ls-remote to check for existence of specific branch- Branch master found

+ :heavy_check_mark:  Checkout master branch.




#### Necessary Files and Structure

+ :heavy_check_mark:  Check that directory "project" exists.

+ :heavy_check_mark:  Check that directory "project/bin" exists.

+ :heavy_check_mark:  Check that directory "project/docs" exists.

+ :heavy_check_mark:  Check that directory "project/src" exists.

+ :heavy_check_mark:  Check that directory "project/tests" exists.

+ :heavy_check_mark:  Check that directory "project/web" exists.

+ :heavy_check_mark:  Check that file "project/Makefile" exists.

---


#### Compile Simulation and Tests

+ :heavy_check_mark:  Change into directory "project".

+ :heavy_check_mark:  Copy directory "Files for correct version".



+ :heavy_check_mark:  Check that make  compiles.



+ :x:  Check that make test compiles.

    Make compile fails with errors:.
<pre>cd tests; make
make[1]: Entering directory '/project/grades/Spring-2021/csci3081/student-repos/Lab_13_Feedback/repo-iter3-01-22/project/tests'
mkdir -p /project/grades/Spring-2021/csci3081/student-repos/Lab_13_Feedback/repo-iter3-01-22-build/test
/soft/gcc/7.1.0/Linux_x86_64/bin/g++ -std=c++11 -fPIC  -Wl,-rpath,/project/grades/Spring-2021/csci3081/student-repos/Lab_13_Feedback/repo-iter3-01-22-build/lib -I/project/grades/Spring-2021/csci3081/dependencies/include -I../src -I../include -I. -I.. -L/project/grades/Spring-2021/csci3081/dependencies/lib -L/project/grades/Spring-2021/csci3081/student-repos/Lab_13_Feedback/repo-iter3-01-22-build/lib *.cc -lgtest_main -lgtest -lgmock -pthread -lcsci3081proj -lEntityProject -lCppWebServer -lwebsockets -lssl -lcrypto -lz -o /project/grades/Spring-2021/csci3081/student-repos/Lab_13_Feedback/repo-iter3-01-22-build/test/csci3081tests
robot_test.cc:9:10: fatal error: Robot.h: No such file or directory
 #include "Robot.h"
          ^~~~~~~~~
compilation terminated.
make[1]: *** [Makefile:16: /project/grades/Spring-2021/csci3081/student-repos/Lab_13_Feedback/repo-iter3-01-22-build/test/csci3081tests] Error 1
make[1]: Leaving directory '/project/grades/Spring-2021/csci3081/student-repos/Lab_13_Feedback/repo-iter3-01-22/project/tests'
make: *** [Makefile:68: test] Error 2
</pre>



+ :leftwards_arrow_with_hook:  Dynamic Check that file exists. (Test not run because of an earlier failing test)

+ :leftwards_arrow_with_hook:  Dynamic Check that file exists. (Test not run because of an earlier failing test)

---

+ :heavy_check_mark:  Check that make clean compiles.



---

---

