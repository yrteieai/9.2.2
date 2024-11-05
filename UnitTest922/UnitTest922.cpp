#include "pch.h"
#include "CppUnitTest.h"
#include "../9.2.2/9.2.2.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest922
{
	TEST_CLASS(UnitTest922)
	{
	public:

		TEST_METHOD(TestSetErrorMessage_UniqueCodes)
		{
			error_count = 0;

			SET_ERROR(404, "File %s %s", "not", "found");
			Assert::AreEqual(1, error_count);
			Assert::AreEqual(404, error_list[0].code);
			Assert::AreEqual("File not found", error_list[0].message);

			SET_ERROR(500, "Internal %s %s", "server", "error");
			Assert::AreEqual(2, error_count);
			Assert::AreEqual(500, error_list[1].code);
			Assert::AreEqual("Internal server error", error_list[1].message);
		}

		TEST_METHOD(TestSetErrorMessage_DuplicateCode)
		{
			error_count = 0;

			SET_ERROR(404, "File %s %s", "not", "found");
			Assert::AreEqual(1, error_count);

			SET_ERROR(404, "Duplicate error");
			Assert::AreEqual(1, error_count); 
			Assert::AreNotEqual("Duplicate error", error_list[0].message); 
		}

		
	};
}
