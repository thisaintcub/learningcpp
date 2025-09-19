
// this file will have all the types and functions with explanations in them. 
// if i forget how to use something ill refer to this file for help.
// i guess im writing my own c++ tutorial just so i definitely understand everything and remember it better lolz
// it will be pretty simple at first, but as i learn itll become more complicated

//// cool includes to know
#include <iostream>

//// basic types:
int integer = 1;
float floating = 1.f;
double doubleVar = 1.;

//

//// constants and literals
// add const for the value to be nonchangeable
const int constant = 1;
// constant++; gives you an error.

// after c++11 they added constexpr. it shows that the value should be evaluated at the compile time rather than runtime.
// its similar to const but also can be used to functions to make them compile the value they return instead of calling them every time in runtime.
// if its impossible to return, welp, itll just call it on runtime
constexpr int thingy(int value)
{
	return value + 6969;
}

// enum is a group of named constans. you can use it as a paramater in a function
// todo: better explanaition
enum kokashk { zeleni, korichnevi };

//

//// pointers and references
// this is a pointer yaaay
int* integerPtr = &integer;

// NOTE: if you wanna declare a lot of pointers in 1 line you have to put the * before every value not after types
// ex:

int *coolptr1, *coolptr2, *coolptr3, *coolptr4;

// because pointer is in value not in the type


//

//// namespaces
// modules are cool and shi
// it makes it easier to sort your code and youd often want to put utils and stuff in a namespace
namespace Utils1 {
	bool isTrueTrue() {
		return true;
	}

	bool isFalseFalse() {
		return false;
	}
}
// and then just call it like this:
bool coolvar = Utils1::isTrueTrue();
// you can also put namespaces in namespaces to do versions in code
namespace Utils2 {
	bool isTrueTrue() {
		return true;
	}

	bool isFalseFalse() {
		return false;
	}
	
	namespace V2 {
		bool isTrueTrue() {
			// holy shit
			return false;
		}

		bool isFalseFalse() {
			return true;
		}
	}
}
// usage
bool coolvarV2 = Utils2::V2::isTrueTrue();
// also for better management of the code you can use inlines so its both a default but has its own version
namespace Utils {
	inline namespace V1 {
		bool isTrueTrue() {
			return true;
		}

		bool isFalseFalse() {
			return false;
		}
	}

	namespace V2 {
		bool isTrueTrue() {
			// holy shit
			return false;
		}

		bool isFalseFalse() {
			return true;
		}
	}
}
// so like
bool coolvar = Utils::isTrueTrue();
bool coolvar = Utils::V1::isTrueTrue();

// in namespace theres usually a lot of stuff but you can pull out just one singular thing using
using Utils::isFalseFalse;
// and when you do using it just refers to Utils::isFalseFalse() when typing out isFalseFalse()

int main()
{
	
}