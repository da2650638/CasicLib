#include "TestMath.h"
#include "TestUtil.h"
#include "TestTrivallyDestructible.h"
#include "TestPOD.h"

#include "TMPLab/OptionalLab.h"



int main() 
{
	std::cout << std::boolalpha;

	TMPLab::_Optional_destruct_base<int> b1(TMPLab::in_place, 111);

	struct NonTrivialDestruct {
		~NonTrivialDestruct() {
			std::cout << "NonTrivialDestruct: 虽然我什么都不干，但是你必须调用我\n";
		}
	};
	TMPLab::_Optional_destruct_base< NonTrivialDestruct> b2(TMPLab::in_place);

	struct NoThrowCons {
		NoThrowCons(int i, float f) noexcept
		{
			std::cout << "我现在什么异常都不抛出\n";
		}
	};
	TMPLab::_Optional_destruct_base<NoThrowCons> b3(TMPLab::in_place, 1, 1.0f);
	std::cout << std::is_nothrow_constructible_v<NoThrowCons, int, float> << std::endl;

	return 0;
}