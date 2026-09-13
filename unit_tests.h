/* unit_tests.h
 * Gerp project
 * Written by: Jerry Qiao (jqiao04)
 * Date started Jul 26 2026
 * 
 * Purpose: to test general functionality and edge cases
 * of all the components of gerp.
*/



#include "processing.h"
#include "Table.h"
#include <string>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>


using namespace std;


// TESTING GERP -> these run best in bash so the cout and cerr can be 
// recorded

// compile
void compile(){
    // unit test is sometimes known to fail things because
    // it doesnt compile gerp
    // probably something wrong with my makefile
    system("touch main.cpp");
    system("make");
}



// try running it with 0 argc
void wrongArgc0(){
    int myExit = system("./gerp > cout.me 2> cerr.me");
    int demoExit = system("./the_gerp > cout.demo 2> cerr.demo");

    assert(demoExit != 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
}

// try running it with 1 argc
void wrongArgc1(){
    int myExit = system("./gerp hi > cout.me 2> cerr.me");
    int demoExit = system("./the_gerp hi > cout.demo 2> cerr.demo");

    assert(demoExit != 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
}

// try running it with too many argc
void wrongArgcTooMany(){
    int myExit = system("./gerp l l l > cout.me 2> cerr.me");
    int demoExit = system("./the_gerp l l l > cout.demo 2> cerr.demo");

    assert(demoExit != 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
}

// give it a directory that does not exist
void dirDoesntExist(){
    // checkfile 1st, checkdir 2nd
    system ("> THIS_SHOULDNT_EXIST.in");
    string dir = "THIS_SHOULDNT_EXIST";
    string inFile = "THIS_SHOULDNT_EXIST.in";
    string myString = "./gerp " + dir + " out.me < " + inFile +
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < " + inFile
    + " > cout.demo 2> cerr.demo";

    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit != 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    assert(system("diff out.me out.demo") == 0);
}

// eof cin file test
void cinEOF(){
    system ("rm -rf dir1 && mkdir dir1");
    system ("> nothingInHere.in");
    string dir = "dir1";
    string inFile = "nothingInHere.in";
    string myString = "./gerp " + dir + " out.me < " + inFile +
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < " + inFile
    + " > cout.demo 2> cerr.demo";

    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    // outfile need to exist if gerp sucessfully entered query phase
    assert(system("diff out.me out.demo") == 0);
}

// quit test with q
void quitWithQ(){
    system ("rm -rf dir1 && mkdir dir1");
    system("echo \""
        "@q"
    "\" > test.in");

    string dir = "dir1";

    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    assert(system("diff out.me out.demo") == 0);
}

// quit with q, with whitespace in front of the @q
void quitWithQ1(){
    // this also test if my gerp can handle whitespaces
    // in its cin.
    system ("rm -rf dir1 && mkdir dir1");
    system("echo \""
        "                       @q"
    "\" > test.in");

    string dir = "dir1";

    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    assert(system("diff out.me out.demo") == 0);
}

// quit with q, with whitespace in back of the @q
void quitWithQ2(){
    system ("rm -rf dir1 && mkdir dir1");
    system("echo \""
        "@q             "
    "\" > test.in");

    string dir = "dir1";

    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    assert(system("diff out.me out.demo") == 0);
}

// quit with q, with whitespace in front and back of the @q
void quitWithQ3(){
    system ("rm -rf dir1 && mkdir dir1");
    system("echo \""
        "                @q             "
    "\" > test.in");

    string dir = "dir1";

    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    assert(system("diff out.me out.demo") == 0);
}

// quit with @quit, with whitespace in front of the @q
void quitWithQuit(){
    system ("rm -rf dir1 && mkdir dir1");
    system("echo \""
        "                       @q"
    "\" > test.in");

    string dir = "dir1";

    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    assert(system("diff out.me out.demo") == 0);
}

// @f to a file that dont exist yet
void changeFileThatDontExist(){
    system ("rm -rf dir1 && mkdir dir1");
    system("echo \""
        "@f out1.me"
    "\" > test1.in");
    system("echo \""
        "@f out2.demo"
    "\" > test2.in");

    string dir = "dir1";
    string myString = "./gerp " + dir + " out.me < test1.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test2.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    assert(system("diff out.me out.demo") == 0);
    assert(system("diff out1.me out2.demo") == 0);
    system("rm test1.in");
    system("rm test2.in");
    system("rm out1.me");
    system("rm out2.demo");
}

// @f to a file that already exist, should clear them
void changeFileThatExists(){
    system ("rm -rf dir1 && mkdir dir1");
    system("echo \"@f out1.me\" > test1.in");
    system("echo \"@f out2.demo\" > test2.in");
    system("echo \"bleehhhhhhhh\" > out1.me");
    system("echo \"gluglugluglu\" > out2.demo");

    string dir = "dir1";
    string myString = "./gerp " + dir + " out.me < test1.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test2.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    assert(system("diff out.me out.demo") == 0);
    assert(system("diff out1.me out2.demo") == 0);
    system("rm test1.in");
    system("rm test2.in");
    system("rm out1.me");
    system("rm out2.demo");
}

// search for things that dont exist
void searchNotFound(){
    system ("rm -rf dir1 && mkdir dir1");
    system("echo \"peanut\" > test.in");

    string dir = "dir1";
    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    assert(system("diff out.me out.demo") == 0);
}

// search for things that dont exist @i
void searchNotFoundInsensitive(){
    system ("rm -rf dir1 && mkdir dir1");
    system("echo \""
        "@i peanut\n@insensitive CHANCLAS"
        "\" > test.in");

    string dir = "dir1/";
    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    assert(system("diff out.me out.demo") == 0);
}

// finding things basic test
void foundBasic(){
    system("echo \""
        "the\n@i chamPiOn\n"
        "\" > test.in");

    string dir = "/comp/15m1/files/proj-gerp-test-dirs/tinyData";
    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    system("sort out.me > out_sorted.me && sort out.demo > out_sorted.demo");
    assert(system("diff out_sorted.me out_sorted.demo") == 0);
}

// SLOW! sample test case, sample execution, champion query
void foundWithSampleTest(){
    string dir = "/comp/15m1/files/proj-gerp-sample-execution";
    string test = "/comp/15m1/files/"
    "proj-gerp-sample-execution/champions-query.txt";

    string myString = "./gerp " + dir + " out.me < " + test +
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < " + test
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    system("sort out.me > out_sorted.me && sort out.demo > out_sorted.demo");
    assert(system("diff out_sorted.me out_sorted.demo") == 0);

}

// sample test in, using 'hello' file
void foundWithSampleTest2(){
    string dir = "/comp/15m1/files/proj-gerp-test-dirs/tinyData";
    string test = "/comp/15m1/files/proj-gerp-test-dirs/tinyData/hello";

    string myString = "./gerp " + dir + " out.me < " + test +
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < " + test
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    system("sort out.me > out_sorted.me && sort out.demo > out_sorted.demo");
    assert(system("diff out_sorted.me out_sorted.demo") == 0);
}

// sample test in
void foundWithSampleTest3(){
    string dir = "/comp/15m1/files/proj-gerp-test-dirs/tinyData";
    string test = "/comp/15m1/files/proj-gerp-test-dirs/tinyData/test.txt";

    string myString = "./gerp " + dir + " out.me < " + test +
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < " + test
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    system("sort out.me > out_sorted.me && sort out.demo > out_sorted.demo");
    assert(system("diff out_sorted.me out_sorted.demo") == 0);
}

// sample test in: TIMES OUT IF RAN NORMALLY
void foundWithSampleTest4(){
    string dir = "/comp/15m1/files/proj-gerp-sample-execution";
    string test = "/comp/15m1/files/"
    "proj-gerp-sample-execution/long-query.txt";

    string myString = "./gerp " + dir + " out.me < " + test +
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < " + test
    + " > cout.demo 2> cerr.demo";

    // Last verified to work with try.cpp:
    // Aug 7 1700

}




// test the cleaning functions
void foundMessyString(){
    system("echo \""
        "the\n@i chamPiOn\n  $T*&^champion(())\n&^*^&\n@i *#*cHaMpIoN?\n"
        "\" > test.in");

    string dir = "/comp/15m1/files/proj-gerp-test-dirs/tinyData";
    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    system("sort out.me > out_sorted.me && sort out.demo > out_sorted.demo");
    assert(system("diff out_sorted.me out_sorted.demo") == 0);
}

// test the insensitive and cleaning funcs
void foundInsensitiveAndMessy(){
    system("echo \""
        "@the GERP GREP GreP @i GREP* @i THE @i i @i #((#)) @i (th#re) @i "
        "(This @i @i hi @i @f @i @q cheeseburger"
        "\" > test.in");

    string dir = "/comp/15m1/files/proj-gerp-test-dirs/tinyData";
    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    system("sort out.me > out_sorted.me && sort out.demo > out_sorted.demo");
    assert(system("diff out_sorted.me out_sorted.demo") == 0);
}

// write to changed file that didnt previously exist
void changeFileWriteNoExist(){
    system("echo \""
        "the\n@i chamPiOn\n  $T*&^champion(())\n"
        "@f out2.me &^*^&\n@i *#*cHaMpIoN?\n"
        "\" > test_me.in");
    system("echo \""
        "the\n@i chamPiOn\n  $T*&^champion(())\n"
        "@f out2.demo &^*^&\n@i *#*cHaMpIoN?\n"
        "\" > test_demo.in");

    string dir = "/comp/15m1/files/proj-gerp-test-dirs/tinyData";
    string myString = "./gerp " + dir + " out1.me < test_me.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out1.demo < test_demo.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    system("sort out1.me > out_sorted1.me");
    system("sort out1.demo > out_sorted1.demo");
    assert(system("diff out_sorted1.me out_sorted1.demo") == 0);
    system("sort out2.me > out_sorted2.me");
    system("sort out2.demo > out_sorted2.demo");
    assert(system("diff out_sorted2.me out_sorted2.demo") == 0);
}

// after running the func above, lets see file redirection behavior
void changeFileWritePrevExist(){
    system("echo \""
        "i wandered lonlley as a cloud over a field of folden daffodils "
        "@f out2.me &^*^&\n@i *#*cHaMpIoN?\n"
        "\" > test_me.in");
    system("echo \""
        "i wandered lonlley as a cloud over a field of folden daffodils "
        "@f out2.demo &^*^&\n@i *#*cHaMpIoN?\n"
        "\" > test_demo.in");

    string dir = "/comp/15m1/files/proj-gerp-test-dirs/tinyData";
    string myString = "./gerp " + dir + " out1.me < test_me.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out1.demo < test_demo.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    system("sort out1.me > out_sorted1.me");
    system("sort out1.demo > out_sorted1.demo");
    assert(system("diff out_sorted1.me out_sorted1.demo") == 0);
    system("sort out2.me > out_sorted2.me");
    system("sort out2.demo > out_sorted2.demo");
    assert(system("diff out_sorted2.me out_sorted2.demo") == 0);
}

// tests search term abruptly ending with eof
void foundEndsWithEOF(){
    // yes technically this is the same func as sample test 3, but i think 
    // this tests a good edge case (i call it a good edge case cuz my gerp
    // previously failed this test)
    string dir = "/comp/15m1/files/proj-gerp-test-dirs/tinyData";
    string test = "/comp/15m1/files/proj-gerp-test-dirs/tinyData/test.txt";

    string myString = "./gerp " + dir + " out.me < " + test +
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < " + test
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    system("sort out.me > out_sorted.me && sort out.demo > out_sorted.demo");
    assert(system("diff out_sorted.me out_sorted.demo") == 0);
}

// I failed one of the autograder's @i edge case
// im just going to spam @i tests

// insensitive edge case testing: @i **
void foundInsensitiveEdge1(){
    // my old Gerp 8.4.2020 failed this test
    // current gerp passes
    system("echo \""
        "@i **"
        "\" > test.in");

    string dir = "/comp/15m1/files/proj-gerp-test-dirs/smallGutenberg";
    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    system("sort out.me > out_sorted.me && sort out.demo > out_sorted.demo");
    assert(system("diff out_sorted.me out_sorted.demo") == 0);
}

// insensitive edge case testing @i *222*
void foundInsensitiveEdge2(){
    system("echo \""
        "@i *222*"
        "\" > test.in");

    string dir = "/comp/15m1/files/proj-gerp-test-dirs/smallGutenberg";
    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    system("sort out.me > out_sorted.me && sort out.demo > out_sorted.demo");
    assert(system("diff out_sorted.me out_sorted.demo") == 0);
}

// insensitive edge case testing @i \n
void foundInsensitiveEdge3(){
    system("echo \""
        "@i" " \\n"
        "\" > test.in");

    string dir = "/comp/15m1/files/proj-gerp-test-dirs/smallGutenberg";
    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    system("sort out.me > out_sorted.me && sort out.demo > out_sorted.demo");
    assert(system("diff out_sorted.me out_sorted.demo") == 0);
}

// insensitive edge case testing: a bunch of weird ascii
void foundInsensitiveEdge4(){
    system("echo \""
        " @i \\ @i \\\\ \\ @i \\' @i \\r @i \\t @i \\b @i \\f @i \\v @i \0"
        "@i \\n"
        "\" > test.in");

    string dir = "/comp/15m1/files/proj-gerp-test-dirs/smallGutenberg";
    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    system("sort out.me > out_sorted.me && sort out.demo > out_sorted.demo");
    assert(system("diff out_sorted.me out_sorted.demo") == 0);
}

// insensitive edge case testing, throw poop at wall
void foundInsensitiveEdge5(){
    // this function times out if ran with the diff commands
    // Last verification: Aug 7 1058 
    // Ran with try.cpp
    // Results: passed
    system("echo \""
        "@i Apple @i APPLE @i apple @i ApPlE @i A @i a @i I @i i @i café"
        " @i CAFÉ @i Straße @i STRASSE @i Σ @i σ @i ς "
        "@i camelCase @i CAMELCASE "
        "@i AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "\" > test.in");

    string dir = "/comp/15m1/files/proj-gerp-test-dirs/smallGutenberg";
    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
}


// insensitive edge case testing: punctuation only
void foundInsensitiveEdge6(){
    // seemed like my 8.4.2020 gerp can't handle search queries of 
    // only punctionation and things of that nature
    // Timed out
    // verified that it passed on try.cpp
    // 8.7 1147
    system("echo \""
        "@i * * @i ""\"""t *** ? @i ???"
        "\" > test.in");

    string dir = "/comp/15m1/files/proj-gerp-test-dirs/smallGutenberg";
    string myString = "./gerp " + dir + " out.me < test.in "
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < test.in "
    + " > cout.demo 2> cerr.demo";
}


//////////////////////////////////////////////////////////////////////

/*
 * name:    cleanUp
 * purpose: delete all the files generated from data test
 * input:   N/A
 * returns: N/A
 * effects: deletes all the files generalted from data testing
 * note:    THIS IS A HELPER FUNCTION AND IS NOT 
 *          DESIGNED TO TEST ANYTHING
 */
void cleanUp(){
    system("rm -f cout.me");
    system("rm -f cerr.me");
    system("rm -f out.me");
    system("rm -f out1.me");
    system("rm -f out2.me");
    system("rm -f out_sorted.me");
    system("rm -f out_sorted1.me");
    system("rm -f out_sorted2.me");

    system("rm -f cout.demo");
    system("rm -f cerr.demo");
    system("rm -f out.demo");
    system("rm -f out1.demo");
    system("rm -f out2.demo");
    system("rm -f out_sorted.demo");
    system("rm -f out_sorted1.demo");
    system("rm -f out_sorted2.demo");

    system("rm -f test.in");
    system("rm -f test_me.in");
    system("rm -f test_demo.in");

    system("rm -f nothingInHere.in");
    system("rm -rf dir1");
    system("rm -f THIS_SHOULDNT_EXIST.in");
    system("make clean");
}

////////////////////////////////////////////////



// TESTING TABLE.H WITH

// constructor sanity test
void tableBasic(){
    Table<char, int> tester;
}

// size test
void tableSizeOnAFreshTable(){
    Table<char, int> tester;
    assert(tester.size() == 0);
}

// insert 1 item
void tableInsert1(){
    Table<char, int> tester;
    tester.insert('a', 2);
    assert(tester.size() == 1);
}

// insert same key and map item twice
void tableInsertSameKeyAndMapTwice(){
    Table<char, int> tester;
    tester.insert('a', 2);
    tester.insert('a', 2);
    assert(tester.size() == 1);
}

// insert same key and diff map item twice
void tableInsertSameKeyTwice(){
    Table<char, int> tester;
    tester.insert('a', 2);
    tester.insert('a', 3);
    assert (tester.size() == 1);
}

// insert some elements with different keys, expand should NOT run
void tableInsertDiffKeys(){
    // I am going to guess these insertions wont collide,
    // but if they do, and all is well, then i know my anti collider works
    Table<char, int> tester;
    tester.insert('a', 2);
    tester.insert('b', 3);
    tester.insert('c', 0);
    assert (tester.size() == 3);
}

// insert enough keys that expand should run
void tableExpand(){
    // assumes the initial capacity is 10
    // true as of 8.7
    Table<char, int> tester;
    tester.insert('a', 2);
    tester.insert('b', 3);
    tester.insert('c', 0);
    tester.insert('g', 3);
    tester.insert('0', 0);
    tester.insert(';', 3);
    tester.insert('4', 0);
    tester.insert('m', 0);
    tester.insert('n', 3);
    tester.insert('6', 0);
    tester.insert('v', 3);
    tester.insert('d', 0);
    assert (tester.size() == 12);
}

// insert a ton of things into a table, expand should 100% run
void tableExpandTortureTest(){
    // insert ascii table from 33 '!' to 125 '}'
    Table<char, int> tester;
    // this should insert about 126 - 33 = 93 elements
    for (int i = 33; i < 126; i++){
        tester.insert(i, 5);
    }
    assert(tester.size() == 93);
}

// try to find an key that does not exist
void tableFindEmpty(){
    Table<char, int> tester;
    set<int> mappedValue = tester.find('c');
    assert(mappedValue.empty());
}

// find 1 item
void tableFindOneThing(){ 
    // "why not try looking for it in spotify or youtube music?"
    Table<char, int> tester;
    tester.insert('c', 0);
    set<int> lineNum = tester.find('c');
    assert(lineNum.size() == 1);
    // learned from G4G
    // does 0 exist in lineNum?
    assert(lineNum.find(0) != lineNum.end()); 
}

// find 1 item by inserting the same thing twice
void findOneThingWithDupe(){ 
    Table<char, int> tester;
    tester.insert('c', 0);
    tester.insert('c', 0);
    set<int> lineNum = tester.find('c');
    assert(lineNum.size() == 1);
    assert(lineNum.find(0) != lineNum.end());
}

// find same key and diff map item
void tableFindSameKeyDiffMap(){
    Table<char, int> tester;
    tester.insert('a', 2);
    tester.insert('a', 3);
    set<int> lineNum = tester.find('a');
    assert(lineNum.size() == 2);
    assert(lineNum.find(2) != lineNum.end());
    assert(lineNum.find(3) != lineNum.end());
}

// find diff keys and diff map item
void tableFindDiffKeys(){
    Table<char, int> tester;
    tester.insert('a', 2);
    tester.insert('b', 3);

    set<int> lineNum = tester.find('a');
    assert(lineNum.size() == 1);
    assert(lineNum.find(2) != lineNum.end());

    lineNum = tester.find('b');
    assert(lineNum.size() == 1);
    assert(lineNum.find(3) != lineNum.end());
}

// find a lot of keys -> also a torture tesst
void tableFindAfterExpand(){
    Table<char, int> tester;
    set<int> lineNum;
    // this should insert and find about 126 - 33 = 93 elements
    for (int i = 33; i < 126; i++){
        // insert i, let the map be 2 * i
        tester.insert(i, i * 2);
        lineNum = tester.find(i);
        assert(lineNum.size() == 1);
        assert(lineNum.find(i * 2) != lineNum.end());
    }
    // find after all is inserted
    for (int i = 33; i < 126; i++){
        lineNum = tester.find(i);
        assert(lineNum.size() == 1);
        assert(lineNum.find(i * 2) != lineNum.end());
    }
    assert(tester.size() == 93);
}

// the previous functions were the Table class in char
// monomorphic form then converted to a template class.
// I anticipate table will be used on string and string view
// types. So I will do some testing below dedicated to see
// how Table behaves w/ strings

// basic sanity test with strings
void tableStringBasic(){
    Table<string, size_t> tester;
    string key = "hi";

    tester.insert(key, 5);
    assert(tester.size() == 1);
    set<size_t> lineNum = tester.find(key);
    assert(lineNum.size() == 1);
    assert(lineNum.find(5) != lineNum.end());

}

// Table should discern upper/lower case strings
void tableStringCaps(){
    Table<string_view, size_t> tester;
    string key1 = "hello";
    string key2 = "hEllo";

    tester.insert(key1, 0);
    tester.insert(key2, 0);

    assert(tester.size() == 2);
}

// Table should not discern between string with same contnet
void tableStringSameContent(){
    Table<string_view, size_t> tester;
    string key1 = "hello";
    string key2 = "hello";

    tester.insert(key1, 0);
    tester.insert(key2, 0);

    assert(tester.size() == 1);
}

// can table handle empty string?
void tableEmptyString(){
    // in gerp, empty strings do not get added to table
    Table<string, size_t> tester;
    string key = "";

    tester.insert(key, 5);
    tester.insert(key, 5);
    assert(tester.size() == 1);
    set<size_t> lineNum = tester.find(key);
    assert(lineNum.size() == 1);
    assert(lineNum.find(5) != lineNum.end());
}

// Table should not discern betwen stringview of same content
void tableStringView1(){
    Table<string_view, size_t> tester;
    string key1 = "hello";
    string key2 = "hello";
    string key3 = "internet";

    string_view view1 {key1};
    string_view view2 {key2};
    string_view view3 {key3};

    tester.insert(view1, 0);
    tester.insert(view2, 9);
    tester.insert(view3, 5);

    assert(tester.size() == 2);
}

// Table should discern between upper/lowercase stringview
void tableStringViewCapsTest(){
    Table<string_view, size_t> tester;
    string key1 = "hello";
    string key2 = "hEllo";
    string key3 = "internet";

    string_view view1 {key1};
    string_view view2 {key2};
    string_view view3 {key3};

    tester.insert(view1, 0);
    tester.insert(view2, 0);
    tester.insert(view3, 0);

    assert(tester.size() == 3);
}

// Table does not like structs, it is ok with pointers to them tho
void tableUsingStructs(){
    struct LineInfo{
        string line;
        string *filePath;
        int lineNumber;
    };

    Table<string, LineInfo*> tester;
    LineInfo buffer;
    buffer.line = "hi";
    buffer.lineNumber = 3;

    tester.insert("key", &buffer);

    set<LineInfo*> map = tester.find("key");
    assert(tester.size() == 1);
    assert(map.size() == 1);
}


////////////////////////////////////

//            TESTING PROCESSING.H                        

// stripNonAlphaNum

// strip uninitialized string
void stripUnInit(){ 
    string str;

    str = stripNonAlphaNum(str);
    assert (str == "");

}

// strip empty string
void stripEmpty(){ // these tests are all gonna have fun names
    string str = "";

    str = stripNonAlphaNum(str);
    assert (str == "");
}

// strip already cleaned up string
void stripClean1(){ 
    string str = "123";
    string cleanString = stripNonAlphaNum(str);
    assert(str == cleanString);
}

// strip already cleaned up string
void stripClean2(){
    string str = "123?bc";
    string cleanString = stripNonAlphaNum(str);
    assert(str == cleanString);
}

// strip already cleaned up string
void stripClean3(){
    string str = "a@c123abc";
    string cleanString = stripNonAlphaNum(str);
    assert(str == cleanString);
}

// strip already cleaned up string
void stripClean4(){
    string str = "aBc123";
    string cleanString = stripNonAlphaNum(str);
    assert(str == cleanString);
}

// strip the front only
void stripFromFront(){
    string str = "@abc123";

    str = stripNonAlphaNum(str);
    assert (str == "abc123");
}

// strip many times from the front
void stripALotFromTheFront(){
    string str = "@@@abc123";

    str = stripNonAlphaNum(str);
    assert (str == "abc123");
}

// strip the back only
void stripFromBack(){
    string str = "abc123@";

    str = stripNonAlphaNum(str);
    assert (str == "abc123");
}

// strip many times from the back
void stripALotFromTheBack(){
    string str = "abc123!!!";

    str = stripNonAlphaNum(str);
    assert (str == "abc123");
}

// strip many times from front and back
void stripFromBothSides1(){
    string str = "abc123!!!";

    str = stripNonAlphaNum(str);
    assert (str == "abc123");
}

// strip many times from the front and the back
void stripFromBothSides2(){
    string str = "!!!";

    str = stripNonAlphaNum(str);
    assert (str == "");
}

// strip many times from the front and the back
void stripFromBothSides3(){
    string str = "!";

    str = stripNonAlphaNum(str);
    assert (str == "");
}

// strip many times from the front and the back
void stripFromBothSides4(){
    string str = "!!!yipee!!!";

    str = stripNonAlphaNum(str);
    assert (str == "yipee");
}

// strip many times from the front and the back
void stripFromBothSides5(){
    string str = "!meow!";

    str = stripNonAlphaNum(str);
    assert (str == "meow");
}




// traverseDirectory

// try it on empty dir
void travEmpty(){
    // var to track whether range_error is thrown
    bool error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    
    try {
        traverseDirectory("");
    }
    catch (const std::runtime_error &e) {
        error_thrown = true;
    }

    // out here, we make our assertions
    assert(error_thrown);
}

// try it on dir that does not exist
void travNonExistent(){
    // var to track whether range_error is thrown
    bool error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    
    try {
        traverseDirectory("THIS_DIR_SHOULD_BE_DELETED_"
                          "BECAUSE_UNIT_TEST_SAY_SO");
    }
    catch (const std::runtime_error &e) {
        error_thrown = true;
    }

    // out here, we make our assertions
    assert(error_thrown);
}

// try it on a dir that has nothing in it
void travNothingInDir(){
    system("rm -r dir1");
    system("mkdir dir1");
    
    // learned from the internet
    stringstream buffer;
    streambuf* old_buffer = cout.rdbuf(buffer.rdbuf());
    traverseDirectory("dir1");
    string captured_text = buffer.str();

    assert (captured_text == "");
    cout.rdbuf(old_buffer);
}

// try it on a dir that has 1 file it
void trav1File(){
    system("rm -r dir1 && mkdir dir1 && cd dir1 && touch file1.useless "
           "&& cd ..");
    
    // learned from the internet
    stringstream buffer;
    streambuf* old_buffer = cout.rdbuf(buffer.rdbuf());
    traverseDirectory("dir1");
    string captured_text = buffer.str();
    cout.rdbuf(old_buffer);

    assert (captured_text == "dir1/file1.useless\n");
}

// try it on a dir that has 1 file it. The input has a slash at the end
void trav1FileWithSlashAtEnd(){
    system("rm -r dir1 && mkdir dir1 && cd dir1 && touch file1.useless "
           "&& cd ..");
    
    // learned from the internet
    stringstream buffer;
    streambuf* old_buffer = cout.rdbuf(buffer.rdbuf());
    traverseDirectory("dir1/"); // <- note the extra slash
    string captured_text = buffer.str();
    cout.rdbuf(old_buffer);

    assert (captured_text == "dir1/file1.useless\n");
}

// try it on a dir that has many file it
void travManyFile(){
    system("rm -r dir1 && mkdir dir1 && cd dir1 && touch file1.test "
           "&& touch file2.test && touch file3.test && cd ..");
    
    // learned from the internet
    stringstream buffer;
    streambuf* old_buffer = cout.rdbuf(buffer.rdbuf());
    traverseDirectory("dir1");
    string captured_text = buffer.str();
    cout.rdbuf(old_buffer);

    // if it fails, play around with the order
    assert (captured_text == "dir1/file1.test\n"
                            "dir1/file2.test\n"
                            "dir1/file3.test\n");
}

// try it on a dir a empty subdirectory
void trav1EmptySubDir(){
    system("rm -r dir1 && mkdir dir1 && cd dir1 && mkdir dir2 "
           "&& cd .. && cd ..");
    
    // learned from the internet
    stringstream buffer;
    streambuf* old_buffer = cout.rdbuf(buffer.rdbuf());
    traverseDirectory("dir1/");
    string captured_text = buffer.str();
    cout.rdbuf(old_buffer);

    // if it fails, play around with the order
    assert (captured_text == "");
}

// try it on a dir a empty subdirectory
void trav1EmptySubDirWithAFile(){
    system("rm -r dir1 && mkdir dir1 && cd dir1 && mkdir dir2 "
           "&& cd dir2 && touch file1.test && cd ../..");
    
    // learned from the internet
    stringstream buffer;
    streambuf* old_buffer = cout.rdbuf(buffer.rdbuf());
    traverseDirectory("dir1");
    string captured_text = buffer.str();
    cout.rdbuf(old_buffer);

    // if it fails, play around with the order
    assert (captured_text == "dir1/dir2/file1.test\n");
}

// dir with a file and a subdir with a file in it
void travFullDirAndFullSubDir(){
    system("rm -r dir1 && mkdir dir1 && cd dir1 && mkdir dir2 "
           "&& touch file2.test && cd dir2 && touch file1.test && cd ../..");
    
    // learned from the internet
    stringstream buffer;
    streambuf* old_buffer = cout.rdbuf(buffer.rdbuf());
    traverseDirectory("dir1");
    string captured_text = buffer.str();
    cout.rdbuf(old_buffer);

    // if it fails, play around with the order
    assert (captured_text == "dir1/file2.test\n"
        "dir1/dir2/file1.test\n");
}

// triple nested file
void travTripleNestedSubDir(){
    system("rm -r dir1 && mkdir dir1 && cd dir1 && mkdir dir2 "
           "&& cd dir2 && mkdir dir3 && cd dir3 && touch file1.test");
    
    // learned from the internet
    stringstream buffer;
    streambuf* old_buffer = cout.rdbuf(buffer.rdbuf());
    traverseDirectory("dir1");
    string captured_text = buffer.str();
    cout.rdbuf(old_buffer);

    // if it fails, play around with the order
    assert (captured_text == "dir1/dir2/dir3/file1.test\n");
}








