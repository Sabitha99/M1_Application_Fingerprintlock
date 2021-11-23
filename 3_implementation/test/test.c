#include "fun.h"
#include "unity.h"
#include "struct.h"

void test_deletefingerprint(void);
void test_searchfingerprint(void);
void test_addfingerprint(void);

/* Required by the unity test framework */
void setUp(){}
/* Required by the unity test framework */
void tearDown(){}

int main()
{
/* Initiate the Unity Test Framework */
  UNITY_BEGIN();

/* Run Test functions */
  RUN_TEST(test_deletefingerprint);
  RUN_TEST(test_searchfingerprint);
  RUN_TEST(test_addfingerprint);

  /* Close the Unity Test Framework */
  return UNITY_END();
}

void test_deletefingerprint(void)
{
    lcd.setCursor(0, 0);
   lcd.printf("Not Valid Finger");
    TEST_ASSERT_EQUAL("Deleted");
   
}

void test_searchfingerprint(void)
{
   lcd.setCursor(0, 0);
   lcd.printf("search for match");
    TEST_ASSERT_EQUAL("Matched");
   
}

void test_addfingerprints(void)
{
   lcd.setCursor(0, 0);
   lcd.printf("Not Valid Finger");
   lcd.setCursor(0, 0);
   lcd.printf("search for match");
   

   TEST_ASSERT_EQUAL("Deleted");
   TEST_ASSERT_EQUAL("Matched");
   TEST_ASSERT_EQUAL("Unlocked");
   
}
