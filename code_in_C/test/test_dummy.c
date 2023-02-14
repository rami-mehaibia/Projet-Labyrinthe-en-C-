#include <stdio.h>
#include <stdlib.h>
#include "../unity/src/unity.h"
#include "../src/hello.h"
#include "../src/structenum.h"
#include "../src/begin.h"
#include "../src/structenum.h"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
void setUp(void) {}
void tearDown(void) {}
void test_programVersion_should_returnGoodVersion(void)
{
    /* Given */

    /* When */
    char* version = PrintHello();

    /* Then */
    TEST_ASSERT_EQUAL_STRING("Hello from anoher universe !\n", version);
}
//........

//........
void test_player_list(void){
	int test=askNumber();
	TEST_ASSERT_LESS_OR_EQUAL_INT(4, test);
	TEST_ASSERT_GREATER_OR_EQUAL_INT(2, test);
	Player *players=createtable(test);
	players=askName(players, test);
  PrintfPlayerList(players,test);
	TEST_ASSERT_EQUAL_STRING("Rami", players[0].Name);
	
	TEST_ASSERT_EQUAL_STRING("Marc", players[1].Name);
	
	}
//........

int main(){
	UNITY_BEGIN();
	RUN_TEST(test_programVersion_should_returnGoodVersion);
	
	RUN_TEST(test_player_list);
	return UNITY_END();
}